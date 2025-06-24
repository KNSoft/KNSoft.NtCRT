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

/* Use inline implementations by KNSoft.NDK */

#define GetCurrentThreadId _Inline_GetCurrentThreadId
#define GetCurrentProcessId _Inline_GetCurrentProcessId
#define GetCurrentProcess _Inline_GetCurrentProcess
#define GetEnvironmentStringsW _Inline_GetEnvironmentStringsW
#define FreeEnvironmentStringsW _Inline_FreeEnvironmentStringsW
#define GetStartupInfoW _Inline_GetStartupInfoW
#define GetModuleHandleW _Inline_GetModuleHandleW
#define IsDebuggerPresent _Inline_IsDebuggerPresent
#define ExitProcess _Inline_ExitProcess
#define TerminateProcess _Inline_TerminateProcess

#define GetLastError _Inline_GetLastError
#define SetLastError _Inline_SetLastError

#define QueryPerformanceCounter _Inline_QueryPerformanceCounter

#define EncodePointer _Inline_EncodePointer
#define DecodePointer _Inline_DecodePointer
#define InitializeCriticalSectionAndSpinCount _Inline_InitializeCriticalSectionAndSpinCount
#define InitializeCriticalSectionEx _Inline_InitializeCriticalSectionEx
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
