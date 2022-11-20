#include <ESP8266WiFi.h>        //https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFi.h
#include "UbidotsESPMQTT.h"     //https://github.com/ubidots/ubidots-mqtt-esp/blob/master/src/UbidotsESPMQTT.h

#define TOKEN "your token here" // Your Ubidots TOKEN

#define WIFINAME "your wifi ssid including case" //Your SSID
#define WIFIPASS "your wifi password" //Your Wifi Pass

Ubidots client(TOKEN);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  client.setDebug(true);
  Serial.begin(115200); //ensure your serial monitor is set to this baud rate to view the output data
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if(!client.connected()){
      client.reconnect();
  }

  client.add("valuex", 123);
  client.add("valuey", 10);
  client.ubidotsPublish("WemosDevice"); //this creates a variable in ubidots for water 
  client.loop();

  delay(600000); //updates every 1min (free ubidots can handle an update as much as 1 per minute if using a single device - recommend to leave at 10min)
}
