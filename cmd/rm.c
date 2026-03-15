/*
 * Copyright (c) 2026 YohanesOktanio. All rights reserved.
 * Octa Core Utils - Utility commands for Windows.
 */
#include <stdio.h>
#include <windows.h>
#include <string.h>

void delete_recursive(const char *path) {
    char search[MAX_PATH];
    WIN32_FIND_DATA fd;
    HANDLE h;

    snprintf(search, MAX_PATH, "%s\\*", path);

    h = FindFirstFile(search, &fd);
    if (h == INVALID_HANDLE_VALUE)
        return;

    do {
        if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0)
            continue;

        char full[MAX_PATH];
        snprintf(full, MAX_PATH, "%s\\%s", path, fd.cFileName);

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            delete_recursive(full);
            RemoveDirectory(full);
        } else {
            DeleteFile(full);
        }

    } while (FindNextFile(h, &fd));

    FindClose(h);
}

int main(int argc, char *argv[]) {

    int recursive = 0;
    int force = 0;
    char *target = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "-rf") == 0 || strcmp(argv[i], "-fr") == 0)
            recursive = 1;
        else if (strcmp(argv[i], "-f") == 0)
            force = 1;
        else
            target = argv[i];
    }

    if (!target) {
        printf("Usage: rm [-r] [-f] file\n");
        return 1;
    }

    DWORD attr = GetFileAttributes(target);

    if (attr == INVALID_FILE_ATTRIBUTES) {
        if (!force)
            printf("File not found\n");
        return 1;
    }

    if (attr & FILE_ATTRIBUTE_DIRECTORY) {

        if (!recursive) {
            printf("Cannot remove directory without -r\n");
            return 1;
        }

        delete_recursive(target);
        RemoveDirectory(target);

    } else {
        if (!DeleteFile(target) && !force) {
            printf("Failed to delete file\n");
            return 1;
        }
    }

    return 0;
}