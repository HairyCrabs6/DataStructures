#pragma once
// #pragma once ��һ��Ԥ����ָ��
// ������ȷ���ڱ�������и��ļ�ֻ������һ�Ρ�
// ��ͨ�����ڷ�ֹͷ�ļ������ݱ���ΰ���������ܻ�������������ض������⡣

//������
typedef struct TreeNode
{
	int key;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode_t;

//����
TreeNode_t* createNode(void);//�������
TreeNode_t* buildTree(TreeNode_t* treenode, int key_temp);//��������������
void preOrder(TreeNode_t* treenode);//ǰ�����
void inOrder(TreeNode_t* treenode);//�������
void postOrder(TreeNode_t* treenode);//�������
void freeTree(TreeNode_t* treenode);//ɾ������������
TreeNode_t* freeNode(TreeNode_t* treenode, int key_temp);//ɾ������������ĳ�����