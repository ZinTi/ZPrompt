// C++系统库
#include <iostream>
#include <string>
#include <regex> // 正则库
using namespace std;

extern "C" {
// C语言系统库
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>

// 自建C语言共享库
#include "zplib.h"

}

// 多文件编程的其他文件-内建命令
#include "cd.h"
#include "help.h"
#include "pwd.h"
#include "match_regex.h"
