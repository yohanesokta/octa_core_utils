/*
 * Copyright (c) 2026 YohanesOktanio. All rights reserved.
 * Octa Core Utils - Utility commands for Windows.
 */
#include <stdio.h>
#include <windows.h>

int main() {

    char path[MAX_PATH];

    DWORD len = GetCurrentDirectory(MAX_PATH, path);

    if (len == 0) {
        printf("Error getting current directory\n");
        return 1;
    }

    printf("%s\n", path);

    return 0;
}