#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASS";

const char* serverURL = "http://YOUR_PC_IP:port/upload";

#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

String deviceID = "NODE_1";

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverURL);
  http.addHeader("Content-Type", "application/json");

  String json = "{";
  json += "\"device_id\":\"" + deviceID + "\",";
  json += "\"temperature\":" + String(t) + ",";
  json += "\"humidity\":" + String(h);
  json += "}";

  http.POST(json);
  http.end();

  delay(5000);
}
