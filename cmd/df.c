#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    const char *path = "C:\\";

    if (argc > 1)
        path = argv[1];

    ULARGE_INTEGER freeBytes;
    ULARGE_INTEGER totalBytes;
    ULARGE_INTEGER totalFree;

    if (!GetDiskFreeSpaceEx(
        path,
        &freeBytes,
        &totalBytes,
        &totalFree))
    {
        printf("df: cannot access %s\n", path);
        return 1;
    }

    printf("Filesystem: %s\n", path);
    printf("Total: %llu MB\n", totalBytes.QuadPart / 1024 / 1024);
    printf("Used: %llu MB\n", 
        (totalBytes.QuadPart - totalFree.QuadPart) / 1024 / 1024);
    printf("Free: %llu MB\n", totalFree.QuadPart / 1024 / 1024);

    return 0;
}