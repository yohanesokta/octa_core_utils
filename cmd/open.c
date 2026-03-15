/*
 * Copyright (c) 2026 YohanesOktanio. All rights reserved.
 * Octa Core Utils - Utility commands for Windows.
 */
#include <windows.h>
#include <shellapi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: open <file|url|folder>\n");
        return 1;
    }

    HINSTANCE result = ShellExecuteA(
        NULL,
        "open",
        argv[1],
        NULL,
        NULL,
        SW_SHOWNORMAL
    );

    if ((INT_PTR)result <= 32) {
        printf("open: failed to open '%s'\n", argv[1]);
        return 1;
    }

    return 0;
}