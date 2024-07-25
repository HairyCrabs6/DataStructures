#define _CRT_SECURE_NO_WARNINGS 
#include "stack.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

Node_t* head;
int NodeNum = 0;

//��ջ
void stack_push(void)
{
	int num = 0;
	char data[100] = {0};
	
	Node_t* node;//Ҫ����Ľ��
	node = (Node_t*)malloc(sizeof(Node_t));
			
	printf("��������ջ��������,���99�ַ�\r\n");
	scanf("%99s", data);//ʹ�� scanf ���ַ�������ʽ��ȡ�û����룬��������ȡ99���ַ��Ա������
	node->data = (char*)malloc((strlen(data) + 1) * sizeof(char));
	if (node->data == NULL) {
		// �����ڴ����ʧ�ܵ����
		printf("�ڴ����ʧ��\r\n");
		return;
	}
	node->next = NULL;
	strcpy(node->data, data);

	//������ջ�Ľ����Ϊͷ���
	node->next = head;
	head = node;
	NodeNum++;
	printf("�ɹ���ջ\r\n");
}

void stack_pop(void)//��ջ
{
	int num = 0;
	char* data;
	Node_t* temp;//��ת�Ľ��
	Node_t* prem;//��λ��ǰһ�����

	temp = head;
	free(temp->data);
	head = temp->next;
	free(temp);
	NodeNum--;
	printf("�ɹ���ջ\r\n");
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
		printf("�������� ջ�� λ��\r\n");
	}
	else//�������
	{
		temp = head;
		for (int i = 1; i < NodeNum; i++)
		{
			temp = temp->next;
			if (strcmp(temp->data, data) == 0)
			{
				printf("�������ڵ� %d ����λ�ã�0��1��2...��˳��0Ϊջ��\r\n", i);
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
