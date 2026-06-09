#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

// CHANGE THIS TO YOUR PC IP and PORT OF CHOICE
const char* serverURL = "http://192.168.x.x:port/upload";

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
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {

    WiFiClient client;
    HTTPClient http;

    http.begin(client, serverURL);
    http.addHeader("Content-Type", "application/json");

    String json = "{";
    json += "\"device\":\"ESP8266\",";
    json += "\"temperature\":25,";
    json += "\"humidity\":60";
    json += "}";

    int code = http.POST(json);

    Serial.print("HTTP Response: ");
    Serial.println(code);

    http.end();
  }

  delay(5000);
}
