#pragma once
// #pragma once ��һ��Ԥ����ָ��
// ������ȷ���ڱ�������и��ļ�ֻ������һ�Ρ�
// ��ͨ�����ڷ�ֹͷ�ļ������ݱ���ΰ���������ܻ�������������ض������⡣

//������
typedef struct TreeNode
{
	int key;//������
	int height;//�������߶�
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode_t;

//����
TreeNode_t* createNode(void);//�������
TreeNode_t* buildTree(TreeNode_t* treenode, int key_temp);//��������������
int height(TreeNode_t* node);//��nodeΪ���ڵ������߶�
int getBalance(TreeNode_t* node);//����ƽ������
TreeNode_t* leftRotate(TreeNode_t* node);//����
TreeNode_t* rightRotate(TreeNode_t* node);//����
void preOrder(TreeNode_t* treenode);//ǰ�����
void inOrder(TreeNode_t* treenode);//�������
void postOrder(TreeNode_t* treenode);//�������
void freeAllTree(TreeNode_t* treenode);//ɾ������������
TreeNode_t* freeNode(TreeNode_t* treenode, int key_temp);//ɾ������������ĳ�����