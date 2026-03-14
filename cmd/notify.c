#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: notify [-i|-w|-e|-q] <message>\n");
        return 1;
    }

    UINT flags = MB_OK | MB_ICONINFORMATION;
    char *msg = argv[1];

    if (!strcmp(argv[1], "-i")) {
        flags = MB_OK | MB_ICONINFORMATION;
        msg = argv[2];
    }
    else if (!strcmp(argv[1], "-w")) {
        flags = MB_OK | MB_ICONWARNING;
        msg = argv[2];
    }
    else if (!strcmp(argv[1], "-e")) {
        flags = MB_OK | MB_ICONERROR;
        msg = argv[2];
    }
    else if (!strcmp(argv[1], "-q")) {
        flags = MB_OK | MB_ICONQUESTION;
        msg = argv[2];
    }

    MessageBoxA(
        NULL,
        msg,
        "Octa Core Notify",
        flags
    );

    return 0;
}