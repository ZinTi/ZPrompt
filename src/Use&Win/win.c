/***********************************************************
 * win.exe程序与use.exe唯一的区别是：
 * (1) use.exe执行时，需要等待子进程system(pathVar)执行完毕才结束，
 * 当子进程是GUI程序时，use在命令行中一直处于阻塞状态；
 * 
 * (2) win.exe程序则在执行子进程时即结束，不会阻塞，
 * 但当子进程是CLI程序时，win.exe则不适用。
 * 
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MaxLength 256

int main(int argc,char* argv[]){
	char* pathVar = (char*)malloc(MaxLength);

	strcpy(pathVar, getenv("ZPrompt_HOME"));
	
	if(!pathVar){ // "!pathVar" <=> "pathVar == NULL"
		printf("ZPrompt is not installed\n");
		return -1;
	}
	
	strcat(pathVar, "\\bin\\win\\");
	if(argc >= 2){
		if(!strcmp(argv[1],"-list")){
			char* listCmd = (char*)malloc( strlen(pathVar)+16 );
			sprintf(listCmd,"powershell dir %s",pathVar);
			system(listCmd);
			return 1;
		}
		
		for(int i=1;i<argc;i++){
			if( i!=1 ){
				sprintf(pathVar,"%s \"%s\"", pathVar, argv[i]); // "双引号"可避免将一个含有空格' '的参数解析为2个或多个参数
			}else{
				strcat(pathVar, argv[i]);
			}
		}

        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        if (!CreateProcess(NULL, pathVar, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            printf("Failed to execute command.\n");
            return -1;
        }

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
		
	}else{
		printf("Last modified: "__DATE__" "__TIME__"\n");
		printf("Insufficient parameters!\n");
	}
	return 0;
}