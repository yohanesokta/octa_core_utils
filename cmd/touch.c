#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: touch <file>\n");
        return 1;
    }

    HANDLE h = CreateFile(
        argv[1],
        GENERIC_WRITE,
        0,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (h == INVALID_HANDLE_VALUE) {
        printf("Failed to open or create file\n");
        return 1;
    }

    FILETIME now;
    GetSystemTimeAsFileTime(&now);

    SetFileTime(h, NULL, NULL, &now);

    CloseHandle(h);

    return 0;
}