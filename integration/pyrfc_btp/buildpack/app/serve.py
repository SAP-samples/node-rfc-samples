import os

from flask import Flask
from pyrfc import Connection
from pyrfc import __version__ as pyrfc_version

app = Flask(__name__)
port = int(os.environ.get("PORT", 3000))


@app.route("/user/<user_id>")
def get_user(user_id):
    try:
        client = Connection(dest="MME")
        result = client.call("BAPI_USER_GET_DETAIL", USERNAME=user_id)
        return result
    except Exception:
        return


@app.route("/")
def hello():
    return f"pyrfc: {pyrfc_version}"


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=port)
