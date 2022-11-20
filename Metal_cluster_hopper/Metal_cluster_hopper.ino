#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"
#include <Wire.h>
//#include <ESP8266Ping.h>
#include <espnow.h>

// Set your access point network credentials
const char* ssid = "Metal cluster hopper";
const char* password = "123456789";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String METSU() {
  return String(WiFi.macAddress());
}

String BOU() {
  return String("1");
}
String JINRAI() {
  return String("Metal Cruster Hopper");}

void setup(){
  // Serial port for debugging purposes
  WiFi.disconnect();
  WiFi.setOutputPower(0);
  Serial.begin(115200);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/METSU", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", METSU().c_str());
  });
  server.on("/BOU", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", BOU().c_str());
  });
  server.on("/JINRAI", HTTP_GET, [](AsyncWebServerRequest *request){
    //request->send(Serial, "text/plain", 12);
    request->send_P(200, "text/plain", JINRAI().c_str());
  });
  
  /*bool status;

  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }*/
  
  // Start server
  server.begin();
      delay(10000);
  Serial.println("---------------------------------------------------------------------------------------------------------------------");
  
 /* WiFi.disconnect();
  server.end();
 WiFi.softAPdisconnect();*/
}
 
void loop(){
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  Serial.println(WiFi.macAddress());
  Serial.println(METSU());
  delay(900);
}
