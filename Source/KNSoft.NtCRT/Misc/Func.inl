#pragma once

#include "../NtCRT.inl"

#include <misc/invalid_parameter.cpp>

EXTERN_C_START

_ACRTIMP
int
__cdecl
_getpid(void)
{
    return (int)(INT_PTR)NtCurrentProcessId();
}

EXTERN_C_END
