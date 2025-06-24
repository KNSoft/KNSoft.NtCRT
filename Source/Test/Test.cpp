#include <KNSoft/NDK/NDK.h>

#include <stdio.h>
#include <conio.h>

int main()
{
    void* p;
    p = new char[100];
    DbgPrint("%p\n", p);
    delete[] p;
    _putwch(L'a');
    _putwch(L'\n');
    _cputws(L"xxxxxxxx\nxxx\n");
    return 0;
}
