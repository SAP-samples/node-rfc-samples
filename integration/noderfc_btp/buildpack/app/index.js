const express = require("express");
const rfc = require("node-rfc");
const fs = require("fs");
const app = express();

const directoryPath = process.env.SAPNWRFC_HOME;
const filenames = directoryPath ? fs.readdirSync(directoryPath) : [];
function environment() {
  return [
    "HOME",
    process.env.HOME,
    "\nSAPNWRFC_HOME",
    process.env.SAPNWRFC_HOME,
    "\nSAPNWRFC_HOME files:",
    JSON.stringify(filenames),
    "\nLD_LIBRARY_PATH",
    process.env.LD_LIBRARY_PATH,
    "\nnode-rfc",
    JSON.stringify(rfc.environment, null, 4),
  ].join("\n");
}

app.use(express.json());

const rfcPool = new rfc.Pool({ connectionParameters: { dest: "MME" } });

app.route("/user/:userId").all(async (req, res) => {
  try {
    const rfcClient = await rfcPool.acquire();
    const user = await rfcClient.call("BAPI_USER_GET_DETAIL", {
      USERNAME: req.params.userId || "DEMO",
    });
    res.send(JSON.stringify(user, null, 4));
  } catch (ex) {
    res.json(ex.message);
  }
});

app.get(["", "/"], function (req, res) {
  res.send(environment());
});

const port = process.env.PORT || 3100;
const server = app.listen(port, async function (port) {
  try {
    const host = server.address().address;
    const port = server.address().port;
    console.log(`Server running on http://${host}:${port}`);
    console.log(environment());
  } catch (ex) {
    console.log(ex);
  }
});
