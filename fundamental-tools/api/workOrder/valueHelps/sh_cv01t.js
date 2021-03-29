// SH CV01T Matchcode via description : abap 2.2.0 at: 2021-03-29 15:40:08

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

const selectParams = [
  {
    FIELDNAME: "DOKAR",
    DATATYPE: "CHAR",
    LENG: 3,
    DECIMALS: 0,
    MEMORYID: "CV2"
  },
  {
    FIELDNAME: "DOKNR",
    DATATYPE: "CHAR",
    LENG: 25,
    DECIMALS: 0,
    MEMORYID: "CV1"
  },
  {
    FIELDNAME: "DOKVR",
    DATATYPE: "CHAR",
    LENG: 2,
    DECIMALS: 0,
    MEMORYID: "CV3"
  },
  {
    FIELDNAME: "DOKTL",
    DATATYPE: "CHAR",
    LENG: 3,
    DECIMALS: 0,
    MEMORYID: "CV4"
  },
  {
    FIELDNAME: "LANGU",
    DATATYPE: "LANG",
    LENG: 1,
    DECIMALS: 0,
  },
  {
    FIELDNAME: "DKTXT",
    DATATYPE: "CHAR",
    LENG: 40,
    DECIMALS: 0,
  },
  {
    FIELDNAME: "DKTXT_UC",
    DATATYPE: "CHAR",
    LENG: 40,
    DECIMALS: 0,
  },
];