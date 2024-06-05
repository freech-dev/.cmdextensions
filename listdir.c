#include <stdio.h>
#include <windows.h>
#include <time.h>

void ls(const char *path) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    char fullPath[MAX_PATH];
    sprintf(fullPath, "%s\\*", path);
    hFind = FindFirstFile(fullPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error opening directory\n");
        return;
    }

    do {
        if (strcmp(findFileData.cFileName, ".") == 0 || strcmp(findFileData.cFileName, "..") == 0) {
            continue;
        }
        sprintf(fullPath, "%s\\%s", path, findFileData.cFileName);
        char fileType[20];
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            sprintf(fileType, "\033[1;32m[Folder]\033[0m");
        } else {
            sprintf(fileType, "\033[1;34m[File]\033[0m");
        }
        FILETIME localFileTime;
        SYSTEMTIME systemTime;
        FileTimeToLocalFileTime(&findFileData.ftCreationTime, &localFileTime);
        FileTimeToSystemTime(&localFileTime, &systemTime);
        FILETIME fileTime;
        SystemTimeToFileTime(&systemTime, &fileTime);
        ULARGE_INTEGER uli;
        uli.LowPart = fileTime.dwLowDateTime;
        uli.HighPart = fileTime.dwHighDateTime;
        time_t creationTime = (uli.QuadPart - 116444736000000000) / 10000000;
        printf("%-20s %-30s \033[1;33m%s\033[0m", fileType, findFileData.cFileName, ctime(&creationTime));
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

int main(int argc, char *argv[]) {
    const char *path;

    if (argc < 2) {
        path = ".";
    } else {
        path = argv[1];
    } 

    ls(path);

    return 0;
}