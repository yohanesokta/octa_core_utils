/*
    Copyright (c) 2026 Yohanes Oktanio
    This software is released under the GNU GENERAL PUBLIC LICENSE Version 3 (GPL-3.0)
    See LICENSE file for more details.
*/

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    char path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH);

    char *p = strrchr(path, '\\');
    if (p) strcpy(p+1, "octa_init.ps1");

    char cmd[1024];
    sprintf(cmd, "powershell -ExecutionPolicy Bypass -File \"%s\"", path);

    system(cmd);
    return 0;
}