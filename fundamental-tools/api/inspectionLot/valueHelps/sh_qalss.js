// SH QALSS Delivery : abap 2.2.0 at: 2021-03-29 15:40:08

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
    FIELDNAME: "LS_VBELN",
    DATATYPE: "CHAR",
    LENG: 10,
    DECIMALS: 0,
    MEMORYID: "VL"
  },
  {
    FIELDNAME: "LS_POSNR",
    DATATYPE: "NUMC",
    LENG: 6,
    DECIMALS: 0,
  },
  {
    FIELDNAME: "PRUEFLOS",
    DATATYPE: "NUMC",
    LENG: 12,
    DECIMALS: 0,
    MEMORYID: "QLS"
  },
];