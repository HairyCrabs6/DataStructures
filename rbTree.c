#include <stdio.h>
#include <stdlib.h>
#include "rbTree.h"

RBTree_t* root;//根结点
RBTree_t* newRBnode;//新结点

//创建红黑树结点
RBTree_t* createNode(int key)
{
    RBTree_t* treenode = (RBTree_t*)malloc(sizeof(RBTree_t));
    if (treenode == NULL)
    {
        printf("内存分配失败\r\n");
        exit(EXIT_FAILURE);//退出程序
    }
    treenode->key = key;
    treenode->color = RED;
    treenode->parent = NULL;
    treenode->left = NULL;
    treenode->right = NULL;
    return treenode;
}

//左旋，思考一个函数应该集成且反复利用的功能
static RBTree_t* leftRotate(RBTree_t* node)
{
    RBTree_t* x = node->right;
    RBTree_t* T1 = x->left;

    if (node->parent == NULL)
    {
        x->parent = NULL;//说明node是根节点，不需要重新构建父节点和新结点的关系
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

//右旋
static RBTree_t* rightRotate(RBTree_t* node)
{
    RBTree_t* x = node->left;
    RBTree_t* T1 = x->right;

    if (node->parent == NULL)
    {
        x->parent = NULL;//说明node是根节点，不需要重新构建父节点和新结点的关系
        root = x;//如果直接将root作为形参传进函数，root的地址并不会被改变，在函数中只能改变变量对应区域的值，不能改变地址
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

//调整红黑树的结构
RBTree_t* insertFixupRB(RBTree_t* treenode)
{
    RBTree_t* uncle;//叔叔结点

    //当treenode是根节点或者treenode的父节点的颜色为黑色时，不进行操作
    while (treenode->parent != NULL && treenode->parent->color == RED)
    {
        if (treenode->parent->parent == NULL)
        {
            treenode->parent->color = BLACK;
            return treenode;
        }
        else if (treenode->parent->parent->left == treenode->parent)//treebnode是左子结点
            uncle = treenode->parent->parent->right;
        else
            uncle = treenode->parent->parent->left;

        //2.XXb型，叔叔结点是黑色，即为空节点，需要旋转+变色操作
        if ((uncle == NULL || uncle->color == BLACK) && uncle == treenode->parent->parent->left)//叔叔是左孩子
        {
            //（1）RLb情况，父节点是右节点，插入节点是右节点且叔叔结点为黑色
            if (treenode == treenode->parent->left)
            {
                //先转化成RRb型
                treenode = treenode->parent;
                rightRotate(treenode);
            }
            //（2）RRb情况，父节点是右节点，插入节点是左节点且叔叔结点为黑色
            treenode->parent->color = BLACK;
            treenode->parent->parent->color = RED;
            treenode = leftRotate(treenode->parent->parent);
        }
        else if ((uncle == NULL || uncle->color == BLACK) && uncle == treenode->parent->parent->right)//叔叔是右孩子
        {
            //（1）LRb情况，父节点是左节点，插入节点是右节点且叔叔结点为黑色
            if (treenode == treenode->parent->right)
            {
                //先转化成LLb型
                treenode = treenode->parent;
                leftRotate(treenode);
            }
            //（2）LLb情况，父节点是左节点，插入节点是左节点且叔叔结点为黑色
            treenode->parent->color = BLACK;
            treenode->parent->parent->color = RED;
            treenode = rightRotate(treenode->parent->parent);
        }

        //1.XXr型，叔叔结点是红色，只需变色操作
        //将1操作放到2的后面，因为uncle可能时NULL，不能使用uncle->color
        else if (uncle->color == RED)
        {
            treenode->parent->color = BLACK;
            uncle->color = BLACK;
            treenode->parent->parent->color = RED;
            treenode = treenode->parent->parent;
        }
        root->color = BLACK;//根节点的颜色必须为黑色
    }
    return treenode;
}

//建立插入红黑树
RBTree_t* insertRBTree(RBTree_t* treenode, int key)
{
    //插入结点并建立二叉搜索树
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

//寻找右子树的最左结点
static RBTree_t* searchMin(RBTree_t* treenode)
{
    RBTree_t* temp = treenode->right;
    RBTree_t* pre_temp = temp;;//定位到的前一个结点
    //在根节点有左右结点的情况下，不用考虑temp是否为空
    do
    {
        pre_temp = temp;
        temp = temp->left;
    } while (temp->left != NULL);
    return pre_temp;//返回的是最小结点的根节点
}

//红黑树删除修复,被删除的如果是红色结点，就不可能进这个函数
//node为删除结点的接替结点,parent为node的父节点
static RBTree_t* deleteFixupRB(RBTree_t* node, RBTree_t* parent)
{   
    int i = 0;
    RBTree_t* siblingNode;//兄弟节点
    do
    {
        if (node != NULL)
        {
            parent = node->parent;
            //（1）u黑x红y黑情况，按照二叉树删除时已经完成
            if (node->color == RED)
            {
                node->color = BLACK;
                break;
            }
            //（2）u黑x黑y红情况
            if (node->right == NULL || node->right->color == BLACK);
            else 
            {//node->right == RED的情况
                node->right->color = BLACK;
                break;
            }
        }
        //（3）u黑x黑y黑四种情况
        if (parent->right == node)//结点为右孩子
        {
            siblingNode = parent->left;
            //Rr转化为Rb
            if (siblingNode->color == RED)
            {
                siblingNode->color = BLACK;
                parent = (rightRotate(parent))->right;
                parent->color = RED;
                siblingNode = parent->left;
                node = parent->right;
            }
            //删除u后又分为三种情况
            if (siblingNode == NULL || siblingNode->color == BLACK )
            {
                if (siblingNode->left == NULL || siblingNode->left->color == BLACK)
                {//兄弟结点的左子结点为空或为黑，右子节点随便
                    //1.Rb0
                    if (siblingNode->right == NULL || siblingNode->right->color == BLACK)//兄弟结点都为黑色
                    {
                        parent->color = BLACK;
                        siblingNode->color = RED;
                        node = parent;
                        break;
                    }

                    //2.Rb2 转换成 Rb1 的第一种情况
                    if (siblingNode->right->color == RED)
                    {
                        siblingNode->color = RED;
                        siblingNode->right->color = BLACK;
                        parent->left = leftRotate(siblingNode);
                        siblingNode = parent->left;
                        node = parent->right;
                    }//这里需要下面Rb1的解法，因此不需要continue
                }
                if (siblingNode->right == NULL || siblingNode->right->color == BLACK)
                {//兄弟结点的右子结点为空或为黑，但左子节点不为空
                    //1.Rb1 的第一种情况
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
                    //1.Rb1 的第二种情况
                    siblingNode->color = parent->color;
                    parent->color = BLACK;
                    siblingNode->left->color = BLACK;
                    node = rightRotate(parent);
                    break;
                }
            }

            if (node->parent != NULL)
                insertFixupRB(node);//将删除的结点作为新结点插入进去
        }
        if (parent->left == node)//结点为左孩子
        {
            siblingNode = parent->right;
            //Rr转化为Rb
            if (siblingNode->color == RED)
            {
                siblingNode->color = BLACK;
                parent->color = RED;
                parent = leftRotate(parent)->left;
                siblingNode = parent->right;
                node = parent->left;
            }
            //删除u后又分为三种情况
            if (siblingNode->color == BLACK)
            {
                //1.Rb0
                if ((siblingNode->left->color == BLACK && siblingNode->right->color == BLACK) ||
                    (siblingNode->left == NULL) && (siblingNode->right == NULL))//兄弟结点都为黑色
                {
                    parent->color = BLACK;
                    siblingNode->color = RED;
                    node = parent;
                    break;
                }

                //1.Rb1 的第二种情况
                else if (siblingNode->left->color == RED && siblingNode->right->color == RED)
                {
                    siblingNode->color = parent->color;
                    parent->color = BLACK;
                    siblingNode->right->color = BLACK;
                    node = leftRotate(parent);
                    break;
                }

                //2.Rb2 转换成 Rb1 的第一种情况
                if (siblingNode->right->color == RED && siblingNode->right->color == BLACK)
                {
                    siblingNode->color = RED;
                    siblingNode->right->color = BLACK;
                    parent->left = leftRotate(siblingNode);
                    siblingNode = parent->left;
                    node = parent->right;
                }//这里需要下面Rb1的解法，因此不需要continue

                //Rb1 的第一种情况
                if (siblingNode->right->color == RED && (siblingNode->left->color == BLACK || siblingNode->left == NULL))
                {
                    siblingNode->color = parent->color;
                    parent->color = BLACK;
                    siblingNode->right->color = BLACK;
                    node = leftRotate(siblingNode);
                }
            }
        }
    } while(i != 0);//此循环只进行一次，使用循环是为了if语句的跳转至循环结束
    return root;
}

RBTree_t* deleteNode(RBTree_t* treenode, int key_temp)//根据搜索二叉树的特点，删除二叉搜索树某个结点
{
    RBTree_t* pre_temp = NULL;//前一个结点
    RBTree_t* temp = NULL;//前一个结点
    int temp_color = -1;//需要删除的结点

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
            printf("找不到该数据\r\n");
            return NULL;
        }

    }

    //相等的情况
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

        treenode = NULL;//替代结点为空
    }
    else if (treenode->left == NULL)//左结点为空，只有右结点，或者左右结点都为空
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
        {//考虑删除的是根节点
            root = treenode->right;
        }
        treenode = treenode->right;
    }
    else if (treenode->right == NULL)//右结点为空，只有左结点
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
        {//考虑删除的是根节点
            root = treenode->left;
        }
        treenode = treenode->left;
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

            if (temp_color == RED)//处理删除红色结点的特殊问题
            {
                treenode->color = RED;
                if (treenode->right)
                    treenode->right->color = BLACK;
            }
        }
        else
        {
            pre_temp = searchMin(treenode);//这里temp是最小结点的根节点
            treenode->key = pre_temp->left->key;
            //treenode->color = pre_temp->left->color;
            temp_color = pre_temp->left->color;//这里对接替结点进行颜色判断，黑色就开始修复
            temp = pre_temp->left;
            pre_temp->left = pre_temp->left->right;
        }
        if (treenode->parent == NULL)//解决删除根节点时的错误，没有及时更新根节点
            root = treenode;
    }

    if (temp_color == BLACK)//删除的结点为黑色
    {
        deleteFixupRB(treenode, pre_temp);//treenode为删除结点的接替结点,pre_temp也是接替节点的父节点
    }
    if (temp != NULL)
    {
        free(temp);
        temp = NULL;
    }
    return root;
}


//前序遍历，根左右
void preOrder(RBTree_t* treenode)
{
    if (treenode == NULL)
        return;
    printf("%d ", treenode->key);
    (treenode->color == RED) ? printf("RED\r\n") : printf("BLACK\r\n");
    preOrder(treenode->left);
    preOrder(treenode->right);
}

//中序遍历，左根右
void inOrder(RBTree_t* treenode)
{
    if (treenode == NULL)
        return;
    inOrder(treenode->left);
    printf("%d ", treenode->key);
    inOrder(treenode->right);
}