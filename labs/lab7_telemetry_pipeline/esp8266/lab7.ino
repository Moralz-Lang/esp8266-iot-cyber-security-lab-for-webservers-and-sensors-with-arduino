#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

// CHANGE THIS TO YOUR PC IP and port of your choice
const char* serverURL = "http://192.168.x.x:port/upload";

#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

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
}

void loop() {

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Sensor read failed");
    delay(3000);
    return;
  }

  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverURL);
  http.addHeader("Content-Type", "application/json");

  String json = "{";
  json += "\"device\":\"ESP8266\",";
  json += "\"temperature\":";
  json += temp;
  json += ",";
  json += "\"humidity\":";
  json += hum;
  json += "}";

  int code = http.POST(json);

  Serial.print("HTTP Code: ");
  Serial.println(code);

  http.end();

  delay(5000);
}
