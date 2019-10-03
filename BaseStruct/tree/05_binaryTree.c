/*************************************************************************
	> File Name: 05_binaryTree_re.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 二  8/14 12:31:18 2018
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
} Node;

Node *get_Node(int val) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->key = val;
    new_node->lchild = new_node->rchild = NULL;
    return new_node;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
}

void preorder(Node *root) {
    if (root == NULL) return ;
    printf("%d ", root->key);
    preorder(root->lchild);
    preorder(root->rchild);
}

void inorder(Node *root) {
    if (root == NULL) return ;
    inorder(root->lchild);
    printf("%d ", root->key);
    inorder(root->rchild);
}

void postorder(Node *root) {
    if (root == NULL) return ;
    postorder(root->lchild);
    postorder(root->rchild);
    printf("%d ", root->key);
}

int main() {
    Node* root = get_Node(1);
    root->lchild = get_Node(2);
    root->rchild = get_Node(3);
    root->lchild->lchild = get_Node(7);
    root->lchild->rchild = get_Node(8);
    root->rchild->lchild = get_Node(4);
    root->rchild->rchild = get_Node(5);
    root->rchild->rchild->lchild = get_Node(6);
    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    clear(root);
    return 0;
}
