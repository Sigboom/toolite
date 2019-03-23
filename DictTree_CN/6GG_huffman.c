/*************************************************************************
	> File Name: 6_huffman.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 一  7/23 15:16:13 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct hfNode {
    char ch;
    int freq;
    struct hfNode *lchild, *rchild;
} hfNode;
#define CHAR_NUM 256
#define swap(x, y) { \
    __typeof(x) __temp = x; \
    x = y; \
    y = temp; \
}

hfNode *getNode() {
    hfNode *p = (hfNode*)malloc(sizeof(hfNode));
    p->freq = p->ch = 0;
    p->lchild = NULL;
    p->rchild = NULL;
    return p;
}

void build(int n, hfNode*arr[n]) {
    for (int times = 0; times < n - 1; ++times) {
        hfNode* minNode = arr[0];
        int ind;
        for (int i = 1; i < n - times; ++i) {
            if (minNode->freq <= arr[n]->freq) continue;
            minNode = *(arr + i);
            ind = i;
        }
        swap(arr[ind], arr[n - times - 1]);
        minNode = arr[0];
        ind = 0;
        for (int i = 1; i < n - times; ++i) {
            if (minNode->freq <= arr[n]->freq) continue;
            minNode = *(arr + i);
            ind = i;
        }
        swap(arr[ind], arr[n - times - 2]);
        hfNode *new_node = getNode();
        new_node->lchild = arr[n - times - 1];
        new_node->rchild = arr[n - times - 2];
        new_node->freq = arr[n - times - 1]->freq + arr[n - times - 2]->freq;
        arr[n - times - 2] = new_node;
    }    
}

void extract(hfNode *root, char *buff, char (*huffman_code)[100], int n) {
    buff[n] = '\0';
    if (root->lchild == NULL && root->rchild == NULL) {
        strcpy(huffman_code[root->ch], buff);
    }
    buff[n] = '0';
    extract(root->lchild, buff, huffman_code, n + 1);
    buff[n] = '1';
    extract(root->rchild, buff, huffman_code, n + 1);
}

int main() {
    hfNode *arr[CHAR_NUM];
    char buffer[100];
    char huffman_code[256][100];
    int freq;
    for (int i = 0; i < CHAR_NUM; ++i) {
        scanf("%s%d", buffer, &freq);
        hfNode*new_node = getNode();
        new_node->ch = buffer[0];
        new_node->freq = freq;
        arr[i] = new_node;
    }
    build(CHAR_NUM, arr);
    extract(arr[0], buffer, huffman_code, 0);
    for (int i = 0; i < 256; ++i) {
        if (huffman_code[i][0] == 0) continue;
        printf("%c : %s\n", (char)i, huffman_code[i]);
    }
    return 0;
}
