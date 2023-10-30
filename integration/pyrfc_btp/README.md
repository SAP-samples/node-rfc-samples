# Python buildpack with flask, PyRFC and SAP NW RFC SDK

[ABAP RFC connectivity from BTP Python buildpack](https://blogs.sap.com/?p=1868795)

## Preparation

1. Copy SAP NW RFC SDK Linux x64 files to  `app` folder and exclude (gitignore) them from repository
2. Add SAP NW RFC SDK folder to app MANIFEST.in file
3. Add PyRFC Linux x64 wheel url to `requirements.txt`
4. Add paths to SAP NW RFC SDK in app `manifest.yaml`

Done.
