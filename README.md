## Not supported features (TODO)
- FLS, now fallback to TLS
- [Expanding wildcard arguments](https://learn.microsoft.com/en-us/cpp/c-language/expanding-wildcard-arguments), now cannot enable link options (`setargv.obj` or `wsetargv.obj`)
- [Global State Isolation](https://learn.microsoft.com/en-us/cpp/c-runtime-library/global-state), now `_CRT_GLOBAL_STATE_ISOLATION` cannot be enabled, and should be linked staticlly
