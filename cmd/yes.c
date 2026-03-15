/*
 * Copyright (c) 2026 YohanesOktanio. All rights reserved.
 * Octa Core Utils - Utility commands for Windows.
 */
#include <stdio.h>

int main(int argc, char *argv[]) {

    const char *str = "y";

    if (argc > 1)
        str = argv[1];

    while (1) {
        printf("%s\n", str);
    }

    return 0;
}