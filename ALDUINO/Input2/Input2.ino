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
const char* mqtt_server = "52.230.104.230"; // Local IP address of Raspberry Pi
const char* username = "thanakij";
const char* pass = "216216216";


// Subscribed Topics
#define subz "RisingHopper"
#define subk "Hellhopper"
bool Ris= false;
int Risi[3],x=0;

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

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");


  if (strstr(topic, subz))
  {
 
    Serial.println("z");
  }
  else
  {
    Serial.println("unsubscribed topic");
  }

}

// Connecting to MQTT broker
void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str() , username, pass)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe(subz);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{
 if (irrecv.decode(&results)){
  
if(results.value==16726215)
{
  Ris==true;
Serial.println("111111");
      digitalWrite(15, HIGH);   
while(x!=3)
  {
  if (irrecv.decode(&results)){
    
        switch(results.value){
          case 0xFFA25D:
          Risi[x]=1;
          //client.publish(subz, "1");
          break;
          case 0xFF629D:
          Serial.println("2");
          Risi[x]=2;
          //client.publish(subz, "2");
          break;
          case 0xFFE21D:
          Serial.println("3");
          Risi[x]=3;
          //client.publish(subz, "3");
          break;
          case 0xFF22DD:
          Serial.println("4");
          Risi[x]=4;
          //client.publish(subz, "4");
          break;
          case 0xFF02FD:
          Serial.println("5");
          Risi[x]=5;
          break;
          case 0xFFC23D:
          Serial.println("6");
          Risi[x]=6;
          break;
          case 0xFFE01F:
          Serial.println("7");
          Risi[x]=7;
          break;
          case 0xFFA857:
          Serial.println("8");
          Risi[x]=8;
          break;
          case 0xFF906F:
          Serial.println("9");
          Risi[x]=9;
          break;
          case 0xFF9867:
          Serial.println("0");
          Risi[x]=0;
          break;
        } key_value = results.value;
        irrecv.resume();
  x=x+1;}
  else Serial.println("4444444444444");}
Serial.println(Risi[0]); 
Serial.println("879797979");
digitalWrite(15, LOW);  
Serial.println(Risi[0]);
Ris==false;
}


    // ตรวจรหัสสัญญาณแล้วแสดงชื่อปุ่มตามสัญญาณ
if(Ris!=true){        switch(results.value){
          case 0xFFA25D:
          Serial.println("1");
          client.publish(subz, "1");
          break;
          case 0xFF629D:
          Serial.println("2");
          client.publish(subz, "2");
          break;
          case 0xFFE21D:
          Serial.println("3");
          client.publish(subz, "3");
          break;
          case 0xFF22DD:
          Serial.println("4");
          client.publish(subz, "4");
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
          client.publish(subz, "0");
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
        }}
        
    // เตรียมพร้อมรับสัญญาณต่อไป
        key_value = results.value;
        irrecv.resume();
  }
  if (!client.connected()) 
  {
    reconnect();
  }
   client.loop();
 
}
void Rising() {
  Serial.println("HAHAHA");

}
