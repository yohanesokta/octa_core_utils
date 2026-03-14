#include <stdio.h>

#ifdef _WIN32
extern char **_environ;
#define environ _environ
#else
extern char **environ;
#endif

int main() {
    char **env = environ;

    while (*env) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}