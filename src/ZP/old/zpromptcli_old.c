#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#include<windows.h>
#include<stdarg.h>

#define NumStrLen1 50
#define MaxSizeOfCmd 20

void PutColorfulString(char* String, WORD color);
void DisplayVersion(void);
void SetConsoleTransparency(int alpha);
void SetConsoleTextColor(int color);
void RunCommand(char* command);
int InputPasswords(char* passwords, unsigned short maxLength);
int ReadStream(char** String);
int GetCommand(char* string);
void ScreenBackspace(const unsigned short num);
//void ChangeStringColor(char* str1, unsigned short num, ...);

int main(int argc,char* argv[]){
	SetConsoleTransparency(200); //设置终端背景透明度为200
	SetConsoleTextColor(0x7);
	DisplayVersion();
	char* str1 = (char*)malloc(sizeof(char)*NumStrLen1);

	/*
	while(1){
		char pwd[20];
		if( InputPasswords(pwd, 16)==-1 ){
			break;
		}
		printf("Your input: %s\n", pwd);
	}*/
	while(1){
		char test[20];
		printf(">>> ");
		gets(test);
		printf("%s\n", IgnoreSpaces(test));

	}
	
	while(1){
		char xxx[50];
		if( GetCommand(xxx) == -1 ){
			break;
		}
		printf("Your input: %s\n", xxx);
	}

	
	/*
	while(1){
		printf("> ");
		if(ReadStream( &str1 )==3){
			continue;
		}

		if(!strcmp(str1,"exit") || !strcmp(str1,"quit")){
			exit(0);
		}else if(strcmp == NULL){
			printf("---\n");
		}else{
			char* cmd1 = (char*)malloc(sizeof(char)*NumStrLen1+11);
			sprintf(cmd1,"powershell %s",str1);
			//system(cmd1);
			//printf("Your Input: %s\n",str1);
		}
	}*/
	return 0;
}

void SetConsoleTransparency(int alpha){
	HWND hwnd = GetConsoleWindow();
	LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);
	SetWindowLong(hwnd,GWL_EXSTYLE,style | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd,RGB(0,0,0),alpha,LWA_ALPHA);
}

void SetConsoleTextColor(int color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,color);
}

void RunCommand(char* command){
	system(command);
}

void DisplayVersion(void){
	printf("XPompt TerminalSimulator(ts) version 0.9 "__DATE__" "__TIME__"\n");
	printf("Mr. Zin\tvip201@126.com\n");
	printf("Usage:\texit\t\tExit ts. Same as quit.\n\tquit\t\tQuit ts.\n");
}

void PutColorfulString(char* String, WORD color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	printf("%s", String);
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY|0x7);
}

int InputPasswords(char* passwords,unsigned short maxLength){
	printf("Enter password: ");
	char ch = '\0';
	for(int cursor=0 ; ch!='\r' ; ){
		ch = getch();
		if(ch=='\r'){
			*(passwords+cursor)='\0';
			printf("\n");
			break;
		}else if(ch=='\x03'){
			*(passwords+cursor)='\0';
			PutColorfulString("^C", 0x47);
			printf("\n");
			return -1;
		}else if(ch=='\b'){
			if(cursor>0){
				printf("\b \b"); //空格代替光标前一个字符——删除一个字符的显示
				cursor--;
			}else{
				printf("\a");
			}
		}else if(ch >=' ' && ch<= '~'){
			if(cursor == maxLength){
				printf("\a");
			}else{
				*(passwords+cursor) = ch;
				PutColorfulString("*", 0x2);
				cursor++;
			}
		}else{
			if(cursor == maxLength){
				printf("\a");
			}else{
				*(passwords+cursor) = ch;
				PutColorfulString("*", 0x4);
				cursor++;
			}
		}
	}
	return 0;
}

int GetCommand(char* string){
	printf("> ");
	unsigned short maxLength = 50;
	char ch = '\0';
	for(int cursor=0 ; ch!='\r' ; ){
		ch = getch();
		if(ch=='\r'){
			*(string+cursor)='\0';
			printf("\n");
			break;
		}else if(ch=='\x03'){
			*(string+cursor)='\0';
			PutColorfulString("^C", 0x47);
			printf("\n");
			return -1;
		}else if(ch==VK_LEFT){
			printf("←");
		}else if(ch==VK_RIGHT){
			printf("→");
		}else if(ch==VK_UP){
			printf("↑");
		}else if(ch==VK_DOWN){
			printf("↓");
		}else if(ch=='\b'){
			if(cursor>0){
				ScreenBackspace( 1 );
				*(string+cursor-1) = '\0';
				cursor--;
			}else{
				printf("\a");
			}
		}else if(ch >=' ' && ch<= '~'){
			if(cursor == maxLength){
				printf("\a");
			}else{
				*(string+cursor) = ch;
				*(string+cursor+1) = '\0';
				printf("%c", ch);
				cursor++;
			}
		}else{
			if(cursor == maxLength){
				printf("\a");
			}else{
				*(string+cursor) = ch;
				*(string+cursor+1) = '\0';
				PutColorfulString("?", 0x4);
				cursor++;
			}
		}

		
		if( !strcmp( IgnoreSpaces(string), "exit") ){
			ScreenBackspace( cursor );
			PutColorfulString(string, 0x2);
		}else if( !strcmp( IgnoreSpaces(string), "quit") ){
			ScreenBackspace( cursor );
			PutColorfulString(string, 0x2);
		}else{
			ScreenBackspace( cursor );
			PutColorfulString(string, 0xF);
		}

	}
	return 0;
}

void ScreenBackspace(const unsigned short num){
	for(unsigned short i=0;i<num;i++){
		printf("\b \b"); //空格代替光标前一个字符——删除一个字符的显示
	}
	return;
}

/*
void ChangeStringColor(char* str1, unsigned short num, ...){
	va_list arg_ptr;
	char* nArgValue = str1;
	int nArgCount = 0; //可变参数的数目
	va_start(arg_ptr, num); //以固定参数的地址为起点确定变参的内存起始地址
	char x = 'n';
	do{
		++nArgCount;
		if(!strcmp(str1, nArgValue)){
			x = 'y';
		}else{
			x = 'n';
		}
		nArgValue = va_arg(arg_ptr, char*); //得到下一个可变参数的值
	}while(nArgValue != "end");
	if(x=='y'){
		ScreenBackspace( strlen(str1) );
		PutColorfulString(str1, 0x5);
	}else{
		ScreenBackspace( strlen(str1) );
		PutColorfulString(str1, 0x8|0x6);
	}
	return;
}*/

/**********读取缓冲区字符串并并回显，相当于gets(str1)*************/
int ReadStream(char** String){
	for(int i=0;;i++){
		*(*String+i) = getch();
		if( *(*String+i)=='\r' ){
			*(*String+i)='\0'; //字符串读取结束
			printf("\n");
			break;
		}else if( *(*String+i)=='\x03' ){
			printf("^C\n");
			return 3;
		}else{
			//printf("%02X ", *(*String+i));
			printf("%c", *(*String+i));
		}
	}
}
/**********读取缓冲区字符串并并回显，相当于gets(str1)*************/
