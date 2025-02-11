#include <stdio.h>
#include <time.h>
#include <conio.h>                 //kbhit()/_kbhit(),getch()
#include <Windows.h>               //Sleep(ms)

void ChangeConsoleTextColor(WORD color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

int main(void){
    //动态计时参数（打印值）
    unsigned int hour = 0, min = 0, sec = 0;
    //默认值（设定的计时参数）
    unsigned int hour_def = 0, min_def = 0, sec_def = 0;
    time_t time_sec = 0;
    time_t old_sec = 0;
    char key;
    int pause_flag = 1;            //暂停标志
    int menu_flag = 1;             //菜单打印标志
    while(1)
    {
        /**************** 菜单打印 ****************/
        if(menu_flag == 1)
        {
            menu_flag = 0;
            system("cls");          //Windows系统清屏命令
            printf("═════════════════════════════════\n"); //菜单
            if(hour_def || min_def || sec_def){
                printf("│\t倒计时时间：%02d:%02d:%02d\t│\n", hour_def, min_def, sec_def);
            }
            else
                printf("|\t未设置计时时间\t\t|\n");
            printf("│ S:设置 空格:开始/暂停 Q:退出\t│\n");
            printf("═════════════════════════════════\n");
            if(pause_flag == 0)
            {
                printf("计时结束\n");
                for(int i = 0; i < 5; i++)
                {
                    printf("\a");             //响蜂鸣器（或系统提示音）
                    Sleep(1);                 //延时1秒，太短电脑不发出声音
                }
                pause_flag = 1;          //停止计时

            }
        }

        /**************** 键盘按键扫描+操作 ****************/
        key = 0;
        if(_kbhit())                      //检测到按键按下
            key = getch();                //读取按键
        switch(key)
        {
            case 's':                     //按s/S设置计时时间
            case 'S':
                printf("请设置计时时间——时 分 秒\n");
                scanf("%d %d %d", &hour_def, &min_def, &sec_def);
                if(hour_def > 24 || min_def > 59 || sec_def > 59)
                {
                    //printf("时间设置失败\n");
                    hour_def = min_def = sec_def = 0; //重置时间
                }
                hour = min = sec = 0;       //计时值清零
                menu_flag = 1;              //打印菜单
                break;
            case ' ':                       //按空格键开始/暂停计时
                if(hour_def || min_def || sec_def)   //如果时间有效
                {
                    if(pause_flag)
                    {
                        pause_flag = 0;     //开始计时或继续计时
                        if(!hour && !min && !sec) //计数值为0
                        {
                            hour = hour_def;   //读取上次设置的时间
                            min = min_def;
                            sec = sec_def;
                            //打印初始时间
                            printf("倒计时: %02d:%02d:%02d\r", hour, min, sec);
                        }
                    }
                    else
                        pause_flag = 1;     //暂停计时
                    time(&time_sec);        //获取当前秒数（1970-1-1 00:00:00到现在）
                    old_sec = time_sec;     //更新旧的秒数
                }
                break;
            case 'q':
            case 'Q': printf("程序退出\n");return 0;
        }

        /**************** 计时操作 ****************/
        time(&time_sec);              //获取秒数保存到time_t变量
        if(pause_flag == 0 && old_sec != time_sec)
        {
            old_sec = time_sec;       //更新旧的秒数
            if(sec > 0)
                sec--;                //计时秒数减1
            else
            {
                sec = 59;             //如果原秒数为0，则变为59
                if(min > 0)
                    min--;            //计时分钟减1
                else
                {
                    min = 59;         //如果分钟数为0，则变为59
                    hour--;           //计时小时数减1
                }
            }
            printf("倒计时: ");
            ChangeConsoleTextColor(0xCE);
            printf("%02d:%02d:%02d\r", hour, min, sec);
            ChangeConsoleTextColor(0x07);

            if(!hour && !min && !sec) //计时结束
                menu_flag = 1;        //打印菜单
        }
    }
    return 0;
}