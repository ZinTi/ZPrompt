#include "frame.h"

void SafeExit(int _Code);
int ParseCommand(char* cmdStr, int mode);
int DelegateItToCMD(char* cmdStr);

// 提示符类
class PromptS{
	private:
		char username[256];
		char hostname[256];
		char wd[1024];
		char status[10];
		unsigned short whoamicolor;
		unsigned short wdcolor;
		unsigned short statuscolor;
	public:
		PromptS(const char* str = "$"){
			DWORD userSize = sizeof(username);
			GetUserNameA(username, &userSize);
			DWORD hostSize = sizeof(hostname);
			GetComputerNameA(hostname, &hostSize);
			DWORD wdLen = GetCurrentDirectoryA(sizeof(wd), wd);
			strcpy(status, str);

			whoamicolor = 0x02;
			wdcolor = 0x06;
			statuscolor = 0x0B;
		} // 有参构造函数初始化
		~PromptS(){} // Destructor

		int PrintPromptS(){
			ChCP(936, 936); // A系列Win API函数获取的是GBK编码格式的目录路径
			ColorPrintf(whoamicolor, "%s@%s ", username, hostname);
			ColorPrintf(wdcolor, "%s\n", wd);
			ColorPrintf(statuscolor, "%s ", status);
			ChCP(0, 0);
			return 0;
		} // 输出提示符

		int ChStatus(const char* str = "$"){
			strcpy(status, str);
			printf("PROMPT set to '%s'\n", status);
			// printf("Returning to default PROMPT of '%s'\n", "$");
			return 0;
		}

		void GetWD(void){
			DWORD wdLen = GetCurrentDirectoryA(sizeof(wd), wd);
		}
};

class UsrInput{
	private:

	public:
		char* usrInput;
	public:
		UsrInput(int size = 1024){
			usrInput = (char*)malloc(size);
		} // Constructor
		~UsrInput(){
			free(usrInput);
		} // Destructor
		int GetsFromConsole(unsigned int iCP = 65001, unsigned int oCP = 65001){
			ChCP(iCP, oCP);
			gets(usrInput);
			ChCP(0, 0);
			return 0;
		}
};

PromptS PS1;
int main(int argc, char* argv[]){
	ChCP(65001, 65001);
	//char yourInput[100];
	UsrInput cmd1;

	if(ShowVersion()){ // != 0
		SafeExit(-1);
	}

	while(1){
		PS1.PrintPromptS();
		cmd1.GetsFromConsole(936, 936); // 使用GB2312获取命令（cd 解析路径A系列API用的 GBK编码）
		ParseCommand(cmd1.usrInput, 0);
	}
	ChCP(0, 0); 
	return 0;
}

int ParseCommand(char* cmdStr, int mode){
	if(!StrNCmpIgnoreCase("cd", cmdStr, 2)){ // 更改当前进程的工作目录
		if(*(cmdStr+2)=='\n'||*(cmdStr+2)=='\0'){
			chdir("~"); // 缺省，切换到用户目录
		}else{
			chdir(cmdStr+3);
		}
		PS1.GetWD();
	}else if(!StrCmpIgnoreCase("version", cmdStr)){ // 显示版本信息
		ShowVersion();
	}else if(!StrCmpIgnoreCase("exit", cmdStr) || !StrCmpIgnoreCase("quit", cmdStr)){ // 退出
		SafeExit(0);
	}else if(!StrNCmpIgnoreCase("prompt", cmdStr, 6)){ // 更改提示符
		if(*(cmdStr+6)=='\n'||*(cmdStr+6)=='\0'){
			PS1.ChStatus(); // 缺省恢复默认
		}else if(*(cmdStr+6)==' '){
			PS1.ChStatus(cmdStr+7);		
		}else{
			DelegateItToCMD(cmdStr);
		}
	}else if(!StrCmpIgnoreCase("help", cmdStr) || !StrCmpIgnoreCase("manual", cmdStr) || !strcmp("?", cmdStr)){
		ShowManual();
	}else if(!StrCmpIgnoreCase("cls", cmdStr) || !StrCmpIgnoreCase("clear", cmdStr)){
		system("cls");
	}else if(!StrCmpIgnoreCase("pwd", cmdStr)){
		pwd();
	}else{
		DelegateItToCMD(cmdStr);
	}

	return 0;
}

int DelegateItToCMD(char* cmdStr){
	return system(cmdStr);
}

void SafeExit(int _Code){
	ChCP(0, 0);
	exit(_Code);
}
