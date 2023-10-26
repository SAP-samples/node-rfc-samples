const express = require("express");
const rfc = require("node-rfc");
const fs = require("fs");
const app = express();

const directoryPath = process.env.SAPNWRFC_HOME;
const filenames = fs.readdirSync(directoryPath);

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

app.get("/", function (req, res) {
  res.send(environment());
});

const port = process.env.PORT || 3000;
app.listen(port, function () {
  console.log(environment());
});
