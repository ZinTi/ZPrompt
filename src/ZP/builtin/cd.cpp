/*******************************************
 * CD命令
 * 使用环境变量：
 *  (1) %PATH_VAR%（cmd）, ${PATH_VAR}（Bash），$env:{PATH_VAR}（powershell）
 *  (2) ~ 用户目录
 *  (3) * 模糊匹配
 * 中文乱码处理
 * 
 * 
 * 
********************************************/
#include "frame.h"

int chdir(const char* newPath){
    if(!SetCurrentDirectoryA(newPath)){
        ChCP(936, 936); // A系列WinAPI目录I/O使用GB2312
        ColorPrintf(0x04, "CD: Cannot find path \'%s\' because it does not exist.\n", newPath);
        ChCP(0, 0);
    }
    return 0;
}