#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <pattern>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *pattern = argv[1];
    char line[1024];

    while (fgets(line, sizeof(line), stdin)) {
        if (strstr(line, pattern)) {
            fputs(line, stdout);
        }
    }
    
    return EXIT_SUCCESS;
}