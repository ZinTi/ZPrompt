/*****************************************************************
 * NodeSLLS : Node SinglyLinkedList of Strings, 以字符串为节点的单链表的节点
 * SLLS     : SinglyLinkedList of Strings, 以字符串为节点的单链表
 * 
 * 
 *************************************************************/
#ifndef SLLS_H
#define SLLS_H

#ifdef _WIN32
    #ifdef SLLS_EXPORTS
        #define SLLS_API __declspec(dllexport)
    #else
        #define SLLS_API __declspec(dllimport)
    #endif
#else
    #define SLLS_API
#endif

// 定义链表节点结构体
typedef struct NodeSLLS {
    char *data;
    struct NodeSLLS* next;
} NodeSLLS, *SLLS;

// 初始化单链表
SLLS_API SLLS InitSLLS(void);
// 创建新节点
SLLS_API SLLS CreateNodeSLLS(const char* data);
// 头插法新增节点
SLLS_API void InsertNodeSLLSAtHead(SLLS head, const char* data);
// 尾插法新增节点
SLLS_API void InsertNodeSLLSAtTail(SLLS head, const char* data);
// 查询节点位置（根据内容，返回位置从1开始）
SLLS_API int FindNodeSLLSByContent(SLLS head, const char* data);
// 查询节点内容（根据位置）
SLLS_API char* FindNodeSLLSByPosition(SLLS head, int position);
// 删除指定位置节点
SLLS_API void DeleteNodeSLLSByPosition(SLLS head, int position);
// 删除匹配内容的节点
SLLS_API void DeleteNodeSLLSByContent(SLLS head, const char* data);
// 修改节点内容（根据匹配原内容）
SLLS_API void ModifyNodeSLLSByContent(SLLS head, const char* oldData, const char* newData);
// 修改节点内容（根据指定位置）
SLLS_API void ModifyNodeSLLSByPosition(SLLS head, int position, const char* newData);
// 冒泡排序实现顺序排序
SLLS_API void SortSLLSAscending(SLLS head);
// 冒泡排序实现倒序排序
SLLS_API void SortSLLSDescending(SLLS head);
// 计算链表的元素个数（不包含头节点）
SLLS_API int GetSLLSLength(SLLS head);
// 打印链表
SLLS_API void PrintSLLS(SLLS head);
// 释放链表内存
SLLS_API void FreeSLLS(SLLS head);

#endif // SLLS_H
