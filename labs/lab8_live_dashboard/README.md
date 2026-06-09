# 🧪 Lab 8 — Live IoT Dashboard

## 🎯 Objective
Build a real-time web dashboard that displays live IoT sensor data.

---

## ⚙️ What This Lab Teaches
- Web dashboards for IoT
- Real-time data updates
- Frontend + backend integration
- Live telemetry visualization

---

## 🧠 Architecture

ESP8266 → Flask API → JSON Storage → Web Dashboard

ESP8266 (FROM LAB 7 COMPATIBLE)

No change needed — reuse Lab 7 firmware.

Just ensure:

POST → http://YOUR_PC_IP:port/upload
---

## 🌐 Features

- Live temperature display
- Live humidity display
- Auto-refresh every 3 seconds
- Latest device status view

---

## 🚀 Run Instructions

### Start server
```bash id="run8"
pip install flask
python server.py
