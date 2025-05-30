#pragma once

#define _CRTBLD
#define _VCRT_BUILD
#define _VCRT_WINDOWS_BUILD
#define _CORECRT_BUILD
#define _CRT_DECLARE_GLOBAL_VARIABLES_DIRECTLY

#include <KNSoft/NDK/NDK.h>

#define _CRT_NTDDI_MIN NTDDI_VISTA
#define _VCRT_WIN32_WINNT _WIN32_WINNT_VISTA

// Section 'section-name' is reserved for C++ dynamic initialization.
#pragma warning(disable: 5247 5248)
#include <corecrt_internal.h>
#include <corecrt_internal_state_isolation.h>
#include <corecrt_internal_stdio.h>
#include <internal_shared.h>
#pragma warning(default: 5247 5248)

#include <vcruntime_internal.h>

#ifdef __cplusplus
#include <vcstartup_internal.h>
#endif

#include "PolyFill.inl"
