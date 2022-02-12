
#include "Wire.h"                // библиотека соединений модулей
#define RX 11                     // Определяем пин UART RX
#define TX 12                     // Определяем пин UART TX
#include <SoftwareSerial.h>      // Подключаем библиотеку программного UART
SoftwareSerial mySerial(RX, TX); // Создаём объект программного UART
void setup() {
  Serial.begin(9600);                               // стартуем связь с портом
  while (!Serial) {delay(10);}                      // ждем запуск порта Serial
  
 //-------Запуск Serial ----------------------------//
  mySerial.begin(9600);                             // стартуем связь с портом
  while (!mySerial) {delay(10);}                      // ждем запуск порта Serial
                                   // устанавливаем соединения 
 //--------Сканируем подключенные устройства--------// 
  Wire.begin();
}

void loop() {
  if (mySerial.available()){
    Serial.println(String(mySerial.readString()));
   } 
}
