#define _CRT_SECURE_NO_WARNINGS 
#include "queue.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

Node_t* front;//��ͷ
Node_t* rear;//��β
int NodeNum = 0;

//���
void queue_push(void)
{
	int num = 0;
	char data[100] = {0};
	
	Node_t* node;//Ҫ����Ľ��
	node = (Node_t*)malloc(sizeof(Node_t));
			
	printf("��������ӽ�������,���99�ַ�\r\n");
	scanf("%99s", data);//ʹ�� scanf ���ַ�������ʽ��ȡ�û����룬��������ȡ99���ַ��Ա������
	node->data = (char*)malloc((strlen(data) + 1) * sizeof(char));

	if (node->data == NULL) 
	{
		// �����ڴ����ʧ�ܵ����
		printf("�ڴ����ʧ��\r\n");
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
	printf("�ɹ����\r\n");
}

void queue_pop(void)//����
{
	int num = 0;
	char* data;
	Node_t* temp;//��ת�Ľ��
	Node_t* prem;//��λ��ǰһ�����

	if (NodeNum == 0)
	{
		printf("������û�����ݣ����ܳ���\r\n");
	}
	else if (NodeNum == 1)//������ֻ��һ������
	{
		front = NULL;
		rear = NULL;
		NodeNum--;
		printf("�ɹ�����\r\n");
	}
	else
	{
		temp = front;
		free(temp->data);
		front = temp->next;
		free(temp);
		NodeNum--;
		printf("�ɹ�����\r\n");
	}

}

void Search_node(void)//Ѱ�ҽ������λ��
{
	int num = 0;
	char data[100] = {0};
	Node_t* temp;//��ת�Ľ��

	printf("������ҪѰ�ҵ����ݣ����99�ַ�\r\n");
	scanf("%99s", data);//ʹ�� scanf ���ַ�������ʽ��ȡ�û����룬��������ȡ99���ַ��Ա������

	if (!front)//û�н��
		printf("û�и�����\r\n;");
	else if (strcmp(front->data, data) == 0)//�ж�ͷ���
	{
		printf("�������� ����ͷ��� λ��\r\n");
	}
	else//�������
	{
		temp = front;
		for (int i = 1; i < NodeNum; i++)
		{
			temp = temp->next;
			if (strcmp(temp->data, data) == 0)
			{
				printf("�������ڵ� %d ����λ�ã�0��1��2...��˳��\r\n", i);
				return;
			}
			printf("û�и�����\r\n");
		}

	}
}

void Print_All_Node(void)//������ӡ���н��
{
	int i = 0;
	Node_t* temp;//��ת�Ľ��

	temp = front;
	if (!front)//û�н��
		printf("û�н��ɹ���ӡ\r\n");
	else
	{
		printf("�� 0 ��λ�õ�ֵΪ %s\r\n", front->data);//ͷ��������
		do
		{
			i++;
			temp = temp->next;
			printf("�� %d ��λ�õ�ֵΪ %s\r\n", i, temp->data);
		} while (temp->next != NULL);
		
	}

}
