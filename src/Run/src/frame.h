#ifndef FRAME_H
#define FRAME_H

//////////////////////////// C++ 系统库 //////////////////////////////
#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <regex>


//////////////////////////////// C库 /////////////////////////////////
extern "C" {
    // C系统库
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <cstdarg>
#include <cstring>

    // 自建共享C库
#include "zplib.h"
#include "SLLS.h" // 以字符串为节点元素的单链表
}

//////////////////////// 当前文件其他头文件 //////////////////////////
// 当前程序定义的一些类模块
#include "slls_ext.h"
#include "prog.h"

// 其他程序模块
#include "info.h"
#include "safe_exit.h"
#include "use_template.h"
#include "str.h"
#include "exception.h"
#include "crepl.h"
#include "config_loader.h"
#include "subprocess.h"
#include "match_regex.h"

//////////////////////////// 项目信息 ///////////////////////////////
#define SUBPROJ_NAME		            "RUN"
#define SUBPROJ_VER			            "0.1"

#define COLOR_ERROR                     0x47
#define MaxSizeFilename		            50
#define MaxLenPathLimit		            256
#define MaxSizeSubproArgs          	    256
#define BoundaryColor		            0x09
//////////////////////////// REPL ////////////////////////////////
#define MaxLenStatements	            100
#define MaxCharSize			            1024

#define CONFIGFILE			            "run.conf"
// 每行最大长度
#define LINE_MAX			            1024
/////////////////////////////////////////////////////////////////////

using namespace std;


#endif //FRAME_H
