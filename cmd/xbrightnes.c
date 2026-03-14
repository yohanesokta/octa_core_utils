#include <windows.h>
#include <stdio.h>
#include <physicalmonitorenumerationapi.h>
#include <highlevelmonitorconfigurationapi.h>

#pragma comment(lib, "dxva2.lib")

PHYSICAL_MONITOR monitor;

BOOL CALLBACK MonitorEnum(HMONITOR hMon, HDC hdc, LPRECT rect, LPARAM data) {

    DWORD count = 0;

    if (!GetNumberOfPhysicalMonitorsFromHMONITOR(hMon, &count))
        return FALSE;

    PHYSICAL_MONITOR *mons = malloc(sizeof(PHYSICAL_MONITOR) * count);

    if (!GetPhysicalMonitorsFromHMONITOR(hMon, count, mons))
        return FALSE;

    monitor = mons[0];

    free(mons);

    return FALSE; 
}

int main(int argc, char *argv[]) {

    EnumDisplayMonitors(NULL, NULL, MonitorEnum, 0);

    DWORD min, cur, max;

    if (!GetMonitorBrightness(monitor.hPhysicalMonitor, &min, &cur, &max)) {
        printf("brightness: monitor not supported\n");
        return 1;
    }

    if (argc == 1) {
        printf("Brightness: %lu%%\n", cur);
        return 0;
    }

    int value = atoi(argv[1]);

    if (value < 0 || value > 100) {
        printf("usage: brightness <0-100>\n");
        return 1;
    }

    if (!SetMonitorBrightness(monitor.hPhysicalMonitor, value)) {
        printf("brightness: failed\n");
        return 1;
    }

    printf("Brightness set to %d%%\n", value);

    DestroyPhysicalMonitor(monitor.hPhysicalMonitor);

    return 0;
}