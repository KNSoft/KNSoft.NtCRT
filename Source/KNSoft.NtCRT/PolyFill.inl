#pragma once

#include <KNSoft/NDK/NDK.inl>

/*
 * _GS_* For GS entropy only, it doesn't need to be accurate
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

#define QueryPerformanceCounter _Inline_QueryPerformanceCounter

#define EncodePointer _Inline_EncodePointer
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
#define SetStdHandle _Inline_SetStdHandle
