// SH H_TJ02 Lifecycle Status : abap 2.2.0 at: 2021-04-14 18:31:25

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

const title = "Lifecycle Status";

const selectParams = [
  {
    FIELDNAME: "ISTAT",
    DATATYPE: "CHAR",
    LENG: 5,
    DECIMALS: 0,
  },
  {
    FIELDNAME: "TXT04",
    DATATYPE: "CHAR",
    LENG: 4,
    DECIMALS: 0,
  },
  {
    FIELDNAME: "TXT30",
    DATATYPE: "CHAR",
    LENG: 30,
    DECIMALS: 0,
  }
];