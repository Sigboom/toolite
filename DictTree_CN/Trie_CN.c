/*************************************************************************
	> File Name: huffman_CN.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 一  8/ 6 23:03:38 2018
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BASE 256
#define CHARMAX 256
#define MAXLINE 200
#define swap(a, b) { \
    __typeof(a) temp = a; \
    a = b; b = temp; \
}

typedef struct TNode {
    int flag;
    struct TNode *child[BASE];
} TNode;

long room = 0;

TNode *get_TNode() {
    room += sizeof(TNode);
    return (TNode*)calloc(sizeof(TNode), 1);
}

TNode *insert_trie(char *str, TNode *root) {
    if (root == NULL) root = get_TNode();
    TNode *p = root;
    for (int i = 0; str[i]; ++i) {
        if (p->child[str[i] + 128] == NULL) p->child[str[i] + 128] = get_TNode();
        p = p->child[str[i] + 128];
    }
    p->flag = 1;
    return root;
} 

void clear_trie(TNode *root) {
    if (root == NULL) return ;
    for (int i = 0; i < BASE; ++i) {
        clear_trie(root->child[i]);
    }
    free(root);
    return ;
}

void search(TNode *root, const char *arm) {
    if (root == NULL) return ;
    TNode *p = root;
    char buff[MAXLINE] = {0};
    int ind = 0;
    for (int head = 0; arm[head]; ++head) {
        for (int i = head; arm[i]; ++i) {
            if (!p->child[arm[i] + 128]) break; 
            buff[ind++] = arm[i];
            p = p->child[arm[i] + 128];
        }
        buff[ind] = '\0';
        if(p->flag == 1) {
            p->flag = 2;
            printf("find code:%s\n", buff);
        }
        ind = 0;
        p = root;
    }
    return ;
}

void clear(char **str, int n) {
    if (str == NULL) return ;
    for (int i = 0; i < n; ++i) {
        free(str[i]);
    }
    free(str);
    return ;
}

int main() {
    int n; 
    scanf("%d", &n);
    char **str = (char**)malloc(sizeof(char*) * n);
    room += sizeof(str) * n;
    for (int i = 0; i < n; ++i) {
        str[i] = (char*)malloc(sizeof(char) * MAXLINE);
        room += MAXLINE;
        scanf("%s", str[i]);
    }

    long time1 = clock();
    TNode *root = NULL;
    for (int i = 0; i < n; ++i) {
        root = insert_trie(str[i], root);
    }

    long time2 = clock();
    char arm[MAXLINE * 2];
    scanf("%s", arm);
    room += MAXLINE * 2;

    long time3 = clock();
    search(root, arm);
    clear_trie(root);
    clear(str, n);
    long time4 = clock();
    printf("run time:%ld, used room:%ld\n", time2 - time1 + time4 - time3, room);
    return 0;
}
