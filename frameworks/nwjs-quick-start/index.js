// SPDX-FileCopyrightText: 2014 SAP SE Srdjan Boskovic <srdjan.boskovic@sap.com>
//
// SPDX-License-Identifier: Apache-2.0

const Client = require("node-rfc").Client;
const client = new Client({ DEST: "MME" });
const onClick = () => {
  alert(`node-rfc:  ${client.version.binding}`);
};
