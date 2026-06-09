from flask import Flask, request, jsonify, render_template, send_file
import json
import os
from datetime import datetime
import csv

app = Flask(__name__)

DATA_FILE = "data/telemetry.json"
AUDIT_FILE = "logs/audit.log"
EXPORT_FILE = "exports/telemetry_export.csv"

os.makedirs("data", exist_ok=True)
os.makedirs("logs", exist_ok=True)
os.makedirs("exports", exist_ok=True)

# create files if missing
for f, default in [
    (DATA_FILE, "[]"),
    (AUDIT_FILE, "")
]:
    try:
        open(f, "x").write(default)
    except:
        pass


# ================= AUDIT LOG =================
def log_audit(message):
    with open(AUDIT_FILE, "a") as f:
        f.write(f"{datetime.now()} - {message}\n")


# ================= UPLOAD =================
@app.route("/upload", methods=["POST"])
def upload():

    data = request.json

    entry = {
        "timestamp": str(datetime.now()),
        "device_id": data.get("device_id"),
        "temperature": data.get("temperature"),
        "humidity": data.get("humidity")
    }

    with open(DATA_FILE, "r") as f:
        logs = json.load(f)

    logs.append(entry)

    with open(DATA_FILE, "w") as f:
        json.dump(logs, f, indent=2)

    log_audit(f"{entry['device_id']} uploaded telemetry")

    return jsonify({"status": "stored"})


# ================= DASHBOARD =================
@app.route("/")
def dashboard():
    return render_template("dashboard.html")


# ================= INVENTORY =================
@app.route("/inventory")
def inventory():
    return render_template("inventory.html")


# ================= HISTORY =================
@app.route("/history")
def history():
    with open(DATA_FILE, "r") as f:
        logs = json.load(f)
    return render_template("history.html", logs=logs)


# ================= AUDIT =================
@app.route("/audit")
def audit():
    with open(AUDIT_FILE, "r") as f:
        logs = f.readlines()
    return render_template("audit.html", logs=logs)


# ================= DEVICES =================
@app.route("/devices")
def devices():

    with open(DATA_FILE, "r") as f:
        logs = json.load(f)

    inventory = {}

    for l in logs:
        inventory[l["device_id"]] = {
            "last_seen": l["timestamp"],
            "temperature": l["temperature"],
            "humidity": l["humidity"]
        }

    return jsonify(inventory)


# ================= CSV EXPORT =================
@app.route("/export")
def export():

    with open(DATA_FILE, "r") as f:
        logs = json.load(f)

    with open(EXPORT_FILE, "w", newline="") as f:
        writer = csv.writer(f)

        writer.writerow(["timestamp","device_id","temperature","humidity"])

        for l in logs:
            writer.writerow([
                l["timestamp"],
                l["device_id"],
                l["temperature"],
                l["humidity"]
            ])

    return send_file(EXPORT_FILE, as_attachment=True)


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
