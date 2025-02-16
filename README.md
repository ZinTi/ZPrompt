# ZPrompt version-0.1
## 一、简介
一个自用的 CLI 工具集。主要运行在 Windows 平台，部分运行在 GNU/Linux 上。

在 GNU/Linux 上有丰富的命令行工具，Windows 上大部分是图形化工具，而且缺乏好的包管理器。有时候自己写了个 CLI 工具或 batch 脚本，想直接在 Powershell / CMD 中调用，但不想都丢到 C 盘原有的系统环境变量下，就干脆单独新建一个环境变量集中管理。于是就写了这个工具集。

不过我现在懒得自己写 CLI 工具了。 GNU/Linux 平台上有什么好用的工具，我一般是去 工具官网 寻找有没有运行于 Windows 上的版本，例如 VIM 、Wget 等；如果只有 GNU/Linux 的版本，我可以使用 `Cygwin` 、`MinGW-w64`、`MSYS2` 重新编译下，然后使用。再不济，也可以使用 Windows 的 `WSL2` 。

## 二、安装和卸载
### 配置环境
使用自动或手动方式配置环境变量，然后验证是否配置成功。

#### (1) 自动处理
将压缩包解压在要安装的目录下，运行 `SetEnv-Windows.exe`，输入`i`或`I`继续，结束后即可使用工具集中的命令了。

#### (2) 手动添加
将压缩包解压在要安装的目录下，使用`sysdm.cpl`命令打开环境变量配置页面。新建系统变量，变量名为 `ZPrompt_HOME` ，变量值为ZPrompt解压缩目录的根目录。编辑系统`PATH`值，在`PATH`尾部追加值`;%ZPrompt_HOME%\lib;%ZPrompt_HOME%\bin;%ZPrompt_HOME%\scripts`。

#### (3) 验证结果
打开 `CMD` / `Powershell` / `Pwsh` / `Windows Terminal` 窗口。输入 `chcolor -l` 命令测试环境`%ZPrompt_HOME%\lib`和`%ZPrompt_HOME%\bin`是否配置成功；输入`np`或`np.bat`(命令会打开notepad.exe) 测试`%ZPrompt_HOME%\scripts`是否配置成功。

### 删除配置
运行解压目录下的`SetEnv-Windows.exe`，输入`u`或`U`删除环境变量。然后你可以手动删除全部文件了。

## 三、目录结构
经配置环境变量后，可通过命令`echo %ZPrompt_HOME%`或`Write-Output $env:ZPrompt_HOME`查看项目根目录的路径，前者为`CMD`的语法，后者为`Powershell`或`pwsh`的语法。
	
bin目录用于存放二进制的应用程序文件。该目录下有两个子目录，一个名为`use`，一个名为`win`。
`use`目录下的命令在使用前，需要在前面加上`use `。同理`win`目录下的命令则可以使用`win` + 该目录下的程序名称运行。bin/use 和 bin/win 相当于两个隔离环境，系统不会从这两个目录下寻找程序，你可以使用 use 和 win 命令运行这两个目录下的程序。

bin/use目录主要包括以下类型的程序:

	(1) 不容易记住文件名的 CLI、TUI 程序或脚本；
	(2) 来源于第三方的 CLI、TUI 程序或脚本；
	(3) 与环境变量中的其他程序重名的 CLI、TUI 程序或脚本(含同一程序的不同版本) 。

bin/win目录主要包括以下类型的程序: 

	(1) 不容易记住文件名的 GUI 程序；
	(2) 来源于第三方的 GUI 程序；
	(3) 与环境变量中的其他程序重名的 GUI 程序。

两个子目录下的程序和bin目录下的程序没有本质区别，设计这两个子目录进行隔离的主要目的是——避免这些程序和系统中一些同名的自建命令和函数冲突。故使用`use.exe`和`win.exe`作为中间媒介传递参数或选项，确保使用的是这两个子目录下的程序，而非系统中其他同名程序或函数。`use`命令和`win`命令的区别是: 前者运行时必须等待子进程(对应use目录下的程序) 结束才结束，适合作为Windows控制台类型的程序和普通脚本的中介；后者运行时则是在创建子进程后无需等待子进程结束才结束，适用于具有图形化的Windows桌面应用程序，避免出现多余的Windows控制台影响用户视觉体验。
```
ZPrompt:.
├─bin       可执行程序：二进制程序、Shell 脚本等
│  ├─use        (使用此目录下的命令，需要加上 `use `前缀)
│  └─win        (使用此目录下的命令，需要加上 `win `前缀)
├─conf      主要存放 configure 配置文件
├─docs      主要存放项目文档
├─include   第三方库头文件
├─lib       运行库等依赖
├─res       项目的各类资源文件如图像
├─scripts   各类脚本文件（例如 CMD 的 batch 脚本、Powershell的 ps1 脚本、VBS 脚本、Python 程序，以及快捷方式 lnk 文件）
└─src       当前项目的程序源代码
```


## 四、开发计划（放弃）
### ZP (ZinSimu)
之前想实现一个简单的 Shell Demo 程序，意义不是很大，就不想写了。

    (1) 实现词法分析器（Lexer）
    lexer.c 用于将输入的Bash脚本拆解为tokens，比如关键字、变量、字符串、操作符等。
    
    (2) 实现语法解释器（Parser）
    parser.c 负责讲标记转换为抽象语法树（AST）。
    
    (3) 内置命令（Built-ins）
    builtins.c 处理内置命令，例如exit(quit)、echo、cd、alias、help(manual)、prompt、version、clear(cls)、ls(dir)、cat(read, type)
    
    (4) 主程序（Main Program）
    zp.c 作为主程序，读取输入，调用词法分析器和语法解释器，并执行相应的命令。
    
    (5) 其他模块（Module）
    listProg、listBuild、updateModule

### Run
以前学C语言时写的模拟交互式REPL的“解释器”，后来想改成使用C++写，不过结构和逻辑混乱，放弃了。





	
