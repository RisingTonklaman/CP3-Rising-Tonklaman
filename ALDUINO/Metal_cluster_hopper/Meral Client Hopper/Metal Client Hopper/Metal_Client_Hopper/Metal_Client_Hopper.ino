#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "ESPAsyncWebServer.h"
#include <ESP8266Ping.h>
#include <espnow.h>

#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;

const char* ssid = "Metal cluster hopper";
const char* password = "123456789";

//Your IP address or domain name with URL path
const char* serverNameDestroy = "http://192.168.4.1/METSU";
const char* serverNameDeath = "http://192.168.4.1/BOU";
const char* serverNameLightning = "http://192.168.4.1/JINRAI";
#include <Wire.h>

/*#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);*/
AsyncWebServer server(80);
String METSU;
String BOU;
String JINRAI;
String METSUBOUJINRAI;
String Assult = WiFi.macAddress();
String AssultMETSU;
int WOLF;
//const String index_html[] PROGMEM = "METSU,BOU,JIN"; // large char array, tested with 14k


void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  WiFi.setOutputPower(0);
  Serial.println();
  
 /* // Address 0x3C for 128x64, you might need to change this value (use an I2C scanner)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(WHITE);*/
 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
     if ((WiFiMulti.run() == WL_CONNECTED)) {
      METSU = httpGETRequest(serverNameDestroy);
      BOU = httpGETRequest(serverNameDeath);
      JINRAI = httpGETRequest(serverNameLightning);
      Serial.println("Metsu: " + METSU + " *C - BOU: " + BOU + " % - JINRAI: " + JINRAI + " hPa");
      METSUBOUJINRAI=JINRAI;
      BOU=BOU+1;
      AssultMETSU=METSU+"K"+Assult;
      delay(500);
      WiFi.disconnect();
      WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.on("/JINRAI", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", METSUBOUJINRAI.c_str());
  });
    server.on("/METSU", HTTP_GET, [](AsyncWebServerRequest *request){
//request->send_P(200, "text/html", index_html);
//request->send(Serial, "text/plain", 12);
    //request->send_P(200, "text/html", Assult+METSU.c_str());
    request->send_P(200, "text/plain", AssultMETSU.c_str());
  });
    server.on("/BOU", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", BOU.c_str());});
  // Start server
  server.begin();
      

     /* Serial.print("T: ");
      Serial.print(METSU);
      Serial.print("C");
      
      Serial.print("H: ");
      Serial.print(BOU);
      Serial.print(" %"); 
      
      Serial.print("P:");
      Serial.print(JINRAI);
      Serial.print("hPa");*/
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}

void loop() {
  unsigned long currentMillis = millis();
  Serial.println(AssultMETSU);
//  Serial.println(AssultMETSU.substring(0, 18));
  delay(900);
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    //Serial.print("Error code: ");
    //Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
