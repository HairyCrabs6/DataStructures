#pragma once
// #pragma once ��һ��Ԥ����ָ��
// ������ȷ���ڱ�������и��ļ�ֻ������һ�Ρ�
// ��ͨ�����ڷ�ֹͷ�ļ������ݱ���ΰ���������ܻ�������������ض������⡣

//��������
typedef struct Node
{
	char *data;
	struct Node* pre;
	struct Node* next;
}Node_t;

//����
void Insert_node(void);//������
void Delete_node(void);//ɾ�����
void Search_node(void);//Ѱ�ҽ������λ��
void PositivePrint_All_Node(void);//���������ӡ���н��
void ReversePrint_All_Node(void);//���������ӡ���н��