#include <windows.h>
#include <stdio.h>

void print_time(FILETIME ft)
{
    SYSTEMTIME utc, local;
    FileTimeToSystemTime(&ft, &utc);
    SystemTimeToTzSpecificLocalTime(NULL, &utc, &local);

    printf("%04d-%02d-%02d %02d:%02d:%02d",
        local.wYear, local.wMonth, local.wDay,
        local.wHour, local.wMinute, local.wSecond);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: stat <file>\n");
        return 1;
    }

    HANDLE h = CreateFile(
        argv[1],
        0,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (h == INVALID_HANDLE_VALUE) {
        printf("stat: cannot open %s\n", argv[1]);
        return 1;
    }

    BY_HANDLE_FILE_INFORMATION info;

    if (!GetFileInformationByHandle(h, &info)) {
        printf("stat: failed\n");
        CloseHandle(h);
        return 1;
    }

    LARGE_INTEGER size;
    size.HighPart = info.nFileSizeHigh;
    size.LowPart  = info.nFileSizeLow;

    printf("File: %s\n", argv[1]);
    printf("Size: %lld bytes\n", size.QuadPart);

    printf("Links: %lu\n", info.nNumberOfLinks);

    printf("File Index: %lu:%lu\n",
        info.nFileIndexHigh,
        info.nFileIndexLow);

    printf("Volume Serial: %lu\n",
        info.dwVolumeSerialNumber);

    printf("Attributes: ");

    if (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) printf("directory ");
    if (info.dwFileAttributes & FILE_ATTRIBUTE_READONLY) printf("readonly ");
    if (info.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) printf("hidden ");
    if (info.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) printf("system ");
    if (info.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) printf("archive ");

    printf("\n");

    printf("Created:  ");
    print_time(info.ftCreationTime);
    printf("\n");

    printf("Accessed: ");
    print_time(info.ftLastAccessTime);
    printf("\n");

    printf("Modified: ");
    print_time(info.ftLastWriteTime);
    printf("\n");

    CloseHandle(h);
    return 0;
}