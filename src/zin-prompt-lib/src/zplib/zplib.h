/*******************************************************************************************
:: ZPLIB动态库编译创建
:: (1) 库的源文件路径：%ZPrompt_HOME%\lib-dev\src\zplib.c
:: (2) 库的头文件路径：%ZPrompt_HOME%\include\zplib.h
:: (3) 暂时存放库的.o目标文件的目录(编译完后删除目标文件)：%ZPrompt_HOME%\lib-dev\src\zplib.o
:: (4) MinGW-w64默认生成的导入库.a文件存放路径：%ZPrompt_HOME%\lib\gcc\zplib.a
:: (5) 生成的VS兼容环境下可以使用的.lib导入库文件存放路径：%ZPrompt_HOME%\lib\vc\zplib.lib
:: (6) 生成的.dll文件存放路径：%ZPrompt_HOME%\lib\zplib.dll
********************************************************************************************/
#define MAIN_PROJ_NAME			    "ZPrompt"
#define MAIN_PROJ_VER				"1.02"
#define MAIN_PROJ_YEARS             "2023-2024"
#define AUTHOR                      "Mr. Zeng Lai"
#define AUTHOR_CONTACT			    "vip201@126.com"

#ifndef INC_ZPLIB_H
#define INC_ZPLIB_H

// Windows平台下导出和导入函数的定义
#ifdef _WIN32
    #ifdef ZPLIB_EXPORTS
        #define ZPLIB_API __declspec(dllexport)
    #else
        #define ZPLIB_API __declspec(dllimport)
    #endif
#else
    // 非Windows平台不需要特殊处理
    #define ZPLIB_API
#endif

/**
 * @brief ZPrompt检查运行环境（检查设置了环境变量没有）
 * @param homePath OUT 项目根目录
 * @return 0 代表成功
 */
ZPLIB_API int ZPrompt_CheckEnv(char* homePath); // return 1: uninstall; return 0: strcpy completed.

/**
 * @brief 打印版本相关信息
 * @param subprojName IN 子程序名称
 * @param subprojVersion IN 子程序版本
 * @param compiledTime IN 编译时间
 * @param compiledDate IN 编译日期
 * @return void
 */
ZPLIB_API void ZPrompt_SubprojVersion(const char* subprojName, const char* subprojVersion, const char* compiledTime, const char* compiledDate);

/**
 * @brief 读取用户使用手册
 * @param path IN 用户使用手册文件路径
 * @return void
 */
ZPLIB_API void ZPrompt_ReadManual(const char* path);

/**
 * @brief 
 * @param
 * @param
 * @return
 */
ZPLIB_API int ConvertHex(char* hexadecimalStr, long* pDecimal);

/**
 * @brief
 * @param
 * @param
 * @return
 */
ZPLIB_API int PutStr(const char* Str);

/**
 * @brief
 * @param
 * @param
 * @return
 */
ZPLIB_API int ColorPrintf(unsigned short color, const char* format, ...);

/**
 * @brief
 * @param
 * @param
 * @return
 */
ZPLIB_API int ColorPuts(unsigned short color, const char* Str, unsigned short line);

/**
 * @brief
 * @param
 * @param
 * @return
 */
ZPLIB_API int ChColor(unsigned short color, unsigned short* pOldColor);

/**
 * @brief
 * @param
 * @param
 * @return
 */
ZPLIB_API int ChCP(unsigned int newInputCP, unsigned int newOutputCP);

/**
 * @brief
 * @param
 * @param
 * @return
 */
ZPLIB_API int IsUTF8(const char* data, int len); // 0不是UTF-8, 1是UTF-8

/**
 * @brief
 * @param
 * @param
 * @return
 */
ZPLIB_API int AutomaticallySelectCodePage(const char* filename);

/**
 * @brief
 * @param
 * @param
 * @return
 */
ZPLIB_API void StrToUppercase(char *str);

/**
 * @brief
 * @param
 * @param
 * @return
 */
ZPLIB_API void StrToLowercase(char *str);

/**
 * @brief
 * @param
 * @param
 * @return
 */
ZPLIB_API int StrCmpIgnoreCase(const char *str1, const char *str2);

/**
 * @brief
 * @param
 * @param
 * @return
 */
ZPLIB_API int StrNCmpIgnoreCase(const char *str1, const char *str2, unsigned long long n);

/**
 * @brief
 * @param
 * @param
 * @return
 */
ZPLIB_API void LoadLoop(const char* text, int style);

#endif // INC_ZPLIB_H

