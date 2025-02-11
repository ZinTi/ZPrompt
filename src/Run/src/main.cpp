#include "frame.h"

class ShortOptions{
private:
	bool help;	   // -h
	bool version;  // -v
	bool logo;	   // -l
	bool subArgs;  // -a
	bool output;   // -o
public:
	ShortOptions(){
		this->help = false;
		this->version = false;
		this->logo = false;
		this->subArgs = false;
		this->output = false;
	}
	~ShortOptions() {} // Destructor
	void printAll(){
		printf("opt.help:     %s\n", help ? "true" : "false");
		printf("opt.version:  %s\n", version ? "true" : "false");
		printf("opt.logo:     %s\n", logo ? "true" : "false");
		printf("opt.subArgs:  %s\n", subArgs ? "true" : "false");
		printf("opt.output:   %s\n", output ? "true" : "false");
		putchar('\n');
	}

	void analyShortOpt(const char* opt){
		for (int i = 1;; i++){
			if (*(opt + i) == '\0')
				break;
			else if (*(opt + i) == 'h')
				this->help = true;
			else if (*(opt + i) == 'v')
				this->version = true;
			else if (*(opt + i) == 'l')
				this->logo = true;
			else if (*(opt + i) == 'a')
				this->subArgs = true;
			else if (*(opt + i) == 'o')
				this->output = true;
			else
				printf("Unknow `-%c`\n", *(opt + i));
		}
	}
	bool getHelp(void){
		return this->help;
	}
	bool getVersion(void){
		return this->version;
	}
	bool getLogo(void){
		return this->logo;
	}
	bool getSubArgs(void){
		return this->subArgs;
	}
	bool getOutput(void){
		return this->output;
	}
};

void PerformOperations(ShortOptions* opt, run::prog::IcoToWinRes* pIcoToWinRes, run::prog::SrcToELF* pSrcToELF, char* subArg){
	if (opt->getVersion()){
		DisplayVersion();
	}
	if (opt->getHelp()){
		DisplayManual();
	}
	if (opt->getLogo()){
		printf("ICO filename> ");
		char tempStr[1024];
		fgets(tempStr, sizeof(tempStr), stdin);
		pIcoToWinRes->setIcoFn(tempStr); // 指定ICO文件名
	}

	if (opt->getSubArgs()){
		printf("Subprocess options> ");
		fgets(subArg, sizeof(subArg), stdin);
	}
	if (opt->getOutput()){ // 指定ELF文件输出名
		pSrcToELF->inputELF();
	}
}

run::prog::IcoToWinRes WR1;
run::prog::SrcToELF srcToELF;

int main(int argc, char* argv[]){
	ChCP(65001, 65001);

	char* subArgs = new char[MaxSizeSubproArgs];

	if (argc == 3){
		if (*argv[1] == '-' && *(argv[1] + 1) != '-'){
			ShortOptions opt1;
			opt1.analyShortOpt(argv[1]);
			PerformOperations(&opt1, &WR1, &srcToELF, subArgs);
			srcToELF.setSrcFn(argv[2]); // Output ELF filename.
		}
		else if (*argv[1] == '-' && *(argv[1] + 1) == '-'){
			PrintError("main()", "The program only supports combined short options and does not support long options or separate short options."); // 只支持组合短选项，不支持长选项和分离短选项
			SafeExit(0);
		}
		else{
			DisplayErrorTips(argv[1]);
			SafeExit(0);
		}
	}
	else if (argc == 2){
		srcToELF.setSrcFn(argv[1]);
	}
	else if (argc == 1){
		CREPL();
		SafeExit(0);
	}
	else{
		printf("Too many arguments.\n");
		SafeExit(0);
	}

	if (srcToELF.CompileAssemble()){ // 改用 try{}catch(){}
		PrintError("srcToELF.CompileAssemble()", "Error! An error occurred during the compilation or assembly.");
	}

	srcToELF.Link();

	ChildProcess* child = new ChildProcess((const char*)srcToELF.getELF(), subArgs, true);
	child->execSubprog();
	delete child;

	ChCP(0, 0);
	return 0;
}