#include "NtCRT.inl"

#include "Misc/Func.inl"
#include "Internal.inl"
#include "Heap.inl"
#include "Lowio.inl"
#include "Stdio.inl"

#include "VCRT/VCRT.inl"

int func()
{
    void* p = new char[100];
    DbgPrint("%p\n", p);
    delete[] p;
    return 0;
}
