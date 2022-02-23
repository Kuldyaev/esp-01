#include <DS18B20.h>             // Подключаем библиотеку для датчика Dallas DS18B20 
#include <Adafruit_BMP085.h>     // Подключаем библиотеку для датчика BMP085/BMP180
#include <AM2320_asukiaaa.h>     // Подключаем библиотеку для датчика AM2320

DS18B20 ds(2);                   // Обзываем датчик Dallas DS18B20 как ds, подключен к пину 2 
Adafruit_BMP085 bmp;             // Обзываем датчик BMP180 как bmp
AM2320_asukiaaa mySensor;        // Обзываем датчик АМ2320 как mySensor

int ledPins[6]={7,8,9,10,11,12}; // формируем массив контактов управления питанием сенсеров и светодиодом   
int a1Pin=A1;                    // контакт подключения аналогового одного емкостного датчика
int a2Pin=A2;                    // контакт подключения аналогового второго емкостного датчика

void setup() {
 for(int i=0;i<8;i++){pinMode(ledPins[i],OUTPUT);}   // настройка выводов индикации светодиодов в режим OUTPUT
 Wire.begin();         //  запускаем библиотеку Wire
 Serial.begin(9600);   // запускаем Serial
 while(!Serial);       // ждем запуск Serial 
 digitalWrite(12, LOW);
 digitalWrite(11, HIGH);   //Обеспечиваем питание на пин 11
 Serial.println("На 5 сек обеспечили питание на ESP01 блок"); 
 delay(5000); 
 digitalWrite(11, LOW);   //Отключаем питание на пин 11
  digitalWrite(9, HIGH);   //Обеспечиваем питание на пин 11
 Serial.println("На 5 сек обеспечили питание на блок ёмкостных датчиков"); 
 delay(5000); 
 digitalWrite(9, LOW);   //Отключаем питание на пин 11
 digitalWrite(10, HIGH);   //Обеспечиваем питание на пин 10
 Serial.println("Светодиод: синий"); 
 delay(1000); 
 digitalWrite(10, LOW);   //Отключаем питание на пин 10
 digitalWrite(8, HIGH);   //Обеспечиваем питание на пин 8
 Serial.println("Светодиод: зеленый"); 
 delay(1000); 
 digitalWrite(8, LOW);   //Отключаем питание на пин 8
  digitalWrite(7, HIGH);   //Обеспечиваем питание на пин 7
 Serial.println("Светодиод: красный"); 
 delay(1000); 
 digitalWrite(7, LOW);   //Отключаем питание на пин 7
 Serial.println("I2C Сканер - поиск устройств:");
 byte error, address;
 int nDevices;
 digitalWrite(12, HIGH);  //Обеспечиваем питание на пин 12  питание для датчиков
 Serial.println("Сканирую...");
   nDevices = 0;
   for(address = 8; address < 127; address++ ){
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0){
            Serial.print("I2C device found at address 0x");
            if (address<16)
                Serial.print("0");
            Serial.print(address,HEX);
            Serial.println(" !");
             nDevices++;
        }
        else if (error==4) {
            Serial.print("Unknow error at address 0x");
            if (address<16)
            Serial.print("0");
            Serial.println(address,HEX);
       } 
    }
    if (nDevices == 0)
        Serial.println("Устройств не найдено");
    else
        Serial.println("Поиcк I2c устройств завершен");
  Wire.end();
  delay(2000);
  Wire.begin();
  mySensor.setWire(&Wire);
  delay(500);
  if (mySensor.update() != 0) {
    Serial.println("Error: Cannot update sensor values.");
  } else {
    Serial.println("Данные для AM2320 температура: " + String(mySensor.temperatureC) + "C");
    Serial.println("Данные для AM2320 влажность: " + String(mySensor.humidity) + "%");
  }
 Serial.println("Показания датчика Dallas DS18B20: " + String(ds.getTempC()));
 Serial.println("Данные для фоторезистора на пине 0: " + String(analogRead(A0)));
 Serial.println("Данные для емкостного датчика на пине 1: " + String(analogRead(A1)));
 Serial.println("Данные для емкостного датчика на пине 2: " + String(analogRead(A2)));
 Wire.end();
  delay(2000);
 Wire.begin();
   if (!bmp.begin()) {
     Serial.println("Could not find a valid BMP085 sensor, check wiring!");
     while (1) {}
   } else {
    Serial.println("Данные для BMP180 температура: " + String(bmp.readTemperature()) + "C");
    Serial.println("Данные для BMP180 атм давление: " + String(bmp.readPressure()/133) + "mm ");
   } 

 delay(5000); 
 digitalWrite(12, LOW);  //Отключаем питание на пин 12   питание для датчиков
}

void loop() {
 digitalWrite(12, HIGH);  //Обеспечиваем питание на пин 12  питание для датчиков
  if (!bmp.begin()) {
     Serial.println("Could not find a valid BMP085 sensor, check wiring!");
     while (1) {}
   } else {
    Serial.println("Данные для BMP180 температура: " + String(bmp.readTemperature()) + "C");
    Serial.println("Данные для BMP180 атм давление: " + String(bmp.readPressure()/133) + "mm ");
   } 
 delay(1000); 
 digitalWrite(12, LOW);  //Отключаем питание на пин 12   питание для датчиков
 delay(59000); 
}
