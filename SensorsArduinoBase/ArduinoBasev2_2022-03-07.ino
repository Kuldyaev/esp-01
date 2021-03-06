
#include <DS18B20.h>             // Подключаем библиотеку для датчика Dallas DS18B20 
#include <Adafruit_BMP085.h>     // Подключаем библиотеку для датчика BMP085/BMP180
#include <AM2320_asukiaaa.h>     // Подключаем библиотеку для датчика AM2320
#include "DS3231.h"              // Подключаем библиотеку часов

DS18B20 ds(2);                   // Обзываем датчик Dallas DS18B20 как ds, подключен к пину 2 
Adafruit_BMP085 bmp;             // Обзываем датчик BMP180 как bmp
AM2320_asukiaaa mySensor;        // Обзываем датчик АМ2320 как mySensor
DS3231 Clock;                    // обозвать часы Clock

byte myData[] = {7, 39, 00, 22, 3, 7, 1};   
// 0-часы, 1- минуты, 2-секунды, 3-года (две посл цифры), 4-месяц, 5-день, 6-день недели, 
int ledPins[6]={7,8,9,10,11,12}; // формируем массив контактов управления питанием сенсеров и светодиодом   
int a1Pin=A1;                    // контакт подключения аналогового одного емкостного датчика
int a2Pin=A2;                    // контакт подключения аналогового второго емкостного датчика
float Sens[8];                   //объявили массив для данных 
bool recievedFlag;               //данные ролучены
bool h12, PM, Century=false;
int botName = 111;


void setup() {
 for(int i=0;i<8;i++){pinMode(ledPins[i],OUTPUT);}   // настройка выводов индикации светодиодов в режим OUTPUT
 Wire.begin();         //  запускаем библиотеку Wire
 Serial.begin(9600);   // запускаем Serial
 while(!Serial);       // ждем запуск Serial 
 //changeTime();                 // функция для установления даты часов - данные из массиваы
 Wire.end();
 delay(500);
}

void loop() {
  digitalWrite(12, HIGH);  //Обеспечиваем питание на пин 12  питание для датчиков
  Wire.begin();
  mySensor.setWire(&Wire);
  digitalWrite(8, HIGH);
  delay(1500);
  if (mySensor.update() != 0) {
    Serial.println("Error: Cannot update sensor values.");
  } else {
    Sens[0] = mySensor.temperatureC;     //  AM2320 температура
    Sens[1] = mySensor.humidity;         //  AM2320 влажность
  }
 Sens[2] = ds.getTempC();                //  Dallas DS18B20 температура
 Sens[3] = analogRead(A0);               // фоторезистор - освещенность
 Sens[4] = analogRead(A1);               // емкостный датчик на пине 1 - влажность земли
 Sens[5] = analogRead(A2);               // емкостный датчик на пине 2 - влажность земли
 Wire.end();
 digitalWrite(8, LOW);
  delay(2000);
 digitalWrite(10, HIGH);
 Wire.begin();
 if (!bmp.begin()) {
   Serial.println("Could not find a valid BMP085 sensor, check wiring!");
   while (1) {}
 } else {
  Sens[6] = bmp.readTemperature();        // BMP180 температура
  Sens[7] = analogRead(A2);               // BMP180 атм давление
 } 
 delay(2000); 
  //---- получаем данные с модуля времени ----- //
  myData[0] = Clock.getHour(h12, PM);
  myData[1] = Clock.getMinute() ;
  myData[2] = Clock.getSecond();
  myData[3] = Clock.getYear();
  myData[4] = Clock.getMonth(Century);
  myData[5] = Clock.getDate();
  myData[6] = Clock.getDoW();
  //----выводим данные из массивов -------------//
 
 Serial.println();
 digitalWrite(10, LOW);
 digitalWrite(12, LOW);  //Отключаем питание на пин 12 питание для датчиков
 //----формируем вывод ---------------------------//
 String meas = "#";
 meas+="bot:" + String(botName) + ";"; 
 for(int i=0;i<7;i++){meas+=String(myData[i]) + "-";};
 meas = meas.substring(0,  meas.length()-1); 
 meas+=";"; 
 for(int i=0;i<8;i++){meas+=String(Sens[i]) + ";";};
 meas+="#";
 //---- передаем данные в Serial -----------------//
 digitalWrite(7, HIGH);
 recievedFlag = false;
 String answer = "";
 for (int i=0;i<10;i++){
   if (!recievedFlag){
    delay(5);
    while (Serial.available() > 0) {                                                                          // ПОКА есть что то на вход
      answer = Serial.readString();                                                                          // забиваем строку принятыми данными
      if (answer.charAt(0) == 'y' && answer.charAt(1) == 'e' && answer.charAt(2) == 's'){
        recievedFlag = true;
       };                                                                                                    // поднять флаг что получили данные
      delay(200);                                                                                            // ЗАДЕРЖКА. Без неё работает некорректно!
    }
    Serial.println(meas);
   }
   delay(800);
 };
 digitalWrite(7, LOW);
 Wire.end();
 delay(59000); 

}

void changeTime(){
    Clock.setHour(myData[0]);
    Clock.setMinute(myData[1]); 
    Clock.setYear(myData[3]);
    Clock.setMonth(myData[4]);
    Clock.setDate(myData[5]);
    Clock.setDoW(myData[6]);
}
