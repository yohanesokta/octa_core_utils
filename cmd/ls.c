/*
 * Copyright (c) 2026 YohanesOktanio. All rights reserved.
 * Octa Core Utils - Utility commands for Windows.
 */
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <time.h>

void print_time(FILETIME ft) {
    SYSTEMTIME st;
    FileTimeToSystemTime(&ft, &st);

    printf("%04d-%02d-%02d %02d:%02d ",
           st.wYear, st.wMonth, st.wDay,
           st.wHour, st.wMinute);
}

int main(int argc, char *argv[]) {

    int show_all = 0;
    int long_mode = 0;
    int long_long = 0;

    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "-a") == 0)
            show_all = 1;

        if (strcmp(argv[i], "-l") == 0)
            long_mode = 1;

        if (strcmp(argv[i], "-ll") == 0) {
            long_mode = 1;
            long_long = 1;
        }
    }

    WIN32_FIND_DATA fd;
    HANDLE h = FindFirstFile("*", &fd);

    if (h == INVALID_HANDLE_VALUE)
        return 1;

    do {

        if (!show_all && (fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
            continue;

        if (!long_mode) {

            printf("%s\n", fd.cFileName);

        } else {

            char type = (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? 'd' : '-';

            printf("%c ", type);

            LARGE_INTEGER size;
            size.HighPart = fd.nFileSizeHigh;
            size.LowPart = fd.nFileSizeLow;

            printf("%10lld ", size.QuadPart);

            print_time(fd.ftLastWriteTime);

            printf("%s", fd.cFileName);

            if (long_long) {

                if (fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
                    printf(" [hidden]");

                if (fd.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
                    printf(" [ro]");

            }

            printf("\n");
        }

    } while (FindNextFile(h, &fd));

    FindClose(h);

    return 0;
}