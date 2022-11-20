#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Metal cluster hopper";
const char* password = "123456789";

//Your IP address or domain name with URL path
const char* serverNameDestroy = "http://192.168.4.1/METSU";
const char* serverNameDeath = "http://192.168.4.1/BOU";
const char* serverNameLightning = "http://192.168.4.1/JINRAI";

#include <Wire.h>
String METSU;
String BOU;
String JINRAI;



void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if(WiFi.status()== WL_CONNECTED ){
      METSU = httpGETRequest(serverNameDestroy);
      BOU = httpGETRequest(serverNameDeath);
      JINRAI = httpGETRequest(serverNameLightning);
      Serial.println("Metsu: " + METSU + " *C ");
      Serial.println("BOU: " + BOU + " % " );
      Serial.println("JINRAI: " + JINRAI + " hPa");
        Serial.print("RSSI:");
  Serial.println(WiFi.RSSI());
      }
    else {
      Serial.println("WiFi Disconnected");
    }
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
