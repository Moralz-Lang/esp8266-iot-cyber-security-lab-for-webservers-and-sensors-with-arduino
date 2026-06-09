from flask import Flask, request, jsonify
from datetime import datetime
import json

app = Flask(__name__)

DATA_FILE = "test_data.json"

# create file if not exists
try:
    open(DATA_FILE, "x").write("[]")
except:
    pass


@app.route("/upload", methods=["POST"])
def upload():

    data = request.json

    entry = {
        "timestamp": str(datetime.now()),
        "device": data.get("device"),
        "temperature": data.get("temperature"),
        "humidity": data.get("humidity")
    }

    with open(DATA_FILE, "r") as f:
        logs = json.load(f)

    logs.append(entry)

    with open(DATA_FILE, "w") as f:
        json.dump(logs, f, indent=2)

    return jsonify({"status": "saved"})


@app.route("/data")
def data():

    with open(DATA_FILE, "r") as f:
        return jsonify(json.load(f))


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
