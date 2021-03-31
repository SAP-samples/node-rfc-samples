// SPDX-FileCopyrightText: 2014 SAP SE Srdjan Boskovic <srdjan.boskovic@sap.com>
//
// SPDX-License-Identifier: Apache-2.0

import noderfc from "node-rfc";

const pool = new noderfc.Pool({ connectionParameters: { dest: "MME" } });

(async () => {
  try {
    // get a client connection instance
    const client = await pool.acquire();

    // invoke ABAP function module, passing structure and table parameters

    // ABAP structure
    const abap_structure = {
      RFCINT4: 345,
      RFCFLOAT: 1.23456789,
      RFCCHAR4: "ABCD",
      RFCDATE: "20180625", // ABAP date format
      // or RFCDATE: new Date('2018-06-25'), // as JavaScript Date object, with clientOption "date"
    };
    // ABAP table
    let abap_table = [abap_structure];

    const result = await client.call("STFC_STRUCTURE", {
      IMPORTSTRUCT: abap_structure,
      RFCTABLE: abap_table,
    });

    // check the result
    console.log(result);
  } catch (err) {
    // connection and invocation errors
    console.error(err);
  }
})();
