/************************************************
 * -s �����м��ļ�����-s����Ĭ�ϲ������м��ļ�
 * -l ����һ��icoͼ�꣬��-l������������ico��Դ
 * -p ���ӽ��̴��ݲ��������ݶ������ʹ��""������
 * -o ָ����ִ���ļ������ƣ��޴˲�����Ĭ��ͬԴ������
 * -e <GB2312 | UTF8>ָ��src����ı����ַ���
 * -c ���������ӵ������У���-c����Ĭ�ϱ��������
 * -t ���ָ����Դ�ļ������ڣ����Զ����ɲ�����һ��ģ�壬�޸ò�����ָ���ļ�������ʱ����ʾ����
 * -r �Ż�����ļ��Ĵ�Сgcc -Os hello.c -o hello.exe -s
 * -? ͬ--help
 * -v ͬ--version
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
	pAttr->saveTemp = 0; //0: �����棬1: ����
	pAttr->icoFilename = (char*)malloc(MaxLengthFilename);
	pAttr->subproArgu = (char*)malloc(MaxLengthCommandLine);
	pAttr->exeFilename = (char*)malloc(MaxLengthFilename);
	pAttr->compileOnly = 0; //0: ���������У�1: ֻ����
	pAttr->useTemplates = 0; //0: ������ʱ��ʹ��ģ�崴��һ���ļ���1: ������ʱ�Զ�����
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
			Compile(argv[1],exeFilename,0); //�����ӽ��̲���
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
				//�������������κ����в����������ԡ�-��Ϊ�ף��ò�������
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
	}else{ //�����
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


