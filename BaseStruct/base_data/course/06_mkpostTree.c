/*************************************************************************
	> File Name: 06_mkpostTree_re.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 二  8/14 12:46:18 2018
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
} Node;

Node *get_Node(int val) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->key = val;
    new_node->lchild = new_node->rchild = NULL;
    return new_node;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void postorder(Node *root) {
    if (root == NULL) return ;
    postorder(root->lchild);
    postorder(root->rchild);
    printf("%d ", root->key);
    return ;
}

Node* build (char pre_str[], char in_str[], int len) {
    Node *node = get_Node(pre_str[0] - '0');
    int ind = strchr(in_str, pre_str[0]) - in_str;
    if (ind > 0) {
        node->lchild = build(pre_str + 1, in_str, ind);
    }
    if (len - ind - 1 > 0) {
        node->rchild = build(pre_str + ind + 1, in_str + ind + 1, len - ind - 1);
    }
    return node;
}

int main() {
    char pre_str[] = "136945827";
    char in_str[] = "963548127";
    Node *root = build(pre_str, in_str, strlen(pre_str));
    postorder(root);
    printf("\n");
    clear(root);
    return 0;
}
