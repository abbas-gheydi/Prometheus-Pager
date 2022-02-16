/**
   Promethues_Pager

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>
#define WIFISSID "YOUR WIFI SSID"
#define PASSWORD "WIFI PASSWORD"
String URLADDR = "http://192.168.1.10:9090/api/v1/alerts"; //promthues address
int currentStateSize;
int newStateSize;


ESP8266WiFiMulti WiFiMulti;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     
 
  digitalWrite(LED_BUILTIN, HIGH);
  

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFISSID, PASSWORD);

}
void fireAlert(){
  
  for (uint8_t t = 30; t > 0; t--) {
  Serial.println("fire ....");

  digitalWrite(LED_BUILTIN, LOW);  
  delay(100);                      
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(100);  
  }
  
}
bool isStateChanged(){
  if (currentStateSize == 0){
    currentStateSize = newStateSize;
  }
  if (newStateSize != currentStateSize){
    currentStateSize = newStateSize;
    return true;
  } else{
   
    return false;
  }

}
void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, URLADDR)) {  

      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // found at server
        if (httpCode == HTTP_CODE_OK ) {
          //String payload = http.getString();
          newStateSize = http.getSize();
          if (isStateChanged()){
            fireAlert();
          }else {
            Serial.println("state not changed..");
          }

          Serial.println(currentStateSize);
          Serial.println(newStateSize);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
       
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(10000);
}
