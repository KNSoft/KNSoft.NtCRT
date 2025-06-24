#pragma once

#define _CRTBLD
#define _VCRT_BUILD
#define _VCRT_WINDOWS_BUILD
#define _CORECRT_BUILD
#define _CRT_DECLARE_GLOBAL_VARIABLES_DIRECTLY
#define _ALLOW_OLD_VALIDATE_MACROS

#include <KNSoft/NDK/NDK.h>

#ifndef _CRT_NTDDI_MIN
#define _CRT_NTDDI_MIN NTDDI_VISTA
#endif

#ifndef _VCRT_WIN32_WINNT
#define _VCRT_WIN32_WINNT _WIN32_WINNT_VISTA
#endif

#include "PolyFill.inl"

// Section 'section-name' is reserved for C++ dynamic initialization.
#pragma warning(disable: 5247 5248)
#include <corecrt_internal.h>
#include <corecrt_internal_state_isolation.h>
#include <corecrt_internal_stdio.h>
#include <internal_shared.h>
#pragma warning(default: 5247 5248)

#include <vcruntime_internal.h>

#ifdef __cplusplus
#pragma push_macro("WINBASEAPI")
#ifdef WINBASEAPI
#undef WINBASEAPI
#endif
#define WINBASEAPI
#include <vcstartup_internal.h>
#pragma pop_macro("WINBASEAPI")
#endif
