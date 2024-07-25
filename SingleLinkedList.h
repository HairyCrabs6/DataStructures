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
void Insert_node(void);//插入结点
void Delete_node(void);//删除结点
void Search_node(void);//寻找结点数据位置
void Print_All_node(void);//遍历打印所有结点