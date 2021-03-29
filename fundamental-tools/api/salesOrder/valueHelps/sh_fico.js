// SH FICO Financial Management Area (10) : abap 2.2.0 at: 2021-03-29 15:40:08

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
  {"SH PSM_FUND_TREX_QUICK":{"title":"Quick Search for Fund"}},
  {"SH PSM_FUND_TREX_QUICK_SUB":{"title":"Quick Search for Fund"}},
  {"SH PSM_FUND_TREX_ADV":{"title":"Advanced Search for Fund"}},
  {"SH PSM_FUND_TREX_ADV_SUB":{"title":"Advanced Search for Fund"}},
  {"SH FICOC":{"title":"Search Using Name"}},
  {"SH FICOO":{"title":"Search via customer"}},
  {"SH FICOV":{"title":"Search Using Attributes"}},
  {"SH FICOK":{"blacklist":{"search":"Screen output without connection to user."},"title":"Search using classification"}},
  {"SH FICOCO":{"title":"Search with Controlling Area"}},
  {"SH FMMD_SHLP_FICO_SUBSTRINGS":{"title":"Search Using Substrings"}},
];