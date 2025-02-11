#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdarg.h>
#include<windows.h>
//#include<conio.h>

char* const ts = "（同上）";

typedef struct opPriority{
    short int priority;
    char symbol[10];
	char* meaning;
}OPPRI;

OPPRI a1[46]={
    {1, "()", "圆括号，函数参数表"},{1,"[]", "数组元素下表"},{1, "->", "指向结构体成员"},{1, ".", "引用结构体成员"},{1,"a++", "后缀增1"},{1,"a--", "后缀减1"},
    {2,"!", "逻辑非"},{2,"~", "按位取反"},{2,"++a", "前缀增1"},{2,"--a","前缀减1"},{2,"-a","取负"},{2,"*p", "间接寻址运算符"},{2,"&a", "取地址运算符"},{2,"(int)", "强制类型转换运算符"},{2,"sizeof", "计算字节数运算符"},
    {3,"m*n","乘"},{3,"m/n","除"},{3,"m%%n","整数求余"},
    {4,"m+n", "加"},{4,"m-n", "减"},
    {5,"<<", "左移"},{5,">>", "右移"},
    {6,"<","小于"},{6,"<=","小于等于"},{6,">","大于"},{6,">=", "大于等于"},
    {7,"==", "等于"},{7,"!=", "不等于"},
    {8,"m&n","按位与"},
    {9,"m^n","按位异或"},
    {10,"m|n","按位或"},
    {11,"&&","逻辑与"},
    {12,"||","逻辑或"},
    {13,"?:","条件运算符"},
    {14,"=", "赋值运算符"},{14,"+=","复合的赋值运算符"},{14,"-=",ts},{14,"*=",ts},{14,"/=",ts},{14,"%%=",ts},{14,"&=",ts},{14,"^=",ts},{14,"|=",ts},{14,"<<=",ts},{14,">>=",ts},
    {15,",", "逗号运算符"}
};

char* yslx[15] = {"-", "单目运算", "双目算术运算", "双目算术运算", "位运算", "关系运算", "关系运算", "位运算", "位运算", "位运算", "逻辑运算", "逻辑运算", "三目运算", "双目运算", "顺序求值运算"}; //运算类型

void ShowTable(const int x);
int ChColor(unsigned short color, unsigned short* pOldColor);
int ChCP(unsigned int newInputCP, unsigned int newOutputCP);

int main(int argc, char** argv){
    ChCP(65001, 65001);
	ShowTable(1);
    ChCP(0,0);
	return 0;
}
void ShowTable(const int x){
	printf("%s\t%s\t%s\t\t\t%s\t%s\n", "优先级", "运算符", "含义", "运算类型", "结合方向");
	for(int i=0;i<46;i++){
        ChColor(a1[i].priority, NULL);
		printf("%d\t%s\t%-*s",a1[i].priority, a1[i].symbol, 24, a1[i].meaning);
		printf("%-16s", yslx[ (a1[i].priority)-1 ]);
        if( a1[i].priority!=2 && a1[i].priority!=13 &&  a1[i].priority!=14 ){
            printf("自左向右");
        }else{
            printf("自右向左");
        }
        ChColor(0x7, NULL);
		printf("\n");
	}
}

int ChColor(unsigned short color, unsigned short* pOldColor){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(pOldColor!=NULL){
		if(GetConsoleScreenBufferInfo(hConsole, &csbi)){
			*pOldColor = csbi.wAttributes;
		}else{
			puts("ERROR: Failed to get console screen buffer information.");
			*pOldColor = 0x07;
		}
	}
	SetConsoleTextAttribute(hConsole, color);
	return 0;
}

int ChCP(unsigned int newInputCP, unsigned int newOutputCP){
    static unsigned int oldInputCP;
    static unsigned int oldOutputCP;
	if(newInputCP != 0){ //
        oldInputCP = GetConsoleCP();
		SetConsoleCP(newInputCP);
	}else{
        SetConsoleCP(oldInputCP);
    }

	if(newOutputCP != 0){
        oldOutputCP = GetConsoleOutputCP();
		SetConsoleOutputCP(newOutputCP);
	}else{
        SetConsoleOutputCP(oldOutputCP);
    }
	return 0;
}