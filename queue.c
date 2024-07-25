#define _CRT_SECURE_NO_WARNINGS 
#include "queue.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

Node_t* front;//队头
Node_t* rear;//队尾
int NodeNum = 0;

//入队
void queue_push(void)
{
	int num = 0;
	char data[100] = {0};
	
	Node_t* node;//要插入的结点
	node = (Node_t*)malloc(sizeof(Node_t));
			
	printf("请输入入队结点的数据,最多99字符\r\n");
	scanf("%99s", data);//使用 scanf 以字符串的形式读取用户输入，限制最多读取99个字符以避免溢出
	node->data = (char*)malloc((strlen(data) + 1) * sizeof(char));

	if (node->data == NULL) 
	{
		// 处理内存分配失败的情况
		printf("内存分配失败\r\n");
		return;
	}
	node->next = NULL;
	strcpy(node->data, data);

	if (NodeNum == 0)
	{
		front = node;
		rear = node;
	}
	else
	{
		rear->next = node;
		rear = node;
	}
	NodeNum++;
	printf("成功入队\r\n");
}

void queue_pop(void)//出队
{
	int num = 0;
	char* data;
	Node_t* temp;//中转的结点
	Node_t* prem;//定位的前一个结点

	if (NodeNum == 0)
	{
		printf("队列里没有数据，不能出队\r\n");
	}
	else if (NodeNum == 1)//队列里只有一个数据
	{
		front = NULL;
		rear = NULL;
		NodeNum--;
		printf("成功出队\r\n");
	}
	else
	{
		temp = front;
		free(temp->data);
		front = temp->next;
		free(temp);
		NodeNum--;
		printf("成功出队\r\n");
	}

}

void Search_node(void)//寻找结点数据位置
{
	int num = 0;
	char data[100] = {0};
	Node_t* temp;//中转的结点

	printf("请输入要寻找的数据，最多99字符\r\n");
	scanf("%99s", data);//使用 scanf 以字符串的形式读取用户输入，限制最多读取99个字符以避免溢出

	if (!front)//没有结点
		printf("没有该数据\r\n;");
	else if (strcmp(front->data, data) == 0)//判断头结点
	{
		printf("该数据在 队列头结点 位置\r\n");
	}
	else//其他结点
	{
		temp = front;
		for (int i = 1; i < NodeNum; i++)
		{
			temp = temp->next;
			if (strcmp(temp->data, data) == 0)
			{
				printf("该数据在第 %d 个的位置，0、1、2...的顺序\r\n", i);
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

	temp = front;
	if (!front)//没有结点
		printf("没有结点可供打印\r\n");
	else
	{
		printf("第 0 个位置的值为 %s\r\n", front->data);//头结点的数据
		do
		{
			i++;
			temp = temp->next;
			printf("第 %d 个位置的值为 %s\r\n", i, temp->data);
		} while (temp->next != NULL);
		
	}

}
