// SH QMTB Inspection Method (6) : abap 2.2.0 at: 2021-03-29 15:40:08

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

const helpSelector = [
  {"SH QMTBS":{"title":"Inspection Method for Search Field"}},
  {"SH QMTBC":{"blacklist":{"search":"Screen output without connection to user."},"title":"Inspection Method for Class"}},
  {"SH QMTB_TREX_SIMPLE":{"title":"Quick Search for Inspection Method Via Search Engine"}},
  {"SH QMTB_TREX_ADVANCED":{"title":"Advanced Search for Inspection Method Via Search Engine"}},
  {"SH QMTB_ES_SIMPLE":{"title":"Simple Search for Inspection Method using Search Engine"}},
  {"SH QMTB_ES_ADVANCED":{"title":"Advanced Search for Inspection Method using Search Engine"}},
];