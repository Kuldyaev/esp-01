#include <Wire.h>                // Подключаем библиотеку Wire
#include <DS18B20.h>             // Подключаем библиотеку для датчика Dallas DS18B20 
#include <Adafruit_BMP085.h>     // Подключаем библиотеку для датчика BMP085/BMP180

DS18B20 ds(2);                   // Обзываем датчик Dallas DS18B20 как ds, подключен к пину 2 
Adafruit_BMP085 bmp;             // Обзываем датчик BMP180 как bmp

void setup() {
 pinMode(7, OUTPUT);  //определим пин 7 как вывод
 pinMode(8, OUTPUT);  //определим пин 8 как вывод
 pinMode(9, OUTPUT);  //определим пин 8 как вывод
 pinMode(10, OUTPUT);  //определим пин 10 как вывод
 pinMode(11, OUTPUT);  //определим пин 11 как вывод
 pinMode(12, OUTPUT);  //определим пин 12 как вывод
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
        Serial.println("Посик I2c устройств завершен");

 Serial.println("Показания датчика Dallas DS18B20: " + String(ds.getTempC()));
 Serial.println("Данные для фоторезистора на пине 0: " + String(analogRead(A0)));
 digitalWrite(12, HIGH);  //Обеспечиваем питание на пин 12  питание для датчиков
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
