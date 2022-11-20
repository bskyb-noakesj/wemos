#include <ESP8266WiFi.h>        //https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFi.h
#include "UbidotsESPMQTT.h"     //https://github.com/ubidots/ubidots-mqtt-esp/blob/master/src/UbidotsESPMQTT.h

#define TOKEN "your token here" // Your Ubidots TOKEN

#define WIFINAME "your wifi ssid including case" //Your SSID
#define WIFIPASS "your wifi password" //Your Wifi Pass


Ubidots client(TOKEN);

void callback(char* topic, byte* payload, unsigned int length) {;
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
  client.ubidotsSetBroker("business.api.ubidots.com");
  client.begin(callback);
  client.ubidotsSubscribe("Wemos1","interval"); //Insert the dataSource and Variable’s Labels
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if(!client.connected()){
      client.reconnect();
      client.ubidotsSubscribe("Wemos1","interval");
  }

  client.loop();

  delay(100000);
}
