#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
 
const char* ssid = "ssid";
const char* password = "passwod";
const int led = D1;

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266! (blinking LED)");
  int led_state = 0;
  for (int ii=0;ii<10;ii++){
    digitalWrite(led,led_state);
    led_state = !led_state;
    delay(1000);
  }
}

void led_on(){
  server.send(200, "text/plain", "LED on");
  digitalWrite(led,HIGH);
}

void led_off(){
  server.send(200, "text/plain", "LED off");
  digitalWrite(led,LOW);
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot); // what happens in the root
  server.on("/on",led_on); // turn led on from webpage /on
  server.on("/off", led_off); // turn led off from webpage /off

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}