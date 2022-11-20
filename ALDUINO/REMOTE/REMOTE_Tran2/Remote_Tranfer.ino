#include <IRremote.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define WIFI_STA_NAME "Home 40/3"
#define WIFI_STA_PASS "01082018"

#define MQTT_SERVER   "localhost"
#define MQTT_PORT     1883
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_NAME     ""

// ตั้งค่า กำหนดขาของภาครับและตัวแปรเก็บข้อมูลสัญญาณที่ถอดรหัสได้
const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void setup(){
// เริ่ม Serial Monitor และโมดูลภาครับ
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop(){
// เริ่มทำงานหากรับสัญญาณได้
  if (irrecv.decode(&results)){



    // ตรวจรหัสสัญญาณแล้วแสดงชื่อปุ่มตามสัญญาณ
        switch(results.value){
          case 0xFFA25D:
          Serial.println("1");
          break;
          case 0xFF629D:
          Serial.println("2");
          break;
          case 0xFFE21D:
          Serial.println("3");
          break;
          case 0xFF22DD:
          Serial.println("4");
          break;
          case 0xFF02FD:
          Serial.println("5");
          break;
          case 0xFFC23D:
          Serial.println("6");
          break;
          case 0xFFE01F:
          Serial.println("7");
          break;
          case 0xFFA857:
          Serial.println("8");
          break;
          case 0xFF906F:
          Serial.println("9");
          break;
          case 0xFF9867:
          Serial.println("0");
          break;
          case 0xFF6897:
          Serial.println("*");
          break;
          case 0xFFB04F:
          Serial.println("#");
          break;
          case 0xFF38C7:
          Serial.println("OK");
          break;
          case 0xFF18E7:
          Serial.println("UP");
          break;
          case 0xFF4AB5:
          Serial.println("DOWN");
          break;
          case 0xFF10EF:
          Serial.println("LEFT");
          break;
          case 0xFF5AA5:
          Serial.println("RIGHT");
          break;
        }
        
    // เตรียมพร้อมรับสัญญาณต่อไป
        key_value = results.value;
        irrecv.resume();
  }
}
