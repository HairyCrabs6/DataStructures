#pragma once
// #pragma once 是一种预处理指令
// 作用是确保在编译过程中该文件只被包含一次。
// 这通常用于防止头文件的内容被多次包含，这可能会引起编译错误或重定义问题。

//定义结点
typedef struct TreeNode
{
	char *data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode_t;

//函数
TreeNode_t* createNode(void);//创建结点
TreeNode_t* buildTree(void);//构建二叉树
void preOrder(TreeNode_t* treenode);//前序遍历
void inOrder(TreeNode_t* treenode);//中序遍历
void postOrder(TreeNode_t* treenode);//后序遍历
void freeTree(TreeNode_t* treenode);//删除二叉树