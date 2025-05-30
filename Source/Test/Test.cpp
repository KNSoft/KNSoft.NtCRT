#include <KNSoft/NDK/NDK.h>

int main()
{
    void* p;
    p = new char[100];
    DbgPrint("%p\n", p);
    delete[] p;
    return 0;
}
