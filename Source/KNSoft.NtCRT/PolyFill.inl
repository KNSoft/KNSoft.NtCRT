#pragma once

#include <KNSoft/NDK/NDK.inl>

/*
 * _GS_* For GS entropy only, we don't care about correctness
 */

FORCEINLINE
VOID
WINAPI
_GS_GetSystemTimeAsFileTime(
    _Out_ LPFILETIME lpSystemTimeAsFileTime)
{
    lpSystemTimeAsFileTime->dwLowDateTime = SharedUserData->SystemTime.LowPart;
    lpSystemTimeAsFileTime->dwHighDateTime = SharedUserData->SystemTime.High1Time;
}

FORCEINLINE
ULONGLONG
WINAPI
_GS_GetTickCount64(VOID)
{
    return
#if defined (_WIN64)
        UnsignedMultiplyHigh((ULONGLONG)SharedUserData->TickCountMultiplier << 32, SharedUserData->TickCountQuad << 8);
#else
        ((SharedUserData->TickCountMultiplier * (ULONGLONG)SharedUserData->TickCount.High1Time) << 8) +
        ((SharedUserData->TickCountMultiplier * (ULONGLONG)SharedUserData->TickCount.LowPart) >> 24);
#endif
}

/*
 * _CRT_* works correctly for CRT only
 */

FORCEINLINE
_Must_inspect_result_
BOOL
WINAPI
_CRT_InitializeCriticalSectionAndSpinCount(
    _Out_ LPCRITICAL_SECTION lpCriticalSection,
    _In_ DWORD dwSpinCount)
{
#if _CRT_NTDDI_MIN >= NTDDI_VISTA
    RtlInitializeCriticalSectionAndSpinCount(lpCriticalSection, dwSpinCount);
    return TRUE;
#else
    NTSTATUS Status = RtlInitializeCriticalSectionAndSpinCount(lpCriticalSection, dwSpinCount);
    if (NT_SUCCESS(Status))
    {
        return TRUE;
    }

    _Inline_BaseSetLastNTError(Status);
    return FALSE;
#endif
}

FORCEINLINE
BOOL
WINAPI
_CRT_InitializeCriticalSectionEx(
    _Out_ LPCRITICAL_SECTION lpCriticalSection,
    _In_ DWORD dwSpinCount,
    _In_ DWORD Flags)
{
#if _CRT_NTDDI_MIN >= NTDDI_VISTA
    return _Inline_InitializeCriticalSectionEx(lpCriticalSection, dwSpinCount, Flags);
#else
    /* So far, none of the calls from CRT use Flags */
    ASSERT(Flags == 0);
    return _CRT_InitializeCriticalSectionAndSpinCount(lpCriticalSection, dwSpinCount);
#endif
}

FORCEINLINE
BOOL
WINAPI
_CRT_FreeLibrary(
    _In_ HMODULE hLibModule)
{
    ASSERT(!LDR_IS_RESOURCE(hLibModule));
    return NT_SUCCESS(LdrUnloadDll(hLibModule));
}

FORCEINLINE
FARPROC
WINAPI
_CRT_GetProcAddress(
    _In_ HMODULE hModule,
    _In_ LPCSTR lpProcName)
{
    NTSTATUS Status;
    ANSI_STRING ProcName, *Name;
    ULONG ProcOridinal;
    PVOID Address;

    if ((UINT_PTR)lpProcName > MAXWORD)
    {
        Name = &ProcName;
        _Inline_RtlInitAnsiString(Name, lpProcName);
        ProcOridinal = 0;
    } else
    {
        Name = NULL;
        ProcOridinal = (ULONG)(ULONG_PTR)lpProcName;
    }
    Status = LdrGetProcedureAddress(hModule, Name, ProcOridinal, &Address);
    if (NT_SUCCESS(Status))
    {
        return (FARPROC)Address;
    }

    _Inline_BaseSetLastNTError(Status);
    return NULL;
}

/* Use ntdll UEH instead of kernel32 */

/* CRT did not ask for the return value of SetUnhandledExceptionFilter */
FORCEINLINE
VOID
WINAPI
_CRT_SetUnhandledExceptionFilter(
    _In_opt_ LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
{
    /* C28023: _Function_class_ annotation warning */
#pragma warning(disable: 28023)
    RtlSetUnhandledExceptionFilter(lpTopLevelExceptionFilter);
#pragma warning(default: 28023)
}

#define SetUnhandledExceptionFilter _CRT_SetUnhandledExceptionFilter
#define UnhandledExceptionFilter RtlUnhandledExceptionFilter

/* Use inline implementations by KNSoft.NDK */

#define GetCurrentThreadId _Inline_GetCurrentThreadId
#define GetCurrentProcessId _Inline_GetCurrentProcessId
#define GetCurrentThread _Inline_GetCurrentThread
#define GetCurrentProcess _Inline_GetCurrentProcess
#define GetEnvironmentStringsW _Inline_GetEnvironmentStringsW
#define FreeEnvironmentStringsW _Inline_FreeEnvironmentStringsW
#define GetStartupInfoW _Inline_GetStartupInfoW
#define GetModuleHandleW _Inline_GetModuleHandleW
#define GetModuleFileNameW _Inline_GetModuleFileNameW
#define GetModuleHandleExW _Inline_GetModuleHandleExW
#define GetProcAddress _CRT_GetProcAddress
#define FreeLibrary _CRT_FreeLibrary
#define IsDebuggerPresent _Inline_IsDebuggerPresent
#define IsThreadAFiber _Inline_IsThreadAFiber
#define ExitProcess _Inline_ExitProcess
#define TerminateProcess _Inline_TerminateProcess

#define TlsAlloc _Inline_TlsAlloc
#define TlsFree _Inline_TlsFree

/* TODO: No FLS inline implementations, fallback to TLS */
#define FlsAlloc(callback) _Inline_TlsAlloc()
#define FlsFree _Inline_TlsFree
#define FlsGetValue _Inline_TlsGetValue
#define FlsSetValue _Inline_TlsSetValue

#define GetLastError _Inline_GetLastError
#define SetLastError _Inline_SetLastError

#define QueryPerformanceCounter _Inline_QueryPerformanceCounter

#define EncodePointer _Inline_EncodePointer
#define DecodePointer _Inline_DecodePointer
#define InitializeCriticalSectionAndSpinCount _CRT_InitializeCriticalSectionAndSpinCount
#define DeleteCriticalSection _Inline_DeleteCriticalSection
#define EnterCriticalSection _Inline_EnterCriticalSection
#define LeaveCriticalSection _Inline_LeaveCriticalSection

#define GetProcessHeap _Inline_GetProcessHeap
#define HeapAlloc _Inline_HeapAlloc
#define HeapReAlloc _Inline_HeapReAlloc
#define HeapFree _Inline_HeapFree
#define HeapSize _Inline_HeapSize
#define HeapQueryInformation _Inline_HeapQueryInformation
#define HeapValidate _Inline_HeapValidate
#define HeapCompact _Inline_HeapCompact

#define GetStdHandle _Inline_GetStdHandle
#define SetStdHandle _Inline_SetStdHandle
#define WriteFile _Inline_WriteFile
#define FlushFileBuffers _Inline_FlushFileBuffers
#define SetFilePointerEx _Inline_SetFilePointerEx
#define CloseHandle _Inline_CloseHandle

#define IsProcessorFeaturePresent _Inline_IsProcessorFeaturePresent
#define InitializeSListHead _Inline_InitializeSListHead
#define InterlockedFlushSList _Inline_InterlockedFlushSList
