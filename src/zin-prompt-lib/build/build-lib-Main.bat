@ECHO OFF
REM 构建动态库 SLLC、SLLS、zplib

REM SET ZPrompt_HOME=B:\ZP-Win

SET SrcFile_SLLC=%ZPrompt_HOME%\src\lib-src\SLLC.c
SET SrcFile_SLLS=%ZPrompt_HOME%\src\lib-src\SLLS.c
SET SrcFile_zplib=%ZPrompt_HOME%\src\lib-src\zplib.c

SET ObjFile_SLLC=%ZPrompt_HOME%\src\lib-src\SLLC.o
SET ObjFile_SLLS=%ZPrompt_HOME%\src\lib-src\SLLS.o
SET ObjFile_zplib=%ZPrompt_HOME%\src\lib-src\zplib.o

SET DllFile_SLLC=%ZPrompt_HOME%\lib\SLLC.dll
SET DllFile_SLLS=%ZPrompt_HOME%\lib\SLLS.dll
SET DllFile_zplib=%ZPrompt_HOME%\lib\zplib.dll

SET DefFile_SLLC=%ZPrompt_HOME%\src\lib-src\SLLC.def
SET DefFile_SLLS=%ZPrompt_HOME%\src\lib-src\SLLS.def
SET DefFile_zplib=%ZPrompt_HOME%\src\lib-src\zplib.def

SET GCC-LibFile_SLLC=%ZPrompt_HOME%\lib\gcc\libSLLC.a
SET GCC-LibFile_SLLS=%ZPrompt_HOME%\lib\gcc\libSLLS.a
SET GCC-LibFile_zplib=%ZPrompt_HOME%\lib\gcc\libzplib.a

SET VC-LibFile_SLLC=%ZPrompt_HOME%\lib\vc\SLLC.lib
SET VC-LibFile_SLLS=%ZPrompt_HOME%\lib\vc\SLLS.lib
SET VC-LibFile_zplib=%ZPrompt_HOME%\lib\vc\zplib.lib

REM 创建目标文件
gcc -c %SrcFile_SLLC% -o %ObjFile_SLLC% -I%ZPrompt_HOME%\include -DSLLC_EXPORTS -Os -flto
gcc -c %SrcFile_SLLS% -o %ObjFile_SLLS% -I%ZPrompt_HOME%\include -DSLLS_EXPORTS -Os -flto
gcc -c %SrcFile_zplib% -o %ObjFile_zplib% -I%ZPrompt_HOME%\include -DZPLIB_EXPORTS -Os -flto

REM 生成动态链接库及导入库
gcc -shared %ObjFile_SLLC% -o %DllFile_SLLC% -Wl,--out-implib,%GCC-LibFile_SLLC% -Os -flto
gcc -shared %ObjFile_SLLS% -o %DllFile_SLLS% -Wl,--out-implib,%GCC-LibFile_SLLS% -Os -flto
gcc -shared %ObjFile_zplib% -o %DllFile_zplib% -Wl,--out-implib,%GCC-LibFile_zplib% -Os -flto

REM 使用dlltool生成VS兼容的.lib文件
dlltool -d %DefFile_SLLC% -l %VC-LibFile_SLLC% --dllname %DllFile_SLLC%
dlltool -d %DefFile_SLLS% -l %VC-LibFile_SLLS% --dllname %DllFile_SLLS%
dlltool -d %DefFile_zplib% -l %VC-LibFile_zplib% --dllname %DllFile_zplib%

REM 删除目标文件
DEL %ObjFile_SLLC%
DEL %ObjFile_SLLS%
DEL %ObjFile_zplib%

REM 查看最终文件
DIR %DllFile_SLLC% %DllFile_SLLS% %DllFile_zplib%

@ECHO CREATE Completed!
PAUSE