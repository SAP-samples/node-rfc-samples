// SH QALS Inspection Lot Number (9) : abap 2.2.0 at: 2021-03-29 15:40:08

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
  {"SH QALSM":{"title":"Material"}},
  {"SH QALSK":{"title":"Vendor"}},
  {"SH QALSD":{"title":"Customers"}},
  {"SH QALSV":{"title":"Goods Movement"}},
  {"SH QALSA":{"title":"Orders"}},
  {"SH QALSS":{"title":"Delivery"}},
  {"SH QALST":{"title":"Inspection Lot Short Text"}},
  {"SH QALSARC":{"title":"Inspection Lot Using Archive"}},
  {"SH QALSL":{"blacklist":{"search":"Screen output without connection to user."},"title":"Detailed Selection"}},
];