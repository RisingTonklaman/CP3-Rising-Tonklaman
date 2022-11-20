#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "Max6675.h"
//----------------------------------------
String Celsiust;
Max6675 ts(21, 22, 23);


//----------------------------------------SSID dan Password wifi mu gan.
const char* ssid = "OPPO A5s"; //--> Nama Wifi / SSID.
const char* password = "123456123"; //-->  Password wifi .
//----------------------------------------

//----------------------------------------Host & httpsPort
const char* host = "script.google.com";
const int httpsPort = 443;

WiFiClientSecure client; //--> Create a WiFiClientSecure object.

String GAS_ID = "AKfycby9gahfOoYGgD6XpLXxvqlSdRbvmCCot8Oh4s2S4mKCkt56ahK-N9-sPtklQ3gQZPq1pw"; //--> spreadsheet script ID

//============================================ void setup
void setup() {

  ts.setOffset(0);
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);
  
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
  
  }
  //----------------------------------------
  
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------

  client.setInsecure();
}

void loop() {
  
    
   Serial.print(ts.getCelsius(), 2);
   Celsiust=ts.getCelsius(), 2;
   Serial.print(" C ");
   Serial.println(Celsiust);
   delay(1000);
   sendData(Celsiust);
 
}

void sendData(String Celsiust) {
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);
  
  //----------------------------------------Connect to Google host
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  
  String url = "/macros/s/" + GAS_ID + "/exec?temp=" + Celsiust; 
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");
  //----------------------------------------

  //---------------------------------------
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
 /* String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }*/
  Serial.print("reply was : ");
  //Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();
} 
