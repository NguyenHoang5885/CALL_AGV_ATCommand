#include <Arduino.h>
#include <ArduinoJson.h>
#include "SoftwareSerial.h"

char *commands_wifi_client_static="\ 
\ 
at+netmode=2\r\n\ 
at+wifi_conf=RTCAGV_TESTZONE,wpa2_aes,rtc@1234\r\n\ 
at+dhcpc=0\r\n\ 
at+net_ip=192.168.3.251,255.255.255.0,192.168.3.1\r\n\ 
at+net_dns=192.168.11.1,8.8.8.8\r\n\ 
\ 
at+remoteip=192.168.3.254\r\n\ 
at+remoteport=5000\r\n\ 
at+remotepro=tcp\r\n\ 
at+timeout=0\r\n\ 
at+mode=client\r\n\ 
at+uart=115200,8,n,1\r\n\ 
at+uartpacklen=64\r\n\ 
at+uartpacktimeout=10\r\n\ 
at+net_commit=1\r\n\ 
at+reconn=1\r\n\ 
"; 

DynamicJsonDocument doc(1024);

void sendHttpPost() {
  String postData;
  serializeJson(doc, postData);
  String request = String("POST /items HTTP/1.1\r\n") +
                   String("Host: 192.168.3.254:5000\r\n") +
                   String("Content-Type: application/json\r\n") +
                   "Content-Length: " + String(postData.length()) + "\r\n" +
                   "\r\n" + postData;
  // Gửi yêu cầu đến Flask
  Serial3.print(request); 
}
void Json() {
  doc["Bo_goi_AGV"] = "Bo_goi_AGV";

  sendHttpPost();
}

#define pull_down_GND 27
void setup() {
  Serial.begin(115200);   
  Serial3.begin(115200);// UART transfer ATcommand

  pinMode(pull_down_GND, OUTPUT);   

  // pull down ES/RST pin Tes(100ms) < time pull down < Trst (6s)
  digitalWrite(pull_down_GND, 0); 
  delay(2000);
  digitalWrite(pull_down_GND, 1); 

  Serial3.println(commands_wifi_client_static);
}

void loop() {
  // Check response from HLK-RM04  
  if (Serial3.available()) {
    String response = Serial3.readString(); 
    Serial.println(response);
    Serial.println("hi"); 
  }
  // Fill down command to Serial
  if (Serial.available()) {
    String response1 = Serial.readString(); 
    Serial3.println(response1); 
    Serial.println(response1);
  }
  Json();
  Serial.println();
  delay(500);
}