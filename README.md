## Unsupported features (To-do)
- FLS, now fallback to TLS
- [Expanding wildcard arguments](https://learn.microsoft.com/en-us/cpp/c-language/expanding-wildcard-arguments), now cannot enable link options (`setargv.obj` or `wsetargv.obj`)
- NT5 Console Output, now fallback to `NtWriteFile(hStdOutput, ...)`, this is incompatible with NT5
- [Global State Isolation](https://learn.microsoft.com/en-us/cpp/c-runtime-library/global-state), this feature is unused now because **NtCRT and MSVCRT should be linked statically**, but NtCRT might be able to be linked independently and could be a DLL in the future
