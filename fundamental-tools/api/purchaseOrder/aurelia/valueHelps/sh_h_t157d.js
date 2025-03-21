// SH H_T157D Reason for Movement : abap 2.2.0 at: 2021-04-14 18:32:56

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

const title = "Reason for Movement";

const selectParams = [
  {
    FIELDNAME: "BWART",
    DATATYPE: "CHAR",
    LENG: 3,
    DECIMALS: 0,
    MEMORYID: "BWA"
  },
  {
    FIELDNAME: "GRUND",
    DATATYPE: "NUMC",
    LENG: 4,
    DECIMALS: 0,
  },
  {
    FIELDNAME: "GRTXT",
    DATATYPE: "CHAR",
    LENG: 20,
    DECIMALS: 0,
  }
];