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

client.open((err) => {
  if (err) return console.error(err);

  client.invoke(
    "RFC_PING_AND_WAIT",
    {
      SECONDS: WAIT,
    },
    (err, res) => {
      if (err) {
        console.error("err", err, client.alive, client.connectionHandle);
        // {
        //   name: 'RfcLibError',
        //   group: 4,
        //   code: 7,
        //   codeString: 'RFC_CANCELED',
        //   key: 'RFC_CANCELED',
        //   message: 'Connection was canceled.'
        // }
      } else {
        console.log("done", res);
      }
    }
    // { timeout: TIMEOUT } // overrides client timeout
  );
});
