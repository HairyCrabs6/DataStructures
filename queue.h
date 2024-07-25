#pragma once
// #pragma once 是一种预处理指令
// 作用是确保在编译过程中该文件只被包含一次。
// 这通常用于防止头文件的内容被多次包含，这可能会引起编译错误或重定义问题。

//定义链表
typedef struct Node
{
	char *data;
	struct Node* next;
}Node_t;

//函数
void queue_push(void);//入队
void queue_pop(void);//出队
void Search_node(void);//寻找结点数据位置
void Print_All_Node(void);//遍历打印所有结点