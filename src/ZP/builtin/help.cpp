#include "frame.h"

#define SUBPROJ_NAME			"ZP"
#define SUBPROJ_VER				"0.9"

void ShowManual(void){
	const char* overview = "This program is a Windows console application written in C language, the program has implemented some of my (the author of this program) commonly used built-in commands. It is also a subproject of a project called ZPrompt. The ZPrompt project is a personal toolkit for porting or copying some of the commonly used GNU tool commands to the Windows platform. See the project documentation for more information.";
	ColorPuts(0x70," OVERVIEW ", 1);
	printf("    %s\n\n", overview);

	ColorPuts(0x70," USAGE ", 1);
	printf("%-25s%s\n","clear, cls","Clear the screen.");
	printf("%-25s%s\n","exit, quit","End the current program.");
	printf("%-25s%s\n","help, manual","Display this help.");
	//printf("%-25s%s\n","listProg","Lists all executable binaries or scripts for the current project.");
	//printf("%-25s%s\n","listCommand","Lists all built-in commands.");
	printf("%-25s%s\n","prompt [newPrompt]","Change your prompt.");
	printf("%-25s%s\n","update <programName>","Move your executable binaries to the path \"${ZPrompt_HOME}/bin/\".");
	printf("%-25s%s\n\n","version","Print version information to your screen.");

	ColorPuts(0x70," DIRECTORY ", 1);
	printf("%-25s%s\n", "${ZPrompt_HOME}/", "Home directory of this software.");
	printf("%-25s%s\n", "${ZPrompt_HOME}/bin/", "Directory of executable binaries.");
	printf("%-25s%s\n", "${ZPrompt_HOME}/conf/", "Directory of configuration files.");
	printf("%-25s%s\n", "${ZPrompt_HOME}/data/", "Directory of local databases.");
	printf("%-25s%s\n", "${ZPrompt_HOME}/lib/", "Directory of dependencies and runtime.");
	printf("%-25s%s\n\n", "${ZPrompt_HOME}/scripts/", "Directory of executable scripts.");

}

int ShowVersion(void){
	char homePath[1024];
	if(ZPrompt_CheckEnv(homePath)){
		puts("ZPrompt is not installed!");
		return -1;
	}else{
		ZPrompt_SubprojVersion(SUBPROJ_NAME, SUBPROJ_VER, __TIME__, __DATE__);
		printf("${ZPrompt_HOME} == %s\n\n", homePath);
	}
	return 0;
}