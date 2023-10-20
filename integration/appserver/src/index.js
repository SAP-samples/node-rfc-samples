const express = require("express");
// const rfc = require("node-rfc");
const fs = require("fs");
const path = require("path");
const app = express();

function envars() {
  return (
    `HOME: ${process.env.HOME}` +
    ` SAPNWRFC_HOME: ${process.env.SAPNWRFC_HOME}` +
    ` LD_LIBRARY_PATH ${process.env.LD_LIBRARY_PATH}` +
    ` filenames: ${JSON.stringify(filenames)}` +
    ` dirPath: ${directoryPath}`
  );
}

const directoryPath = path.join(__dirname, "nwrfcsdk"); // process.env.SAPNWRFC_HOME;
const filenames = fs.readdirSync(directoryPath);

app.get("/", function (req, res) {
  res.send(envars());
});

const port = process.env.PORT || 3000;
app.listen(port, function () {
  console.log(envars());
});
