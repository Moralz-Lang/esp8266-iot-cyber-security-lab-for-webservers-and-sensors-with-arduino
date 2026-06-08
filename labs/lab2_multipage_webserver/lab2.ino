#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "LAB2_WIFI";
const char* password = "12345678";

ESP8266WebServer server(80);

// ================= HOME PAGE =================
void handleRoot() {
  server.send(200, "text/html",
    "<h1>ESP8266 Lab 2 Dashboard</h1>"
    "<p>Multi-page Web Server Running</p>"
    "<a href='/status'>Status</a><br>"
    "<a href='/network'>Network</a><br>"
    "<a href='/api'>API</a>"
  );
}

// ================= STATUS PAGE =================
void handleStatus() {
  String page = "<h1>Status Page</h1>";
  page += "<p>Device is ONLINE</p>";
  page += "<p>Uptime (ms): " + String(millis()) + "</p>";
  server.send(200, "text/html", page);
}

// ================= NETWORK PAGE =================
void handleNetwork() {
  String page = "<h1>Network Info</h1>";
  page += "<p>IP Address: " + WiFi.localIP().toString() + "</p>";
  page += "<p>SSID: " + WiFi.SSID() + "</p>";
  page += "<p>RSSI: " + String(WiFi.RSSI()) + "</p>";
  server.send(200, "text/html", page);
}

// ================= API JSON =================
void handleAPI() {
  server.send(200, "application/json",
    "{\"device\":\"ESP8266\",\"status\":\"online\",\"lab\":2}"
  );
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

  // ROUTES
  server.on("/", handleRoot);
  server.on("/status", handleStatus);
  server.on("/network", handleNetwork);
  server.on("/api", handleAPI);

  server.begin();
}

void loop() {
  server.handleClient();
}
