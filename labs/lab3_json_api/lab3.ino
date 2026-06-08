#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "LAB3_WIFI";
const char* password = "12345678";

ESP8266WebServer server(80);

// Simulated device values
int fakeTemp = 24;
int fakeHumidity = 55;

// ================= ROOT =================
void handleRoot() {
  server.send(200, "text/html",
    "<h1>Lab 3 JSON API Server</h1>"
    "<p>Visit /api for JSON output</p>"
  );
}

// ================= JSON API =================
void handleAPI() {

  String json = "{";
  json += "\"device\":\"ESP8266\",";
  json += "\"status\":\"online\",";
  json += "\"temperature\":";
  json += fakeTemp;
  json += ",";
  json += "\"humidity\":";
  json += fakeHumidity;
  json += ",";
  json += "\"uptime\":";
  json += millis();
  json += "}";

  server.send(200, "application/json", json);
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
  server.on("/api", handleAPI);

  server.begin();
}

void loop() {
  server.handleClient();
}
