
  #include <ESP8266WiFi.h>


void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.print("ESP Board MAC Address:  ");
 
}
 
void loop(){
 Serial.println(WiFi.macAddress());
}
