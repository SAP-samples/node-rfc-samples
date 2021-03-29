// SH TCE_TRANSPORT_TARGET Transport Target of Request (5) : abap 2.2.0 at: 2021-03-29 15:40:08

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
  {"SH TCE_SYSTEMS":{"title":"Active Systems"}},
  {"SH TCE_CONSOLIDATION_TARGETS":{"title":"Consolidation Targets for the Current System"}},
  {"SH TCE_NEW_TRANSPORT_TARGETS":{"blacklist":{"search":"Screen output without connection to user."},"title":"Selection of a Transport Target"}},
  {"SH TCE_TARGET_SAP":{"title":"Only the Standard Transport Target SAP"}},
  {"SH TCE_OLD_TRANSPORT_TARGETS":{"blacklist":{"search":"Screen output without connection to user."},"title":"Selection of a Transport Target"}},
];