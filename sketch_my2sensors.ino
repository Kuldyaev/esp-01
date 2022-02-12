#include <AM2320_asukiaaa.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
AM2320_asukiaaa mySensor;

void setup() {
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  while(!Serial);
  Serial.println("started");
}

void loop() {
  digitalWrite(12, HIGH); 
  delay(1000);
  Wire.begin();
  mySensor.setWire(&Wire);
  if (mySensor.update() != 0) {
    Serial.println("Error: Cannot update sensor values.");
  } else {
    Serial.println("temperatureC: " + String(mySensor.temperatureC) + " C");
    Serial.println("temperatureF: " + String(mySensor.temperatureF) + " F");
    Serial.println("humidity: " + String(mySensor.humidity) + " %");
  }
  Serial.println("at " + String(millis()) + " ms");
  Serial.println("");
  Wire.end();
  delay(5000);
  Wire.begin();
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
 Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
  
  // Calculate altitude assuming 'standard' barometric
  // pressure of 1013.25 millibar = 101325 Pascal
  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");

  Serial.print("Pressure at sealevel (calculated) = ");
  Serial.print(bmp.readSealevelPressure());
  Serial.println(" Pa");

// you can get a more precise measurement of altitude
// if you know the current sea level pressure which will
// vary with weather and such. If it is 1015 millibars
// that is equal to 101500 Pascals.
  Serial.print("Real altitude = ");
  Serial.print(bmp.readAltitude(101500));
  Serial.println(" meters");
  
  Serial.println();
  Wire.end();
  digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
  delay(15000);
}
