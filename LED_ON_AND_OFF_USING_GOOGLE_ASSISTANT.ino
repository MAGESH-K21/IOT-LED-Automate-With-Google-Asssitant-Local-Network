#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#define led 16
#define wifi "Redmi"
#define password "12345678"
#define server "io.adafruit.com"
#define port 1883
#define username "magesh_k"
#define  key "aio_sJdf05E8Th3CjAY4di9sNLKbcrHO" 
WiFiClient esp;
Adafruit_MQTT_Client mqtt(&esp, server, port, username, key);
Adafruit_MQTT_Subscribe feed(&mqtt,username"/feeds/googleassistant");
void setup()
{
  pinMode(16,OUTPUT);
  Serial.begin(115200);
  delay(500);
  Serial.println("Connecting to ");
  Serial.println(wifi);
  WiFi.begin(wifi,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");
  mqtt.subscribe(&feed);
  Serial.println("Connecting to MQTT");
  while(mqtt.connect())
  {
    delay(500);
    Serial.print(".");
  }
}
void loop()
{
Serial.println(" ");
while(mqtt.readSubscription(5000))
{
  Serial.print("Got: ");
  int a = atoi((char*)feed.lastread);
  Serial.println(a);
  if(a==0)
  {
    digitalWrite(led,LOW);
  }
  else
  {
    digitalWrite(led,HIGH);
  }
}
}
