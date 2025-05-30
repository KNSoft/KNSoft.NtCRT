#pragma once

#include "../NtCRT.inl"

/* See also: $(VCToolsInstallDir)crt\src\vcruntime */

EXTERN_C_START

/* GS */

#define GetSystemTimeAsFileTime _GS_GetSystemTimeAsFileTime
#define GetTickCount64 _GS_GetTickCount64

#define PROCESSOR_FAST_FAIL_AVAILABLE
#include <gs_report.c>
#include <gs_support.c>

#undef GetSystemTimeAsFileTime
#undef GetTickCount64

#include <locks.cpp>
// #include <winapi_downlevel.cpp>

EXTERN_C_END
