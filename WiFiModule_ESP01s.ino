#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define SERVER_IP "192.168.0.90:5000"
#ifndef STASSID
#define STASSID "2_4G_MegaFon_FR1000-A658"
#define STAPSK  "********"
#endif

boolean recievedFlag;
String botName, TempA, TempD, HumA, LightA, TempB, PresB;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println();
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("started");
  delay(500);
}

void loop() {
  String myText = "";
  Serial.println();
  delay(3000);
  while (Serial.available() > 0) {         // ПОКА есть что то на вход
    myText = Serial.readString();        // забиваем строку принятыми данными
    recievedFlag = true;                   // поднять флаг что получили данные
    delay(2);                              // ЗАДЕРЖКА. Без неё работает некорректно!
  }

  //Работаем с mytext - парсим строку //
  int openSymbol = myText.indexOf('#');
  int lastSymbol = myText.lastIndexOf('#');
  if(openSymbol > -1 && lastSymbol > -1 && lastSymbol > openSymbol){
    String newString = myText.substring(openSymbol+1, lastSymbol-1);
    myText = newString;
    for (int i = 0; i < 7; i++) {
      int divSymbol = myText.indexOf(';');
      String workString = myText.substring(0, divSymbol);
      newString = myText.substring(divSymbol+1);
      int indexSymbol = workString.indexOf(':');
      String dataName = workString.substring(0, indexSymbol);
      if (dataName.charAt(0) == 'b' && dataName.charAt(1) == 'o' && dataName.charAt(2) == 't'){ botName = workString.substring(indexSymbol+1);} 
      else if (dataName.charAt(0) == 't' && dataName.charAt(1) == 'A'){ TempA = workString.substring(indexSymbol+1);}
      else if (dataName.charAt(0) == 'h' && dataName.charAt(1) == 'A'){ HumA = workString.substring(indexSymbol+1);}
      else if (dataName.charAt(0) == 'l' && dataName.charAt(1) == 'A'){ LightA = workString.substring(indexSymbol+1);}
      else if (dataName.charAt(0) == 't' && dataName.charAt(1) == 'D'){ TempD = workString.substring(indexSymbol+1);}
      else if (dataName.charAt(0) == 't' && dataName.charAt(1) == 'B'){ TempB = workString.substring(indexSymbol+1);}
      else if (dataName.charAt(0) == 'p' && dataName.charAt(1) == 'B'){ PresB = workString.substring(indexSymbol+1);}
      myText = newString;
    }
  }
  //   создаем body для POST запроса //
  String sendText = "{\"bot\":\"" + botName + "\",\"data\":{\"tempDallas\":\"" + TempD + "\",\"tempBMP180\":\"" + TempB + "\",\"humAM2320\":\"" + HumA + "\",\"lightA\":\"" + LightA + "\",\"tempAM2320\":\"" + TempA + "\",\"presBMP180\":\"" + PresB + "\"}}";



  if (myText.length() > 1) {
    if ((WiFi.status() == WL_CONNECTED)) {
      WiFiClient client;
      HTTPClient http;
      delay(500);
      http.begin(client, "http://" SERVER_IP "/test"); //HTTP
      http.addHeader("Content-Type", "application/json");

      int httpCode = http.POST(String(sendText));

      if (httpCode > 0) {
        //Serial.printf("[HTTP] POST... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK) {
          const String& payload = http.getString();
          Serial.println("AnsCode:" + String(httpCode) + ";Payload:" + String(payload));
        }
        delay(500);
      } else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
        Serial.println();
      }
      http.end();
    }
  }
  delay(2000);
}
