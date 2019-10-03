/*************************************************************************
	> File Name: 6_general_list.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 四  7/26 09:48:47 2018
 ************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node*lchild, *rchild;
} Node;

Node*getNewNode(char ch) {
    Node*p = (Node*)malloc(sizeof(Node));
    p->key = ch;
    p->lchild = p->rchild = NULL;
    return p;
}

Node*build(char *str, Node *root, int init) {
    if (str[0] == 0) return NULL;
    static int i;
    if (init) i = 0;
    Node *p = NULL;
    int flag = 0;
    while (str[i]) {
        switch (str[i]) {
            case '(': {
                i += 1;
                p = build(str, p, 0);
            } break;
            case ')': {
                if (root == NULL) return p;
                return root;
            } break;
            case ',': {
                flag = 1; 
            } break;
            case ' ':break;
            default:{
                p = getNewNode(str[i]);
                if (root) {
                    if (flag == 0) root->lchild = p;
                    else root->rchild = p;
                }
            }
            break;
        }
        i += 1;
    }
    return (root ? root : p);
}

void output(Node*root) {
    if (root == NULL) {
        return ;
    }
    output(root->lchild);
    printf("%c ", root->key);
    output(root->rchild);
}

int main() {
    char str[100];
    scanf("%[^\n]s", str);
    Node *p = NULL;
    p = build(str, p, 1);
    output(p);
    printf("\n");
    return 0;
}
