//系统库
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <winsock2.h>
#include <windows.h>

// 自建库
#include "zplib.h"

#pragma comment(lib, "ws2_32.lib") // 链接Winsock库

#define MaxLenStr 50
#define NTP_TIMESTAMP_DELTA 2208988800ull // 1970年到1900年之间的秒数

void ShowManual(void);
void ShowCurrentDateTime(short int loop);
void Get_NTP_time(const char *server);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("What do you want to know?");
    } else {
        if (!StrCmpIgnoreCase(argv[1], "time")) {
            if (argc >= 3 && !strcmp(argv[2], "-l")) {
                ShowCurrentDateTime(1);
            } else {
                ShowCurrentDateTime(0);
            }
        } else if (!StrCmpIgnoreCase(argv[1], "ntpTime")) {
            // 从time.windows.com获取NTP时间，或者使用用户提供的NTP服务器地址
            const char* ntp_server = (argc >= 3) ? argv[2] : "time.windows.com";
            printf("从 %s 获取NTP时间\n", ntp_server);
            Get_NTP_time(ntp_server);
        } else {
            printf("I don't understand what you're saying.\n");
            ShowManual();
        }
    }

    return 0;
}

void ShowManual(void){
    printf("[ USAGE ]\n");
    printf("    tellMe.exe time [-l]\n");
    printf("    tellMe.exe ntptime [授时服务器域名 | 授时服务器ip地址]\n");
}

void ShowCurrentDateTime(short int loop) {
    printf("tellme.exe time [-l]\n");

    HANDLE hOut = NULL; //定义句柄变量
    CONSOLE_CURSOR_INFO cursorInfo; //光标信息变量
    hOut = GetStdHandle(STD_OUTPUT_HANDLE); //获取标准输出句柄
    GetConsoleCursorInfo(hOut, &cursorInfo); //获取当前光标信息
    cursorInfo.dwSize = 25;
    cursorInfo.bVisible = 0;
    SetConsoleCursorInfo(hOut, &cursorInfo);

    time_t now_time;

    printf("Current datetime: \n");
    do {
        time(&now_time);
        char nowtimestr[MaxLenStr];
        strcpy(nowtimestr, ctime(&now_time));
        nowtimestr[strlen(nowtimestr)-1] = '\0'; // 去掉最后一个换行符

        ColorPuts(0xCE, nowtimestr, 0);
        
        if (loop) {
            Sleep(1000); // 延时1秒
            putchar('\r'); //光标回到行首（回车不换行）
        } else {
            putchar('\n');
        }
    } while (loop);

    CloseHandle(hOut);
}

void Get_NTP_time(const char *server) {
    //  获取NTP时间的同时运行LoadLoop("Loading")以目的是告诉用户当前程序还在运行中，当获取到数据后停止运行LoadLoop("Loading")并输出数据。

    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in server_addr;
    struct hostent *host;
    char packet[48] = {0};  // NTP请求数据包大小为48字节
    packet[0] = 0x1B;       // 设置NTP请求头，LI=0, VN=3, Mode=3 (client)

    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Winsock 初始化失败.\n");
        return;
    }

    // 解析域名，获取IP地址
    if ((host = gethostbyname(server)) == NULL) {
        printf("域名解析失败: %s\n", server);
        WSACleanup();
        return;
    }

    // 创建socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
        printf("Socket 创建失败.\n");
        WSACleanup();
        return;
    }

    // 配置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(123);  // NTP默认端口123
    server_addr.sin_addr.s_addr = *(unsigned long*)host->h_addr_list[0];  // 使用解析的IP地址

    // 发送NTP请求
    if (sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("发送数据失败.\n");
        closesocket(sockfd);
        WSACleanup();
        return;
    }

    // 接收NTP响应
    int server_addr_len = sizeof(server_addr);
    if (recvfrom(sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&server_addr, &server_addr_len) == SOCKET_ERROR) {
        printf("接收数据失败.\n");
        closesocket(sockfd);
        WSACleanup();
        return;
    }

    // 解析NTP响应中的时间戳（前32位是秒数，后32位是小数部分）
    unsigned long long ntp_time = (unsigned long long)(packet[43] & 0xFF) | 
                                  (unsigned long long)(packet[42] & 0xFF) << 8 | 
                                  (unsigned long long)(packet[41] & 0xFF) << 16 | 
                                  (unsigned long long)(packet[40] & 0xFF) << 24;

    // 转换为Unix时间戳（减去NTP时间戳的偏移）
    time_t unix_time = (time_t)(ntp_time - NTP_TIMESTAMP_DELTA);

    // 打印时间
    printf("NTP 时间：");
    ColorPuts(0xCE, ctime(&unix_time), 0);

    // 清理
    closesocket(sockfd);
    WSACleanup();
}
