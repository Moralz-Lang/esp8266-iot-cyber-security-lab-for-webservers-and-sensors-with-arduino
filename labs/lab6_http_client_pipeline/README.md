# 🧪 Lab 6 — HTTP Client Telemetry System

## 🎯 Objective
Send IoT sensor data from ESP8266 to a PC server using HTTP POST requests.

---

## ⚙️ What This Lab Teaches
- HTTP client requests
- JSON data transfer
- IoT backend communication
- Client-server architecture

---

## 🖥️ System Architecture

ESP8266 → WiFi → Flask Server → JSON Storage

---

## 📡 API Endpoint

### POST `/upload`

Example payload:
```json
{
  "device": "ESP8266",
  "temperature": 25,
  "humidity": 60
}
```

---
## 🧠 WHAT THIS LAB DOES

* ✔ ESP8266 connects to WiFi
* ✔ Sends JSON telemetry to PC
* ✔ PC receives and logs data
* ✔ First real IoT “device → server” pipeline

---
