// SH GMGRANT_SPONSOR Search grants with sponsor : abap 2.2.0 at: 2021-04-14 18:36:59

const helpSign = [{ id: 'I', name: 'Include' }, { id: 'E', name: 'Exclude' }];
const helpOption = [
  { id: 'EQ', name: 'is' },
  { id: 'NE', name: 'is not' },
  { id: 'GT', name: 'greater than' },
  { id: 'LT', name: 'less than' },
  { id: 'GE', name: 'not less' },
  { id: 'LE', name: 'not greater' },
  { id: 'BT', name: 'between' },
  { id: 'NB', name: 'not between' },
  { id: 'CP', name: 'with pattern' },
  { id: 'NP', name: 'w/o pattern' }
];

const title = "Search grants with sponsor";

const selectParams = [
  {
    FIELDNAME: "GRANT_NBR",
    DATATYPE: "CHAR",
    LENG: 20,
    DECIMALS: 0,
    MEMORYID: "GM_GRANT_NBR"
  },
  {
    FIELDNAME: "COMPANY_CODE",
    DATATYPE: "CHAR",
    LENG: 4,
    DECIMALS: 0,
    MEMORYID: "BUK"
  },
  {
    FIELDNAME: "PARTNER",
    DATATYPE: "CHAR",
    LENG: 10,
    DECIMALS: 0,
    MEMORYID: "BPA"
  }
];