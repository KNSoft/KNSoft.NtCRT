#pragma once

#include "../../NtCRT.inl"

EXTERN_C_START

/* See also: $(UCRTContentRoot)Source\$(TargetUniversalCRTVersion)\ucrt\startup\argv_data.cpp */

int __argc = 0;
char** __argv = nullptr;
wchar_t** __wargv = nullptr;
char* _pgmptr = nullptr;
wchar_t* _wpgmptr = nullptr;
char* _acmdln = nullptr;
wchar_t* _wcmdln = nullptr;

_BEGIN_SECURE_CRT_DEPRECATION_DISABLE

int* __cdecl __p___argc() { return &__argc; }
char*** __cdecl __p___argv() { return &__argv; }
wchar_t*** __cdecl __p___wargv() { return &__wargv; }
char** __cdecl __p__pgmptr() { return &_pgmptr; }
wchar_t** __cdecl __p__wpgmptr() { return &_wpgmptr; }
char** __cdecl __p__acmdln() { return &_acmdln; }
wchar_t** __cdecl __p__wcmdln() { return &_wcmdln; }

_ACRTIMP
_Success_(return == 0)
errno_t
__cdecl
_get_wpgmptr(
    _Outptr_result_z_ wchar_t** _Value)
{
    _VALIDATE_RETURN_ERRCODE(_Value != nullptr, EINVAL);
    _VALIDATE_RETURN_ERRCODE(_wpgmptr != nullptr, EINVAL);

    *_Value = _wpgmptr;
    return 0;
}

_ACRTIMP
_Success_(return == 0)
errno_t
__cdecl
_get_pgmptr(
    _Outptr_result_z_ char** _Value)
{
    _VALIDATE_RETURN_ERRCODE(_Value != nullptr, EINVAL);
    _VALIDATE_RETURN_ERRCODE(_pgmptr != nullptr, EINVAL);

    *_Value = _pgmptr;
    return 0;
}

_END_SECURE_CRT_DEPRECATION_DISABLE

static ANSI_STRING g_CmdlineA = { 0 };

bool
__cdecl
__acrt_initialize_command_line()
{
    PUNICODE_STRING Cmdline = &NtCurrentPeb()->ProcessParameters->CommandLine;

    if (Cmdline->Buffer == NULL ||
        Cmdline->Length == 0 ||
        Cmdline->MaximumLength <= Cmdline->Length ||
        Cmdline->Buffer[Cmdline->Length / sizeof(WCHAR)] != UNICODE_NULL ||
        !NT_SUCCESS(RtlUnicodeStringToAnsiString(&g_CmdlineA, Cmdline, TRUE)))
    {
        return false;
    }

    _wcmdln = Cmdline->Buffer;
    _acmdln = g_CmdlineA.Buffer;
    return true;
}

bool
__cdecl
__acrt_uninitialize_command_line(
    _In_ bool terminating)
{
    if (!terminating)
    {
        RtlFreeAnsiString(&g_CmdlineA);
    }
    return true;
}

/* TODO: Expanding wildcard arguments is not supported yet */

errno_t __acrt_expand_narrow_argv_wildcards(char** const argv, char*** const result)
{
    return ENOTSUP;
}

errno_t __acrt_expand_wide_argv_wildcards(wchar_t** const argv, wchar_t*** const result)
{
    return ENOTSUP;
}

EXTERN_C_END
