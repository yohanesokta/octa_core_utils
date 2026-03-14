#include <stdio.h>
#include <windows.h>
#include <string.h>

int is_directory(const char *path) {
    DWORD attr = GetFileAttributes(path);
    return (attr != INVALID_FILE_ATTRIBUTES &&
           (attr & FILE_ATTRIBUTE_DIRECTORY));
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Usage: mv <source> <destination>\n");
        return 1;
    }

    char dest[MAX_PATH];

    if (is_directory(argv[2])) {

        char *name = strrchr(argv[1], '\\');
        if (!name)
            name = argv[1];
        else
            name++;

        snprintf(dest, MAX_PATH, "%s\\%s", argv[2], name);

    } else {
        snprintf(dest, MAX_PATH, "%s", argv[2]);
    }

    if (!MoveFileEx(argv[1], dest, MOVEFILE_REPLACE_EXISTING)) {
        printf("Move failed\n");
        return 1;
    }

    return 0;
}