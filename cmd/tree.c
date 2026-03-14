#include <windows.h>
#include <stdio.h>
#include <string.h>

int files = 0;
int dirs = 0;

void tree(const char *path, int depth)
{
    char search[MAX_PATH];
    snprintf(search, MAX_PATH, "%s\\*", path);

    WIN32_FIND_DATA fd;
    HANDLE h = FindFirstFile(search, &fd);

    if (h == INVALID_HANDLE_VALUE)
        return;

    do {

        if (!strcmp(fd.cFileName, ".") || !strcmp(fd.cFileName, ".."))
            continue;

        for (int i = 0; i < depth; i++)
            printf("│   ");

        printf("├── %s\n", fd.cFileName);

        char full[MAX_PATH];
        snprintf(full, MAX_PATH, "%s\\%s", path, fd.cFileName);

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            dirs++;
            tree(full, depth + 1);
        } else {
            files++;
        }

    } while (FindNextFile(h, &fd));

    FindClose(h);
}

int main(int argc, char *argv[])
{
    const char *path = ".";

    if (argc > 1)
        path = argv[1];

    printf("%s\n", path);

    tree(path, 0);

    printf("\n%d directories, %d files\n", dirs, files);

    return 0;
}