#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<windows.h>
#define MaxLengthOptionsKey 20
#define MaxLengthOptionsValue 100

typedef struct Options{
	short int type; //连值短参数、无值短参数、等号连值长参数、无值长参数、组合短参数 （不允许使用空格连短参数）
	char* key;
	char* value;
}OPTIONS,*pOPTIONS;

int GetOptions(pOPTIONS pOP, char* argv);
int InitialStructOptions(pOPTIONS pOP);
int JudgeOptionsType(const char* options);

int main(int argc,char* argv[]){
	OPTIONS x1;
	pOPTIONS px1 = &x1;
	InitialStructOptions(px1);
	for(int i=1;i<argc;i++){
		GetOptions(px1, argv[i]);
	}
	

	return 0;
}

int GetOptions(pOPTIONS pOP, char* argv){
	if(*argv=='-' && *(argv+1)!='-'){
		//短参数
		if(*(argv+1)=='s'){

		}

	}else if(*argv=='-' && *(argv+1)=='-'){
		//长参数
		for(int i=0;;i++){
			if(*(argv+i)!='\0'){
				*(pOP->key+i)=
			}else{
				break;
			}
		}
	}else{
		
	}
	
}

int JudgeOptionsType(const char* options){
	short int l = strlen(options);
	if( l<2 || !strcmp(options,"--")){
		return 0;
	}
	for(int i=1;i<l;i++){
		if( *options=='-' && *(options+1)=='-' ){
			return 1; //printf("LongOptions\n");
		}else if( *(options+1)>='A'&&*(options+1)<='Z' || *(options+1)>='a'&&*(options+1)<='z' ){
			return 2; //printf("ShortOptions\n");
		}else{
			return 0; //printf("NotOptions\n");
		}
	}
	return 0;
}

int InitialStructOptions(pOPTIONS pOP){
	pOP->key = (char*)malloc(MaxLengthOptionsKey);
	pOP->value = (char*)malloc(MaxLengthOptionsValue);
	return 0;
}