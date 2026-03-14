#include <windows.h>
#include <stdio.h>

unsigned long long du(const char *path)
{
    char search[MAX_PATH];
    snprintf(search, MAX_PATH, "%s\\*", path);

    WIN32_FIND_DATA fd;
    HANDLE h = FindFirstFile(search, &fd);

    if (h == INVALID_HANDLE_VALUE)
        return 0;

    unsigned long long total = 0;

    do {

        if (!strcmp(fd.cFileName, ".") || !strcmp(fd.cFileName, ".."))
            continue;

        char full[MAX_PATH];
        snprintf(full, MAX_PATH, "%s\\%s", path, fd.cFileName);

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            total += du(full);
        } else {
            LARGE_INTEGER size;
            size.HighPart = fd.nFileSizeHigh;
            size.LowPart = fd.nFileSizeLow;
            total += size.QuadPart;
        }

    } while (FindNextFile(h, &fd));

    FindClose(h);

    return total;
}

int main(int argc, char *argv[])
{
    const char *path = ".";

    if (argc > 1)
        path = argv[1];

    unsigned long long size = du(path);

    printf("%llu bytes\t%s\n", size, path);

    return 0;
}