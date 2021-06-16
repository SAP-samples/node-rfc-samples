import { Client, sapnwrfcEvents } from "node-rfc";

// parse command line arguments to numbers
const [WAIT, TIMEOUT] = process.argv.slice(2).map((e) => {
  return Number(e);
});

sapnwrfcEvents.on("sapnwrfc:clientCancel", (data) =>
  console.log("event", data)
);
// event { id: 1, connectionHandle: 140576595093504

const client = new Client({ dest: "MME" }, { timeout: TIMEOUT });

client
  .open()
  .then((client) => {
    client
      .call(
        "RFC_PING_AND_WAIT",
        {
          SECONDS: WAIT,
        }
        // { timeout: TIMEOUT } // overrides client timeout
      )
      .then((res) => {
        console.log("done", res);
      })
      .catch((err) => {
        console.error("err", err, client.alive, client.connectionHandle);
        // {
        //   name: 'RfcLibError',
        //   group: 4,
        //   code: 7,
        //   codeString: 'RFC_CANCELED',
        //   key: 'RFC_CANCELED',
        //   message: 'Connection was canceled.'
        // }
      });
  })
  .catch((ex) => {
    console.error(ex);
  });
