#include <windows.h>
#include <stdio.h>

int main() {
    char username[256];
    DWORD size = sizeof(username);

    if (GetUserNameA(username, &size)) {
        printf("%s\n", username);
    } else {
        fprintf(stderr, "whoami: failed to get username\n");
        return 1;
    }

    return 0;
}