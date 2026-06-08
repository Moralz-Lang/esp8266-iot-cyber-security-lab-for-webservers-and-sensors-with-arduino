#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "LAB1_WIFI";
const char* password = "12345678";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html",
              "<h1>ESP8266 Lab 1 Web Server</h1>"
              "<p>Status: Online</p>");
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}
