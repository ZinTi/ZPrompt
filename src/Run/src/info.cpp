#include "frame.h"

void DisplayVersion(void){
	ZPrompt_SubprojVersion(SUBPROJ_NAME, SUBPROJ_VER, __TIME__, __DATE__);
	printf("Enter \".help\" for usage hints.\n");
}

void DisplayManual(void){
	printf("[USAGE]\n");
	printf("(1) Interactive Mode");
	printf("\t%s\n", "run.exe");
	printf("If no options are specified, the program will enter interactive mode.");
	printf("List of all commands (case-insensitive):\n");
	printf(".exit\tExit CREPL.\n");
	printf(".help\tDisplay this help.\n");
	printf(".quit\tQuit CREPL. Same as \".exit\".\n");
	printf(".renew\tUse a new environment.\n");
	printf(".sys\tExecute a system shell command.\n");
	printf(".undo\tUndo the previous statement.\n\n");

	printf("(2) Parameter Mode\n");
	printf("\t%s [OPTIONS] <srcfile>\n", "run.exe");
	printf("The program only supports combined short options and does not support long options or separate short options.\n");
	printf("[OPTIONS]\n");
	printf(" -a\tPass a parameter to subprocess.\n");
	printf(" -h\tDisplays the help manual for this program.\n");
	printf(" -l\tAdd a logo to the output file.\n");
	printf(" -o\tRename the executable file.\n");
	printf(" -s\tDo not delete intermediate files.\n");
	printf(" -v\tDisplays the version of the program.\n\n");
}