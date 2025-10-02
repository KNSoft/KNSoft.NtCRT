#pragma once

#include <KNSoft/NDK/NT/MinDef.h>

/* ImageHlp.h */

#define UNDNAME_COMPLETE                 (0x0000)  // Enable full undecoration
#define UNDNAME_NO_LEADING_UNDERSCORES   (0x0001)  // Remove leading underscores from MS extended keywords
#define UNDNAME_NO_MS_KEYWORDS           (0x0002)  // Disable expansion of MS extended keywords
#define UNDNAME_NO_FUNCTION_RETURNS      (0x0004)  // Disable expansion of return type for primary declaration
#define UNDNAME_NO_ALLOCATION_MODEL      (0x0008)  // Disable expansion of the declaration model
#define UNDNAME_NO_ALLOCATION_LANGUAGE   (0x0010)  // Disable expansion of the declaration language specifier
#define UNDNAME_NO_MS_THISTYPE           (0x0020)  // NYI Disable expansion of MS keywords on the 'this' type for primary declaration
#define UNDNAME_NO_CV_THISTYPE           (0x0040)  // NYI Disable expansion of CV modifiers on the 'this' type for primary declaration
#define UNDNAME_NO_THISTYPE              (0x0060)  // Disable all modifiers on the 'this' type
#define UNDNAME_NO_ACCESS_SPECIFIERS     (0x0080)  // Disable expansion of access specifiers for members
#define UNDNAME_NO_THROW_SIGNATURES      (0x0100)  // Disable expansion of 'throw-signatures' for functions and pointers to functions
#define UNDNAME_NO_MEMBER_TYPE           (0x0200)  // Disable expansion of 'static' or 'virtual'ness of members
#define UNDNAME_NO_RETURN_UDT_MODEL      (0x0400)  // Disable expansion of MS model for UDT returns
#define UNDNAME_32_BIT_DECODE            (0x0800)  // Undecorate 32-bit decorated names
#define UNDNAME_NAME_ONLY                (0x1000)  // Crack only the name for primary declaration;
                                                   //  return just [scope::]name.  Does expand template params
#define UNDNAME_NO_ARGUMENTS             (0x2000)  // Don't undecorate arguments to function
#define UNDNAME_NO_SPECIAL_SYMS          (0x4000)  // Don't undecorate special names (v-table, vcall, vector xxx, metatype, etc)

/*
 * Debug Interface Access SDK
 *   See also: https://learn.microsoft.com/en-us/visualstudio/debugger/debug-interface-access/idiasymbol-get-undecoratednameex
 */

#define UNDNAME_RESERVED1           UNDNAME_NO_MS_THISTYPE
#define UNDNAME_RESERVED2           UNDNAME_NO_CV_THISTYPE
#define UNDNAME_TYPE_ONLY           UNDNAME_NO_ARGUMENTS    // Input is just a type encoding; composes an abstract declarator.
#define UNDNAME_HAVE_PARAMETERS     UNDNAME_NO_SPECIAL_SYMS // The real template parameters are available.
#define UNDNAME_NO_ECSU             (0x8000)                // Suppresses enum/class/struct/union.
#define UNDNAME_NO_IDENT_CHAR_CHECK (0x10000)               // Suppresses check for valid identifier characters.
#define UNDNAME_NO_PTR64            (0x20000)               // Does not include ptr64 in output.

typedef char* pchar_t;
typedef const char* pcchar_t;
typedef void* (__cdecl* Alloc_t)(size_t const);
typedef void(__cdecl* Free_t)(void* const);
typedef char* (__cdecl* GetParameter_t)(long);

EXTERN_C_START

_CRTIMP char* __cdecl __unDName(pchar_t, pcchar_t, int, Alloc_t, Free_t, unsigned short);
_CRTIMP pchar_t __cdecl unDNameEx(pchar_t, pcchar_t, int, Alloc_t, Free_t, GetParameter_t, unsigned long);

EXTERN_C_END
