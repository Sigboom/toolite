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

#define BASE 2
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
        for (int j = 0; j < 8; ++j) {
            if ((int)str[i] & (1 << j)) {
                if (!p->child[1]) p->child[1] = get_TNode();
                p = p->child[1];
            } else {
                if (!p->child[0]) p->child[0] = get_TNode();
                p = p->child[0];
            }
        }
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
    char out[MAXLINE] = {0};
    room += MAXLINE;
    int ind = 0, k, flag = 0;
    for (int head = 0; p && arm[head]; ++head) {
        for (int i = head; p && arm[i]; ++i) {
            for (int j = 0; p && j < 8; ++j) {
                p = arm[i] & (1 << j) ? p->child[1] : p->child[0];
            }
            out[ind++] = arm[i];
            out[ind] = '\0';
            for (k = 0; p && k < BASE && !p->child[k]; ++k);
            if (k == BASE) break; 
        }
        if(p && p->flag == 1 && ++flag) {
            p->flag = 2;
            printf("find code:%s\n", out);                            
        }
        p = root;
        ind = 0;
    }
    if (!flag) printf("No find!\n");
    return ;
}

void get_pattern(int n, char **str) {
    for (int i = 0; i < n; ++i) {
        str[i] = (char*)malloc(sizeof(char) * MAXLINE);
        room += MAXLINE;
        scanf("%s", str[i]);
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
    get_pattern(n, str);
    room += CHARMAX + sizeof(char*) * n;

    long time1 = clock();
    TNode *root = NULL;
    for (int i = 0; i < n; ++i) {
        root = insert_trie(str[i], root);
    }
  
    long time2 = clock();
    char arm[MAXLINE * 3];
    scanf("%s", arm);
    long time3 = clock();
    search(root, arm);
    clear_trie(root);
    clear(str, n);
    long time4 = clock();
    room += CHARMAX * 3;
    printf("run time:%ld, used room:%ld\n", time2 - time1 + time4 - time3, room);
    
    return 0;
}
