// SH MEKKN Purchasing Documents per Network : abap 2.2.0 at: 2021-04-14 18:31:25

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

const title = "Purchasing Documents per Network";

const selectParams = [
  {
    FIELDNAME: "NPLNR",
    DATATYPE: "CHAR",
    LENG: 12,
    DECIMALS: 0,
    MEMORYID: "NET"
  },
  {
    FIELDNAME: "AUFPL",
    DATATYPE: "NUMC",
    LENG: 10,
    DECIMALS: 0,
  },
  {
    FIELDNAME: "APLZL",
    DATATYPE: "NUMC",
    LENG: 8,
    DECIMALS: 0,
  },
  {
    FIELDNAME: "BSTYP",
    DATATYPE: "CHAR",
    LENG: 1,
    DECIMALS: 0,
  },
  {
    FIELDNAME: "EKORG",
    DATATYPE: "CHAR",
    LENG: 4,
    DECIMALS: 0,
    MEMORYID: "EKO"
  },
  {
    FIELDNAME: "EBELN",
    DATATYPE: "CHAR",
    LENG: 10,
    DECIMALS: 0,
    MEMORYID: "BES"
  },
  {
    FIELDNAME: "EBELP",
    DATATYPE: "NUMC",
    LENG: 5,
    DECIMALS: 0,
    MEMORYID: "BSP"
  },
  {
    FIELDNAME: "ZEKKN",
    DATATYPE: "NUMC",
    LENG: 2,
    DECIMALS: 0,
  }
];