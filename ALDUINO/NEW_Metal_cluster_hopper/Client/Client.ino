#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;
#include <espnow.h>

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
String AssultMETSU;
unsigned long previousMillis = 0;
const long interval = 5000; 
String Kaijuu[6];
int i,y ;
String EDEN[2];
uint8_t broadcastAddressZ[]={0x58, 0xBF, 0x25, 0xDA, 0x21, 0xDF};
uint8_t broadcastAddress[2][6];
typedef struct test_struct {
    String MACHopper =AssultMETSU ;
    String Hopper ;
    uint8_t SupHopper[2][6];
} test_struct;
test_struct test;
test_struct myData;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  char macStr[18];
  Serial.print(" send status: ");
  if (sendStatus == 0) {
    Serial.println("Delivery success");
  }
  else {
    Serial.println("Delivery fail");
  }
}

/*void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("myData.MacHopper: ");
  Serial.println(myData.MACHopper);
      Serial.print("Hopper: ");
  Serial.println(myData.Hopper);
  Serial.println();
 // state!=state;
}*/

void setup() {
  Serial.begin(115200);
    WiFi.disconnect();
  WiFi.setOutputPower(0);
  Serial.println();
 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  /*WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");*/
  AssultMETSU = httpGETRequest(serverNameDestroy);
      BOU = httpGETRequest(serverNameDeath);
      JINRAI = httpGETRequest(serverNameLightning);
      Serial.println(AssultMETSU);
      Serial.println();
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
    for(y=0;y<=1;y++){
    EDEN[y]=getValue(AssultMETSU,'K',y);
    Serial.printf("EDEN[%d]=",y);
    Serial.println(EDEN[y]);
for(i=0;i<=5;i++){
  Kaijuu[i] = getValue(EDEN[y],':',i); 
  Serial.printf("Kaijuu[%d]=",i);
  Serial.println(Kaijuu[i]);
  String hexValue = Kaijuu[i];
  byte tens = (hexValue[0] < '9') ? hexValue[0] - '0' : hexValue[0] - '7';
  byte ones = (hexValue[1] < '9') ? hexValue[1] - '0' : hexValue[1] - '7';
  byte number = (16 * tens) + ones;
  broadcastAddress[y][i] = number;
  Serial.println(number);
  Serial.printf("broadcastAddress[%d][%d]=",y,i);
  Serial.println(broadcastAddress[y][i]);
}
   Serial.println("_____________");
}
Serial.println("---------------------");
  WiFi.disconnect();
// server.end();
 WiFi.softAPdisconnect();
  /*for(i=0;i<=1;i++){
    esp_now_add_peer(broadcastAddress[i], ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
    }*/
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
 esp_now_add_peer(broadcastAddressZ, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
 
  /*esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);*/
  delay(10000);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) {
     // Check WiFi connection status
    if ((WiFiMulti.run() == WL_CONNECTED)) {
      Serial.println( "Metsu: "+AssultMETSU );
      // save the last HTTP GET Request
      previousMillis = currentMillis;
      test.MACHopper = AssultMETSU;
  test.Hopper = JINRAI;
  test.SupHopper[4][6] = broadcastAddress[4][6];
  esp_now_send(0, (uint8_t *) &test, sizeof(test));
    }
    else {
      Serial.println("WiFi Disconnected");
      Serial.println( "Metsu: "+AssultMETSU );
      test.MACHopper = AssultMETSU;
  test.Hopper = JINRAI;
  test.SupHopper[4][6] = broadcastAddress[4][6];
  esp_now_send(0, (uint8_t *) &test, sizeof(test));
    }
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
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
