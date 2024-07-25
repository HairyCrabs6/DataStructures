#define _CRT_SECURE_NO_WARNINGS 
#include "BinarySearchTree.h"
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
	treenode->key = 0;
	treenode->left = NULL;
	treenode->right = NULL;
	return treenode;
}

//遇见递归问题，先考虑每次递归会干什么，再考虑递归到最后怎么结束，递归必须再此调用本函数
TreeNode_t* buildTree(TreeNode_t* treenode, int key_temp)//构建二叉树,左右
{//key_temp为存储新结点的key值
	if (treenode == NULL)//递归到最后一级的结点，没有左右结点
	{
		treenode = createNode();//创建的新结点
		treenode->key = key_temp;
	}
	else if(key_temp < treenode->key)//比根结点小，归入左
	{
		treenode->left = buildTree(treenode->left, key_temp);
	}
	else//比根结点大或者等于，归入右
	{
		treenode->right = buildTree(treenode->right, key_temp);
	}
	return treenode;
}

//前序遍历，根左右
void preOrder(TreeNode_t* treenode)
{
	if (treenode == NULL)
		return;
	printf("%d ", treenode->key);
	preOrder(treenode->left);
	preOrder(treenode->right);
}

//中序遍历，左根右
void inOrder(TreeNode_t* treenode)
{
	if (treenode == NULL)
		return;
	inOrder(treenode->left);
	printf("%d ", treenode->key);
	inOrder(treenode->right);
}

//后序遍历，左右根
void postOrder(TreeNode_t* treenode)
{
	if (treenode == NULL)
		return;
	postOrder(treenode->left);
	postOrder(treenode->right);
	printf("%d ", treenode->key);
}

void freeTree(TreeNode_t* treenode)//删除二叉树
{
	if (treenode == NULL)
		return;
	freeTree(treenode->left);
	freeTree(treenode->right);
	free(treenode);
}

//寻找右子树的最左结点
TreeNode_t* searchMin(TreeNode_t* treenode)
{
	TreeNode_t* temp = treenode->right;
	TreeNode_t* pre_temp = temp;;//定位到的前一个结点
	//在根节点有左右结点的情况下，不用考虑temp是否为空
	do
	{
		pre_temp = temp;
		temp = temp->left;
	} while (temp->left != NULL);
	return pre_temp;//返回的是最小结点的根节点
}

TreeNode_t* freeNode(TreeNode_t* treenode, int key_temp)//根据搜索二叉树的特点，删除二叉搜索树某个结点
{
	TreeNode_t* pre_temp;//前一个结点
	TreeNode_t* temp;

	if (treenode == NULL)return;
	else if (key_temp < treenode->key)
	{
		treenode->left = freeNode(treenode->left, key_temp);
	}
	else if (key_temp > treenode->key)
	{
		treenode->right = freeNode(treenode->right, key_temp);
	}
	else//相等的情况
	{
		if (treenode->left == NULL)//左结点为空，只有右结点，或者左右结点都为空
		{
			temp = treenode;
			treenode = treenode->right;
			free(temp);
		}
		else if (treenode->right == NULL)//右结点为空，只有左结点
		{
			temp = treenode;
			treenode = treenode->left;
			free(temp);
		}
		else//左右结点都有数据
		{
			//用数值最相近的数据来代替要删除的结点
			//最相近的数据在 结点左边的最大值 或 结点右边的最小值
			//左子树中最右边的节点 没有右结点
			//右子树中最左边的节点 没有左节点
			//这里找右子树的最左结点
			if (treenode->right->left == NULL)
			{//该根结点只有单独的左右子结点
				treenode->key = treenode->right->key;
				free(treenode->right);
				treenode->right = NULL;
				return treenode;
			}
			pre_temp = searchMin(treenode);//这里temp是最小结点的根节点
			treenode->key = pre_temp->left->key;
			temp = pre_temp->left;
			pre_temp->left = pre_temp->left->right;
			free(temp);//没有删除根节点，找了一个数值相近的值带入，把相近的结点删除
			return treenode;
		}
	}
	return treenode;
}