#include "frame.h"

char* ChFilenameExtension(const char* oldFn, char* newFn, const char* newExtension){
	if (oldFn == NULL){
		PrintError("ChFilenameExtention(oldFn, newExtension)", "Error! oldFn is NULL.\n");
		SafeExit(-1);
	}
	const char* dot_position = strrchr(oldFn, '.');
	unsigned short n = (unsigned short)(dot_position - oldFn);
	if (dot_position != NULL){
		strncpy(newFn, oldFn, n);
		newFn[n] = '\0';
		strcat(newFn, newExtension);
	}
	else{
		strcpy(newFn, oldFn);
		strcat(newFn, newExtension);
	}
	return newFn;
}