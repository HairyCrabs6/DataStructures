#define _CRT_SECURE_NO_WARNINGS 
#include "AVLTree.h"
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
	treenode->height = 1;
	treenode->left = NULL;
	treenode->right = NULL;
	return treenode;
}

//��nodeΪ���ڵ������߶�
int height(TreeNode_t* node)
{
	if (node == NULL)
		return 0;
	return node->height;
}

//����ƽ������
int getBalance(TreeNode_t* node)
{
	if (node == NULL)
		return 0;
	return height(node->left) - height(node->right);
}

//����
TreeNode_t* leftRotate(TreeNode_t* node)
{
	TreeNode_t* x = node->right;
	TreeNode_t* T1 = x->left;

	x->left = node;
	node->right = T1;

	//���¸߶�
	node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));//�ǵ���1���������
	x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

	return x;
}

//����
TreeNode_t* rightRotate(TreeNode_t* node)
{
	TreeNode_t* x = node->left;
	TreeNode_t* T1 = x->right;

	x->right = node;
	node->left = T1;

	//���¸߶�
	node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
	x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

	return x;
}

//�����ݹ����⣬�ȿ���ÿ�εݹ���ʲô���ٿ��ǵݹ鵽�����ô�������ݹ�����ٴ˵��ñ�����
TreeNode_t* buildTree(TreeNode_t* treenode, int key_temp)//����������,����
{
	int balance;//ƽ������
	//key_tempΪ�洢�½���keyֵ
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

	//���¸߶�
	treenode->height = 1 + (height(treenode->left) > height(treenode->right) ? height(treenode->left) : height(treenode->right));

	//����ƽ������
	balance = getBalance(treenode);

	//����ƽ�����ӽ��е���
	//��1��LL�� 
	if (balance > 1 && getBalance(treenode->left) > 0)
		treenode = rightRotate(treenode);
	//��2��LR�� 
	else if (balance > 1 && getBalance(treenode->left) < 0)
	{
		treenode->left = leftRotate(treenode->left);//���������LL��
		treenode = rightRotate(treenode);
	}
	//��3��RR�� 
	else if (balance < -1 && getBalance(treenode->right) < 0)
		treenode = leftRotate(treenode);
	//��4��RL�� 
	else if (balance < -1 && getBalance(treenode->right) > 0)
	{
		treenode->right = rightRotate(treenode->right);//���������RR��
		treenode = leftRotate(treenode);
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

void freeAllTree(TreeNode_t* treenode)//ɾ������������
{
	if (treenode == NULL)
		return;
	freeAllTree(treenode->left);
	freeAllTree(treenode->right);
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

//������Ҫɾ���Ľ�㵽�滻��������
TreeNode_t* UpdateMinHeight(TreeNode_t* temp)//����������ݵ���treenode->right
{
	if (temp == NULL)return temp;
	temp->left = UpdateMinHeight(temp->left);
	//���¸߶�
	temp->height = 1 + (height(temp->left) > height(temp->right) ? height(temp->left) : height(temp->right));
	return temp;
}

TreeNode_t* freeNode(TreeNode_t* treenode, int key_temp)//�����������������ص㣬ɾ������������ĳ�����
{
	TreeNode_t* pre_temp;//ǰһ�����
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
	else//��ȵ����
	{
		if (treenode->left == NULL)//����Ϊ�գ�ֻ���ҽ�㣬�������ҽ�㶼Ϊ��
		{
			temp = treenode;
			treenode = treenode->right;
			if(treenode != NULL)
				treenode->height = 1 + (height(treenode->left) > height(treenode->right) ? height(treenode->left) : height(treenode->right));
			free(temp);
		}
		else if (treenode->right == NULL)//�ҽ��Ϊ�գ�ֻ������
		{
			temp = treenode;
			treenode = treenode->left;
			if (treenode != NULL)
				treenode->height = 1 + (height(treenode->left) > height(treenode->right) ? height(treenode->left) : height(treenode->right)); 
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
				temp = treenode->right->right;
				free(treenode->right);
				treenode->right = temp;
			}
			else
			{
				pre_temp = searchMin(treenode);//����temp����С���ĸ��ڵ�
				treenode->key = pre_temp->left->key;
				temp = pre_temp->left;
				pre_temp->left = pre_temp->left->right;
				free(temp);//û��ɾ�����ڵ㣬����һ����ֵ�����ֵ���룬������Ľ��ɾ��
				treenode->right = UpdateMinHeight(treenode->right);//��������
				treenode->height = 1 + (height(treenode->left) > height(treenode->right) ? height(treenode->left) : height(treenode->right));
			}
		}
	}

	// ���ƽ�����Ӳ�������Ӧ����ת����
	int balance = getBalance(treenode);
	if (balance > 1 && getBalance(treenode->left) > 0) 
	{
		return rightRotate(treenode);//����֮��߶Ȳ���
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