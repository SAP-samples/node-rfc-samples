// SH MEKKD Purchase Orders per PO Date : abap 2.2.0 at: 2021-04-14 18:32:56

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

const title = "Purchase Orders per PO Date";

const selectParams = [
  {
    FIELDNAME: "BSTYP",
    DATATYPE: "CHAR",
    LENG: 1,
    DECIMALS: 0,
  },
  {
    FIELDNAME: "BEDAT",
    DATATYPE: "DATS",
    LENG: 8,
    DECIMALS: 0,
  },
  {
    FIELDNAME: "EBELN",
    DATATYPE: "CHAR",
    LENG: 10,
    DECIMALS: 0,
    MEMORYID: "BES"
  }
];