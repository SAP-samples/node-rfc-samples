// SH AANLP Investment Projects : abap 2.2.0 at: 2021-04-14 18:32:56

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

const title = "Investment Projects";

const selectParams = [
  {
    FIELDNAME: "POSID",
    DATATYPE: "CHAR",
    LENG: 24,
    DECIMALS: 0,
    MEMORYID: "PRO"
  },
  {
    FIELDNAME: "ANLKL",
    DATATYPE: "CHAR",
    LENG: 8,
    DECIMALS: 0,
    MEMORYID: "ANK"
  },
  {
    FIELDNAME: "MCOA1",
    DATATYPE: "CHAR",
    LENG: 30,
    DECIMALS: 0,
  },
  {
    FIELDNAME: "ANLN1",
    DATATYPE: "CHAR",
    LENG: 12,
    DECIMALS: 0,
    MEMORYID: "AN1"
  },
  {
    FIELDNAME: "ANLN2",
    DATATYPE: "CHAR",
    LENG: 4,
    DECIMALS: 0,
    MEMORYID: "AN2"
  },
  {
    FIELDNAME: "BUKRS",
    DATATYPE: "CHAR",
    LENG: 4,
    DECIMALS: 0,
    MEMORYID: "BUK"
  },
  {
    FIELDNAME: "POSNR",
    DATATYPE: "NUMC",
    LENG: 8,
    DECIMALS: 0,
  }
];