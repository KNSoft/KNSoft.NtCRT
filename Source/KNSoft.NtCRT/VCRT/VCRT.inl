#pragma once

#include "../NtCRT.inl"

/* See also: $(VCToolsInstallDir)crt\src\vcruntime */

EXTERN_C_START

/* GS */

#define GetSystemTimeAsFileTime _GS_GetSystemTimeAsFileTime
#define GetTickCount64 _GS_GetTickCount64

/* Before VS2026, define PROCESSOR_FAST_FAIL_AVAILABLE to prevent fallback */
#define PROCESSOR_FAST_FAIL_AVAILABLE
#include <gs_report.c>
#include <gs_support.c>

#undef GetSystemTimeAsFileTime
#undef GetTickCount64

#include <debugger_jmc.c>

EXTERN_C_END

#include <locks.cpp>
#include <tncleanup.cpp>
#include <utility_desktop.cpp>
#include <throw.cpp>
#include <frame.cpp>

#define reentrancy_sentinel vcrt_reentrancy_sentinel
#include <per_thread_data.cpp>
#undef reentrancy_sentinel

#include <std_type_info.cpp>
