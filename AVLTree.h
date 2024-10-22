#pragma once
// #pragma once 是一种预处理指令
// 作用是确保在编译过程中该文件只被包含一次。
// 这通常用于防止头文件的内容被多次包含，这可能会引起编译错误或重定义问题。

//定义结点
typedef struct TreeNode
{
	int key;//数据域
	int height;//该子树高度
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode_t;

//函数
TreeNode_t* createNode(void);//创建结点
TreeNode_t* buildTree(TreeNode_t* treenode, int key_temp);//构建二叉搜索树
int height(TreeNode_t* node);//以node为根节点求树高度
int getBalance(TreeNode_t* node);//计算平衡因子
TreeNode_t* leftRotate(TreeNode_t* node);//左旋
TreeNode_t* rightRotate(TreeNode_t* node);//右旋
void preOrder(TreeNode_t* treenode);//前序遍历
void inOrder(TreeNode_t* treenode);//中序遍历
void postOrder(TreeNode_t* treenode);//后序遍历
void freeAllTree(TreeNode_t* treenode);//删除整个二叉树
TreeNode_t* freeNode(TreeNode_t* treenode, int key_temp);//删除二叉搜索树某个结点