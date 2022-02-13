#include <AM2320_asukiaaa.h>
#include <Adafruit_BMP085.h>
#define RX 9                     // Определяем пин UART RX
#define TX 10
#include <SoftwareSerial.h>      // Подключаем библиотеку программного UART
SoftwareSerial mySerial(RX, TX); // Создаём объект программного UART  
Adafruit_BMP085 bmp;
AM2320_asukiaaa mySensor;

unsigned long last_time;

struct Str {
  int val_a;
  int val_b;
  int val_c;
  int val_d;
  int val_e;
};

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
  Str buf;
  String meas = "#MEAS";
  digitalWrite(12, HIGH); 
  delay(1000);
  Wire.begin();
  mySensor.setWire(&Wire);
  if (mySensor.update() != 0) {
    Serial.println("Error: Cannot update sensor values.");
  } else {
    meas+=":t=" + String(mySensor.temperatureC) + "C" +";h=" + String(mySensor.humidity) + "%";
    int val = analogRead(A0);
    meas+=";l="+String(val);
    buf.val_a = mySensor.temperatureC*100;
    buf.val_b = mySensor.humidity*100;
    buf.val_c = val;
  }
  Wire.end();
  delay(2000);
  Wire.begin();
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  meas+=";T="+String(bmp.readTemperature())+" *C;p="+String(bmp.readPressure()/133)+"mm$#";
  buf.val_d = bmp.readTemperature()*100;
  buf.val_e = bmp.readPressure()/133;
  Serial.println(meas);
  mySerial.write((byte*)&buf, sizeof(buf));
  delay(2000);
  Wire.end();
  digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
  Wire.begin();
  delay(1000);
  digitalWrite(11, HIGH); 
  last_time=millis();
  while(millis() < last_time+15000){
     delay(100);
    if (Serial.available()){
        if(String(Serial.readString())=="OK"){delay(15000);}
        Serial.println(String(Serial.readString()));
    } 
    delay(15000);
  }
  digitalWrite(11, LOW);    // turn the LED off by making the voltage LOW
  Wire.end();
  delay(10000);
}
