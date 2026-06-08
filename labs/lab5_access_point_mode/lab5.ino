#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Change to what you like for different name
const char* ssid = "ESP-LAB-5";
const char* password = "12345678";

ESP8266WebServer server(80);

// ================= HOME PAGE =================
void handleRoot() {

  server.send(200, "text/html",
    "<h1>Lab 5 - ESP8266 Access Point</h1>"
    "<p>You are connected directly to ESP8266 hotspot</p>"
    "<a href='/status'>Status</a>"
  );
}

// ================= STATUS PAGE =================
void handleStatus() {

  String page = "<h1>Status Page</h1>";
  page += "<p>Uptime: " + String(millis() / 1000) + " seconds</p>";
  page += "<p>Connected Clients Supported: 4</p>";

  server.send(200, "text/html", page);
}

void setup() {

  Serial.begin(115200);

  // ================= CREATE HOTSPOT =================
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  Serial.println("\nAccess Point Started");
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());

  // ================= ROUTES =================
  server.on("/", handleRoot);
  server.on("/status", handleStatus);

  server.begin();
}

void loop() {
  server.handleClient();
}
