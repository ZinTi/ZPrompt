/************************************************
 * -s 保留中间文件，无-s参数默认不保留中间文件
 * -l 增加一个ico图标，无-l参数无需输入ico资源
 * -p 给子进程传递参数，传递多个参数使用""括起来
 * -o 指定可执行文件的名称，无此参数则默认同源程序名
 * -e <GB2312 | UTF8>指定src代码的编码字符集
 * -c 编译汇编链接但不运行，无-c参数默认编译后即运行
 * -t 如果指定的源文件不存在，则自动生成并运行一个模板，无该参数当指定文件不存在时将提示错误
 * -r 优化输出文件的大小gcc -Os hello.c -o hello.exe -s
 * -? 同--help
 * -v 同--version
 * 
 * 
 * 
 * run  -save-temps=<arg> --logo=run.ico --subpro-arg="-v -h" --output=run.exe --compile-only=1
 *     --template=1 --
 ************************************************/

#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MaxLengthFilename 50
#define MaxLengthCommandLine 100

typedef struct attribute{
	int saveTemp;
	char* icoFilename;
	char* subproArgu;
	char* exeFilename;
	int compileOnly;
	int useTemplates;
}ATTRIBUTE,*pATTRIBUTE;

int InitializeAttyibute(pATTRIBUTE pAttr){
	pAttr->saveTemp = 0; //0: 不保存，1: 保存
	pAttr->icoFilename = (char*)malloc(MaxLengthFilename);
	pAttr->subproArgu = (char*)malloc(MaxLengthCommandLine);
	pAttr->exeFilename = (char*)malloc(MaxLengthFilename);
	pAttr->compileOnly = 0; //0: 编译且运行，1: 只编译
	pAttr->useTemplates = 0; //0: 不存在时不使用模板创建一个文件，1: 不存在时自动创建
	return 0;
}

int AnalyzeShortArguments(const char* arguments, pATTRIBUTE pAttr){
	int argumentsLen = strlen(arguments);
	for(int i=1;i<argumentsLen;i++){
		if(*(arguments+i)=='s'){
			pAttr->saveTemp = 1;
		}else if(*(arguments+i)=='l'){
			strcpy(pAttr->icoFilename,"await");
		}else if(*(arguments+i)=='p'){
			strcpy(pAttr->subproArgu,"await");
		}else if(*(arguments+i)=='o'){
			strcpy(pAttr->exeFilename,"await");
		}else if(*(arguments+i)=='c'){
			pAttr->compileOnly = 1;
		}else if(*(arguments+i)=='t'){
			pAttr->useTemplates = 1;
		}
	}
	return 0;
}

int AnalyzeLongArguments(){

}

int main(int argc,char* argv[]){
	ATTRIBUTE attr1;
	pATTRIBUTE pAttr1=&attr1;
	InitializeAttyibute(pAttr1);

	for(int i=1;i<argc;i++){
		if( *argv[i]=='-' && (*(argv[i]+1)<'0' || *(argv[i]+1)>'9') ){
			if(*(argv[i]+1)=='-'){
				if(!strcmp(argv[1],"--version")){
					DisplayVersion();
				}else if(!strcmp(argv[1],"--help")){
					DisplayManual();
				}else{
					printf("Please enter the correct parameters!\n");
					printf("You can use the parameter \"--help\" or \"-h\" to get help.\n");
				}
			}else{
				AnalyzeShortArguments(argv[i], pAttr1);
			}
		}else{
			printf("not para\n");
		}
	}


	if(argc==3){
		if(!strcmp(argv[1],"--logo") || !strcmp(argv[1],"-l")){
			char* icoFN = (char*)malloc(100);
			printf("ICO file name: ");
			gets(icoFN);
			CompileWithIcon(argv[2],exeFilename,icoFN);
			RunProgram(exeFilename,NULL);
			free(icoFN);
		}else if(!strcmp(argv[1],"--save") || !strcmp(argv[1],"-s")){
			Compile(argv[2],exeFilename,1);
			RunProgram(exeFilename, NULL);
		}else{
			Compile(argv[1],exeFilename,0); //传递子进程参数
			RunProgram(exeFilename, argv[2]);
		}
	}else if(argc==2){
		if( *argv[1]=='-' ){ 
			if(!strcmp(argv[1],"--version") || !strcmp(argv[1],"-v")){
				DisplayVersion();
				exit(0);
			}else if(!strcmp(argv[1],"--help") || !strcmp(argv[1],"-h")){
				DisplayManual();
				exit(0);
			}else{
				//当参数不符合任何已有参数，但仍以“-”为首，该参数有误。
				printf("Please enter the correct parameters!\n");
				printf("You can use the parameter \"--help\" or \"-h\" to get help.\n");
			}
		}else{
			Compile(argv[1],exeFilename,0);
			RunProgram(exeFilename,NULL);
		}
	}else if(argc==1){
		DisplayVersion();
		printf("Please enter the parameters.\n");
		printf("You can use the parameter \"--help\" or \"-h\" to get help.\n\n");
	}else{ //多参数
		printf("Too many parameters.\n");
	}

	if(argc==1){
		printf("Please enter the parameters.\n");
		printf("You can use the parameter \"--help\" or \"-h\" to get help.\n\n");
	}else{
		for(int i=1;i<argc;i++){
			if( *argv[i]=='-' && (*(argv[i]+1)<'0' || *(argv[i]+1)>'9') ){
				if(*(argv[i]+1)=='-'){
					;
				}else{
					printf("common para\n");
				}	
			}else{
				printf("not para\n");
			}
		}
	}
	system("PAUSE");
	return 0;
}


