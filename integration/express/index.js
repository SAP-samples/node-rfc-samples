// SPDX-FileCopyrightText: 2014 SAP SE Srdjan Boskovic <srdjan.boskovic@sap.com>
//
// SPDX-License-Identifier: Apache-2.0

const express = require("express"),
  Pool = require("node-rfc").Pool,
  cookieParser = require("cookie-parser"),
  session = require("express-session"),
  uuid = require("uuid"),
  log = require("loglevel");

// trace the flow
log.setDefaultLevel(
  process.argv[2] === "-d" ? log.levels.DEBUG : log.levels.SILENT
);

// Sales Order API
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

const PORT = 3000,
  app = express(),
  Connections = new Map();

app.use(
  express.json(),
  cookieParser(),
  session({
    secret: uuid.v1(),
    resave: false,
    saveUninitialized: true,
  })
);

let pool;

console.log(process.argv);

app.all("*", (req, res, next) => {
  if (req.cookies["user.session"]) {
    log.debug(req.cookies);
    log.debug(Connections);
    req.rfcClient = Connections.get(req.cookies["user.session"]);
    next();
  } else {
    if (req.url === "/login") {
      next();
    } else {
      res.json("Do the login first");
      // res.redirect("/login");
    }
  }
});

// Authenticate and open client connection
// Closed in /logout or automatically
app.route("/login").all(async (req, res) => {
  const username = req.body.username || defaults.username;
  if (req.rfcClient) {
    res.json(`${username} already logged in`);
  } else {
    try {
      if (!pool) {
        pool = new Pool(
          Object.keys(req.body) > 0
            ? req.body
            : { connectionParameters: { dest: "MME" } }
        );
      }
      const rfcClient = await pool.acquire();
      const user = await rfcClient.call("BAPI_USER_GET_DETAIL", {
        USERNAME: username,
      });
      const userSession = `${username}:${req.sessionID}`,
        result = {
          userSession: userSession,
          client: rfcClient.connectionHandle,
          status: "connected",
        };
      Connections.set(userSession, rfcClient);
      res.cookie("user.session", userSession, {
        maxAge: 1000 * 60 * 15, // expires in 15 min
        httpOnly: true,
        signed: false,
      });

      log.debug(req.cookies);
      log.debug(Connections);

      //res.json(user.PARAMETER);
      res.header("Content-Type", "application/json");
      res.send(JSON.stringify(result, null, 4));
    } catch (ex) {
      res.json(ex.message);
    }
  }
});

// Sales Order
app
  .route(/^\/salesorder\/(getlist|get|create|update|status)?\/?$/i)
  .all(async (req, res) => {
    let select, result;
    try {
      const path = req.path.toLowerCase().replace("/salesorder/", "");
      switch (path) {
        case "getlist": {
          select =
            Object.keys(req.body).length > 0
              ? {
                  CUSTOMER_NUMBER: req.body.CUSTOMER_NUMBER,
                  SALES_ORGANIZATION: req.body.SALES_ORGANIZATION,
                }
              : {
                  CUSTOMER_NUMBER: defaults.CUSTOMER_NUMBER,
                  SALES_ORGANIZATION: defaults.SALES_ORGANIZATION,
                };

          result = await req.rfcClient.call(SalesOrderAPI.getList, select);
          break;
        }

        case "get": {
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

          select =
            Object.keys(req.body).length > 0
              ? {
                  I_BAPI_VIEW: I_BAPI_VIEW,
                  SALES_DOCUMENTS: [{ VBELN: req.body.id }],
                }
              : {
                  I_BAPI_VIEW: I_BAPI_VIEW,
                  SALES_DOCUMENTS: [{ VBELN: defaults.VBELN }],
                };
          result = await req.rfcClient.call(SalesOrderAPI.get, select);
          break;
        }
        case "create": {
          result = "todo";
          break;
        }
        case "update": {
          result = "todo";
          break;
        }
        case "status": {
          const select = {
            SALESDOCUMENT:
              Object.keys(req.body).length > 0
                ? req.body.SALESDOCUMENT
                : defaults.VBELN,
          };
          result = await req.rfcClient.call(SalesOrderAPI.getStatus, select);
          break;
        }
        default: {
          throw new Error(`Route not supported: ${req.path}`);
        }
      }
      //res.json(result);
      res.header("Content-Type", "application/json");
      res.send(JSON.stringify(result, null, 4));
    } catch (ex) {
      log.info(ex);
      res.json(ex.message);
    }
  });

// Close the connection (optional)
app.route("/logout").all(async (req, res) => {
  let result = "disconneted";
  if (pool && req.rfcClient && req.rfcClient.alive) {
    const C = Connections.get(req.sessionID);
    result = {
      userSession: req.cookies["user.session"],
      client: req.rfcClient.connectionHandle,
      status: "disconnected",
    };
    await pool.release(req.rfcClient);
    Connections.delete(req.cookies["user.session"]);
    res.cookie("user.session", "", { expires: new Date(0) });
    log.debug(req.cookies);
    log.debug(Connections);
  }
  //res.json(result);
  res.header("Content-Type", "application/json");
  res.send(JSON.stringify(result, null, 4));
});

// Server
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
