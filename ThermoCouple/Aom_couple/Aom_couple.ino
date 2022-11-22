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
}

void loop() {
  
    
   Serial.print(ts.getCelsius(), 2);
   Celsiust=ts.getCelsius(), 2;
   Serial.print(" C ");
   //Serial.println(Celsiust);
   delay(1000);
 
}
