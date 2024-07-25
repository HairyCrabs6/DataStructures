#define _CRT_SECURE_NO_WARNINGS 
#include "SingleLinkedList.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

Node_t* head;
int NodeNum = 0;

//������
void Insert_node(void)
{
	int num = 0;
	char data[100] = {0};
	Node_t* temp;
	

	Node_t* node;//Ҫ����Ľ��
	node = (Node_t*)malloc(sizeof(Node_t));
	
	do
	{
		printf("������Ҫ�������λ�ã�0����ͷ��㣬������������\r\n");
		scanf_s("%d", &num);
	} while (num < 0 || num > NodeNum);
		
	printf("������ý�������,���99�ַ�\r\n");
	scanf("%99s", data);//ʹ�� scanf ���ַ�������ʽ��ȡ�û����룬��������ȡ99���ַ��Ա������

	node->data = (char*)malloc((strlen(data) + 1) * sizeof(char));
	memset(node->data, 0, (strlen(data) + 1) * sizeof(char));

	if (node->data == NULL) {
		// �����ڴ����ʧ�ܵ����
		printf("�ڴ����ʧ��\r\n");
		return;
	}
	node->next = NULL;
	strcpy(node->data, data);


	if (NodeNum == 0)//�����Ϊ0
	{
		head = node;
	}
	else if (num == 0)//�������Ϊ0������ͷ���
	{
		node->next = head;
		head = node;
	}
	else//�������
	{
		temp = head;
		while(temp->next != NULL)
		{
			temp = temp->next;
		} 
			
		temp->next = node;
		if (temp->next)//��һ����Ϊ��
			node->next = temp->next->next;
		else
			node->next = NULL;
	}
	NodeNum++;
	printf("�ɹ��������뵽 %d λ��\r\n", num);

}

void Delete_node(void)//ɾ�����
{
	int num = 0;
	char* data;
	Node_t* temp;//��ת�Ľ��
	Node_t* pre;//��λ��ǰһ�����

	do
	{
		printf("������Ҫɾ������λ�ã�0����ͷ��㣬������������\r\n");
		scanf_s("%d", &num);
	} while (num < 0 || num > NodeNum);

	if (NodeNum == 0)
		printf("û�н�㣬ɾ��ʧ��\r\n");
	else if (num == 0)//ɾ��ͷ���
	{
		temp = head;
		free(temp->data);
		head = head->next;
		free(temp);
		NodeNum--;
		printf("�ɹ��� %d λ�õĽ��ɾ��\r\n", num);
	}
	else//�������
	{
		pre = head;
		for (int i = 1; i < (num - 1); i++)
		{
			pre = pre->next;
		}
		temp = pre->next;
		pre->next = temp->next;
		free(temp->data);
		free(temp);
		NodeNum--;
		printf("�ɹ��� %d λ�õĽ��ɾ��\r\n", num);
	}
	
	
}

void Search_node(void)//Ѱ�ҽ������λ��
{
	int num = 0;
	char data[100] = {0};
	Node_t* temp;//��ת�Ľ��

	printf("������ҪѰ�ҵ����ݣ����99�ַ�\r\n");
	scanf("%99s", data);//ʹ�� scanf ���ַ�������ʽ��ȡ�û����룬��������ȡ99���ַ��Ա������

	if (!head)//û�н��
		printf("û�и�����\r\n;");
	else if (strcmp(head->data, data) == 0)//�ж�ͷ���
	{
		printf("�������� ͷ��� λ��\r\n");
	}
	else//�������
	{
		temp = head;
		for (int i = 1; i < NodeNum; i++)
		{
			temp = temp->next;
			if (strcmp(temp->data, data) == 0)
			{
				printf("�������ڵ� %d ����λ�ã�0��1��2...��˳��\r\n", i);
				break;
			}
			printf("û�и�����\r\n");
		}

	}
}

void Print_All_node(void)//������ӡ���н��
{
	int i = 0;
	Node_t* temp;//��ת�Ľ��

	temp = head;
	if (!head)//û�н��
		printf("û�н��ɹ���ӡ\r\n");
	else
	{
		printf("�� 0 ��λ�õ�ֵΪ %s\r\n", head->data);//ͷ��������
		do
		{
			i++;
			temp = temp->next;
			printf("�� %d ��λ�õ�ֵΪ %s\r\n", i, temp->data);
		} while (temp->next != NULL);
		
	}

}
