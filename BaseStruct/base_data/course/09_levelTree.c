/*************************************************************************
	> File Name: 6_levelTree.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 六  7/28 00:04:14 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node, *pNode;
 
pNode init(char data) {
    pNode p = (pNode)malloc(sizeof(Node));
    p->data = data;
    p->lchild = p->rchild = NULL;
    return p;
}
 
void clear(pNode p) {
    if (!p) return ;
    clear(p->lchild);
    clear(p->rchild);
    free(p);
}

void output(pNode p) {
    if (!p) return ;
    printf("%c", p->data);
    if (p->lchild == NULL && p->rchild == NULL) {
        return ;
    }
    printf("(");
    if (p->lchild) {
        output(p->lchild);
    }
    if (p->rchild) {
        printf(",");
        output(p->rchild);
    }
    printf(")");
}
 
int main() {
    int len = 0, size = 50;
    char *str = (char *)malloc(size);
    char ch;
    str[0] = 0;
    while (scanf("%c", &ch)) {
        if (ch == '$') {
            break;
        }
        str[len++] = ch;
        if (len == size) {
            size *= 2;
            str = realloc(str, size);
        }
    }
    pNode *p_arr = (pNode *)malloc(sizeof(pNode) * (strlen(str) / 2 + 1));
    int ind = 1;
    p_arr[ind] = NULL;
    for (int i = 0; i < len; ++i) {
        if (str[i] == ' ') continue;
        p_arr[ind] = init(str[i]);
        if (ind != 1) {
            if (ind % 2) {
                p_arr[ind / 2]->rchild = p_arr[ind];
            } else {
                p_arr[ind / 2]->lchild = p_arr[ind];
            }
        }
        ++ind;
    }
    output(p_arr[1]);
    printf("\n");
    clear(p_arr[1]);
    free(p_arr);
    free(str);
    return 0;
} 


