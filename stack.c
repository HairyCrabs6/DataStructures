#define _CRT_SECURE_NO_WARNINGS 
#include "stack.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

Node_t* head;
int NodeNum = 0;

//入栈
void stack_push(void)
{
	int num = 0;
	char data[100] = {0};
	
	Node_t* node;//要插入的结点
	node = (Node_t*)malloc(sizeof(Node_t));
			
	printf("请输入入栈结点的数据,最多99字符\r\n");
	scanf("%99s", data);//使用 scanf 以字符串的形式读取用户输入，限制最多读取99个字符以避免溢出
	node->data = (char*)malloc((strlen(data) + 1) * sizeof(char));
	if (node->data == NULL) {
		// 处理内存分配失败的情况
		printf("内存分配失败\r\n");
		return;
	}
	node->next = NULL;
	strcpy(node->data, data);

	//将刚入栈的结点作为头结点
	node->next = head;
	head = node;
	NodeNum++;
	printf("成功入栈\r\n");
}

void stack_pop(void)//出栈
{
	int num = 0;
	char* data;
	Node_t* temp;//中转的结点
	Node_t* prem;//定位的前一个结点

	temp = head;
	free(temp->data);
	head = temp->next;
	free(temp);
	NodeNum--;
	printf("成功出栈\r\n");
}

void Search_node(void)//寻找结点数据位置
{
	int num = 0;
	char data[100] = {0};
	Node_t* temp;//中转的结点

	printf("请输入要寻找的数据，最多99字符\r\n");
	scanf("%99s", data);//使用 scanf 以字符串的形式读取用户输入，限制最多读取99个字符以避免溢出

	if (!head)//没有结点
		printf("没有该数据\r\n;");
	else if (strcmp(head->data, data) == 0)//判断头结点
	{
		printf("该数据在 栈顶 位置\r\n");
	}
	else//其他结点
	{
		temp = head;
		for (int i = 1; i < NodeNum; i++)
		{
			temp = temp->next;
			if (strcmp(temp->data, data) == 0)
			{
				printf("该数据在第 %d 个的位置，0、1、2...的顺序，0为栈顶\r\n", i);
				return;
			}
			printf("没有该数据\r\n");
		}

	}
}

void Print_All_Node(void)//遍历打印所有结点
{
	int i = 0;
	Node_t* temp;//中转的结点

	temp = head;
	if (!head)//没有结点
		printf("没有结点可供打印\r\n");
	else
	{
		printf("第 0 个位置的值为 %s\r\n", head->data);//头结点的数据
		do
		{
			i++;
			temp = temp->next;
			printf("第 %d 个位置的值为 %s\r\n", i, temp->data);
		} while (temp->next != NULL);
		
	}

}
