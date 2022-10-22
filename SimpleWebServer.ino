#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "ssid";
const char* password = "password";
const int port = 80;

ESP8266WebServer server(port);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  delay(10);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  Serial.println(WiFi.localIP());

  String html = "<h1>Lights</h1><p><a href=\"on\"><button>ON</button></a>&nbsp;<a href=\"off\"><button>OFF</button></a></p>";

  server.on("/", HTTP_GET, [html]() {
    server.send(200, "text/html", html);
  });

  server.on("/on", HTTP_GET, [html]() {
    digitalWrite(LED_BUILTIN, LOW); 
    server.send(200, "text/html", html);
  });

  server.on("/off", HTTP_GET, [html]() {
    digitalWrite(LED_BUILTIN, HIGH); 
    server.send(200, "text/html", html);
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
