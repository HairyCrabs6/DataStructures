#include <stdio.h>
#include <stdlib.h>
#include "rbTree.h"

RBTree_t* root;//�����
RBTree_t* newRBnode;//�½��

//������������
RBTree_t* createNode(int key)
{
    RBTree_t* treenode = (RBTree_t*)malloc(sizeof(RBTree_t));
    if (treenode == NULL)
    {
        printf("�ڴ����ʧ��\r\n");
        exit(EXIT_FAILURE);//�˳�����
    }
    treenode->key = key;
    treenode->color = RED;
    treenode->parent = NULL;
    treenode->left = NULL;
    treenode->right = NULL;
    return treenode;
}

//������˼��һ������Ӧ�ü����ҷ������õĹ���
static RBTree_t* leftRotate(RBTree_t* node)
{
    RBTree_t* x = node->right;
    RBTree_t* T1 = x->left;

    if (node->parent == NULL)
    {
        x->parent = NULL;//˵��node�Ǹ��ڵ㣬����Ҫ���¹������ڵ���½��Ĺ�ϵ
        root = x;
    }
    else if (node == node->parent->left)
    {
        x->parent = node->parent;
        node->parent->left = x;
    }
    else if (node == node->parent->right)
    {
        x->parent = node->parent;
        node->parent->right = x;
    }

    x->left = node;
    node->right = T1;
    if (node->right)
        node->right->parent = node;
    node->parent = x;

    return x;
}

//����
static RBTree_t* rightRotate(RBTree_t* node)
{
    RBTree_t* x = node->left;
    RBTree_t* T1 = x->right;

    if (node->parent == NULL)
    {
        x->parent = NULL;//˵��node�Ǹ��ڵ㣬����Ҫ���¹������ڵ���½��Ĺ�ϵ
        root = x;//���ֱ�ӽ�root��Ϊ�βδ���������root�ĵ�ַ�����ᱻ�ı䣬�ں�����ֻ�ܸı������Ӧ�����ֵ�����ܸı��ַ
    }
    else if (node == node->parent->left)
    {
        x->parent = node->parent;
        node->parent->left = x;
    }
    else if (node == node->parent->right)
    {
        x->parent = node->parent;
        node->parent->right = x;
    }

    x->right = node;
    node->left = T1;
    if (node->left)
        node->left->parent = node;
    node->parent = x;

    return x;
}

//����������Ľṹ
RBTree_t* insertFixupRB(RBTree_t* treenode)
{
    RBTree_t* uncle;//������

    //��treenode�Ǹ��ڵ����treenode�ĸ��ڵ����ɫΪ��ɫʱ�������в���
    while (treenode->parent != NULL && treenode->parent->color == RED)
    {
        if (treenode->parent->parent == NULL)
        {
            treenode->parent->color = BLACK;
            return treenode;
        }
        else if (treenode->parent->parent->left == treenode->parent)//treebnode�����ӽ��
            uncle = treenode->parent->parent->right;
        else
            uncle = treenode->parent->parent->left;

        //2.XXb�ͣ��������Ǻ�ɫ����Ϊ�սڵ㣬��Ҫ��ת+��ɫ����
        if ((uncle == NULL || uncle->color == BLACK) && uncle == treenode->parent->parent->left)//����������
        {
            //��1��RLb��������ڵ����ҽڵ㣬����ڵ����ҽڵ���������Ϊ��ɫ
            if (treenode == treenode->parent->left)
            {
                //��ת����RRb��
                treenode = treenode->parent;
                rightRotate(treenode);
            }
            //��2��RRb��������ڵ����ҽڵ㣬����ڵ�����ڵ���������Ϊ��ɫ
            treenode->parent->color = BLACK;
            treenode->parent->parent->color = RED;
            treenode = leftRotate(treenode->parent->parent);
        }
        else if ((uncle == NULL || uncle->color == BLACK) && uncle == treenode->parent->parent->right)//�������Һ���
        {
            //��1��LRb��������ڵ�����ڵ㣬����ڵ����ҽڵ���������Ϊ��ɫ
            if (treenode == treenode->parent->right)
            {
                //��ת����LLb��
                treenode = treenode->parent;
                leftRotate(treenode);
            }
            //��2��LLb��������ڵ�����ڵ㣬����ڵ�����ڵ���������Ϊ��ɫ
            treenode->parent->color = BLACK;
            treenode->parent->parent->color = RED;
            treenode = rightRotate(treenode->parent->parent);
        }

        //1.XXr�ͣ��������Ǻ�ɫ��ֻ���ɫ����
        //��1�����ŵ�2�ĺ��棬��Ϊuncle����ʱNULL������ʹ��uncle->color
        else if (uncle->color == RED)
        {
            treenode->parent->color = BLACK;
            uncle->color = BLACK;
            treenode->parent->parent->color = RED;
            treenode = treenode->parent->parent;
        }
        root->color = BLACK;//���ڵ����ɫ����Ϊ��ɫ
    }
    return treenode;
}

//������������
RBTree_t* insertRBTree(RBTree_t* treenode, int key)
{
    //�����㲢��������������
    if (treenode == NULL)
    {
        treenode = createNode(key);
        newRBnode = treenode;
    }
    else if (key >= treenode->key)
    {
        treenode->right = insertRBTree(treenode->right, key);
        treenode->right->parent = treenode;
    }
    else if (key < treenode->key)
    {
        treenode->left = insertRBTree(treenode->left, key);
        treenode->left->parent = treenode;
    }
    return  treenode;
}

//Ѱ����������������
static RBTree_t* searchMin(RBTree_t* treenode)
{
    RBTree_t* temp = treenode->right;
    RBTree_t* pre_temp = temp;;//��λ����ǰһ�����
    //�ڸ��ڵ������ҽ�������£����ÿ���temp�Ƿ�Ϊ��
    do
    {
        pre_temp = temp;
        temp = temp->left;
    } while (temp->left != NULL);
    return pre_temp;//���ص�����С���ĸ��ڵ�
}

//�����ɾ���޸�,��ɾ��������Ǻ�ɫ��㣬�Ͳ����ܽ��������
//nodeΪɾ�����Ľ�����,parentΪnode�ĸ��ڵ�
static RBTree_t* deleteFixupRB(RBTree_t* node, RBTree_t* parent)
{   
    int i = 0;
    RBTree_t* siblingNode;//�ֵܽڵ�
    do
    {
        if (node != NULL)
        {
            parent = node->parent;
            //��1��u��x��y����������ն�����ɾ��ʱ�Ѿ����
            if (node->color == RED)
            {
                node->color = BLACK;
                break;
            }
            //��2��u��x��y�����
            if (node->right == NULL || node->right->color == BLACK);
            else 
            {//node->right == RED�����
                node->right->color = BLACK;
                break;
            }
        }
        //��3��u��x��y���������
        if (parent->right == node)//���Ϊ�Һ���
        {
            siblingNode = parent->left;
            //Rrת��ΪRb
            if (siblingNode->color == RED)
            {
                siblingNode->color = BLACK;
                parent = (rightRotate(parent))->right;
                parent->color = RED;
                siblingNode = parent->left;
                node = parent->right;
            }
            //ɾ��u���ַ�Ϊ�������
            if (siblingNode == NULL || siblingNode->color == BLACK )
            {
                if (siblingNode->left == NULL || siblingNode->left->color == BLACK)
                {//�ֵܽ������ӽ��Ϊ�ջ�Ϊ�ڣ����ӽڵ����
                    //1.Rb0
                    if (siblingNode->right == NULL || siblingNode->right->color == BLACK)//�ֵܽ�㶼Ϊ��ɫ
                    {
                        parent->color = BLACK;
                        siblingNode->color = RED;
                        node = parent;
                        break;
                    }

                    //2.Rb2 ת���� Rb1 �ĵ�һ�����
                    if (siblingNode->right->color == RED)
                    {
                        siblingNode->color = RED;
                        siblingNode->right->color = BLACK;
                        parent->left = leftRotate(siblingNode);
                        siblingNode = parent->left;
                        node = parent->right;
                    }//������Ҫ����Rb1�Ľⷨ����˲���Ҫcontinue
                }
                if (siblingNode->right == NULL || siblingNode->right->color == BLACK)
                {//�ֵܽ������ӽ��Ϊ�ջ�Ϊ�ڣ������ӽڵ㲻Ϊ��
                    //1.Rb1 �ĵ�һ�����
                    if (siblingNode->left->color == RED)
                    {
                        siblingNode->color = parent->color;
                        parent->color = BLACK;
                        siblingNode->left->color = BLACK;
                        node = rightRotate(parent);
                        break;
                    }
                }
                else if (siblingNode->left->color == RED && siblingNode->right->color == RED)
                {
                    //1.Rb1 �ĵڶ������
                    siblingNode->color = parent->color;
                    parent->color = BLACK;
                    siblingNode->left->color = BLACK;
                    node = rightRotate(parent);
                    break;
                }
            }

            if (node->parent != NULL)
                insertFixupRB(node);//��ɾ���Ľ����Ϊ�½������ȥ
        }
        if (parent->left == node)//���Ϊ����
        {
            siblingNode = parent->right;
            //Rrת��ΪRb
            if (siblingNode->color == RED)
            {
                siblingNode->color = BLACK;
                parent->color = RED;
                parent = leftRotate(parent)->left;
                siblingNode = parent->right;
                node = parent->left;
            }
            //ɾ��u���ַ�Ϊ�������
            if (siblingNode->color == BLACK)
            {
                //1.Rb0
                if ((siblingNode->left->color == BLACK && siblingNode->right->color == BLACK) ||
                    (siblingNode->left == NULL) && (siblingNode->right == NULL))//�ֵܽ�㶼Ϊ��ɫ
                {
                    parent->color = BLACK;
                    siblingNode->color = RED;
                    node = parent;
                    break;
                }

                //1.Rb1 �ĵڶ������
                else if (siblingNode->left->color == RED && siblingNode->right->color == RED)
                {
                    siblingNode->color = parent->color;
                    parent->color = BLACK;
                    siblingNode->right->color = BLACK;
                    node = leftRotate(parent);
                    break;
                }

                //2.Rb2 ת���� Rb1 �ĵ�һ�����
                if (siblingNode->right->color == RED && siblingNode->right->color == BLACK)
                {
                    siblingNode->color = RED;
                    siblingNode->right->color = BLACK;
                    parent->left = leftRotate(siblingNode);
                    siblingNode = parent->left;
                    node = parent->right;
                }//������Ҫ����Rb1�Ľⷨ����˲���Ҫcontinue

                //Rb1 �ĵ�һ�����
                if (siblingNode->right->color == RED && (siblingNode->left->color == BLACK || siblingNode->left == NULL))
                {
                    siblingNode->color = parent->color;
                    parent->color = BLACK;
                    siblingNode->right->color = BLACK;
                    node = leftRotate(siblingNode);
                }
            }
        }
    } while(i != 0);//��ѭ��ֻ����һ�Σ�ʹ��ѭ����Ϊ��if������ת��ѭ������
    return root;
}

RBTree_t* deleteNode(RBTree_t* treenode, int key_temp)//�����������������ص㣬ɾ������������ĳ�����
{
    RBTree_t* pre_temp = NULL;//ǰһ�����
    RBTree_t* temp = NULL;//ǰһ�����
    int temp_color = -1;//��Ҫɾ���Ľ��

    if (treenode == NULL)return NULL;
    while (key_temp != treenode->key)
    {
        if (key_temp < treenode->key)
        {
            treenode = treenode->left;
        }
        else if (key_temp > treenode->key)

        {
            treenode = treenode->right;
        }
        if (treenode == NULL)
        {
            printf("�Ҳ���������\r\n");
            return NULL;
        }

    }

    //��ȵ����
    if (treenode->left == NULL && treenode->right == NULL)
    {
        pre_temp = treenode->parent;
        temp = treenode;
        temp_color = treenode->color;

        if (treenode->parent == NULL);
        else if (treenode == treenode->parent->right)
            treenode->parent->right = NULL;
        else
            treenode->parent->left = NULL;

        treenode = NULL;//������Ϊ��
    }
    else if (treenode->left == NULL)//����Ϊ�գ�ֻ���ҽ�㣬�������ҽ�㶼Ϊ��
    {
        pre_temp = treenode->parent;
        temp = treenode;
        temp_color = treenode->color;

        if (treenode->parent == NULL);
        else if (treenode == treenode->parent->right)
            treenode->parent->right = treenode->right;
        else
            treenode->parent->left = treenode->right;

        treenode->right->parent = treenode->parent;
        if (treenode == root)
        {//����ɾ�����Ǹ��ڵ�
            root = treenode->right;
        }
        treenode = treenode->right;
    }
    else if (treenode->right == NULL)//�ҽ��Ϊ�գ�ֻ������
    {
        temp_color = treenode->color;
        pre_temp = treenode->parent;
        temp = treenode;

        if (treenode->parent == NULL);
        else if (treenode == treenode->parent->right)
            treenode->parent->right = treenode->left;
        else
            treenode->parent->left = treenode->left;

        treenode->left->parent = treenode->parent;
        if (treenode == root)
        {//����ɾ�����Ǹ��ڵ�
            root = treenode->left;
        }
        treenode = treenode->left;
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
            temp_color = treenode->color;
            pre_temp = treenode->parent;
            temp = treenode;

            if (treenode->parent == NULL);
            else if (treenode == treenode->parent->right)
                treenode->parent->right = treenode->right;
            else
                treenode->parent->left = treenode->right;

            treenode->right->parent = treenode->parent;
            treenode->right->left = treenode->left;
            treenode = treenode->right;
            treenode->left->parent = treenode;

            if (temp_color == RED)//����ɾ����ɫ������������
            {
                treenode->color = RED;
                if (treenode->right)
                    treenode->right->color = BLACK;
            }
        }
        else
        {
            pre_temp = searchMin(treenode);//����temp����С���ĸ��ڵ�
            treenode->key = pre_temp->left->key;
            //treenode->color = pre_temp->left->color;
            temp_color = pre_temp->left->color;//����Խ����������ɫ�жϣ���ɫ�Ϳ�ʼ�޸�
            temp = pre_temp->left;
            pre_temp->left = pre_temp->left->right;
        }
        if (treenode->parent == NULL)//���ɾ�����ڵ�ʱ�Ĵ���û�м�ʱ���¸��ڵ�
            root = treenode;
    }

    if (temp_color == BLACK)//ɾ���Ľ��Ϊ��ɫ
    {
        deleteFixupRB(treenode, pre_temp);//treenodeΪɾ�����Ľ�����,pre_tempҲ�ǽ���ڵ�ĸ��ڵ�
    }
    if (temp != NULL)
    {
        free(temp);
        temp = NULL;
    }
    return root;
}


//ǰ�������������
void preOrder(RBTree_t* treenode)
{
    if (treenode == NULL)
        return;
    printf("%d ", treenode->key);
    (treenode->color == RED) ? printf("RED\r\n") : printf("BLACK\r\n");
    preOrder(treenode->left);
    preOrder(treenode->right);
}

//��������������
void inOrder(RBTree_t* treenode)
{
    if (treenode == NULL)
        return;
    inOrder(treenode->left);
    printf("%d ", treenode->key);
    inOrder(treenode->right);
}