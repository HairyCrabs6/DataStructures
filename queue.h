#pragma once
// #pragma once ��һ��Ԥ����ָ��
// ������ȷ���ڱ�������и��ļ�ֻ������һ�Ρ�
// ��ͨ�����ڷ�ֹͷ�ļ������ݱ���ΰ���������ܻ�������������ض������⡣

//��������
typedef struct Node
{
	char *data;
	struct Node* next;
}Node_t;

//����
void queue_push(void);//���
void queue_pop(void);//����
void Search_node(void);//Ѱ�ҽ������λ��
void Print_All_Node(void);//������ӡ���н��