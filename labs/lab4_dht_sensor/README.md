# 🧪 Lab 4 — DHT Sensor Integration (Real IoT Data)

## 🎯 Objective
Connect a real DHT11/DHT22 sensor to ESP8266 and output live temperature and humidity via API.

---

## ⚙️ What This Lab Teaches
- Sensor integration (DHT11/DHT22)
- Real-world IoT telemetry
- Reading analog/digital sensor data
- API output with live values

---

## 🔌 Hardware Required
- NodeMCU ESP8266
- DHT11 or DHT22 sensor
- Jumper wires

---

## 📡 API Endpoint

### `/api`

Example response:

```json
{
  "device": "ESP8266",
  "temperature": 25.3,
  "humidity": 60.2,
  "status": "active"
}
