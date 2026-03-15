/*
 * Copyright (c) 2026 YohanesOktanio. All rights reserved.
 * Octa Core Utils - Utility commands for Windows.
 */
#include <stdio.h>

void print_file(const char *name) {

    FILE *f = fopen(name, "rb");

    if (!f) {
        printf("cat: cannot open %s\n", name);
        return;
    }

    int c;
    while ((c = fgetc(f)) != EOF)
        putchar(c);

    fclose(f);
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: cat <file...>\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
        print_file(argv[i]);

    return 0;
}