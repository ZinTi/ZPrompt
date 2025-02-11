// 系统库
#include <stdio.h>
#include <windows.h>

#include "color.h"

#define MAX_PATH_LISTPROG 1024

/**
 * @brief ZPrompt检查运行环境（检查设置了环境变量没有）
 * @param homePath OUT 项目根目录
 * @return 0 代表成功
 */
int checkEnv(char* homePath);

void printProgramFilename(const char* fileName);

void listFilesInDirectory(const char* directoryPath);

int listProgram(void);

/**
 * @brief 比较两个字符串是否相同，忽略英文字母大小写的差异
 * @param str1 字符串 1
 * @param str2 字符串 2
 * @return 返回 0 代表相同（大小写不敏感）
 */
int StrCmpIgnoreCase(const char* str1, const char* str2);

/**
 * @brief 比较两个字符串前 n 个字符是否相同，忽略英文字母大小写的差异
 * @param str1 字符串 1
 * @param str2 字符串 2
 * @param n 比较字符数
 * @return 返回 0 代表相同（大小写不敏感）
 */
int StrNCmpIgnoreCase(const char* str1, const char* str2, unsigned long long n);

TextColor fRed_bNone = {COLOR_RED, COLOR_NONE};
TextColor fLRed_bNone = {COLOR_BRIGHT_RED, COLOR_NONE};
TextColor fBlue_bNone = {COLOR_BLUE, COLOR_NONE};
TextColor fYellow_bNone = {COLOR_YELLOW, COLOR_NONE};
TextColor fGray_bLYellow = {COLOR_BRIGHT_BLACK, COLOR_BRIGHT_YELLOW};

int main(void) {
    listProgram();
    return 0;
}

int checkEnv(char* homePath) {
    if (homePath == NULL) {
        puts("CheckEnv: Please allocate memory first!");
        return -1;
    }

    if (getenv("ZPrompt_HOME") == NULL) {
        puts("ZPrompt is not installed!");
        return 1;
    }

    strcpy(homePath, getenv("ZPrompt_HOME"));
    return 0;
}

void printProgramFilename(const char* fileName) {
    const char* fileExtension = strrchr(fileName, '.');
    if (!StrCmpIgnoreCase(fileExtension, ".exe") || !StrCmpIgnoreCase(fileExtension, ".com") || !StrCmpIgnoreCase(fileExtension, ".bin")) {
        ColorPrintf(fRed_bNone, "%s", fileName);
    }
    else if (!StrCmpIgnoreCase(fileExtension, ".bat") || !StrCmpIgnoreCase(fileExtension, ".cmd") || !StrCmpIgnoreCase(fileExtension, ".vbs") || !StrCmpIgnoreCase(fileExtension, ".vbe")) {
        ColorPrintf(fLRed_bNone, "%s", fileName);
    }
    else if (!StrCmpIgnoreCase(fileExtension, ".ps1") || !StrCmpIgnoreCase(fileExtension, ".py") || !StrCmpIgnoreCase(fileExtension, ".pyw")) {
        ColorPrintf(fBlue_bNone, "%s", fileName);
    }
    else if (!StrCmpIgnoreCase(fileExtension, ".lnk")) {
        ColorPrintf(fYellow_bNone, "%s", fileName);
    }
    else {
        printf("%s", fileName);
    }
    putchar('\n');
}

void listFilesInDirectory(const char* directoryPath) {
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    char searchPath[MAX_PATH_LISTPROG];
    snprintf(searchPath, MAX_PATH_LISTPROG, "%s\\*.*", directoryPath);

    hFind = FindFirstFileA(searchPath, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Search failed, please check the path: %s\n", directoryPath);
        return;
    }

    do {
        const char* fileName = findFileData.cFileName;
        // 忽略.和..目录
        if (strcmp(fileName, ".") != 0 && strcmp(fileName, "..") != 0) {
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { // Ŀ¼
                ColorPrintf(fGray_bLYellow, "%s", fileName);
                putchar('\n');
            }
            else {
                printProgramFilename(fileName);
            }
        }
    }
    while (FindNextFileA(hFind, &findFileData) != 0);
    putchar('\n');

    FindClose(hFind);
}

int listProgram(void) {
    char homePath[MAX_PATH_LISTPROG];
    checkEnv(homePath);

    char* str[4] = {"\\bin", "\\scripts", "\\bin\\use", "\\bin\\win"};
    for (int i = 0; i < 4; i++) {
        char* path = (char*)malloc(MAX_PATH_LISTPROG);
        sprintf(path, "%s%s", homePath, str[i]);
        if (i == 2) {
            printf("\nuse <command> [args] ...\n");
        }
        else if (i == 3) {
            printf("\nwin <command> [args] ...\n");
        }
        listFilesInDirectory(path);
        free(path);
    }

    return 0;
}

int StrCmpIgnoreCase(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        char c1 = (*str1 >= 'A' && *str1 <= 'Z') ? (*str1 - 'A' + 'a') : *str1;
        char c2 = (*str2 >= 'A' && *str2 <= 'Z') ? (*str2 - 'A' + 'a') : *str2;
        if (c1 != c2) {
            return c1 - c2; // 返回字符差值，类似于strcmp
        }
        str1++;
        str2++;
    }
    return *str1 - *str2; // 考虑到字符串长度不同的情况
}

int StrNCmpIgnoreCase(const char* str1, const char* str2, unsigned long long n) {
    while (n && *str1 && *str2) {
        char c1 = (*str1 >= 'A' && *str1 <= 'Z') ? (*str1 - 'A' + 'a') : *str1;
        char c2 = (*str2 >= 'A' && *str2 <= 'Z') ? (*str2 - 'A' + 'a') : *str2;
        if (c1 != c2) {
            return c1 - c2; // 返回字符差值
        }
        str1++;
        str2++;
        n--;
    }

    // 如果 n 为 0 或两个字符串在前 n 个字符都相等，则返回 0
    if (n == 0) {
        return 0;
    }

    // 处理字符串长度不同的情况
    return (*str1) ? 1 : ((*str2) ? -1 : 0);
}
