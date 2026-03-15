/*
 * Copyright (c) 2026 YohanesOktanio. All rights reserved.
 * Octa Core Utils - Utility commands for Windows.
 */
#include <windows.h>
#include <stdio.h>

int main() {

    LPCH env = GetEnvironmentStringsA();
    LPCH var = env;

    while (*var) {
        printf("%s\n", var);
        var += strlen(var) + 1;
    }

    FreeEnvironmentStringsA(env);

    return 0;
}