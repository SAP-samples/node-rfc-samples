import { Pool, sapnwrfcEvents } from "node-rfc";

// parse command line arguments to numbers
const [WAIT, TIMEOUT] = process.argv.slice(2).map((e) => {
  return Number(e);
});

sapnwrfcEvents.on("sapnwrfc:clientCancel", (data) =>
  console.log("event", data)
);
// event { id: 1, connectionHandle: 140576595093504

const pool = new Pool({
  connectionParameters: { dest: "MME" },
  clientOptions: { timeout: TIMEOUT },
});

(async () => {
  let client;
  try {
    client = await pool.acquire();

    const res = await client.call(
      "RFC_PING_AND_WAIT",
      {
        SECONDS: WAIT,
      }
      // { timeout: TIMEOUT } // overrides client timeout
    );

    console.log("done", res, pool.status);
  } catch (err) {
    console.error(
      "err",
      err,
      client.alive,
      client.connectionHandle,
      pool.status
    );
    // {
    //   name: 'RfcLibError',
    //   group: 4,
    //   code: 7,
    //   codeString: 'RFC_CANCELED',
    //   key: 'RFC_CANCELED',
    //   message: 'Connection was canceled.'
    // }
  }
})();
