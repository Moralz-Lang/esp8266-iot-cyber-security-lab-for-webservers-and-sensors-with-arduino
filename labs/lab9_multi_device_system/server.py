from flask import Flask, request, jsonify, render_template
import json
import os
from datetime import datetime

app = Flask(__name__)

DATA_FILE = "data/telemetry.json"

os.makedirs("data", exist_ok=True)

try:
    open(DATA_FILE, "x").write("[]")
except:
    pass


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

    return jsonify({"status": "saved"})


# ================= DASHBOARD =================
@app.route("/")
def dashboard():
    return render_template("dashboard.html")


# ================= INVENTORY =================
@app.route("/inventory")
def inventory():
    return render_template("inventory.html")


# ================= LATEST =================
@app.route("/latest")
def latest():

    with open(DATA_FILE, "r") as f:
        logs = json.load(f)

    return jsonify(logs[-1] if logs else {})


# ================= DEVICES LIST =================
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


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
