//
//  main.c
//  p7
//
//  Created by JEONGMIN on 2016. 4. 18..
//  Copyright © 2016년 JEONGMIN. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode* SearchTree;
typedef struct TreeNode* Node;
typedef struct TreeNode {
    int value;
    SearchTree left;
    SearchTree right;
}TreeNode;              //make struct TreeNode.


//declare available function in this main function.
Node findNode(SearchTree root, int key);
Node FindMin(SearchTree root);
Node FindMax(SearchTree root);
SearchTree deleteNode(SearchTree root, int key);
SearchTree insertNode(SearchTree root, int key);
void printInorder(SearchTree root);
void printPreorder(SearchTree root);
void printPostorder(SearchTree root);

int main(int argc, char* argv[]) {
    
    char ch1, ch2;
    int su;
    
    FILE *fp1 = fopen(argv[1], "r");        //to read input.txt file, make file input/ouput function.
    SearchTree my_Tree =NULL;       //Make binanry search tree.
    while (!feof(fp1)){         //if file's end isn't NUll, repeat this while.
        
        fscanf(fp1, "%c", &ch1);
        
        switch (ch1) {
                
            case 'i' :
                fscanf(fp1, "%d", &su);
                my_Tree = insertNode(my_Tree, su);      // insert integer value in my_Tree.
                break;
                
            case 'd' :
                fscanf(fp1, "%d", &su);
                my_Tree = deleteNode(my_Tree, su);      // delete integer value in my_Tree.
                break;
                
            case 'f' :
                fscanf(fp1, "%d", &su);
                findNode(my_Tree, su);          //find integer value in my_Tree.
                break;
                
            case 'p' :
                
                fscanf(fp1, "%c", &ch2);
                
                if (ch2 == 'i') {           //ch2 is 'i', print Inorder traversal.
                    printInorder(my_Tree);
                    printf("\n");
                }
                else if (ch2 == 'r') {
                    printPreorder(my_Tree);     //ch2 is 'r', print Preorder traversal.
                    printf("\n");
                }
                else if (ch2 == 'o') {
                    printPostorder(my_Tree);    //ch2 is 'o', print Postorder traversal.
                    printf("\n");
                }
                break;
        }      //switch end
    }// while end
    
    fclose(fp1);     //to close input.txt file, call this function.
    free(my_Tree);  //release dynamic allocation.
} // main end



Node findNode(SearchTree root, int key) {
    if (root == NULL) {
        printf("%d is not in the tree\n", key);
        return NULL;
    }
    if (key < root->value)
        return findNode(root->left, key);         //  recursive function. return Maximum node in the tree.
    
    else if (key > root->value)
        return findNode(root->right, key);      //recursive function. return Maximum node in the tree.

    
    else if (key == root->value){
        printf("%d is in the tree\n", key);     //if key equals root's value, print key.
        return root;
    }
    return 0;
}

SearchTree insertNode(SearchTree root, int key) {
    if (root == NULL) {
        root = (Node)malloc(sizeof(struct TreeNode));   // dynamic allocate root.
        
        if (root == NULL) {
            printf("Out of space!!!\n");
        }
        else {
            root->value = key;
            root->left = root->right = NULL;        // initiate tree.
        }
    }// first if end.
    else if (key < root->value) {
        root->left = insertNode(root->left, key);      //recursive function. insert key to tree.
    }
    else if (key > root->value) {
        root->right = insertNode(root->right,key);
    }
    else
        printf("the key already exists\n");     //if the key exists in the tree, print error message.
    
    return root;
}

Node FindMin(SearchTree root) {
    if (root == NULL)
        return NULL;
    else if (root->left == NULL)
        return root;
    else //root->left != NULL
        return FindMin(root->left);     //recursive function. return Maximum node in the tree.
}

Node FindMax(SearchTree root) {
    if (root == NULL)
        return NULL;
    
    else
        while (root->right != NULL)
            root = root->right;
    
    return root;
}

SearchTree deleteNode(SearchTree root, int key) {
    
    Node TmpCell;
    
    if (root == NULL)
        printf("Element not found\n");
    
    else if (key < root->value)
        root->left = deleteNode(root->left,key);//save delete performance in the root's left child
    
    else if (key > root->value)
        root->right = deleteNode(root->right, key); //save delete performance in the root's right child
    
    else if (root->left && root->right) {
        
        TmpCell = FindMin(root->right);
        root->value = TmpCell->value;
        root->right = deleteNode(root->right , root->value);
    }
    
    //if root's child is 2, execute this function.
    
    else {
        TmpCell = root;
        if (root->left == NULL)
            root = root->right;
        else if (root->right == NULL)
            root = root->left;
        free(TmpCell);
    }
    // if root's child is 1 or 0, execute this function.
    return root;
}

void printInorder(SearchTree root){
    if (root) {
        printInorder(root->left);
        printf("%d ", root->value);
        printInorder(root->right);
    }
}       //print inorder traversal.
void printPreorder(SearchTree root){
    if (root) {
        printf("%d ", root->value);
        printPreorder(root->left);
        printPreorder(root->right);
    }
}       //print preorder traversal.
void printPostorder(SearchTree root){
    if (root) {
        printPostorder(root->left);
        printPostorder(root->right);
        printf("%d ", root->value);
    }   //print postorder traversal.
}