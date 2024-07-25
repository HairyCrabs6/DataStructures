#define _CRT_SECURE_NO_WARNINGS 
#include "BinarySearchTree.h"
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
	treenode->key = 0;
	treenode->left = NULL;
	treenode->right = NULL;
	return treenode;
}

//�����ݹ����⣬�ȿ���ÿ�εݹ���ʲô���ٿ��ǵݹ鵽�����ô�������ݹ�����ٴ˵��ñ�����
TreeNode_t* buildTree(TreeNode_t* treenode, int key_temp)//����������,����
{//key_tempΪ�洢�½���keyֵ
	if (treenode == NULL)//�ݹ鵽���һ���Ľ�㣬û�����ҽ��
	{
		treenode = createNode();//�������½��
		treenode->key = key_temp;
	}
	else if(key_temp < treenode->key)//�ȸ����С��������
	{
		treenode->left = buildTree(treenode->left, key_temp);
	}
	else//�ȸ�������ߵ��ڣ�������
	{
		treenode->right = buildTree(treenode->right, key_temp);
	}
	return treenode;
}

//ǰ�������������
void preOrder(TreeNode_t* treenode)
{
	if (treenode == NULL)
		return;
	printf("%d ", treenode->key);
	preOrder(treenode->left);
	preOrder(treenode->right);
}

//��������������
void inOrder(TreeNode_t* treenode)
{
	if (treenode == NULL)
		return;
	inOrder(treenode->left);
	printf("%d ", treenode->key);
	inOrder(treenode->right);
}

//������������Ҹ�
void postOrder(TreeNode_t* treenode)
{
	if (treenode == NULL)
		return;
	postOrder(treenode->left);
	postOrder(treenode->right);
	printf("%d ", treenode->key);
}

void freeTree(TreeNode_t* treenode)//ɾ��������
{
	if (treenode == NULL)
		return;
	freeTree(treenode->left);
	freeTree(treenode->right);
	free(treenode);
}

//Ѱ����������������
TreeNode_t* searchMin(TreeNode_t* treenode)
{
	TreeNode_t* temp = treenode->right;
	TreeNode_t* pre_temp = temp;;//��λ����ǰһ�����
	//�ڸ��ڵ������ҽ�������£����ÿ���temp�Ƿ�Ϊ��
	do
	{
		pre_temp = temp;
		temp = temp->left;
	} while (temp->left != NULL);
	return pre_temp;//���ص�����С���ĸ��ڵ�
}

TreeNode_t* freeNode(TreeNode_t* treenode, int key_temp)//�����������������ص㣬ɾ������������ĳ�����
{
	TreeNode_t* pre_temp;//ǰһ�����
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
	else//��ȵ����
	{
		if (treenode->left == NULL)//����Ϊ�գ�ֻ���ҽ�㣬�������ҽ�㶼Ϊ��
		{
			temp = treenode;
			treenode = treenode->right;
			free(temp);
		}
		else if (treenode->right == NULL)//�ҽ��Ϊ�գ�ֻ������
		{
			temp = treenode;
			treenode = treenode->left;
			free(temp);
		}
		else//���ҽ�㶼������
		{
			//����ֵ�����������������Ҫɾ���Ľ��
			//������������� �����ߵ����ֵ �� ����ұߵ���Сֵ
			//�����������ұߵĽڵ� û���ҽ��
			//������������ߵĽڵ� û����ڵ�
			//��������������������
			if (treenode->right->left == NULL)
			{//�ø����ֻ�е����������ӽ��
				treenode->key = treenode->right->key;
				free(treenode->right);
				treenode->right = NULL;
				return treenode;
			}
			pre_temp = searchMin(treenode);//����temp����С���ĸ��ڵ�
			treenode->key = pre_temp->left->key;
			temp = pre_temp->left;
			pre_temp->left = pre_temp->left->right;
			free(temp);//û��ɾ�����ڵ㣬����һ����ֵ�����ֵ���룬������Ľ��ɾ��
			return treenode;
		}
	}
	return treenode;
}