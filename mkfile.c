#include <stdio.h>
#include <stdlib.h>

void create_file(const char* fileName, const char* path) {
    char fullPath[100];
    sprintf(fullPath, "%s/%s", path, fileName);
    FILE* createFile = fopen(fullPath, "w");
    fclose(createFile);
}
 
int main(int argc, char *argv[]) {
    const char* path;

    if (argc == 1) {
        printf("Please provide a file name");
        return 0;
    }

    if (argc > 3) {
        path = ".";
    } else {
        path = argv[2];
    }

    create_file(argv[1], path);

    printf("Created file \033[1;32m%s\033[0m in \033[1;33m%s\033[0m\n", argv[1], path);
}
