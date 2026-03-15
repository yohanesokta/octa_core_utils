/*
 * Copyright (c) 2026 YohanesOktanio. All rights reserved.
 * Octa Core Utils - Utility commands for Windows.
 */
#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: rmdir <directory>\n");
        return 1;
    }

    if (RemoveDirectory(argv[1])) {
        return 0;
    } else {
        printf("rmdir: failed to remove '%s'\n", argv[1]);
        return 1;
    }
}