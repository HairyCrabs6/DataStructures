#define _CRT_SECURE_NO_WARNINGS 
#include "BinaryTree.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

TreeNode_t* createNode(void)//�������������
{
	TreeNode_t* treenode = (TreeNode_t*)malloc(sizeof(TreeNode_t));
	if (treenode == NULL)
	{
		printf("�ڴ����ʧ��\r\n");
		exit(EXIT_FAILURE);//�˳�����
	}
	treenode->left = NULL;
	treenode->right = NULL;
	return treenode;
}

//�����ݹ����⣬�ȿ���ÿ�εݹ���ʲô���ٿ��ǵݹ鵽�����ô�������ݹ�����ٴ˵��ñ�����
TreeNode_t* buildTree(void)//����������,����
{
	char data[100] = {0};
	TreeNode_t* treenode = createNode();

	printf("�밴����ʾ��������������ݣ�����NULLΪ�ս��\r\n");
	scanf("%99s", data);
	if (memcmp("NULL", data, strlen("NULL")) == 0)
		return NULL;
	treenode->data = malloc(strlen(data) + 1);
	memcpy(treenode->data, data, strlen(data) + 1);
	treenode->left = buildTree();
	treenode->right = buildTree();
	return treenode;
}

//ǰ�������������
void preOrder(TreeNode_t* treenode)
{
	if (treenode == NULL)
		return;
	printf("%s ", treenode->data);
	preOrder(treenode->left);
	preOrder(treenode->right);
}

//��������������
void inOrder(TreeNode_t* treenode)
{
	if (treenode == NULL)
		return;
	inOrder(treenode->left);
	printf("%s ", treenode->data);
	inOrder(treenode->right);
}

//������������Ҹ�
void postOrder(TreeNode_t* treenode)
{
	if (treenode == NULL)
		return;
	postOrder(treenode->left);
	postOrder(treenode->right);
	printf("%s ", treenode->data);
}

void freeTree(TreeNode_t* treenode)//ɾ��������
{
	if (treenode == NULL)
		return;
	free(treenode->data);
	freeTree(treenode->left);
	freeTree(treenode->right);
	free(treenode);
}