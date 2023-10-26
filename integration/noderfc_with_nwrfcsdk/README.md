# Node.JS buildpack with express, node-rfc and SAP NW RFC SDK

[Express](https://expressjs.com/) server with [node-rfc](https://github.com/sap/node-rfc) requires SAP NW RFC SDK shared SO libraries, to be registered in buildpack runtime. During deployment on BTP, the rebuild of node-rfc and other native modules can be triggered. In that case, the node-rfc rebuild also requires SAP NW RFC SDK shared SO libraries and include files.

One possibility to include SAP NW RFC SDK is [custom buildpack](https://docs.cloudfoundry.org/buildpacks/custom.html), with SAP NW RFC SDK added. Another possibility is using standard buildpack and modified SAP/node-rfc, with SAP NW RFC SDK included.

The first approach is described in CF documentation [Creating custom buildpacks for Cloud Foundry](https://docs.cloudfoundry.org/buildpacks/custom.html) and the second approach, with less efforts, is described here. Modified SAP/node-rfc, with SAP NW RFC SDK added, can be also used with other server frameworks.

> **_NOTE_** SAP NW RFC SDK is **not** included in standard [node-rfc](https://github.com/sap/node-rfc) because the license is different. The only public distribution channel for SAP NW RFC SDK is SAP Support Portal.

## Preparation

Copy SAP NW RFC SDK for Linux 64 to application `app` folder and clone SAP/node-rfc in that same `app` folder. After both steps done, the buildpack looks like:

```shell
$ cd buildpack/app
$ # copy SAP NW RFC SDK here
$ git clone https://github.com/sap/node-rfc

$ cd buildpack
$ tree -L 2

├── manifest.yaml
└── src
    ├── index.js
    ├── node_modules
    ├── node-rfc
    ├── nwrfcsdk
    ├── package.json
    └── package-lock.json
```

## NPM package with SAP NW RFC SDK

To make SAP NW RFC SDK available in SAP/node-rfc (re)build time, it shall be added to SAP/node-rfc dependencies. The NW RFC SDK is therefore "promoted" to local NPM package, by adding [package.json](./buildpack/app/nwrfcsdk/package.json) file in [nwrfcsdk](./buildpack/app/nwrfcsdk) folder

```json
{
    "name": "nwrfcsdk",
    "version": "1.0.0",
    "description": "SAP NW RFC SDK",
    "files": [
        "nwrfcsdk"
    ],
    "author": "",
    "license": "SAP Developer License"
}`
```

The `nwrfcsdk` package is then added to SAP/node-rfc [package.json](./buildpack/app/node-rfc/package.json) dependencies:

```json
  "dependencies": {
    "bluebird": "^3.7.2",
    "decimal.js": "^10.4.3",
    "node-addon-api": "^6.1.0",
    "node-gyp-build": "^4.6.0",
    "nwrfcsdk": "file:../nwrfcsdk"
  },
```

When node-rfc is installed on BTP, the `nwrfcsdk` package will be pulled as dependency and added to application node modules. The RFC SDK shared libraries from that location shall be therefore registered for buildpack and application runtime, using `LD_LIBRARY_PATH` env variable

manifest.yaml

```yaml
---
applications:
  - name: rfcapp
    stack: cflinuxfs4
    env:
      LD_LIBRARY_PATH: /home/vcap/app/node_modules/nwrfcsdk/lib
```

Now let prepare SAP/node-rfc for deployment. During deployment native NPM modules like SAP/node-rfc may be or must be re-built. The re-build will first install `nwrfcsdk` and other dependencies and the build process must be able to find `nwrfcsdk` include files and shared SO libraries. The node-rfc standard build process uses `SAPNWRFC_HOME` env variable for that, pointing to SAP NW RFC SDK root folder. I could not find the way to provide env variable during deployment, seems possible with custom buildpack only. Therefore following steps are done.

First node-rfc dependencies are installed, with SAPNWRFC_HOME env variable set to local RFC SDK root folder. It can point to `nwrfcsdk` in buildpack or to other location, if already set in your cflinuxfs4 system. Let say we use the RFC SDK from buildpack and set

```shell
export SAPNWRFC_HOME=/home/btp-developer/node-rfc-samples/integration/noderfc_with_nwrfcsdk/buildpack/app/nwrfcsdk
export LD_LIBRARY_PATH=$SAPNWRFC_HOME/lib
```

Now install node-rfc dependencies and build the package:

```shell
cd node-rfc
npm install
npm run build
```

The node-rfc re-build during deployment would now fail because SAPNWRFC_HOME env variable is not available on BTP during deployment. The `node-rfc/binding.gyp` must be therefore modified, to point to `nwrfcsdk` package location during deployment, which is temporary `node_modules` folder on BTP. The `binding.gyp` is therefore modified as follows

```gyp
'variables': {
    #'nwrfcsdk_dir': '<!(echo $SAPNWRFC_HOME)',
    'nwrfcsdk_dir': '/tmp/app/node_modules/nwrfcsdk',
```

Now, the modified node-rfc can be installed and used in application for local testing and can be deployed on BTP

```shell
cd buildpack/app
npm install
```

