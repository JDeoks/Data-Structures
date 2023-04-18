//
//  main.c
//  RB_tree
//  1_3_b
//  Created by Seo JeongDeok on 2021/04/22.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

enum nodeColor {RED, BLACK}; // RED=0, BLACK=1

// structure definition of a node in red-black tree
typedef struct Node {
    int key;
    int color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

Node* NIL; // a sentinel node
Node* root;
int HB = -1;
int RBP = 1;
// main operations
Node* newNode(int x);
//Node* search(Node* node, int x);
//Node* search_min(Node* node);
void rotate_left(Node* x);
void rotate_right(Node* y);
Node* insertBST(Node* rnode, Node* temp);
void insertFixup(Node* rnode, Node* temp);
int checkRB(Node* rnode);
int black_height(Node * node);
void BH(int N);
//int reverseBH(Node * node);
void REDRED(Node* rnode);
void searchLeaf(Node* node);
//void deleteBST(Node* node, Node* temp);
//void deleteFixup(Node* root, Node* temp);

// helper functions
int height(Node* node);
void print_inorder(Node* node);
void print_levelNodes(Node* node, int level, int verbose);
void print_levelOrder(Node* node, int verbose);

int main()
{
    printf("1_3_b\n");
    FILE* FP = fopen("numbers.txt", "r");
    if (FP == NULL) {
        printf("File Could Not Be Opened\n");
        exit(1);
    }

    // assign NIL in memory
    NIL = (Node*)malloc(sizeof(Node));
    if(NIL == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    NIL->color = BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NULL;

    root = NIL;
    int NUM;
    int a;
    fscanf(FP, "%d", &a);
    
    for(int i = 0; i < a; i++){
        fscanf(FP, "%d", &NUM);
        Node* newnode = newNode(NUM);
        root = insertBST(root, newnode);
         print_levelOrder(root, 1);
        if(checkRB(root) == 1)
             printf("valid tree");
        else
             printf("invalid tree\n");
         HB = -1;
         printf("\n");
    }
    return 0;
}

// create a new node
Node* newNode(int x)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if(node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    node->key = x;
    node->color = RED;
    node->left = NIL;
    node->right = NIL;
    node->parent = NULL;
    return node;
}



//
// print keys with inorder traversal
void print_inorder(Node* node)
{
    if(node != NIL)
    {
        print_inorder(node->left);
        printf("%d ", node->key);
        print_inorder(node->right);
    }
}

// print nodes in the same level
void print_levelNodes(Node* node, int level, int verbose)
{
    if(node == NIL) {
        return;
    }
    if(level == 1) {
        if(node->color == RED) {
            printf("R");
        }
        else {
            printf("B");
        }
        printf("(%d", node->key);
        if(verbose) {
            printf(", bh:%d ", black_height(node));
            printf(" h:%d ", height(node));
            if(node->left != NIL)
                printf(",%d", node->left->key);
            else
                printf(",N");
            if(node->right != NIL)
                printf(",%d", node->right->key);
            else
                printf(",N");
        }
        printf(") ");
    }
    else if(level > 1) {
        print_levelNodes(node->left, level-1, verbose);
        print_levelNodes(node->right, level-1, verbose);
    }
}

// print nodes with level-order traversal
void print_levelOrder(Node* node, int verbose)
{
    int h = height(node);
    for(int level=1;level <= h;level++) {
        printf("height %d ", level);
        print_levelNodes(node, level, verbose);
        printf("\n");
    }
}

// get height of a node
int height(Node* node)
{
    if(node == NIL) {
        return 0;
    }
    else {
        int lh = height(node->left);
        int rh = height(node->right);
        if(lh >= rh) {
            return lh + 1;
        }
        else {
            return rh + 1;
        }
    }
}

int checkRB(Node* rnode)
{
    if(rnode->color != BLACK){
        //property  2
        RBP= 0;
    }
    REDRED(rnode);//property 4
    searchLeaf(rnode);//property 5
    if(RBP == 0)
        return -1;
    else
        return 1;
}

void REDRED(Node* node)
{
    if(node->left != NIL)
        REDRED(node->left);
    if(node->right != NIL)
        REDRED(node->right);
    if(node->color == RED && node->parent->color == RED){
        RBP = 0;
    }

}

void searchLeaf(Node* node)
{
    if(node->left != NIL)
        searchLeaf(node->left);
    if(node->right != NIL)
        searchLeaf(node->right);
    if(node->left == NIL && node->right == NIL)
        BH(black_height(node));
}

int black_height(Node * node)//리프노드를 받아서 노드의 bh값 반환
{
    int bh = 0;
    while(node->parent != NULL){
        if(node->color == BLACK)
            bh++;
        node = node->parent;
    }
    return bh;
}

void BH(int N)
{
    if(HB == -1)
        HB = N;
    if(HB != N)
        RBP = 0;
}

/*int reverseBH(Node * node)
{
    int bh = 0;
    Node* cnode = root;
    while(1){
        if(cnode->key < node->key){
            cnode = cnode->right;
            if(cnode->color == BLACK)
                bh++;
        }
        else if(cnode->key > node->key){
            cnode = cnode->left;
            if(cnode->color == BLACK)
                bh++;
        }
        if(cnode->key == node->key)
            return bh;
    }
    return 0;
}
*/

Node* insertBST(Node* rnode, Node* temp)
{
    Node* node = rnode;
    printf("%d\n", temp->key);
    if(rnode == NIL){
        temp->color = BLACK;
        rnode = temp;
        
    }
    else{
        while(1){
            if(temp->key > node->key){//big
                if(node->right != NIL){
                    node = node->right;
                }
                else
                    break;
            }
            else if(temp->key < node->key){//small
                if(node->left != NIL){
                    node = node->left;
                }
                else
                    break;
            }
            else{
                printf("already exist\n");
                return node;
            }
        }
        //search position
        if(temp->key > node->key){//big
            node->right = temp;
            temp->parent = node;
        }
        else{//small
            node->left = temp;
            temp->parent = node;
        }
        //link temp
       
        insertFixup(rnode,temp);
    }

    while(rnode->parent != NULL){
        rnode = rnode->parent;
    }

    
    return rnode;
}

void insertFixup(Node* rnode, Node* temp)
{
    Node* U;
    if(temp == rnode){//첫 노드일대는 그냥 return;
        temp->color = BLACK;
        return;
    }
    else{
        if(temp->parent->color == RED){
            
            if(temp->parent->parent->left == temp->parent){
                //find U node
                U = temp->parent->parent->right;
                
                if(U->color == RED){
                    //CASE 3
                    temp->parent->color = BLACK;
                    U->color = BLACK;
                    temp->parent->parent->color = RED;
                    insertFixup(rnode, temp->parent->parent);//G node recursion
                }
                else{
                    //CASE 4 OR CASE 5
                    if(temp->parent->right == temp){
                        //CASE 4
                        rotate_left(temp->parent);
                        temp = temp->left;
                    }
                    //CASE 5
                    rotate_right(temp->parent->parent);
                    temp->parent->color = BLACK;
                    temp->parent->right->color = RED;
                    
                }
            }
            else{
                U = temp->parent->parent->left;
                if(U->color == RED){
                    //CASE 3
                    temp->parent->color = BLACK;
                    U->color = BLACK;
                    temp->parent->parent->color = RED;
                    insertFixup(rnode, temp->parent->parent);//G node recursion
                }
                else{
                    //CASE 4 OR CASE 5
                    if(temp->parent->left == temp){
                        //CASE 4
                        rotate_right(temp->parent);
                        temp = temp->right;
                    }
                    //CASE 5
                    rotate_left(temp->parent->parent);
                    temp->parent->color = BLACK;
                    temp->parent->left->color = RED;

                }
            }

        }
    }
}

void rotate_left(Node* x)
{
    Node* y = x->right;
    x->right = y->left;
    x->right->parent = x;
    if(x->parent->left == x)
        x->parent->left = y;
    else{
        x->parent->right = y;
    }
    y->parent = x->parent;
    x->parent = y;
    y->left = x;
}

void rotate_right(Node* y)
{
    Node* x = y->left;
    y->left = x->right;
    y->left->parent = y;
    if(y->parent->left == x)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->parent = y->parent;
    y->parent = x;
    x->right = y;
}

