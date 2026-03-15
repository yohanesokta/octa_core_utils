/*
 * Copyright (c) 2026 YohanesOktanio. All rights reserved.
 * Octa Core Utils - Utility commands for Windows.
 */
#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Usage: cp <source> <destination>\n");
        return 1;
    }

    if (!CopyFile(argv[1], argv[2], FALSE)) {
        printf("Copy failed\n");
        return 1;
    }

    return 0;
}