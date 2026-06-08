#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

const char* ssid = "LAB4_WIFI";
const char* password = "12345678";

ESP8266WebServer server(80);

// ================= DHT SENSOR =================
#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// ================= ROOT =================
void handleRoot() {
  server.send(200, "text/html",
    "<h1>Lab 4 - DHT Sensor IoT</h1>"
    "<p>Go to /api for sensor data</p>"
  );
}

// ================= SENSOR API =================
void handleAPI() {

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    server.send(500, "application/json",
      "{\"error\":\"Sensor read failed\"}"
    );
    return;
  }

  String json = "{";
  json += "\"device\":\"ESP8266\",";
  json += "\"temperature\":";
  json += temp;
  json += ",";
  json += "\"humidity\":";
  json += hum;
  json += ",";
  json += "\"status\":\"active\"";
  json += "}";

  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);

  dht.begin();

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
