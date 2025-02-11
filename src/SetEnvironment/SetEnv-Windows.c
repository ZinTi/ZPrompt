// 这个程序要使用静态链接，不能使用自建库的动态链接，不然环境没配置好找不到自建库的动态链接库
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define PROG_ENV_VAR  "ZPrompt_HOME"

void ManagerRun(LPCSTR exe,LPCSTR param);
void Menu(void);
char* GetFilePath(void);
int ConfEnv(char mode);
void SetEnvVar(const char* newEnvVar, const char* currentPath);
void RmEnvVar(const char* envVar);
void ModiPath_AddVal(const char* Str);
void ModiPath_RmVal(const char* rmStr);

int main(int argc,char *argv[]) {
    if(argc == 1){ //初次运行，即双击EXE
        ShowWindow(GetConsoleWindow(),SW_HIDE);
        ManagerRun(argv[0], "2");
        return 1;
    }else if(argc == 2){ //再次运行,即ManagerRun
        Menu();
    }
    return 0;
}

void ManagerRun(LPCSTR exe,LPCSTR param) { //非管理员身份运行将跳出UAC提示
    SHELLEXECUTEINFO ShExecInfo;
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = "runas";
    ShExecInfo.lpFile = exe;
    ShExecInfo.lpParameters = param;
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_SHOW;
    ShExecInfo.hInstApp = NULL;
    BOOL ret = ShellExecuteEx(&ShExecInfo);
    CloseHandle(ShExecInfo.hProcess); //杀掉当前线程
    return;
}

void Menu(void) {
    printf("=== Configure the environment for ZPrompt ===\n\n");
    while(1){
        puts("The installer will do the following:");
        puts("(1) Check whether there are environment variables of the old version of the program, and try to uninstall it;");
        printf("(2) Add a system variable %s=%s;\n", PROG_ENV_VAR, GetFilePath());
        printf("(3) Modify the system variable \"Path\" by appending the following content to the end of it: \";%%%s%%\\scripts;%%%s%%\\bin;%%%s%%\\lib\".\n\n", PROG_ENV_VAR, PROG_ENV_VAR, PROG_ENV_VAR);
        printf("If you need to remove the environment variable of the program, enter \"u\" or \"U\".\n\n");
        printf("Continue? (i/u/e) > ");
        char option,c;
        scanf("%c",&option);
        while((c=getchar()) != '\n' && c != EOF);
        if(ConfEnv(option)==0){
            puts("Any key exit.");
            getch();
            break;
        }
    }
}

char* GetFilePath(void) {
    char* currentDir;
	currentDir = (char *)malloc(MAX_PATH);
    GetModuleFileName(NULL, currentDir, MAX_PATH);
	strrchr(currentDir, '\\')[0] = 0;
	return currentDir;
}

void SetEnvVar(const char* newEnvVar, const char* currentPath) {
    char setxCommand[MAX_PATH * 2];
    snprintf(setxCommand, sizeof(setxCommand), "setx %s \"%s\" /M", newEnvVar, currentPath);
    puts(setxCommand);
    system(setxCommand);
}

void RmEnvVar(const char* envVar){
    char command[1024];
    sprintf(command, "REG DELETE \"HKLM\\SYSTEM\\ControlSet001\\Control\\Session Manager\\Environment\" /v %s /f", envVar);
    puts(command);
    system(command);
}

void ModiPath_AddVal(const char* Str) {
    HKEY hKey;
    LONG regOpenResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment", 0, KEY_SET_VALUE | KEY_QUERY_VALUE, &hKey);
    if (regOpenResult == ERROR_SUCCESS) {
        DWORD bufferSize;
        RegQueryValueEx(hKey, "Path", NULL, NULL, NULL, &bufferSize);
        char* currentValue = (char*)malloc(bufferSize);
        RegQueryValueEx(hKey, "Path", NULL, NULL, (LPBYTE)currentValue, &bufferSize);
        size_t newLength = strlen(Str) + strlen(currentValue) + 1;
        char* newValue = (char*)malloc(newLength);
        sprintf(newValue, "%s%s", currentValue, Str); // Str中已包含过分号分隔符
        RegSetValueEx(hKey, "Path", 0, REG_EXPAND_SZ, (const BYTE*)newValue, strlen(newValue));
        SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)"Environment", SMTO_ABORTIFHUNG, 5000, NULL);
        free(currentValue);
        free(newValue);
        RegCloseKey(hKey);
    }
}

void ModiPath_RmVal(const char* rmStr) {
    HKEY hKey;
    LONG regOpenResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Control\\Session Manager\\Environment", 0, KEY_SET_VALUE | KEY_QUERY_VALUE, &hKey);
    if (regOpenResult == ERROR_SUCCESS) {
        DWORD bufferSize;
        RegQueryValueEx(hKey, "Path", NULL, NULL, NULL, &bufferSize);
        char* currentValue = (char*)malloc(bufferSize);
        RegQueryValueEx(hKey, "Path", NULL, NULL, (LPBYTE)currentValue, &bufferSize);
		int len = strlen(rmStr); //  "\\"算一个字符
        size_t newLength = strlen(currentValue) + 1;
        char* addr = strstr(currentValue,rmStr); // 只保留搜索到的字符串及其后边的
        int begin = addr - currentValue;
		int end = begin + len;
		char newValue[newLength-len];
		for(int i=0,j=0;i<newLength;i++){
			if(i<begin||i>=end){
				newValue[j] = currentValue[i];
				j++;
			}
		}
		//printf("[DEBUG] 修改前：%s\n移除：%s\n修改后：%s\n",currentValue,rmStr,newValue);
        RegSetValueEx(hKey, "Path", 0, REG_EXPAND_SZ, (const BYTE*)newValue, strlen(newValue));
        SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)"Environment", SMTO_ABORTIFHUNG, 5000, NULL);
        free(currentValue);
        RegCloseKey(hKey);
    }
}

int ConfEnv(char mode){
    char* path[3] = {";%ZPrompt_HOME%\\lib", ";%ZPrompt_HOME%\\bin", ";%ZPrompt_HOME%\\scripts"};
    switch(mode){
        case 'i':
        case 'I':
            puts("\n--- Checking and uninstalling older versions of the program ---");  // uninstall(安装前先卸载旧版)
            for(int i=0;i<3;i++){
                ModiPath_RmVal(path[i]);
            }
            if(getenv(PROG_ENV_VAR) != NULL){ // getenv()获得的值继承自父进程，而REG是直接操作注册表，所以有时候已经删除envVar了，但getEnv仍返回envVar的值
                RmEnvVar(PROG_ENV_VAR);
            }
            puts("\n--- Installing ---"); // install（安装）
            char* currentPath = GetFilePath();
            SetEnvVar(PROG_ENV_VAR, currentPath);
            for(int i=2;i>=0;i--){
                ModiPath_AddVal(path[i]);
            }
            free(currentPath);//释放堆区内存
            puts("Installation complete!");
            break;

        case 'u':
        case 'U':
            puts("\n--- Uninstalling ---");// uninstall
            for(int i=0;i<3;i++){
                ModiPath_RmVal(path[i]);
            }
            RmEnvVar(PROG_ENV_VAR);
            puts("Uninstall complete!");
            break;

        case 'e':
        case 'E':
            exit(0);

        default:
            puts("The option you entered is invalid");
            return -1;

    }
    return 0;
}