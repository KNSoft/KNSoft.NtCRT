#pragma once

#include "../NtCRT.inl"

#include <heap/calloc_base.cpp>
#include <heap/expand.cpp>
#include <heap/free_base.cpp>
#include <heap/heap_handle.cpp>
#include <heap/heapchk.cpp>
#include <heap/heapmin.cpp>
#include <heap/malloc_base.cpp>
#include <heap/msize.cpp>
#include <heap/realloc_base.cpp>

EXTERN_C_START

/* TODO: Verify me */
/* _heapwalk, see also: $(UCRTContentRoot)Source\$(TargetUniversalCRTVersion)\ucrt\heap\heapwalk.cpp */

static
int
__cdecl
try_walk(PRTL_HEAP_WALK_ENTRY const entry) throw()
{
    __try
    {
        NTSTATUS Status = RtlWalkHeap(__acrt_heap, entry);
        if (NT_SUCCESS(Status))
        {
            return _HEAPOK;
        } else if (Status == STATUS_NO_MORE_ENTRIES)
        {
            return _HEAPEND;
        }
        return _HEAPBADNODE;
    } __except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION)
    {
        return _HEAPBADNODE;
    }
}

_ACRTIMP
int
__cdecl
_heapwalk(
    _Inout_ _HEAPINFO * _EntryInfo)
{
    _VALIDATE_RETURN(_EntryInfo != nullptr, EINVAL, _HEAPBADPTR);

    RTL_HEAP_WALK_ENTRY entry = { 0 };
    entry.Flags = 0;
    entry.SegmentIndex = 0;
    entry.DataAddress = _EntryInfo->_pentry;

    if (entry.DataAddress == nullptr && !NT_SUCCESS(RtlWalkHeap(__acrt_heap, &entry)))
    {
        return _HEAPBADBEGIN;
    } else
    {
        if (_EntryInfo->_useflag == _USEDENTRY)
        {
            if (!RtlValidateHeap(__acrt_heap, 0, _EntryInfo->_pentry))
            {
                return _HEAPBADNODE;
            }
            entry.Flags = RTL_HEAP_BUSY;
        }

        int const status = try_walk(&entry);
        if (status != _HEAPOK)
        {
            return status;
        }
    }

    while (TRUE)
    {
        if (entry.Flags & RTL_HEAP_BUSY)
        {
            _EntryInfo->_pentry = static_cast<int*>(entry.DataAddress);
            _EntryInfo->_size = entry.DataSize;
            _EntryInfo->_useflag = _USEDENTRY;
            return _HEAPOK;
        }

        int const status = try_walk(&entry);
        if (status != _HEAPOK)
        {
            return status;
        }
    }
}

EXTERN_C_END
