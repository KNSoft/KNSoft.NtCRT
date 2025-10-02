#pragma once

#include "NtCRT.inl"

/*
 * See also:
 *   $(UCRTContentRoot)Source\$(TargetUniversalCRTVersion)\ucrt\internal\winapi_thunks.cpp
 *   $(VCToolsInstallDir)crt\src\vcruntime\winapi_downlevel.cpp
 */

EXTERN_C_START

namespace
{
    enum Crt_Type : unsigned
    {
        Crt_Ucrt = 0,
        Crt_Vcrt
    };

    /* System DLLs */

    enum SysDll_Id : unsigned
    {
        SysDll_Kernel32 = 0,
#if _CRT_NTDDI_MIN >= NTDDI_VISTA
        SysDll_KernelBase,
#else
        SysDll_KernelBase = SysDll_Kernel32,
#endif
        SysDll_User32,
        SysDll_AdvApi32,
        SysDll_AppmodelRuntime,
        SysDll_WinRT,
        SysDll_Count
    };

    static UNICODE_STRING const SysDllNames[SysDll_Count] =
    {
        RTL_CONSTANT_STRING(L"kernel32.dll"),
#if _CRT_NTDDI_MIN >= NTDDI_VISTA
        RTL_CONSTANT_STRING(L"KernelBase.dll"),
#endif
        RTL_CONSTANT_STRING(L"user32.dll"),
        RTL_CONSTANT_STRING(L"advapi32.dll"),
        RTL_CONSTANT_STRING(L"api-ms-win-appmodel-runtime-l1-1-2.dll"),
        RTL_CONSTANT_STRING(L"api_ms_win_core_winrt_l1_1_0.dll"),
    };

    /* 0 (NULL): Uninitialized, -1 (INVALID_HANDLE_VALUE): Failed */
    static _Interlocked_operand_ PVOID volatile SysDll_Handles[SysDll_Count];

    /* System APIs */

    enum SysAPI_Id : unsigned
    {
        SysAPI_AreFileApisANSI,
        SysAPI_CompareStringEx,
        SysAPI_EnumSystemLocalesEx,
        SysAPI_FlsAlloc,
        SysAPI_FlsFree,
        SysAPI_FlsGetValue,
        SysAPI_FlsGetValue2,
        SysAPI_FlsSetValue,
        SysAPI_GetActiveWindow,
        SysAPI_GetDateFormatEx,
        SysAPI_GetTempPath2W,
        SysAPI_GetFileInformationByName,
        SysAPI_GetEnabledXStateFeatures,
        SysAPI_GetLastActivePopup,
        SysAPI_GetLocaleInfoEx,
        SysAPI_GetProcessWindowStation,
        SysAPI_GetSystemTimePreciseAsFileTime,
        SysAPI_GetTimeFormatEx,
        SysAPI_GetUserDefaultLocaleName,
        SysAPI_GetUserObjectInformationW,
        SysAPI_GetXStateFeaturesMask,
        SysAPI_IsValidLocaleName,
        SysAPI_LCMapStringEx,
        SysAPI_LCIDToLocaleName,
        SysAPI_LocaleNameToLCID,
        SysAPI_LocateXStateFeature,
        SysAPI_MessageBoxA,
        SysAPI_MessageBoxW,
        SysAPI_RoInitialize,
        SysAPI_RoUninitialize,
        SysAPI_AppPolicyGetProcessTerminationMethod,
        SysAPI_AppPolicyGetThreadInitializationType,
        SysAPI_AppPolicyGetShowDeveloperDiagnostic,
        SysAPI_AppPolicyGetWindowingModel,
        SysAPI_SetThreadStackGuarantee,
        SysAPI_SystemFunction036,
        SysAPI_Count
    };

    static const struct SYS_API
    {
        ANSI_STRING Name;
        SysDll_Id DllId;
    } SysAPIs[SysAPI_Count] = {
        { RTL_CONSTANT_STRING("AreFileApisANSI"),                       SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("CompareStringEx"),                       SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("EnumSystemLocalesEx"),                   SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("FlsAlloc"),                              SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("FlsFree"),                               SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("FlsGetValue"),                           SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("FlsGetValue2"),                          SysDll_KernelBase       },
        { RTL_CONSTANT_STRING("FlsSetValue"),                           SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("GetActiveWindow"),                       SysDll_User32           },
        { RTL_CONSTANT_STRING("GetDateFormatEx"),                       SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("GetTempPath2W"),                         SysDll_KernelBase       },
        { RTL_CONSTANT_STRING("GetFileInformationByName"),              SysDll_KernelBase       },
        { RTL_CONSTANT_STRING("GetEnabledXStateFeatures"),              SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("GetLastActivePopup"),                    SysDll_User32           },
        { RTL_CONSTANT_STRING("GetLocaleInfoEx"),                       SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("GetProcessWindowStation"),               SysDll_User32           },
        { RTL_CONSTANT_STRING("GetSystemTimePreciseAsFileTime"),        SysDll_KernelBase       },
        { RTL_CONSTANT_STRING("GetTimeFormatEx"),                       SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("GetUserDefaultLocaleName"),              SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("GetUserObjectInformationW"),             SysDll_User32           },
        { RTL_CONSTANT_STRING("GetXStateFeaturesMask"),                 SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("IsValidLocaleName"),                     SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("LCMapStringEx"),                         SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("LCIDToLocaleName"),                      SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("LocaleNameToLCID"),                      SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("LocateXStateFeature"),                   SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("MessageBoxA"),                           SysDll_User32           },
        { RTL_CONSTANT_STRING("MessageBoxW"),                           SysDll_User32           },
        { RTL_CONSTANT_STRING("RoInitialize"),                          SysDll_WinRT            },
        { RTL_CONSTANT_STRING("RoUninitialize"),                        SysDll_WinRT            },
        { RTL_CONSTANT_STRING("AppPolicyGetProcessTerminationMethod"),  SysDll_AppmodelRuntime  },
        { RTL_CONSTANT_STRING("AppPolicyGetThreadInitializationType"),  SysDll_AppmodelRuntime  },
        { RTL_CONSTANT_STRING("AppPolicyGetShowDeveloperDiagnostic"),   SysDll_AppmodelRuntime  },
        { RTL_CONSTANT_STRING("AppPolicyGetWindowingModel"),            SysDll_AppmodelRuntime  },
        { RTL_CONSTANT_STRING("SetThreadStackGuarantee"),               SysDll_Kernel32         },
        { RTL_CONSTANT_STRING("SystemFunction036"),                     SysDll_AdvApi32         },
    };

    /* 0 (NULL): Uninitialized, -1 (INVALID_HANDLE_VALUE): Failed */
    static _Interlocked_operand_ PVOID volatile SysAPI_Pointers[SysAPI_Count];
}

/* We don't set page protection and ".fptable" segment */
bool
__cdecl
__acrt_initialize_winapi_thunks()
{
    return true;
}

bool
__cdecl
__acrt_uninitialize_winapi_thunks(
    _In_ bool terminating)
{
    if (terminating)
    {
        return true;
    }

    for (auto& module : SysDll_Handles)
    {
        if (module)
        {
            if (module != INVALID_HANDLE_VALUE)
            {
                LdrUnloadDll(module);
            }
            module = NULL;
        }
    }

    return true;
}

static
PVOID
__cdecl
try_load_library_from_system_directory(
    PCUNICODE_STRING DllName) throw()
{
    PVOID DllBase;
    NTSTATUS Status;

    /* LDR_PATH_SEARCH_SYSTEM32 since NT6.0/6.1 with KB2533623 */
    if (_NTCRT_NT5_SUPPORT && SharedUserData->NtMajorVersion < 6)
    {
        goto _Fallback;
    }

    Status = LdrLoadDll((PCWSTR)(LDR_PATH_IS_FLAGS | LDR_PATH_SEARCH_SYSTEM32),
                        NULL,
                        (PUNICODE_STRING)DllName,
                        &DllBase);
    if (NT_SUCCESS(Status))
    {
        return DllBase;
    }
    if (Status != STATUS_INVALID_PARAMETER ||
        wcsncmp(DllName->Buffer, L"api-ms-", 7) == 0 ||
        wcsncmp(DllName->Buffer, L"ext-ms-", 7) == 0)
    {
        return NULL;
    }

_Fallback:
    return NT_SUCCESS(LdrLoadDll(NULL, NULL, (PUNICODE_STRING)DllName, &DllBase)) ? DllBase : NULL;
}

static
PVOID
__cdecl
try_get_module(
    SysDll_Id DllId) throw()
{
    PVOID cached_handle, new_handle;

    if (cached_handle = __crt_interlocked_read_pointer(SysDll_Handles + DllId))
    {
        return cached_handle != INVALID_HANDLE_VALUE ? cached_handle : NULL;
    }

    new_handle = try_load_library_from_system_directory(SysDllNames + DllId);
    if (new_handle == NULL)
    {
        if (cached_handle = __crt_interlocked_exchange_pointer(SysDll_Handles + DllId, INVALID_HANDLE_VALUE))
        {
            _ASSERTE(cached_handle == INVALID_HANDLE_VALUE);
        }
        return NULL;
    }

    if (cached_handle = __crt_interlocked_exchange_pointer(SysDll_Handles + DllId, new_handle))
    {
        _ASSERTE(cached_handle == new_handle);
        LdrUnloadDll(new_handle);
    }

    return new_handle;
}

static
__forceinline
void*
__cdecl
try_get_proc_address(
    const ANSI_STRING* Name,
    SysDll_Id DllId) throw()
{
    PVOID Pointer;
    PVOID DllHandle = try_get_module(DllId);

    if (DllHandle == NULL)
    {
        return NULL;
    }

    return NT_SUCCESS(LdrGetProcedureAddress(DllHandle, (PANSI_STRING)Name, 0, &Pointer)) ? Pointer : NULL;
}

DECLSPEC_NOINLINE
static
void*
__cdecl
try_get_function_slow(
    SysAPI_Id ApiId,
    Crt_Type CrtType) throw()
{
    void* new_fp = try_get_proc_address(&SysAPIs[ApiId].Name, SysAPIs[ApiId].DllId);
    void* cached_fp;

    if (CrtType == Crt_Ucrt)
    {
        __acrt_lock(__acrt_function_pointer_table_lock);
    }

    if (!new_fp)
    {
        cached_fp = __crt_interlocked_exchange_pointer(SysAPI_Pointers + ApiId, INVALID_HANDLE_VALUE);
        if (cached_fp)
        {
            _ASSERTE(cached_fp == INVALID_HANDLE_VALUE);
        }
        goto end;
    }

    cached_fp = __crt_interlocked_exchange_pointer(SysAPI_Pointers + ApiId, new_fp);
    if (cached_fp)
    {
        _ASSERTE(cached_fp == new_fp);
    }

end:
    if (CrtType == Crt_Ucrt)
    {
        __acrt_unlock(__acrt_function_pointer_table_lock);
    }
    return new_fp;
}

static
__forceinline
void*
__cdecl
try_get_function(
    SysAPI_Id ApiId,
    Crt_Type CrtType) throw()
{
    void* cached_fp = ReadPointerNoFence(SysAPI_Pointers + ApiId);
    if (cached_fp)
    {
        return cached_fp;
    } else if (cached_fp == INVALID_HANDLE_VALUE)
    {
        return NULL;
    } else
    {
        return try_get_function_slow(ApiId, CrtType);
    }
}

static
__forceinline
void*
__cdecl
get_function(
    SysAPI_Id ApiId) throw()
{
    return ReadPointerNoFence(SysAPI_Pointers + ApiId);
}

#define TRY_GET_API(x, t) ((decltype(x)*)try_get_function(_CRT_CONCATENATE(SysAPI_, x), t))
#define GET_API(x) ((decltype(x)*)get_function(_CRT_CONCATENATE(SysAPI_, x)))

/* UCRT Thunks */

BOOL WINAPI __acrt_AreFileApisANSI()
{
    if (auto const are_file_apis_ansi = TRY_GET_API(AreFileApisANSI, Crt_Ucrt))
    {
        return are_file_apis_ansi();
    }

    // If we were unable to get the AreFileApisANSI function, we can safely
    // assume that the file APIs are, in fact, ANSI:
    return TRUE;
}

int WINAPI __acrt_CompareStringEx(
    LPCWSTR          const locale_name,
    DWORD            const flags,
    LPCWCH           const string1,
    int              const string1_count,
    LPCWCH           const string2,
    int              const string2_count,
    LPNLSVERSIONINFO const version,
    LPVOID           const reserved,
    LPARAM           const param
)
{
    if (auto const compare_string_ex = TRY_GET_API(CompareStringEx, Crt_Ucrt))
    {
        // On WCOS devices, CompareStringEx may calls into icu.dll which is an OS component using the UCRT.
        // If icu.dll calls any UCRT export under OS mode (ex: malloc), then CompareStringEx will return under Prog Mode even if
        // we started in OS mode. To prevent this, an OS mode guard is in place.
        __crt_state_management::scoped_global_state_reset os_mode_guard;
        return compare_string_ex(locale_name, flags, string1, string1_count, string2, string2_count, version, reserved, param);
    }

    return CompareStringW(__acrt_LocaleNameToLCID(locale_name, 0), flags, string1, string1_count, string2, string2_count);
}

// This has been split into its own function to work around a bug in the Dev12
// C++ compiler where nested captureless lambdas are not convertible to the
// required function pointer type.
static BOOL enum_system_locales_ex_nolock(
    LOCALE_ENUMPROCEX const enum_proc
) throw()
{
    static LOCALE_ENUMPROCEX static_enum_proc;

    static_enum_proc = enum_proc;
    BOOL const result = EnumSystemLocalesW(
        [](LPWSTR locale_string)
    {
        return (static_enum_proc)(locale_string, 0, 0);
    },
        LCID_INSTALLED);
    static_enum_proc = nullptr;

    return result;
}

BOOL WINAPI __acrt_EnumSystemLocalesEx(
    LOCALE_ENUMPROCEX const enum_proc,
    DWORD             const flags,
    LPARAM            const param,
    LPVOID            const reserved
)
{
    if (auto const enum_system_locales_ex = TRY_GET_API(EnumSystemLocalesEx, Crt_Ucrt))
    {
        return enum_system_locales_ex(enum_proc, flags, param, reserved);
    }

    return __acrt_lock_and_call(__acrt_locale_lock, [&]() -> BOOL
    {
        return enum_system_locales_ex_nolock(enum_proc);
    });
}

// Historically, we needed to conditionally call FLS functions for x86 since the UCRT needed to be consumable down to XP.
// This is no longer the case as XP is no longer supported, however the enclave implementations of these functions
// unconditionally call the TLS equivalent APIs (TlsAlloc, etc), hence why these are still kept around
DWORD WINAPI __acrt_FlsAlloc(PFLS_CALLBACK_FUNCTION const callback)
{
    return FlsAlloc(callback);
}

BOOL WINAPI __acrt_FlsFree(DWORD const fls_index)
{
    return FlsFree(fls_index);
}

PVOID WINAPI __acrt_FlsGetValue(DWORD const fls_index)
{
    return FlsGetValue(fls_index);
}

extern "C"
DECLSPEC_GUARDNOCF
PVOID WINAPI __acrt_FlsGetValue2(DWORD const fls_index)
{
#if (defined(_M_ARM64_) || defined(_M_ARM64EC)) && _UCRT_DLL
    return FlsGetValue2(fls_index);
#else
    /*
    * N.B.: This function must be called after checking __acrt_use_tls2_apis.
    */
    auto const flsgetvalue2 = GET_API(FlsGetValue2);
    return flsgetvalue2(fls_index);
#endif
}

BOOL WINAPI __acrt_FlsSetValue(DWORD const fls_index, PVOID const fls_data)
{
    return FlsSetValue(fls_index, fls_data);
}

BOOL WINAPI __acrt_IsThreadAFiber()
{
    return IsThreadAFiber();
}

int WINAPI __acrt_GetDateFormatEx(
    LPCWSTR           const locale_name,
    DWORD             const flags,
    SYSTEMTIME CONST* const date,
    LPCWSTR           const format,
    LPWSTR            const buffer,
    int               const buffer_count,
    LPCWSTR           const calendar
)
{
    if (auto const get_date_format_ex = TRY_GET_API(GetDateFormatEx, Crt_Ucrt))
    {
        return get_date_format_ex(locale_name, flags, date, format, buffer, buffer_count, calendar);
    }

    return GetDateFormatW(__acrt_LocaleNameToLCID(locale_name, 0), flags, date, format, buffer, buffer_count);
}

int WINAPI __acrt_GetTempPath2W(
    DWORD nBufferLength,
    LPWSTR lpBuffer
)
{
    if (auto const get_temp_path2w = TRY_GET_API(GetTempPath2W, Crt_Ucrt))
    {
        return get_temp_path2w(nBufferLength, lpBuffer);
    }
    return GetTempPathW(nBufferLength, lpBuffer);
}

BOOL WINAPI __acrt_GetFileInformationByName(
    LPCWSTR FileName,
    DWORD FileInformationClass,                // FILE_INFO_BY_NAME_CLASS
    PVOID FileInfoBuffer,
    ULONG FileInfoBufferSize
)
{
    if (auto const get_file_info = TRY_GET_API(GetFileInformationByName, Crt_Ucrt))
    {
        return get_file_info(FileName, (FILE_INFO_BY_NAME_CLASS)FileInformationClass, FileInfoBuffer, FileInfoBufferSize);
    }
    return FALSE;
}

DWORD64 WINAPI __acrt_GetEnabledXStateFeatures()
{
    if (auto const get_enabled_xstate_features = TRY_GET_API(GetEnabledXStateFeatures, Crt_Ucrt))
    {
        return get_enabled_xstate_features();
    }

    abort(); // No fallback; callers should check availablility before calling
}

int WINAPI __acrt_GetLocaleInfoEx(
    LPCWSTR const locale_name,
    LCTYPE  const lc_type,
    LPWSTR  const data,
    int     const data_count
)
{
    if (auto const get_locale_info_ex = TRY_GET_API(GetLocaleInfoEx, Crt_Ucrt))
    {
        return get_locale_info_ex(locale_name, lc_type, data, data_count);
    }

    return GetLocaleInfoW(__acrt_LocaleNameToLCID(locale_name, 0), lc_type, data, data_count);
}

VOID WINAPI __acrt_GetSystemTimePreciseAsFileTime(LPFILETIME const system_time)
{
    if (auto const get_system_time_precise_as_file_time = TRY_GET_API(GetSystemTimePreciseAsFileTime, Crt_Ucrt))
    {
        return get_system_time_precise_as_file_time(system_time);
    }

    return GetSystemTimeAsFileTime(system_time);
}

int WINAPI __acrt_GetTimeFormatEx(
    LPCWSTR           const locale_name,
    DWORD             const flags,
    SYSTEMTIME CONST* const time,
    LPCWSTR           const format,
    LPWSTR            const buffer,
    int               const buffer_count
)
{
    if (auto const get_time_format_ex = TRY_GET_API(GetTimeFormatEx, Crt_Ucrt))
    {
        return get_time_format_ex(locale_name, flags, time, format, buffer, buffer_count);
    }

    return GetTimeFormatW(__acrt_LocaleNameToLCID(locale_name, 0), flags, time, format, buffer, buffer_count);
}

int WINAPI __acrt_GetUserDefaultLocaleName(
    LPWSTR const locale_name,
    int    const locale_name_count
)
{
    if (auto const get_user_default_locale_name = TRY_GET_API(GetUserDefaultLocaleName, Crt_Ucrt))
    {
        return get_user_default_locale_name(locale_name, locale_name_count);
    }

    return __acrt_LCIDToLocaleName(GetUserDefaultLCID(), locale_name, locale_name_count, 0);
}

BOOL WINAPI __acrt_GetXStateFeaturesMask(
    PCONTEXT const context,
    PDWORD64 const feature_mask
)
{
    if (auto const get_xstate_features_mask = TRY_GET_API(GetXStateFeaturesMask, Crt_Ucrt))
    {
        return get_xstate_features_mask(context, feature_mask);
    }

    abort(); // No fallback; callers should check availablility before calling
}

BOOL WINAPI __acrt_InitializeCriticalSectionEx(
    LPCRITICAL_SECTION const critical_section,
    DWORD              const spin_count,
    DWORD              const flags
)
{
    return _CRT_InitializeCriticalSectionEx(critical_section, spin_count, flags);
}

BOOL WINAPI __acrt_IsValidLocaleName(LPCWSTR const locale_name)
{
    if (auto const is_valid_locale_name = TRY_GET_API(IsValidLocaleName, Crt_Ucrt))
    {
        return is_valid_locale_name(locale_name);
    }

    return IsValidLocale(__acrt_LocaleNameToLCID(locale_name, 0), LCID_INSTALLED);
}

int WINAPI __acrt_LCMapStringEx(
    LPCWSTR          const locale_name,
    DWORD            const flags,
    LPCWSTR          const source,
    int              const source_count,
    LPWSTR           const destination,
    int              const destination_count,
    LPNLSVERSIONINFO const version,
    LPVOID           const reserved,
    LPARAM           const sort_handle
)
{
    if (auto const lc_map_string_ex = TRY_GET_API(LCMapStringEx, Crt_Ucrt))
    {
        return lc_map_string_ex(locale_name, flags, source, source_count, destination, destination_count, version, reserved, sort_handle);
    }
#pragma warning(disable:__WARNING_PRECONDITION_NULLTERMINATION_VIOLATION) // 26035 LCMapStringW annotation is presently incorrect 11/26/2014 Jaykrell
    return LCMapStringW(__acrt_LocaleNameToLCID(locale_name, 0), flags, source, source_count, destination, destination_count);
}

int WINAPI __acrt_LCIDToLocaleName(
    LCID   const locale,
    LPWSTR const name,
    int    const name_count,
    DWORD  const flags
)
{
    if (auto const lcid_to_locale_name = TRY_GET_API(LCIDToLocaleName, Crt_Ucrt))
    {
        return lcid_to_locale_name(locale, name, name_count, flags);
    }

    return __acrt_DownlevelLCIDToLocaleName(locale, name, name_count);
}

LCID WINAPI __acrt_LocaleNameToLCID(
    LPCWSTR const name,
    DWORD   const flags
)
{
    if (auto const locale_name_to_lcid = TRY_GET_API(LocaleNameToLCID, Crt_Ucrt))
    {
        return locale_name_to_lcid(name, flags);
    }

    return __acrt_DownlevelLocaleNameToLCID(name);
}

PVOID WINAPI __acrt_LocateXStateFeature(
    PCONTEXT const content,
    DWORD    const feature_id,
    PDWORD   const length
)
{
    if (auto const locate_xstate_feature = TRY_GET_API(LocateXStateFeature, Crt_Ucrt))
    {
        return locate_xstate_feature(content, feature_id, length);
    }

    abort(); // No fallback; callers should check availablility before calling
}

int WINAPI __acrt_MessageBoxA(
    HWND   const hwnd,
    LPCSTR const text,
    LPCSTR const caption,
    UINT   const type
)
{
    if (auto const message_box_a = TRY_GET_API(MessageBoxA, Crt_Ucrt))
    {
        return message_box_a(hwnd, text, caption, type);
    }

    abort(); // No fallback; callers should check availablility before calling
}

int WINAPI __acrt_MessageBoxW(
    HWND    const hwnd,
    LPCWSTR const text,
    LPCWSTR const caption,
    UINT    const type
)
{
    if (auto const message_box_w = TRY_GET_API(MessageBoxW, Crt_Ucrt))
    {
        return message_box_w(hwnd, text, caption, type);
    }

    abort(); // No fallback; callers should check availablility before calling
}

BOOLEAN WINAPI __acrt_RtlGenRandom(
    PVOID const buffer,
    ULONG const buffer_count
)
{
    if (auto const rtl_gen_random = TRY_GET_API(SystemFunction036, Crt_Ucrt))
    {
        return rtl_gen_random(buffer, buffer_count);
    }

    abort(); // No fallback (this function should exist)
}

HRESULT WINAPI __acrt_RoInitialize(RO_INIT_TYPE const init_type)
{
    if (auto const ro_initialize = TRY_GET_API(RoInitialize, Crt_Ucrt))
    {
        return ro_initialize(init_type);
    }

    return S_OK; // No fallback (this is a best-effort wrapper)
}

void WINAPI __acrt_RoUninitialize()
{
    if (auto const ro_uninitialize = TRY_GET_API(RoUninitialize, Crt_Ucrt))
    {
        return ro_uninitialize();
    }

    // No fallback (this is a best-effort wrapper)
}

LONG WINAPI __acrt_AppPolicyGetProcessTerminationMethodInternal(_Out_ AppPolicyProcessTerminationMethod* policy)
{
    if (auto const app_policy_get_process_terminaton_method_claims = TRY_GET_API(AppPolicyGetProcessTerminationMethod, Crt_Ucrt))
    {
        return app_policy_get_process_terminaton_method_claims(GetCurrentThreadEffectiveToken(), policy);
    }

    return STATUS_NOT_FOUND;
}

LONG WINAPI __acrt_AppPolicyGetThreadInitializationTypeInternal(_Out_ AppPolicyThreadInitializationType* policy)
{
    if (auto const app_policy_get_thread_initialization_type_claims = TRY_GET_API(AppPolicyGetThreadInitializationType, Crt_Ucrt))
    {
        return app_policy_get_thread_initialization_type_claims(GetCurrentThreadEffectiveToken(), policy);
    }

    return STATUS_NOT_FOUND;
}

LONG WINAPI __acrt_AppPolicyGetShowDeveloperDiagnosticInternal(_Out_ AppPolicyShowDeveloperDiagnostic* policy)
{
    if (auto const app_policy_get_show_developer_diagnostic_claims = TRY_GET_API(AppPolicyGetShowDeveloperDiagnostic, Crt_Ucrt))
    {
        return app_policy_get_show_developer_diagnostic_claims(GetCurrentThreadEffectiveToken(), policy);
    }

    return STATUS_NOT_FOUND;
}

LONG WINAPI __acrt_AppPolicyGetWindowingModelInternal(_Out_ AppPolicyWindowingModel* policy)
{
    if (auto const app_policy_get_windowing_model_claims = TRY_GET_API(AppPolicyGetWindowingModel, Crt_Ucrt))
    {
        return app_policy_get_windowing_model_claims(GetCurrentThreadEffectiveToken(), policy);
    }

    return STATUS_NOT_FOUND;
}

BOOL WINAPI __acrt_SetThreadStackGuarantee(PULONG const stack_size_in_bytes)
{
    if (auto const set_thread_stack_guarantee = TRY_GET_API(SetThreadStackGuarantee, Crt_Ucrt))
    {
        return set_thread_stack_guarantee(stack_size_in_bytes);
    }

    return FALSE;
}

bool __cdecl __acrt_can_show_message_box()
{
    bool can_show_message_box = false;
    if (__acrt_get_windowing_model_policy() == windowing_model_policy_hwnd
        && TRY_GET_API(MessageBoxA, Crt_Ucrt) != nullptr
        && TRY_GET_API(MessageBoxW, Crt_Ucrt) != nullptr)
    {
        can_show_message_box = true;
    }
    return can_show_message_box;
}

bool __cdecl __acrt_can_use_vista_locale_apis()
{
    return TRY_GET_API(CompareStringEx, Crt_Ucrt) != nullptr;
}

// This function simply attempts to get each of the locale-related APIs.  This
// allows a caller to "pre-load" the modules in which these APIs are hosted.  We
// use this in the _wsetlocale implementation to avoid calls to LoadLibrary while
// the locale lock is held.
void __cdecl __acrt_eagerly_load_locale_apis()
{
    TRY_GET_API(AreFileApisANSI, Crt_Ucrt);
    TRY_GET_API(CompareStringEx, Crt_Ucrt);
    TRY_GET_API(EnumSystemLocalesEx, Crt_Ucrt);
    TRY_GET_API(GetDateFormatEx, Crt_Ucrt);
    TRY_GET_API(GetLocaleInfoEx, Crt_Ucrt);
    TRY_GET_API(GetTimeFormatEx, Crt_Ucrt);
    TRY_GET_API(GetUserDefaultLocaleName, Crt_Ucrt);
    TRY_GET_API(IsValidLocaleName, Crt_Ucrt);
    TRY_GET_API(LCMapStringEx, Crt_Ucrt);
    TRY_GET_API(LCIDToLocaleName, Crt_Ucrt);
    TRY_GET_API(LocaleNameToLCID, Crt_Ucrt);
}

bool __cdecl __acrt_tls2_supported()
{
    return TRY_GET_API(FlsGetValue2, Crt_Ucrt) != nullptr;
}

bool __cdecl __acrt_can_use_xstate_apis()
{
    return TRY_GET_API(LocateXStateFeature, Crt_Ucrt) != nullptr;
}

HWND __cdecl __acrt_get_parent_window()
{
    auto const get_active_window = TRY_GET_API(GetActiveWindow, Crt_Ucrt);
    if (!get_active_window)
    {
        return nullptr;
    }

    HWND const active_window = get_active_window();
    if (!active_window)
    {
        return nullptr;
    }

    auto const get_last_active_popup = TRY_GET_API(GetLastActivePopup, Crt_Ucrt);
    if (!get_last_active_popup)
    {
        return active_window;
    }

    return get_last_active_popup(active_window);
}

bool __cdecl __acrt_is_interactive()
{
    auto const get_process_window_station = TRY_GET_API(GetProcessWindowStation, Crt_Ucrt);
    if (!get_process_window_station)
    {
        return true;
    }

    auto const get_user_object_information = TRY_GET_API(GetUserObjectInformationW, Crt_Ucrt);
    if (!get_user_object_information)
    {
        return true;
    }

    HWINSTA const hwinsta = get_process_window_station();
    if (!hwinsta)
    {
        return false;
    }

    USEROBJECTFLAGS uof{};
    if (!get_user_object_information(hwinsta, UOI_FLAGS, &uof, sizeof(uof), nullptr))
    {
        return false;
    }

    if ((uof.dwFlags & WSF_VISIBLE) == 0)
    {
        return false;
    }

    return true;
}

/* VCRT Thunks */

DWORD __cdecl __vcrt_FlsAlloc(_In_opt_ PFLS_CALLBACK_FUNCTION const callback)
{
    if (auto const fls_alloc = TRY_GET_API(FlsAlloc, Crt_Vcrt))
    {
        return fls_alloc(callback);
    }

    return TlsAlloc();
}

BOOL __cdecl __vcrt_FlsFree(_In_ DWORD const fls_index)
{
    if (auto const fls_free = TRY_GET_API(FlsFree, Crt_Vcrt))
    {
        return fls_free(fls_index);
    }

    return TlsFree(fls_index);
}

PVOID __cdecl __vcrt_FlsGetValue(_In_ DWORD const fls_index)
{
    if (auto const fls_get_value = TRY_GET_API(FlsGetValue, Crt_Vcrt))
    {
        return fls_get_value(fls_index);
    }

    return TlsGetValue(fls_index);
}

BOOL __cdecl __vcrt_FlsSetValue(_In_ DWORD const fls_index, _In_opt_ PVOID const fls_data)
{
    if (auto const fls_set_value = TRY_GET_API(FlsSetValue, Crt_Vcrt))
    {
        return fls_set_value(fls_index, fls_data);
    }

    return TlsSetValue(fls_index, fls_data);
}

BOOL __cdecl __vcrt_InitializeCriticalSectionEx(
    _Out_ LPCRITICAL_SECTION const critical_section,
    _In_  DWORD              const spin_count,
    _In_  DWORD              const flags
)
{
    return _CRT_InitializeCriticalSectionEx(critical_section, spin_count, flags);
}

EXTERN_C_END
