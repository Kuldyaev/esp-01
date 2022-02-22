#include <DS18B20.h>             // Подключаем библиотеку для датчика Dallas DS18B20 
#include <Adafruit_BMP085.h>     // Подключаем библиотеку для датчика BMP085/BMP180

DS18B20 ds(2);                   // Обзываем датчик Dallas DS18B20 как ds, подключен к пину 2 
Adafruit_BMP085 bmp;             // Обзываем датчик BMP180 как bmp

void setup() {
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
 Serial.println("Показания датчика Dallas DS18B20: " + String(ds.getTempC()));
 Serial.println("Данные для фоторезистора на пине 0: " + String(analogRead(A0)));
 
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

 delay(5000); 
 digitalWrite(12, LOW);  //Отключаем питание на пин 12   питание для датчиков
}
