#pragma once

#include <SdkDdkVer.h>

/* CRT Windows Build */
#define _CRTBLD
#define _VCRT_BUILD
#define _CORECRT_BUILD
#define _VCRT_WINDOWS_BUILD
#define _CRT_WINDOWS

/* CRT Settings */
#ifdef _WINDLL
// #error Should be linked staticly!
// #define CRTDLL 1
// #define _CRT_GLOBAL_STATE_ISOLATION // TODO, see: https://learn.microsoft.com/en-us/cpp/c-runtime-library/global-state
#endif
#define _CRT_DECLARE_GLOBAL_VARIABLES_DIRECTLY
#define _ALLOW_OLD_VALIDATE_MACROS
#define _VCRT_ALLOW_INTERNALS

/* NT5 Compatible (set _WIN32_WINNT to _WIN32_WINNT_WINXP) */
#if _WIN32_WINNT >= _WIN32_WINNT_WIN6
#define _CRT_NTDDI_MIN NTDDI_VISTA
#define _VCRT_WIN32_WINNT _WIN32_WINNT_VISTA
#define NT_VERSION_MIN NT_VERSION_VISTA
#else
#define _CRT_NTDDI_MIN NTDDI_WINXP
#define _VCRT_WIN32_WINNT _WIN32_WINNT_WINXP
#define NT_VERSION_MIN NT_VERSION_WINXP
#endif

/* Avoid includes "winternl.h" in ARM64EC */
#if defined(_M_ARM64EC)
#define _WINTERNL_
#endif

#include <KNSoft/NDK/NDK.h>

#include "PolyFill.inl"

/* Internal headers */

// Section 'section-name' is reserved for C++ dynamic initialization.
#pragma warning(disable: 5247 5248)
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
