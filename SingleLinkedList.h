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
void Insert_node(void);//������
void Delete_node(void);//ɾ�����
void Search_node(void);//Ѱ�ҽ������λ��
void Print_All_node(void);//������ӡ���н��