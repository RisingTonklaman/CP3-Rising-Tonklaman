#include <ESP8266WiFi.h>
#include <espnow.h>

// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress1[] = {0x58, 0xBF, 0x25, 0xD7, 0x6A, 0x28};
//uint8_t broadcastAddress2[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct test_struct {
  int x;
  int y;
  String Hopper;
  uint8_t macHopper;
} test_struct;
test_struct test;

/*unsigned long lastTime = 0;
  unsigned long timerDelay = 2000;  // send readings timer*/

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  char macStr[18];
  Serial.print("Packet to:");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status: ");
  if (sendStatus == 0) {
    Serial.println("Delivery success");
  }
  else {
    Serial.println("Delivery fail");
  }
  Serial.println();
  Serial.println(test.Hopper);
}

void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  WiFi.setOutputPower(0);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  esp_now_add_peer(broadcastAddress1, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  // esp_now_add_peer(broadcastAddress2, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

}

void loop() {


  test.x = random(1, 50);
  test.y = random(1, 50);
  test.Hopper = WiFi.macAddress();
  /*char macHopper[18];
  snprintf(macHopper, sizeof(macHopper), "%02x:%02x:%02x:%02x:%02x:%02x",
           macHopper[0], macHopper[1], macHopper[2], macHopper[3], macHopper[4], macHopper[5]);
  test.Hopper = macHopper;
  Serial.print(test.Hopper);*/
  // Send message via ESP-NOW
  esp_now_send(0, (uint8_t *) &test, sizeof(test));
  delay(900);

}
