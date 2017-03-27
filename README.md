# nodeginx

Node.js in an nginx module.

**This is not ready for any type of actual use, but pull requests are welcome!**

1. Make sure Node is available as a shared library. This repo contains `libnode.51.dylib` for macOS.
2. Build this project as a nginx dynamic module.
3. When built successfully, a `nodeginx` directive is available in your nginx config. This will execute a Node.js script. The module `#define`'s `NODE_MODULE_PATH`, which points to `"/tmp/handler.js"`. Note that this file must be accessible by the user running the nginx worker threads. Unfortunately, in it's current state, Node will crash on every other request. This is because it hits an assertion in V8 due to the platform already being initialized. I told you it's not ready for use yet :-)
