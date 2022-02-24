/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(2, LOW); 
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);//green
   digitalWrite(7, LOW); 
  digitalWrite(6, LOW);
  digitalWrite(5, HIGH);//red
   delay(3000); 

   

  digitalWrite(2, LOW); 
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(7, LOW); 
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);//yellow
  delay(1000); 
   
   
   // wait for a second
  digitalWrite(4, LOW);  
   digitalWrite(3, LOW);
  digitalWrite(2, HIGH);// turn the LED off by making the voltage LOW
   digitalWrite(5, LOW); 
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);//green
  
  delay(3000);                       // wait for a second

  digitalWrite(2, LOW); 
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
   digitalWrite(7, LOW); 
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);//yellow
   delay(1000);
}
    
