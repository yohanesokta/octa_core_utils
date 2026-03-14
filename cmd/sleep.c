#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: sleep <seconds>\n");
        return 1;
    }

    double sec = atof(argv[1]);

    if (sec < 0) {
        printf("sleep: invalid time\n");
        return 1;
    }

    Sleep((DWORD)(sec * 1000));

    return 0;
}