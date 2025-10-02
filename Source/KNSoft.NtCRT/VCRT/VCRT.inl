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

EXTERN_C_END

#include <locks.cpp>
#include <tncleanup.cpp>
#include <utility_desktop.cpp>
#include <per_thread_data.cpp>
