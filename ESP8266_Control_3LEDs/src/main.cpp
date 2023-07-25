/*

If you can, please support me on my Youtube's channel: @ElectricalThinking29
by hitting like, share and subscribe's buttons to my videos.

*** LICENSE ***

Copyright 2023 @ElectricalThinking29

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "*****";
const char* password = "****";
ESP8266WebServer server(80);
const int led1 = D5;
const int led2 = D6;
const int led3 = D7;

// put function declarations here:
void handleRoot();
void handleLed1On();
void handleLed1Off();
void handleLed2On();
void handleLed2Off();
void handleLed3On();
void handleLed3Off();
String readStatus(int led);

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  IPAddress local_IP(192, 168, 1, 184);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress primaryDNS(8, 8, 8, 8); //optional
  WiFi.config(local_IP, gateway, subnet, primaryDNS);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/led1on", handleLed1On);
  server.on("/led1off", handleLed1Off);

  server.on("/led2on", handleLed2On);
  server.on("/led2off", handleLed2Off);

  server.on("/led3on", handleLed3On);
  server.on("/led3off", handleLed3Off);

  server.begin();
}
 
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

// put function definitions here:
void handleRoot() {
  String html = "<html>\
    <body>\
      <h1>ESP8266 Web Server</h1>\
      <p>LED 1 <a href=\"/led1on\"><button>ON</button></a>&nbsp;<a href=\"/led1off\"><button>OFF</button></a> Status: " 
        + readStatus(digitalRead(led1)) + "</p>\
      <p>LED 2 <a href=\"/led2on\"><button>ON</button></a>&nbsp;<a href=\"/led2off\"><button>OFF</button></a> Status: " 
        + readStatus(digitalRead(led2)) + "</p>\
      <p>LED 3 <a href=\"/led3on\"><button>ON</button></a>&nbsp;<a href=\"/led3off\"><button>OFF</button></a> Status: " 
        + readStatus(digitalRead(led3)) + "</p>\
    </body>\
  </html>";
  server.send(200, "text/html", html);
}
void handleLed1On() {
  digitalWrite(led1, LOW);
  handleRoot();
}
void handleLed1Off() {
  digitalWrite(led1, HIGH);
  handleRoot();
}
void handleLed2On() {
  digitalWrite(led2, LOW);
  handleRoot();
}
void handleLed2Off() {
  digitalWrite(led2, HIGH);
  handleRoot();
}
void handleLed3On() {
  digitalWrite(led3, LOW);
  handleRoot();
}
void handleLed3Off() {
  digitalWrite(led3, HIGH);
  handleRoot();
}
String readStatus(int led){
  if (led == 0){
    return "ON";
  }
  if (led == 1) {
    return "OFF";
  }
  return "ERROR";
}