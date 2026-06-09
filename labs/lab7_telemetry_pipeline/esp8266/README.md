# 🧪 Lab 7 — Real Sensor Telemetry Pipeline

## 🎯 Objective
Replace simulated values with real sensor data using DHT11 and send it to a server.

---

## ⚙️ What This Lab Teaches
- Real sensor integration (DHT11)
- Live IoT telemetry systems
- HTTP POST communication
- Data logging backend

---

## 🧠 System Architecture

ESP8266 + DHT11 → HTTP POST → Flask Server → JSON Storage

---

## 📡 API Endpoint

### POST `/upload`

```json
{
  "device": "ESP8266",
  "temperature": 24.5,
  "humidity": 55.2
}
