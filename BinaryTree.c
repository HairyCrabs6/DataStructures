#define _CRT_SECURE_NO_WARNINGS 
#include "BinaryTree.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

TreeNode_t* createNode(void)//创建二叉树结点
{
	TreeNode_t* treenode = (TreeNode_t*)malloc(sizeof(TreeNode_t));
	if (treenode == NULL)
	{
		printf("内存分配失败\r\n");
		exit(EXIT_FAILURE);//退出程序
	}
	treenode->left = NULL;
	treenode->right = NULL;
	return treenode;
}

//遇见递归问题，先考虑每次递归会干什么，再考虑递归到最后怎么结束，递归必须再此调用本函数
TreeNode_t* buildTree(void)//构建二叉树,左右
{
	char data[100] = {0};
	TreeNode_t* treenode = createNode();

	printf("请按照提示输入二叉树的数据，输入NULL为空结点\r\n");
	scanf("%99s", data);
	if (memcmp("NULL", data, strlen("NULL")) == 0)
		return NULL;
	treenode->data = malloc(strlen(data) + 1);
	memcpy(treenode->data, data, strlen(data) + 1);
	treenode->left = buildTree();
	treenode->right = buildTree();
	return treenode;
}

//前序遍历，根左右
void preOrder(TreeNode_t* treenode)
{
	if (treenode == NULL)
		return;
	printf("%s ", treenode->data);
	preOrder(treenode->left);
	preOrder(treenode->right);
}

//中序遍历，左根右
void inOrder(TreeNode_t* treenode)
{
	if (treenode == NULL)
		return;
	inOrder(treenode->left);
	printf("%s ", treenode->data);
	inOrder(treenode->right);
}

//后序遍历，左右根
void postOrder(TreeNode_t* treenode)
{
	if (treenode == NULL)
		return;
	postOrder(treenode->left);
	postOrder(treenode->right);
	printf("%s ", treenode->data);
}

void freeTree(TreeNode_t* treenode)//删除二叉树
{
	if (treenode == NULL)
		return;
	free(treenode->data);
	freeTree(treenode->left);
	freeTree(treenode->right);
	free(treenode);
}