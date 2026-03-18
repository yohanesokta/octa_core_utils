#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h> 
#include <sys/stat.h>
#include <errno.h>
#include "cJSON.h"

#define PATH_MAX 4096

char config_path[PATH_MAX];

int ensure_folder(const char *path)
{
#ifdef _WIN32
    return _mkdir(path) == 0 || errno == EEXIST;
#else
    return mkdir(path, 0755) == 0 || errno == EEXIST;
#endif
}

void init_config_path()
{
    char cwd[PATH_MAX];
    if (_getcwd(cwd, sizeof(cwd)) != NULL)
    {
        char vscode_folder[PATH_MAX];
        snprintf(vscode_folder, PATH_MAX, "%s\\.vscode", cwd);
        ensure_folder(vscode_folder);

        snprintf(config_path, PATH_MAX, "%s\\.vscode\\settings.json", cwd);
    }
    else
    {
        fprintf(stderr, "Failed to get current working directory\n");
        exit(EXIT_FAILURE);
    }
}

char *read_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return NULL;

    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(len + 1);
    if (!data)
        return NULL;

    fread(data, 1, len, file);
    data[len] = '\0';
    fclose(file);
    return data;
}

int write_file(const char *filename, const char *data)
{
    FILE *file = fopen(filename, "w");
    if (!file)
        return 0;
    fprintf(file, "%s", data);
    fclose(file);
    return 1;
}


void update_setting(const char *key, int value) {
    
    char *json_data = read_file(config_path);
    cJSON *root = NULL;

    if (json_data && strlen(json_data) > 0) {
        root = cJSON_Parse(json_data);
        free(json_data);
        if (!root) {
            fprintf(stderr, "Warning: Failed to parse existing JSON, creating new root\n");
            root = cJSON_CreateObject();
        }
    } else {
        free(json_data);
        root = cJSON_CreateObject(); 
    }

    
    cJSON_DeleteItemFromObject(root, key);

    cJSON_AddNumberToObject(root, key, value);

    
    char *out = cJSON_Print(root);
    if (!write_file(config_path, out)) {
        fprintf(stderr, "Failed to write to %s\n", config_path);
    }

    free(out);
    cJSON_Delete(root);
}

void print_usage(const char *prog_name)
{
    printf("Usage: %s <option> <value>\n", prog_name);
    printf("Options:\n");
    printf("  fcode  -> Editor font size\n");
    printf("  fterm  -> Terminal font size\n");
    printf("  set    -> Set theme (light/dark/clear)\n");
}

void unset_setting(const char *key) {
    char *json_data = read_file(config_path);
    cJSON *root = NULL;

    if (json_data) {
        root = cJSON_Parse(json_data);
        free(json_data);
    }

    if (!root) return;

    cJSON_DeleteItemFromObject(root, key);

    char *out = cJSON_Print(root);
    if (write_file(config_path, out)) {
        printf("Removed setting %s from %s\n", key, config_path);
    } else {
        fprintf(stderr, "Failed to write to %s\n", config_path);
    }

    free(out);
    cJSON_Delete(root);
}

void update_setting_str(const char *key, const char *value) {
    char *json_data = read_file(config_path);
    cJSON *root = NULL;

    if (json_data) {
        root = cJSON_Parse(json_data);
        free(json_data);
    }

    if (!root) {
        root = cJSON_CreateObject();
    }

    cJSON *existing = cJSON_GetObjectItem(root, key);
    if (existing)
        cJSON_ReplaceItemInObject(root, key, cJSON_CreateString(value));
    else
        cJSON_AddStringToObject(root, key, value);

    char *out = cJSON_Print(root);
    if (write_file(config_path, out)) {
        printf("Updated %s to \"%s\" in %s\n", key, value, config_path);
    } else {
        fprintf(stderr, "Failed to write to %s\n", config_path);
    }

    free(out);
    cJSON_Delete(root);
}
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    init_config_path();

    const char *option = argv[1];
    int value = atoi(argv[2]);

    if (strcmp(option, "fcode") == 0)
    {
        update_setting("editor.fontSize", value);
    }
    else if (strcmp(option, "fterm") == 0)
    {
        update_setting("terminal.integrated.fontSize", value);
    }
    else if (strcmp(option, "set") == 0)
    {
        printf("Setting theme to: %s\n", argv[2]);
        if (strcmp(argv[2], "light") == 0)
        {
            update_setting_str("workbench.colorTheme", "Default Light+");
        }
        else if (strcmp(argv[2], "dark") == 0)
        {
            update_setting_str("workbench.colorTheme", "Default Dark+");
        }
        else if (strcmp(argv[2], "clear") == 0)
        {
            unset_setting("workbench.colorTheme");
        }
        else
        {
            fprintf(stderr, "Unknown theme: %s\n", argv[2]);
            print_usage(argv[0]);
            return EXIT_FAILURE;
        }
    }
    else
    {
        fprintf(stderr, "Unknown option: %s\n", option);
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}