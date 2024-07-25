#pragma once
// #pragma once ��һ��Ԥ����ָ��
// ������ȷ���ڱ�������и��ļ�ֻ������һ�Ρ�
// ��ͨ�����ڷ�ֹͷ�ļ������ݱ���ΰ���������ܻ�������������ض������⡣

//������
typedef struct TreeNode
{
	char *data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode_t;

//����
TreeNode_t* createNode(void);//�������
TreeNode_t* buildTree(void);//����������
void preOrder(TreeNode_t* treenode);//ǰ�����
void inOrder(TreeNode_t* treenode);//�������
void postOrder(TreeNode_t* treenode);//�������
void freeTree(TreeNode_t* treenode);//ɾ��������