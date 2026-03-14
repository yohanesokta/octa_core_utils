#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int file_exists(const char *path) {
    DWORD attr = GetFileAttributes(path);
    return (attr != INVALID_FILE_ATTRIBUTES &&
           !(attr & FILE_ATTRIBUTE_DIRECTORY));
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: which <program>\n");
        return 1;
    }

    char *path = getenv("PATH");
    if (!path) {
        printf("PATH not found\n");
        return 1;
    }

    char *token = strtok(path, ";");

    while (token) {

        char full[MAX_PATH];
        snprintf(full, MAX_PATH, "%s\\%s.exe", token, argv[1]);

        if (file_exists(full)) {
            printf("%s\n", full);
            return 0;
        }

        token = strtok(NULL, ";");
    }

    printf("Command not found\n");
    return 1;
}