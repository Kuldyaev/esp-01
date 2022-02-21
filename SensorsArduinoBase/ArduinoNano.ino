#include <AM2320_asukiaaa.h>
#include <Adafruit_BMP085.h>
#define RX 9                     // Определяем пин UART RX
#define TX 10
#include <SoftwareSerial.h>      // Подключаем библиотеку программного UART
#include <DS18B20.h>             // Подключаем библиотеку для датчика Dallas DS18B20   
SoftwareSerial mySerial(RX, TX); // Создаём объект программного UART  
Adafruit_BMP085 bmp;
AM2320_asukiaaa mySensor;

DS18B20 ds(2);
int botName = 111;
unsigned long last_time;
boolean recievedFlag;

void setup() {
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
  while(!Serial);
 //-------Запуск Serial ----------------------------//
  mySerial.begin(9600);                             // стартуем связь с портом
  while (!mySerial) {delay(10);}                      // ждем запуск порта Serial
  Serial.println("started");
}

void loop() {
  //-------------------Получение данных ------------------------//
  String meas = "#";
  digitalWrite(12, HIGH); 
  delay(1000);
  Wire.begin();
  mySensor.setWire(&Wire);
  if (mySensor.update() != 0) {
    Serial.println("Error: Cannot update sensor values.");
  } else {
    meas+="bot:00" + String(botName) + ";tA:" + String(mySensor.temperatureC) + ";hA:" + String(mySensor.humidity) + ";tD:" + String(ds.getTempC());
    meas+=";lA:"+String(analogRead(A0));
  }
  Wire.end();
  delay(2000);
  Wire.begin();
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  meas+=";tB:"+String(bmp.readTemperature())+";pB:"+String(bmp.readPressure()/133) + ";#";
  //Serial.println(meas);
  delay(2000);
  Wire.end();
  digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
  //-------------------Передача данных ------------------------//
  Wire.begin();
  delay(1000);
  digitalWrite(11, HIGH);    // включаем питание на WiFi ESP-01
  delay(1502);
  last_time = millis();
  String myText = "";
  String newString = "";
  while(millis()-last_time<10000){ 
    while (Serial.available() > 0) {                                                                          // ПОКА есть что то на вход
      myText = Serial.readString();                                                                          // забиваем строку принятыми данными
      recievedFlag = true;                                                                                  // поднять флаг что получили данные
      delay(2);                                                                                            // ЗАДЕРЖКА. Без неё работает некорректно!
    }
    //Serial.println(myText);  
    int openSSymbol = myText.indexOf('#');                                                                  //Начальный символ полученной строки верный
    int lastSSymbol = myText.lastIndexOf('#');                                                             //Строка оканчивается верным символом
    if(openSSymbol > -1 && lastSSymbol > -1 && lastSSymbol > openSSymbol && recievedFlag){                //верный начальный и окончательный символ на месте
     newString = myText.substring(openSSymbol+1, lastSSymbol);                                         //Выделяем смысловую часть сообщения
     if (newString.charAt(0) == 'R' && newString.charAt(1) == 'Y'){                                   // Если сообщение "RY"
       myText = "";                                                                                  // Обнуляем строки
       newString = "";                                                                              // Обнуляем строки и ждем сообщение
       Serial.println(meas); 
      
     }
    }
   delay(5000);
  }
  
  digitalWrite(11, LOW);    // выключаем питание на WiFi ESP-01
  Wire.end();
  //-------------------Пауза ------------------------//
  delay(30000);
}
