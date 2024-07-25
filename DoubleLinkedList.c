#define _CRT_SECURE_NO_WARNINGS 
#include "DoubleLinkedList.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

Node_t* head;
int NodeNum = 0;

//插入结点
void Insert_node(void)
{
	int num = 0;
	char data[100] = {0};
	Node_t* temp;
	

	Node_t* node;//要插入的结点
	node = (Node_t*)malloc(sizeof(Node_t));
	
	do
	{
		printf("请输入要插入结点的位置，0代表头结点，仅能输入数字\r\n");
		scanf_s("%d", &num);
	} while (num < 0 || num > NodeNum);
		
	printf("请输入该结点的数据,最多99字符\r\n");
	scanf("%99s", data);//使用 scanf 以字符串的形式读取用户输入，限制最多读取99个字符以避免溢出

	node->data = (char*)malloc((strlen(data) + 1) * sizeof(char));

	if (node->data == NULL) {
		// 处理内存分配失败的情况
		printf("内存分配失败\r\n");
		return;
	}
	node->pre = NULL;
	node->next = NULL;
	strcpy(node->data, data);

	if (NodeNum == 0)//结点数为0
	{
		head = node;
	}
	else if (num == 0)//结点数不为0，插入头结点
	{
		head->pre = node;
		node->next = head;
		head = node;
	}
	else//其他结点
	{
		temp = head;
		for (int i = 1; i < num; i++)
		{
			temp = temp->next;//遍历到插入结点之前的结点
		}
			
		if (temp->next)//下一个不为空
		{
			node->pre = temp;
			node->next = temp->next;
			temp->next = node;
			temp->next->pre = node;			
		}
		else
		{
			temp->next = node;
			node->pre = temp;
			node->next = NULL;
		}
	}
	NodeNum++;
	printf("成功将结点插入到 %d 位置\r\n", num);

}

void Delete_node(void)//删除结点
{
	int num = 0;
	char* data;
	Node_t* temp;//中转的结点
	Node_t* prem;//定位的前一个结点

	do
	{
		printf("请输入要删除结点的位置，0代表头结点，仅能输入数字\r\n");
		scanf_s("%d", &num);
	} while (num < 0 || num > NodeNum);

	if (NodeNum == 0)
		printf("没有结点，删除失败\r\n");
	else if (num == 0)//删除头结点
	{
		temp = head;
		free(temp->data);
		head = head->next;
		head->pre = NULL;
		free(temp);
		NodeNum--;
		printf("成功将 %d 位置的结点删除\r\n", num);
	}
	else//其他结点
	{
		prem = head;
		for (int i = 1; i <= (num - 1); i++)
		{
			prem = prem->next;
		}
		temp = prem->next;
		if (temp->next != NULL)//被删除的下一个不为空
		{
			prem->next = temp->next;
			temp->next->pre = prem;
			free(temp->data);
			free(temp);
			NodeNum--;
			printf("成功将 %d 位置的结点删除\r\n", num);
		}
		else
		{
			prem->next = NULL;
			free(temp->data);
			free(temp);
			NodeNum--;
			printf("成功将 %d 位置的结点删除\r\n", num);
		}


	}
	
	
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
		printf("该数据在 头结点 位置\r\n");
	}
	else//其他结点
	{
		temp = head;
		for (int i = 1; i < NodeNum; i++)
		{
			temp = temp->next;
			if (strcmp(temp->data, data) == 0)
			{
				printf("该数据在第 %d 个的位置，0、1、2...的顺序\r\n", i);
				return;
			}
		}
		printf("没有该数据\r\n");

	}
}

void Print_All_node(void)//正序遍历打印所有结点
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
