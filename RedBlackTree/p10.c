
#include <stdio.h>
#include <stdlib.h>

#define TRIALS 20
#define TRUE 1
#define FALSE 0
#define SWAPPING 2

#define LEFT 0
#define RIGHT 1

#define MALLOC(data)					((data *)calloc(1, sizeof(data)))
#define MOVE(list)					((list) = (list)->post)
#define APPEND(list, tail)			((tail)->post = list, MOVE(tail))
#define SET_RED(node)				((node)->color = 1)
#define SET_BLACK(node)				((node)->color = 0)
#define IS_RED(node)					((node)->color & 1)
#define IS_BLACK(node)				(!IS_RED(node))
#define ALL_BLACK(node)				((!(node)->left || IS_BLACK((node)->left))\
&& (!(node)->right || IS_BLACK((node)->right)))

typedef struct _rb_node{
    int key;
    int color;
#define RED 1
#define BLACK 0
    struct _rb_node *left;
    struct _rb_node *right;
}Node;
typedef struct _rb_tree{
    Node *data;
}RBtree;
typedef struct _linked_list{
    Node *dataPtr;
    struct _linked_list *post;
}List;

RBtree *Init_RBtree();
Node *Init_RBNode(int input);
void Memset_RBtree(RBtree *src);
void Clear_Node(Node *src);
void Print_LevelOrder(RBtree *src);

Node *LL_Rotate(Node *prnt);
Node *RR_Rotate(Node *prnt);
Node *LR_Rotate(Node *prnt);
Node *RL_Rotate(Node *prnt);

void Insert_RB_Node(RBtree *src, int key);
Node *Insert_RB(Node *prnt, Node **new, int *flag);

void Delete_RB_Node(RBtree *src, int dkey);
Node *Delete_RB(Node *prnt, Node **del, int dkey, int *flag);
Node *Borrow_Red(Node *prnt, int flag);
Node *Change_Color(Node *prnt, Node *del);
Node *Delete_Single(Node *prnt);

void Swap_Val(int *x, int *y){int t = *x; *x = *y; *y = t;}

/*###############*/
int main(int argc, char* argv[])
{
    
    RBtree* my_Tree = Init_RBtree();
    FILE *fi = fopen (argv[1], "r");
    int su = 0;
    size_t end = 0;
    char buf[512] = {0};
    fgets(buf , sizeof(buf), fi);
    end = ftell(fi);        // tells cursor's location
    rewind(fi);
    while(!feof(fi))
    {
        fscanf(fi,"%d ",&su);
        if(ftell(fi) <= end)
        {
            Insert_RB_Node(my_Tree, su);
            
        }
        
        else
        {
            Delete_RB_Node(my_Tree, su);
        }
    }
    Print_LevelOrder(my_Tree);
    fclose(fi);
    Memset_RBtree(my_Tree);
    return 0;
    
}

/*###############*/
RBtree *Init_RBtree()
{
    RBtree *new = MALLOC(RBtree);
    new->data = NULL;
    return new;
}
//initate RBtree.

Node *Init_RBNode(int input)
{
    Node *new = MALLOC(Node);
    new->key = input;
    SET_RED(new);
    new->left = NULL;
    new->right = NULL;
    return new;
}
//initiate node
void Memset_RBtree(RBtree *src)
{
    Clear_Node(src->data);
    free(src);
}//all free in tree
void Clear_Node(Node *src)
{
    if(src)
    {
        Clear_Node(src->left);
        Clear_Node(src->right);
        free(src);
    }
}//all free in tree
void Print_LevelOrder(RBtree *src)
{
    List *newQue = NULL, *curQue = NULL;
    List *queHead = NULL, *queTail = NULL;
    int level = 0;
    if(!src->data)
        return;
    queHead = MALLOC(List);
    queHead->dataPtr = NULL;
    queHead->post = curQue = MALLOC(List);
    curQue->dataPtr = src->data;
    curQue->post = NULL;
    while(queHead->post)
    {
        curQue = queHead->post;
        queHead->post = NULL;
        queTail = queHead;
        printf("level(%d) : ", ++level);
        while(curQue)
        {
            if(curQue->dataPtr)
            {
                newQue = MALLOC(List);
                newQue->post = NULL;
                if(curQue->dataPtr->left)
                {
                    newQue->dataPtr	= curQue->dataPtr->left;
                }
                else
                {
                    newQue->dataPtr = NULL;
                }
                APPEND(newQue, queTail);
                
                newQue = MALLOC(List);
                newQue->post = NULL;
                if(curQue->dataPtr->right)
                {
                    newQue->dataPtr	= curQue->dataPtr->right;
                }
                else
                {
                    newQue->dataPtr = NULL;
                }
                APPEND(newQue, queTail);
                newQue = curQue;
                if(IS_RED(newQue->dataPtr))
                    printf("%d(R) ", newQue->dataPtr->key);
                else
                    printf("%d(B) ", newQue->dataPtr->key);
            }
            else
                printf("N ");
            newQue = curQue;
            MOVE(curQue);
            free(newQue);
        }
        printf("\n");
    }
    free(queHead);
}
//print level by level.



Node *LL_Rotate(Node *prnt)
{
    Node *new = prnt->left;
    SET_BLACK(new);
    prnt->left = new->right;
    new->right = prnt;
    SET_RED(prnt);
    return new;
}
//if case LL , rotate right.

Node *RR_Rotate(Node *prnt)
{
    Node *new = prnt->right;
    SET_BLACK(new);
    prnt->right = new->left;
    new->left = prnt;
    SET_RED(prnt);
    return new;
}
//if case RR , rotate left.

Node *LR_Rotate(Node *prnt)
{
    prnt->left = RR_Rotate(prnt->left);
    return LL_Rotate(prnt);
}

//if case LR , rotate left and then rotate right.

Node *RL_Rotate(Node *prnt)
{
    prnt->right = LL_Rotate(prnt->right);
    return RR_Rotate(prnt);
}
//if case RL , rotate right and then, rotate left.

void Insert_RB_Node(RBtree *src, int key)
{
    int flag = FALSE;
    Node *new = Init_RBNode(key);
    src->data = Insert_RB(src->data, &new, &flag);
    SET_BLACK(src->data);
}
// insert RBtree to myTree, and then set root's color black.
Node *Insert_RB(Node *prnt, Node **new, int *flag)
{
    if(!prnt)
        prnt = *new;
    else if(prnt->key > (*new)->key)
    {
        prnt->left = Insert_RB(prnt->left, new, flag);
        if(!*flag)
        {
            if(prnt->left == (*new))
            {
                if(IS_BLACK(prnt))
                    *flag = TRUE;
            }
            else
            {
                if(prnt->right && IS_RED(prnt->right))
                {
                    SET_BLACK(prnt->left);
                    SET_BLACK(prnt->right);
                    SET_RED(prnt);
                    *new = prnt;
                    return prnt;
                }
                else
                {
                    if(prnt->left->left && IS_RED(prnt->left->left))
                        prnt = LL_Rotate(prnt);
                    else
                        prnt = LR_Rotate(prnt);
                }
                *flag = TRUE;
            }
        }
    }
    else if(prnt->key < (*new)->key)
    {
        prnt->right = Insert_RB(prnt->right, new, flag);
        if(!*flag)
        {
            if(prnt->right == (*new))
            {
                if(IS_BLACK(prnt))
                    *flag = TRUE;
            }
            else
            {
                if(prnt->left && IS_RED(prnt->left))
                {
                    SET_BLACK(prnt->left);
                    SET_BLACK(prnt->right);
                    SET_RED(prnt);
                    *new = prnt;
                    return prnt;
                }
                else
                {
                    if(prnt->right->right && IS_RED(prnt->right->right))
                        prnt = RR_Rotate(prnt);
                    else
                        prnt = RL_Rotate(prnt);
                }
                *flag = TRUE;
            }
        }
        
    }
    else
    {
        printf("key(%d) is already in the tree.\n", (*new)->key);
        free(*new);
    }
    return prnt;
}


//insert Node by Binary search tree. and then  rotation and change the color



void Delete_RB_Node(RBtree *src, int dkey)
{
    int flag = FALSE;
    Node *del = NULL;
    if(src->data)
        src->data = Delete_RB(src->data, &del, dkey, &flag);
}

//delete Node in RBTree.

Node *Delete_RB(Node *prnt, Node **del, int dkey, int *flag)
{
    if(!prnt)
    {
        printf("key(%d) is not in the tree.\n", dkey);
        *flag = TRUE;
    }
    else if(*flag == SWAPPING)
    {
        if(prnt->right)
            prnt->right = Delete_RB(prnt->right, del, dkey, flag);
        else
        {
            Swap_Val(&prnt->key, &(*del)->key);
            if(IS_RED(prnt) || !ALL_BLACK(prnt))
                *flag = TRUE;
            prnt = Delete_Single(prnt);
            *del = prnt;
        }
    }
    else if(prnt->key == dkey)
    {
        if(prnt->left)
        {
            *del = prnt;
            *flag = SWAPPING;
            prnt->left = Delete_RB(prnt->left, del, dkey, flag);
        }
        else
        {
            if(IS_RED(prnt) || !ALL_BLACK(prnt))
                *flag = TRUE;
            prnt = Delete_Single(prnt);
            *del = prnt;
        }
    }
    else if(prnt->key > dkey)
    {
        prnt->left = Delete_RB(prnt->left, del, dkey, flag);
        if(!*flag)
        {
            if(prnt->right && IS_RED(prnt->right))
            {
                prnt = RR_Rotate(prnt);
                prnt->left = Change_Color(prnt->left, *del);
            }
            else
            {
                if(IS_RED(prnt))
                    prnt = Change_Color(prnt, *del);
                else
                {
                    if(ALL_BLACK(prnt->right))
                    {
                        prnt = Change_Color(prnt, *del);
                        *del = prnt;
                        return prnt;
                    }
                    else
                        prnt = Borrow_Red(prnt, RIGHT);
                }
            }
            *flag = TRUE;
        }
    }
    else //if(prnt->key < dkey)
    {
        prnt->right = Delete_RB(prnt->right, del, dkey, flag);
        if(!*flag)
        {
            if(prnt->left && IS_RED(prnt->left))
            {
                prnt = LL_Rotate(prnt);
                prnt->right = Change_Color(prnt->right, *del);
            }
            else
            {
                if(IS_RED(prnt))
                    prnt = Change_Color(prnt, *del);
                else
                {
                    if(ALL_BLACK(prnt->left))
                    {
                        prnt = Change_Color(prnt, *del);
                        *del = prnt;
                        return prnt;
                    }
                    else
                        prnt = Borrow_Red(prnt, LEFT);
                }
            }
            *flag = TRUE;
        }
    }
    return prnt;
}
//delete Node in RBtree.


Node *Borrow_Red(Node *prnt, int flag)
{
    int t = prnt->color;
    if(flag == LEFT)
    {
        if(prnt->left->left && IS_RED(prnt->left->left))
            prnt = LL_Rotate(prnt);
        else
            prnt = LR_Rotate(prnt);
    }
    else // flag == RIGHT
    {
        if(prnt->right->right && IS_RED(prnt->right->right))
            prnt = RR_Rotate(prnt);
        else
            prnt = RL_Rotate(prnt);
    }
    prnt->color = t;
    SET_BLACK(prnt->left);
    SET_BLACK(prnt->right);
    return prnt;
}

//borrow red node from its sibling in left case.
//borrow red node from its sibling in right case.




Node *Change_Color(Node *prnt, Node *del)
{
    SET_BLACK(prnt);
    if(prnt->left == del)
        SET_RED(prnt->right);
    else
        SET_RED(prnt->left);
    return prnt;
}
//change color.


Node *Delete_Single(Node *prnt)
{
    Node *del = prnt;
    if(prnt->left && IS_RED(prnt->left))
    {
        prnt = prnt->left;
        SET_BLACK(prnt);
    }
    else if(prnt->right && IS_RED(prnt->right))
    {
        prnt = prnt->right;
        SET_BLACK(prnt);
    }
    else
        prnt = NULL;
    free(del);
    return prnt;
}

// actually, delete extra node in the tree.
