#include "frame.h"

void pwd(void){
    char wd[1024];
    ChCP(936, 936);
    DWORD wdLen = GetCurrentDirectoryA(sizeof(wd), wd);
    printf("%s\n\n", wd);
    ChCP(0, 0);
}