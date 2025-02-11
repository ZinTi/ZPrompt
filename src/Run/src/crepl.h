#ifndef CREPL_INC
#define CREPL_INC

/* 函数原型 */
int CREPL(void);
bool IsItSpecialCommand(const char* str);
int RunOrNot(char* str);
int determineType(const char* str);

#endif