#include <AM2320_asukiaaa.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
AM2320_asukiaaa mySensor;

unsigned long last_time;

void setup() {
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
//  while(!Serial);
  Serial.println("started");
}

void loop() {
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
  }
  Wire.end();
  delay(2000);
  Wire.begin();
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  meas+=";T="+String(bmp.readTemperature())+" *C;p="+String(bmp.readPressure()/133)+"mm$#";
  Serial.println(meas);
  Wire.end();
  digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
  Wire.begin();
  delay(1000);
  digitalWrite(11, HIGH); 
  last_time=millis();
  while(millis() < last_time+15000){
    if (Serial.available()){
        Serial.println(String(Serial.readString()));
       } 
  }
  digitalWrite(11, LOW);    // turn the LED off by making the voltage LOW
  Wire.end();
  delay(500);
}
