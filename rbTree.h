#pragma once
//定义颜色
typedef enum color
{
    RED,
    BLACK
} Color;

//定义结点
typedef struct RBTree
{
    int key;//数据域
    Color color;//结点颜色
    struct RBTree* parent;//父节点
    struct RBTree* left;
    struct RBTree* right;
}RBTree_t;

RBTree_t* createNode(int key);//创建新结点
RBTree_t* insertRBTree(RBTree_t* treenode, int key);//建立插入红黑树
RBTree_t* insertFixupRB(RBTree_t* treenode);//调整红黑树的结构
RBTree_t* deleteNode(RBTree_t* treenode, int key_temp);//根据搜索二叉树的特点，删除二叉搜索树某个结点
void preOrder(RBTree_t* treenode);//前序遍历，根左右
void inOrder(RBTree_t* treenode);//中序遍历，左根右