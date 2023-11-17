import os

from flask import Flask, jsonify
from pyrfc import Connection
from pyrfc import __version__ as pyrfc_version

app = Flask(__name__)
port = int(os.environ.get("PORT", 3000))


@app.route("/dest/<dest_id>")
def get_dest(dest_id="MME"):
    try:
        client = Connection(dest=dest_id)
        result = client.call("BAPI_USER_GET_DETAIL", USERNAME="MME-TECH-02")
        return jsonify(result)
    except Exception as ex:
        print(ex)
        return jsonify({"error": str(ex)})


@app.route("/")
def hello():
    return f"pyrfc: {pyrfc_version}"


if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True, port=port)
