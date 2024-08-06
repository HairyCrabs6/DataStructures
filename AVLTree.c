#define _CRT_SECURE_NO_WARNINGS 
#include "AVLTree.h"
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
	treenode->height = 1;
	treenode->left = NULL;
	treenode->right = NULL;
	return treenode;
}

//以node为根节点求树高度
int height(TreeNode_t* node)
{
	if (node == NULL)
		return 0;
	return node->height;
}

//计算平衡因子
int getBalance(TreeNode_t* node)
{
	if (node == NULL)
		return 0;
	return height(node->left) - height(node->right);
}

//左旋
TreeNode_t* leftRotate(TreeNode_t* node)
{
	TreeNode_t* x = node->right;
	TreeNode_t* T1 = x->left;

	x->left = node;
	node->right = T1;

	//更新高度
	node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));//记得在1后面加括号
	x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

	return x;
}

//右旋
TreeNode_t* rightRotate(TreeNode_t* node)
{
	TreeNode_t* x = node->left;
	TreeNode_t* T1 = x->right;

	x->right = node;
	node->left = T1;

	//更新高度
	node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
	x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

	return x;
}

//遇见递归问题，先考虑每次递归会干什么，再考虑递归到最后怎么结束，递归必须再此调用本函数
TreeNode_t* buildTree(TreeNode_t* treenode, int key_temp)//构建二叉树,左右
{
	int balance;//平衡因子
	//key_temp为存储新结点的key值
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

	//更新高度
	treenode->height = 1 + (height(treenode->left) > height(treenode->right) ? height(treenode->left) : height(treenode->right));

	//计算平衡因子
	balance = getBalance(treenode);

	//根据平衡因子进行调整
	//（1）LL型 
	if (balance > 1 && getBalance(treenode->left) > 0)
		treenode = rightRotate(treenode);
	//（2）LR型 
	else if (balance > 1 && getBalance(treenode->left) < 0)
	{
		treenode->left = leftRotate(treenode->left);//先左旋变成LL型
		treenode = rightRotate(treenode);
	}
	//（3）RR型 
	else if (balance < -1 && getBalance(treenode->right) < 0)
		treenode = leftRotate(treenode);
	//（4）RL型 
	else if (balance < -1 && getBalance(treenode->right) > 0)
	{
		treenode->right = rightRotate(treenode->right);//先右旋变成RR型
		treenode = leftRotate(treenode);
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

void freeAllTree(TreeNode_t* treenode)//删除整个二叉树
{
	if (treenode == NULL)
		return;
	freeAllTree(treenode->left);
	freeAllTree(treenode->right);
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

//更新需要删除的结点到替换结点的树高
TreeNode_t* UpdateMinHeight(TreeNode_t* temp)//这里参数传递的是treenode->right
{
	if (temp == NULL)return temp;
	temp->left = UpdateMinHeight(temp->left);
	//更新高度
	temp->height = 1 + (height(temp->left) > height(temp->right) ? height(temp->left) : height(temp->right));
	return temp;
}

TreeNode_t* freeNode(TreeNode_t* treenode, int key_temp)//根据搜索二叉树的特点，删除二叉搜索树某个结点
{
	TreeNode_t* pre_temp;//前一个结点
	TreeNode_t* temp;

	if (treenode == NULL)return;
	else if (key_temp < treenode->key)
	{
		treenode->left = freeNode(treenode->left, key_temp);
		treenode->height = 1 + (height(treenode->left) > height(treenode->right) ? height(treenode->left) : height(treenode->right));
	}
	else if (key_temp > treenode->key)
	{
		treenode->right = freeNode(treenode->right, key_temp);
		treenode->height = 1 + (height(treenode->left) > height(treenode->right) ? height(treenode->left) : height(treenode->right));
	}
	else//相等的情况
	{
		if (treenode->left == NULL)//左结点为空，只有右结点，或者左右结点都为空
		{
			temp = treenode;
			treenode = treenode->right;
			if(treenode != NULL)
				treenode->height = 1 + (height(treenode->left) > height(treenode->right) ? height(treenode->left) : height(treenode->right));
			free(temp);
		}
		else if (treenode->right == NULL)//右结点为空，只有左结点
		{
			temp = treenode;
			treenode = treenode->left;
			if (treenode != NULL)
				treenode->height = 1 + (height(treenode->left) > height(treenode->right) ? height(treenode->left) : height(treenode->right)); 
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
				temp = treenode->right->right;
				free(treenode->right);
				treenode->right = temp;
			}
			else
			{
				pre_temp = searchMin(treenode);//这里temp是最小结点的根节点
				treenode->key = pre_temp->left->key;
				temp = pre_temp->left;
				pre_temp->left = pre_temp->left->right;
				free(temp);//没有删除根节点，找了一个数值相近的值带入，把相近的结点删除
				treenode->right = UpdateMinHeight(treenode->right);//更新树高
				treenode->height = 1 + (height(treenode->left) > height(treenode->right) ? height(treenode->left) : height(treenode->right));
			}
		}
	}

	// 检查平衡因子并进行相应的旋转操作
	int balance = getBalance(treenode);
	if (balance > 1 && getBalance(treenode->left) > 0) 
	{
		return rightRotate(treenode);//右旋之后高度不对
	}
	if (balance < -1 && getBalance(treenode->right) < 0) 
	{
		return leftRotate(treenode);
	}
	if (balance > 1 && getBalance(treenode->left) < 0) 
	{
		treenode->left = leftRotate(treenode->left);
		return rightRotate(treenode);
	}
	if (balance < -1 && getBalance(treenode->right) > 0) 
	{
		treenode->right = rightRotate(treenode->right);
		return leftRotate(treenode);
	}

	return treenode;
}