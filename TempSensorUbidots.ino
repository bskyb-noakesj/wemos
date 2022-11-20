#include <ESP8266WiFi.h>        //https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFi.h
#include "UbidotsESPMQTT.h"     //https://github.com/ubidots/ubidots-mqtt-esp/blob/master/src/UbidotsESPMQTT.h
#include "DHT.h"

#define DHTPIN D4     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors

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
  while(!Serial) { }
  
  dht.begin();

  Serial.println("Device Started");
  Serial.println("-------------------------------------");
  Serial.println("Running DHT!");
  Serial.println("-------------------------------------");
}

void loop() {

  if(!client.connected()){
      client.reconnect();
  }

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");

  client.add("Humidity", h);
  client.add("Temperature", t);
  client.ubidotsPublish("Wemos2"); //this creates a variable in ubidots for water 
  client.loop();

  delay(600000); //updates every 1min (free ubidots can handle an update as much as 1 per minute if using a single device - recommend to leave at 10min)
}
