#include <WiFi.h>
#include <IRremote.h>
#include <PubSubClient.h>

const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;


// Update these with values suitable for your network.
const char* ssid = "OPPO A5s";
const char* password = "123456123";



WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;


// Connecting to WiFi Router
void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("RSSI:");
  Serial.println(WiFi.RSSI());
}



void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn();
  setup_wifi();
}

void loop()
{
 Serial.print("RSSI:");
  Serial.println(WiFi.RSSI());
  delay(700);
}
