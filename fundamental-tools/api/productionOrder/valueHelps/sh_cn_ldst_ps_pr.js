// SH CN_LDST_PS_PR WBS Element, Short Text : abap 2.2.0 at: 2021-03-29 15:40:08

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
    FIELDNAME: "LANGUAGE",
    DATATYPE: "LANG",
    LENG: 1,
    DECIMALS: 0,
    MEMORYID: "SPR"
  },
  {
    FIELDNAME: "PSPID",
    DATATYPE: "CHAR",
    LENG: 24,
    DECIMALS: 0,
    MEMORYID: "PSP"
  },
  {
    FIELDNAME: "POSID",
    DATATYPE: "CHAR",
    LENG: 24,
    DECIMALS: 0,
    MEMORYID: "PRO"
  },
  {
    FIELDNAME: "SHORTTEXT",
    DATATYPE: "CHAR",
    LENG: 40,
    DECIMALS: 0,
  },
  {
    FIELDNAME: "SHORTTEXTU",
    DATATYPE: "CHAR",
    LENG: 40,
    DECIMALS: 0,
  },
];