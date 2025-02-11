#include <stdio.h>
#include <time.h>
#include <conio.h>                 //kbhit()/_kbhit(),getch()
#include <Windows.h>               //Sleep(ms)

void ChangeConsoleTextColor(WORD color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

int main(void){
    //��̬��ʱ��������ӡֵ��
    unsigned int hour = 0, min = 0, sec = 0;
    //Ĭ��ֵ���趨�ļ�ʱ������
    unsigned int hour_def = 0, min_def = 0, sec_def = 0;
    time_t time_sec = 0;
    time_t old_sec = 0;
    char key;
    int pause_flag = 1;            //��ͣ��־
    int menu_flag = 1;             //�˵���ӡ��־
    while(1)
    {
        /**************** �˵���ӡ ****************/
        if(menu_flag == 1)
        {
            menu_flag = 0;
            system("cls");          //Windowsϵͳ��������
            printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n"); //�˵�
            if(hour_def || min_def || sec_def){
                printf("��\t����ʱʱ�䣺%02d:%02d:%02d\t��\n", hour_def, min_def, sec_def);
            }
            else
                printf("|\tδ���ü�ʱʱ��\t\t|\n");
            printf("�� S:���� �ո�:��ʼ/��ͣ Q:�˳�\t��\n");
            printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
            if(pause_flag == 0)
            {
                printf("��ʱ����\n");
                for(int i = 0; i < 5; i++)
                {
                    printf("\a");             //�����������ϵͳ��ʾ����
                    Sleep(1);                 //��ʱ1�룬̫�̵��Բ���������
                }
                pause_flag = 1;          //ֹͣ��ʱ

            }
        }

        /**************** ���̰���ɨ��+���� ****************/
        key = 0;
        if(_kbhit())                      //��⵽��������
            key = getch();                //��ȡ����
        switch(key)
        {
            case 's':                     //��s/S���ü�ʱʱ��
            case 'S':
                printf("�����ü�ʱʱ�䡪��ʱ �� ��\n");
                scanf("%d %d %d", &hour_def, &min_def, &sec_def);
                if(hour_def > 24 || min_def > 59 || sec_def > 59)
                {
                    //printf("ʱ������ʧ��\n");
                    hour_def = min_def = sec_def = 0; //����ʱ��
                }
                hour = min = sec = 0;       //��ʱֵ����
                menu_flag = 1;              //��ӡ�˵�
                break;
            case ' ':                       //���ո����ʼ/��ͣ��ʱ
                if(hour_def || min_def || sec_def)   //���ʱ����Ч
                {
                    if(pause_flag)
                    {
                        pause_flag = 0;     //��ʼ��ʱ�������ʱ
                        if(!hour && !min && !sec) //����ֵΪ0
                        {
                            hour = hour_def;   //��ȡ�ϴ����õ�ʱ��
                            min = min_def;
                            sec = sec_def;
                            //��ӡ��ʼʱ��
                            printf("����ʱ: %02d:%02d:%02d\r", hour, min, sec);
                        }
                    }
                    else
                        pause_flag = 1;     //��ͣ��ʱ
                    time(&time_sec);        //��ȡ��ǰ������1970-1-1 00:00:00�����ڣ�
                    old_sec = time_sec;     //���¾ɵ�����
                }
                break;
            case 'q':
            case 'Q': printf("�����˳�\n");return 0;
        }

        /**************** ��ʱ���� ****************/
        time(&time_sec);              //��ȡ�������浽time_t����
        if(pause_flag == 0 && old_sec != time_sec)
        {
            old_sec = time_sec;       //���¾ɵ�����
            if(sec > 0)
                sec--;                //��ʱ������1
            else
            {
                sec = 59;             //���ԭ����Ϊ0�����Ϊ59
                if(min > 0)
                    min--;            //��ʱ���Ӽ�1
                else
                {
                    min = 59;         //���������Ϊ0�����Ϊ59
                    hour--;           //��ʱСʱ����1
                }
            }
            printf("����ʱ: ");
            ChangeConsoleTextColor(0xCE);
            printf("%02d:%02d:%02d\r", hour, min, sec);
            ChangeConsoleTextColor(0x07);

            if(!hour && !min && !sec) //��ʱ����
                menu_flag = 1;        //��ӡ�˵�
        }
    }
    return 0;
}