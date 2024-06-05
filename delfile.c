#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void delete_file(const char* fileName) {
    char fullPath[100];
    sprintf(fullPath, "%s", fileName);
    remove(fullPath);
}
 
int main(int argc, char *argv[]) {
    const char* path;

    if (argc == 1) {
        printf("Please provide a file name");
        return 0;
    }

    delete_file(argv[1]);
    printf("Deleted file \033[1;32m%s\033[0m\n", argv[1]);
}

