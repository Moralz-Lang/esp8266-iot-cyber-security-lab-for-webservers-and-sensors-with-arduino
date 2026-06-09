from flask import Flask, request, jsonify, render_template
import json
import os

app = Flask(__name__)

DATA_FILE = "data/telemetry.json"

os.makedirs("data", exist_ok=True)

try:
    open(DATA_FILE, "x").write("[]")
except:
    pass


@app.route("/")
def dashboard():
    return render_template("dashboard.html")


@app.route("/upload", methods=["POST"])
def upload():

    data = request.json

    with open(DATA_FILE, "r") as f:
        logs = json.load(f)

    logs.append(data)

    with open(DATA_FILE, "w") as f:
        json.dump(logs, f, indent=2)

    return jsonify({"status": "ok"})


@app.route("/latest")
def latest():

    with open(DATA_FILE, "r") as f:
        logs = json.load(f)

    if not logs:
        return jsonify({"status": "no data"})

    return jsonify(logs[-1])


@app.route("/data")
def data():

    with open(DATA_FILE, "r") as f:
        return jsonify(json.load(f))


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
