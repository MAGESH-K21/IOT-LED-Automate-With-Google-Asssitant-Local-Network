#include <ESP8266WebServer.h>
ESP8266WebServer server;
#define username "Magesh"
#define password "12345678"
String myhtml="<html><head><title>First Page</title></head><body style=\"background-color:cyan\"><h1><center>IOT</center></h1><form><center> What do you want to do? <br><br><button type=\"submit\" name=\"state\" value=\"0\">LED ON</button><button type=\"submit\" name=\"state\" value=\"1\">LED OFF</button></center></form></body></html>";

void setup(){
  pinMode(16,OUTPUT);
  Serial.begin(115200);
  WiFi.softAP(username,password);
  Serial.print(WiFi.softAPIP());
  server.begin();
  server.on("/led",response);
}
void response(){
    server.send(200,"text/html",myhtml);
    if(server.arg("state")=="1")
    {
    digitalWrite(16,HIGH);
    }
    else
    {
    digitalWrite(16,LOW);
    }
}
void loop(){
  server.handleClient();
}
