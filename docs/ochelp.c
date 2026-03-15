/*
 * Copyright (c) 2026 YohanesOktanio. All rights reserved.
 * Octa Core Utils - Utility commands for Windows.
 */
#include <stdio.h>
#include "ochelp_data.h"

int main() {
    if (help_text) {
        printf("%s", help_text);
    } else {
        printf("Error: Help text not found.\n");
        return 1;
    }
    return 0;
}
