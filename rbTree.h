#pragma once
//������ɫ
typedef enum color
{
    RED,
    BLACK
} Color;

//������
typedef struct RBTree
{
    int key;//������
    Color color;//�����ɫ
    struct RBTree* parent;//���ڵ�
    struct RBTree* left;
    struct RBTree* right;
}RBTree_t;

RBTree_t* createNode(int key);//�����½��
RBTree_t* insertRBTree(RBTree_t* treenode, int key);//������������
RBTree_t* insertFixupRB(RBTree_t* treenode);//����������Ľṹ
RBTree_t* deleteNode(RBTree_t* treenode, int key_temp);//�����������������ص㣬ɾ������������ĳ�����
void preOrder(RBTree_t* treenode);//ǰ�������������
void inOrder(RBTree_t* treenode);//��������������