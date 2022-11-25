#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#else
#error "Board not found"
#endif
byte J='Risinghopper';
byte T='Hellrising';
byte RR='UltramanZERO';
byte K='2';
#include <PubSubClient.h>

//Relays for switching appliances
#define Relay1            15
#define Relay2            2
#define Relay3            4
#define Relay4            22

bool status_sub1 = false;
bool status_sub2 = false;
bool status_sub3 = false;
bool status_sub4 = false;

// Update these with values suitable for your network.

const char* ssid = "OPPO A5s";
const char* password = "123456123";
const char* mqtt_server = "52.230.104.230"; // Local IP address of Raspberry Pi

const char* username = "thanakij";
const char* pass = "216216216";


// Subscribed Topics

#define sub1 "Esp32/Relay1"
#define sub2 "Esp32/Relay2"
#define sub3 "Esp32/Relay3"
#define sub4 "Esp32/Relay4"

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
}

void callback(char* topic, String* payload, unsigned int length)
{
  
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");


  if (strstr(topic, sub1))
  {
    for (int i = 0; i < length; i++) {
      Serial.println((char)payload[i]);
    }
    Serial.println("relay1");
    // Switch on the LED if an 1 was received as first character
    (char)payload[0] != status_sub1;
    status_sub1 =! status_sub1;
    if (status_sub1 == true) {
      digitalWrite(Relay1, HIGH);   // Turn the LED on (Note that LOW is the voltage level
      // but actually the LED is on; this is because
      // it is active low on the ESP-01)
    } else {
      digitalWrite(Relay1, LOW);  // Turn the LED off by making the voltage HIGH
    }
    
    
  }

  else if ( strstr(topic, sub2))
  {
    for (int i = 0; i < length; i++) {
      
      
     if (payload == J)
    {digitalWrite(Relay1, HIGH);
    digitalWrite(Relay2, HIGH);
    digitalWrite(Relay3, HIGH);
    digitalWrite(Relay4, HIGH);
     }
    
      else if ((char)payload[i] == T)
    {digitalWrite(Relay1, LOW);
    digitalWrite(Relay2, LOW);
    digitalWrite(Relay3, LOW);
    digitalWrite(Relay4, LOW);
     }
    
    if ((char)payload[i] == K)
    {// Switch on the LED if an 1 was received as first character
    (char)payload[0] != status_sub2;
    status_sub2 =! status_sub2;
    if (status_sub2 == true) {
      digitalWrite(Relay2, HIGH);   // Turn the LED on (Note that LOW is the voltage level
      // but actually the LED is on; this is because
      // it is active low on the ESP-01)
    } else {
      digitalWrite(Relay2, LOW);  // Turn the LED off by making the voltage HIGH
    }
    }
    }
    
   
    
    
  }
  else if ( strstr(topic, sub3))
  {
    for (int i = 0; i < length; i++) {
      Serial.println((char)payload[i]);
    }
    Serial.println("relay3");
    // Switch on the LED if an 1 was received as first character
    (char)payload[0] != status_sub4;
    status_sub3 =! status_sub3;
    if (status_sub3 == true) {
      digitalWrite(Relay3, HIGH);   // Turn the LED on (Note that LOW is the voltage level
      // but actually the LED is on; this is because
      // it is active low on the ESP-01)
    } else {
      digitalWrite(Relay3, LOW);  // Turn the LED off by making the voltage HIGH
    }
    
    
  }
  else if ( strstr(topic, sub4))
  {
    for (int i = 0; i < length; i++) {
//      Serial.println((char)payload[i]);
    }
    Serial.println("relay4");
    // Switch on the LED if an 1 was received as first character
    //(char)payload[0] != status_sub4;
    status_sub4 =! status_sub4;
    if (status_sub4 == true) {
      digitalWrite(Relay4, HIGH);   // Turn the LED on (Note that LOW is the voltage level
      // but actually the LED is on; this is because
      // it is active low on the ESP-01)
    } else {
      digitalWrite(Relay4, LOW);  // Turn the LED off by making the voltage HIGH
    }
    
    
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
      client.subscribe(sub1);
      client.subscribe(sub2);
      client.subscribe(sub3);
      client.subscribe(sub4);
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

  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);


  Serial.begin(115200);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{

  if (!client.connected()) 
  {
    reconnect();
  }
   client.loop();
 
}
