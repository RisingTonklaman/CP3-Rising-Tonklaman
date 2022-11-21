#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "ESPAsyncWebServer.h"
//#include <ESP8266Ping.h>
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
AsyncWebServer server(80);
String METSU;
String BOU;
String JINRAI;
String METSUBOUJINRAI;
String Assult = WiFi.macAddress();
String AssultMETSU;
int i;
bool state;
uint8_t broadcastAddress[4][6];
typedef struct test_struct {
    String MACHopper =AssultMETSU ;
    String Hopper ;
    uint8_t SupHopper[4][6];
} test_struct;
test_struct test;
test_struct myData;
//const String index_html[] PROGMEM = "METSU,BOU,JIN"; // large char array, tested with 14k
/*void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  char macStr[18];
  Serial.print(" send status: ");
  if (sendStatus == 0) {
    Serial.println("Delivery success");
  }
  else {
    Serial.println("Delivery fail");
  }
}*/
void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  WiFi.setOutputPower(0);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  /*while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }*/
  Serial.println("");
  Serial.println("Connected to WiFi");
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  /*for(i=0;i<=3;i++){
    esp_now_add_peer(broadcastAddress[i], ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
    }*/
    //esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  //esp_now_register_recv_cb(OnDataRecv);
delay(500);
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
    //request->send_P(200, "text/html", Assult+METSU.c_str());
    request->send_P(200, "text/plain", AssultMETSU.c_str());
  });
    server.on("/BOU", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", BOU.c_str());});
  server.begin();
      delay(10000);
  Serial.println("---------------------------------------------------------------------------------------------------------------------");
  Serial.println(AssultMETSU);
  WiFi.disconnect();
 // server.end();
// WiFi.softAPdisconnect();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("myData.MacHopper: ");
  Serial.println(myData.MACHopper);
      Serial.print("Hopper: ");
  Serial.println(myData.Hopper);
  Serial.println();
    myData.SupHopper[4][6]=broadcastAddress[4][6];
    delay(20000);
}

void loop() {
  unsigned long currentMillis = millis();
  Serial.println(AssultMETSU);
   /*if(state=1){esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
    test.MACHopper = myData.MACHopper;
  test.Hopper = myData.Hopper;
  test.SupHopper[4][6] = myData.SupHopper[4][6];  
  esp_now_send(0, (uint8_t *) &test, sizeof(test));}

  else{}*/
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

    payload = http.getString();
  }

  http.end();

  return payload;
}
