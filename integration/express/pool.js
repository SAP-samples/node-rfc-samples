// SPDX-FileCopyrightText: 2014 SAP SE Srdjan Boskovic <srdjan.boskovic@sap.com>
//
// SPDX-License-Identifier: Apache-2.0

const express = require("express");
const Pool = require("node-rfc").Pool;

// Generic ABAP Value Help API used in prototyping system
const SalesOrderAPI = {
    getList: "BAPI_SALESORDER_GETLIST",
    get: "BAPISDORDER_GETDETAILEDLIST",
    create: "BAPI_SALESORDER_CREATEFROMDAT2",
    update: "BAPI_SALESORDER_CHANGE",
    getStatus: "BAPI_SALESORDER_GETSTATUS",
    confirmDelivery: "BAPI_SALESORDER_CONFIRMDELVRY",
  },
  defaults = {
    username: "DEMO",
    CUSTOMER_NUMBER: "0000100000",
    SALES_ORGANIZATION: "1000",
    VBELN: "0000000087",
  };

const PORT = 3000;
const app = express();
let pool, client;

//app.use(express.json());
app.use(express.json());

app.all("*", (req, res, next) => {
  // cookie doesn't exist redirect to login
  if (client) {
    next();
  } else {
    if (req.url === "/login") {
      next();
    } else {
      res.json("Do the login first");
    }
    //res.redirect("/login");
  }
});

// Authenticate and open client connection
// Closed in /logout or automatically
app.route("/login").all(async (req, res) => {
  try {
    pool = new Pool(
      Object.keys(req.body) > 0
        ? req.body
        : { connectionParameters: { dest: "MME" } }
    );
    const username = req.body.username || defaults.username;
    client = await pool.acquire();
    const user = await client.call("BAPI_USER_GET_DETAIL", {
      USERNAME: username,
    });

    res.json("connected");
  } catch (ex) {
    res.json(ex.message);
  }
});

app
  .route(/^\/salesorder\/(getlist|get|create|update|status)?\/?$/i)
  .all(async (req, res) => {
    try {
      let selection, result;
      const path = req.path.toLowerCase().replace("/salesorder/", "");
      switch (path) {
        case "getlist":
          selection =
            Object.keys(req.body).length > 0
              ? {
                  CUSTOMER_NUMBER: req.body.CUSTOMER_NUMBER,
                  SALES_ORGANIZATION: req.body.SALES_ORGANIZATION,
                }
              : {
                  CUSTOMER_NUMBER: defaults.CUSTOMER_NUMBER,
                  SALES_ORGANIZATION: defaults.SALES_ORGANIZATION,
                };

          result = await client.call(SalesOrderAPI.getList, selection);
          break;

        case "get":
          const I_BAPI_VIEW = {
            HEADER: "X",
            ITEM: "X",
            SDSCHEDULE: "X",
            BUSINESS: "X",
            PARTNER: "X",
            ADDRESS: "X",
            STATUS_H: "X",
            STATUS_I: "X",
            SDCOND: "X",
            SDCOND_ADD: "X",
            CONTRACT: "X",
            TEXT: "X",
            FLOW: "X",
            BILLPLAN: "X",
            CONFIGURE: "X",
            CREDCARD: "X",
            INCOMP_LOG: "X",
          };

          selection =
            Object.keys(req.body).length > 0
              ? {
                  I_BAPI_VIEW: I_BAPI_VIEW,
                  SALES_DOCUMENTS: [{ VBELN: req.body.id }],
                }
              : {
                  I_BAPI_VIEW: I_BAPI_VIEW,
                  SALES_DOCUMENTS: [{ VBELN: defaults.VBELN }],
                };
          result = await client.call(SalesOrderAPI.get, selection);
          break;

        case "create":
          result = "todo";
          break;
        case "update":
          result = "todo";
          break;
        case "status":
          const selection = {
            SALESDOCUMENT:
              Object.keys(req.body).length > 0
                ? req.body.SALESDOCUMENT
                : defaults.VBELN,
          };
          result = await client.call(SalesOrderAPI.getStatus, selection);
          break;
        default:
          throw new Error(`Route not supported: ${req.path}`);
      }
      //res.json(result);
      res.header("Content-Type", "application/json");
      res.send(JSON.stringify(result, null, 4));
    } catch (ex) {
      console.log(ex);
      res.json(ex.message);
    }
  });

// Close the connection (optional)
app.route("/logout").all(async (req, res) => {
  if (pool && client.alive) await pool.release(client);
  res.json("disconnected");
});

app.listen(PORT, () =>
  console.log(
    "Sales Order API ready:",
    `\nhttp://localhost:${PORT}/login`,
    `\nhttp://localhost:${PORT}/salesorder/getlist`,
    `\nhttp://localhost:${PORT}/salesorder/get`,
    `\nhttp://localhost:${PORT}/salesorder/create`,
    `\nhttp://localhost:${PORT}/salesorder/update`,
    `\nhttp://localhost:${PORT}/salesorder/status`,
    `\nhttp://localhost:${PORT}/logout`
  )
);
