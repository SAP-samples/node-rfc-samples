// SH H_TPZ3 Business Partner Role Category : abap 2.2.0 at: 2021-04-14 18:32:56

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

const title = "Business Partner Role Category";

const selectParams = [
  {
    FIELDNAME: "ROLETYP",
    DATATYPE: "CHAR",
    LENG: 4,
    DECIMALS: 0,
    MEMORYID: "BPR"
  },
  {
    FIELDNAME: "XROLETYP",
    DATATYPE: "CHAR",
    LENG: 30,
    DECIMALS: 0,
  }
];