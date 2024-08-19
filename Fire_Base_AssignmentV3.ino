// Blinking an LED with Google Firebase
//Glenn Truett
// 5/31/2024
// JamTruet@uat.edu

#include <M5StickCPlus.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <IOXhop_FirebaseESP32.h>
#include <IOXhop_FirebaseStream.h>
#include <WiFi.h>
#include "secrets.h"
#include <string.h>

#define BUILTIN_LED 10

void setup() {

  
  M5.begin();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(3);  
  M5.Lcd.setRotation(3);  
  M5.Lcd.print("LED Blink");
  
  //Serial stuff
  Serial.begin(115200);
  while(!Serial){
  }

  //WiFi Stuff
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  Serial.print("Connecting to: ");
  Serial.print(SECRET_SSID);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);

  }
  M5.Lcd.setCursor(30, 30);
  M5.Lcd.setTextSize(3);  
  M5.Lcd.setRotation(3);  
  M5.Lcd.print("GLENN");

  pinMode(BUILTIN_LED, OUTPUT);
  //Firebase Stuff
  Firebase.begin(host, firebaseAuth);
  Firebase.setString("LED_STATUS", "OFF");
 
}

void loop() {
  
  String fireStatus = Firebase.getString("LED_STATUS");
  
  //logic
  if(fireStatus == "OFF"){
    Serial.println("LED Turned OFF");
    digitalWrite(BUILTIN_LED, HIGH);
  }
  else if(fireStatus == "ON"){
    Serial.println("LED Turned ON");
    digitalWrite(BUILTIN_LED, LOW);
  }
  else {
    Serial.println("Wrong Credential! Please send ON/OFF");
  }


}
