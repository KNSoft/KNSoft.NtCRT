#pragma once

#include "../NtCRT.inl"

/* See also: $(UCRTContentRoot)Source\$(TargetUniversalCRTVersion)\ucrt\conio\initcon.cpp */

#include <corecrt_internal_lowio.h>

_CRT_LINKER_FORCE_INCLUDE(__dcrt_console_output_terminator);

static HANDLE __dcrt_lowio_console_output_handle = _console_uninitialized_handle;

static const UNICODE_STRING g_usConOut = RTL_CONSTANT_STRING(L"\\??\\CONOUT$");
static const OBJECT_ATTRIBUTES g_oaConOut = RTL_CONSTANT_OBJECT_ATTRIBUTES(&g_usConOut, OBJ_CASE_INSENSITIVE);

static
void
__dcrt_lowio_initialize_console_output()
{
    IO_STATUS_BLOCK IoStatusBlock;
    HANDLE ConOutHandle;

    __dcrt_lowio_console_output_handle = NT_SUCCESS(NtCreateFile(&ConOutHandle,
                                                                 GENERIC_WRITE | SYNCHRONIZE | FILE_READ_ATTRIBUTES,
                                                                 (POBJECT_ATTRIBUTES)&g_oaConOut,
                                                                 &IoStatusBlock,
                                                                 NULL,
                                                                 0,
                                                                 FILE_SHARE_READ | FILE_SHARE_WRITE,
                                                                 FILE_OPEN,
                                                                 FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT,
                                                                 NULL,
                                                                 0)) ? ConOutHandle : INVALID_HANDLE_VALUE;
}

extern "C"
BOOL
__cdecl
__dcrt_lowio_ensure_console_output_initialized()
{
    if (__dcrt_lowio_console_output_handle == _console_uninitialized_handle)
    {
        __dcrt_lowio_initialize_console_output();
    }
    if (__dcrt_lowio_console_output_handle == _console_invalid_handle)
    {
        return FALSE;
    }
    return TRUE;
}

extern "C"
void
__cdecl
__dcrt_terminate_console_output()
{
    if (__dcrt_lowio_console_output_handle != _console_invalid_handle &&
        __dcrt_lowio_console_output_handle != _console_uninitialized_handle)
    {
        NtClose(__dcrt_lowio_console_output_handle);
    }
}

template <typename Func>
static
BOOL
console_output_reopen_and_retry(
    Func const& fp) throw()
{
    BOOL result = fp();

    if (!result && _Inline_GetLastError() == ERROR_INVALID_HANDLE)
    {
        __dcrt_terminate_console_output();
        __dcrt_lowio_initialize_console_output();
        result = fp();
    }
    return result;
}

extern "C"
BOOL
__cdecl
__dcrt_write_console(
    _In_ void const* lpBuffer,
    _In_ DWORD nNumberOfCharsToWrite,
    _Out_ LPDWORD lpNumberOfCharsWritten)
{
    return console_output_reopen_and_retry(
        [lpBuffer, nNumberOfCharsToWrite, lpNumberOfCharsWritten]()
    {
        /* FIXME: NtWriteFile works but not completely identical to WriteConsoleW */
        NTSTATUS Status;
        IO_STATUS_BLOCK IoStatusBlock;

        Status = NtWriteFile(__dcrt_lowio_console_output_handle,
                             NULL,
                             NULL,
                             NULL,
                             &IoStatusBlock,
                             (PVOID)lpBuffer,
                             nNumberOfCharsToWrite * sizeof(wchar_t),
                             NULL,
                             NULL);
        if (Status == STATUS_PENDING)
        {
            Status = NtWaitForSingleObject(__dcrt_lowio_console_output_handle, FALSE, NULL);
            if (NT_SUCCESS(Status))
            {
                Status = IoStatusBlock.Status;
            }
        }
        if (NT_SUCCESS(Status))
        {
            if (lpNumberOfCharsWritten != NULL)
            {
                *lpNumberOfCharsWritten = (ULONG)IoStatusBlock.Information;
            }
            return TRUE;
        }

        if (NT_WARNING(Status) && lpNumberOfCharsWritten != NULL)
        {
            *lpNumberOfCharsWritten = (ULONG)IoStatusBlock.Information;
        }
        _Inline_BaseSetLastNTError(Status);
        return FALSE;
    });
}
