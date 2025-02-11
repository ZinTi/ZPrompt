/*****************************************************************
 * NodeSLLC : Node SinglyLinkedList of Char, 以字符为节点的单链表的节点
 * SLLC     : SinglyLinkedList of Char, 以字符为节点的单链表
 * 
 * 
 *************************************************************/
#ifndef SLLC_H
#define SLLC_H
#ifdef _WIN32
    #ifdef SLLC_EXPORTS
        #define SLLC_API __declspec(dllexport)
    #else
        #define SLLC_API __declspec(dllimport)
    #endif
#else
    #define SLLC_API
#endif

// 定义链表节点结构体
typedef struct NodeSLLC {
    char data;
    struct NodeSLLC* next;
} NodeSLLC, *SLLC;

// 初始化链表
SLLC_API SLLC InitSLLC();
// 头插法新增节点
SLLC_API void InsertHeadSLLC(SLLC head, char data);
// 尾插法新增节点
SLLC_API void InsertTailSLLC(SLLC head, char data);
// 查询第一次出现某字符的节点位置
SLLC_API int FindFirstSLLC(SLLC head, char data);
// 查询最后一次出现某字符的节点位置
SLLC_API int FindLastSLLC(SLLC head, char data);
// 查询指定位置的字符内容
SLLC_API char GetDataAtSLLC(SLLC head, int index);
// 删除指定位置的节点
SLLC_API void DeleteAtSLLC(SLLC head, int index);
// 修改指定位置的节点内容
SLLC_API void ModifyAtSLLC(SLLC head, int index, char newData);
// 计算链表长度
SLLC_API int ListLengthSLLC(SLLC head);
// 打印链表内容
SLLC_API void PrintSLLC(SLLC head);
// 顺序排序
SLLC_API void SortSLLC(SLLC head);
// 倒序排序
SLLC_API void ReverseSortSLLC(SLLC head);
// 在链表尾部追加字符串作为一串节点
SLLC_API void AppendStringSLLC(SLLC head, const char* str);
// 复制链表（深复制）
SLLC_API SLLC CopySLLC(SLLC head);
// 将链表内容拼接成字符串
SLLC_API char* ToStringSLLC(SLLC head);
// 释放链表内存
SLLC_API void FreeSLLC(SLLC head);

#endif // SLLC_H
