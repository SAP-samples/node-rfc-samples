// SH MCWEA Business entities : abap 2.2.0 at: 2021-04-14 18:36:59

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

const title = "Business entities";

const selectParams = [
  {
    FIELDNAME: "BUKRS",
    DATATYPE: "CHAR",
    LENG: 4,
    DECIMALS: 0,
    MEMORYID: "BUK"
  },
  {
    FIELDNAME: "SWENR",
    DATATYPE: "CHAR",
    LENG: 8,
    DECIMALS: 0,
    MEMORYID: "WEH"
  },
  {
    FIELDNAME: "XWETEXT",
    DATATYPE: "CHAR",
    LENG: 30,
    DECIMALS: 0,
  },
  {
    FIELDNAME: "OBJNR",
    DATATYPE: "CHAR",
    LENG: 22,
    DECIMALS: 0,
    MEMORYID: "ONR"
  },
  {
    FIELDNAME: "IMKEY",
    DATATYPE: "CHAR",
    LENG: 8,
    DECIMALS: 0,
  }
];