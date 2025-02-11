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
	
	strcat(pathVar, "\\bin\\use\\");
	if(argc >= 2){
		if(!strcmp(argv[1],"-list")){
			char* listCmd = (char*)malloc( strlen(pathVar)+9 );
			sprintf(listCmd,"tree /f %s",pathVar);
			system(listCmd);
			return 1;
		}
		
		for(int i=1;i<argc;i++){
			if( i!=1 ){
				sprintf(pathVar,"%s \"%s\"", pathVar, argv[i]);
			}else{
				strcat(pathVar, argv[i]);
			}
		}
		system(pathVar);
		
	}else{
		printf("Last modified: "__DATE__" "__TIME__"\n");
		printf("Insufficient parameters!\n");
	}
	return 0;
}