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

typedef struct HFNode {
    int ch;
    int freq;
    struct HFNode *lchild, *rchild;
} HFNode;

typedef struct TNode {
    int flag;
    struct TNode *child[BASE];
} TNode;

long room = 0;

HFNode *get_HFNode() {
    room += sizeof(HFNode);
    return (HFNode*)calloc(sizeof(HFNode), 1);
}

TNode *get_TNode() {
    room += sizeof(TNode);
    return (TNode*)calloc(sizeof(TNode), 1);
}

void buildHF(int n, HFNode* arr[n]) {
    for (int i = 0; i < n - 1; ++i) {
        int min_ind = 0;
        int min_freq = arr[0]->freq;
        for (int j = 1; j < n - i; ++j) {
            if (arr[j]->freq >= min_freq) continue;
            min_freq = arr[j]->freq;
            min_ind = j;       
        }
        swap(arr[min_ind], arr[n - i - 1]);
        min_ind = 0;
        min_freq = arr[0]->freq;
        for (int j = 1; j < n - i - 1; ++j) {
            if (arr[j]->freq >= min_freq) continue;
            min_freq = arr[j]->freq;
            min_ind = j;
        }
        swap(arr[min_ind], arr[n - i - 2]);
        HFNode*new_node = get_HFNode();
        new_node->freq = arr[n - i - 1]->freq + arr[n - i - 2]->freq;
        new_node->lchild = arr[n - i - 1];
        new_node->rchild = arr[n - i - 2];
        arr[n - i - 2] = new_node;
    }
    return ;
}

void extract(HFNode *root, char *buff, int n, char *huffman_code[CHARMAX]) {
    buff[n] = '\0';
    if (root->lchild == NULL && root->rchild == NULL) {
        huffman_code[root->ch] = (char*)malloc(sizeof(char) * MAXLINE);
        room += MAXLINE;
        strcpy(huffman_code[root->ch], buff);
        return ;
    }
    buff[n] = '0';
    extract(root->lchild, buff, n + 1, huffman_code);
    buff[n] = '1';
    extract(root->rchild, buff, n + 1, huffman_code);
    return ;
}

void show_huff(char **huffman_code) {
    for (int i = 0; i < CHARMAX; ++i) {
        if (huffman_code[i] == NULL) continue;
        printf("huffman_code[%d]:%s\n", i, huffman_code[i]);
    }
    return ;
}

void clear_hf(HFNode *root) {
    if (root == NULL) return ;
    clear_hf(root->lchild);
    clear_hf(root->rchild);
    free(root);
}

void cntocode(char *str, char *buff, char *huffman_code[]) {
    int end = 0;
    for (int i = 0; str[i]; ++i) {
        if (huffman_code[str[i] + 128] == NULL) continue;
        strcpy(&buff[end], huffman_code[str[i] + 128]);
        end += strlen(huffman_code[str[i] + 128]);
    } 
    //printf("%s's code: %s\n", str, buff);
    return ;
}

TNode *insert_trie(char *str, TNode *root) {
    if (root == NULL) root = get_TNode();
    TNode *p = root;
    for (int i = 0; str[i]; ++i) {
        if (p->child[str[i] - '0'] == NULL) p->child[str[i] - '0'] = get_TNode();
        p = p->child[str[i] - '0'];
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

void codetocn(char *buff, char *ans, char *huffman_code[]) {
    //printf("buff : %s\n", buff);
    int ind = 0, k = 0, len = strlen(buff);
    while (ind < len) {
        for (int i = 0; i < CHARMAX; ++i) {
            if (huffman_code[i] == NULL) continue;
            if (strncmp(huffman_code[i], &buff[ind], strlen(huffman_code[i])) == 0) {
                ans[k++] = i - 128;
                ind += strlen(huffman_code[i]);
            }
        }
    }
    return ;
}

void search(TNode *root, const char *arm, char *huffman_code[]) {
    if (root == NULL) return ;
    TNode *p = root;
    char buff[MAXLINE] = {0}, out[MAXLINE] = {0};
    room += MAXLINE * 2;
    int ind = 0;
    for (int head = 0; arm[head]; ++head) {
        for (int i = head; arm[i]; ++i) {
            if (!p->child[arm[i] - '0']) break; 
            buff[ind++] = arm[i];
            buff[ind + 1] = '\0';
            p = p->child[arm[i] - '0'];
        }
        if(p->flag == 1) {
            p->flag = 2;
            codetocn(buff, out, huffman_code);
            printf("find code:%s\n", out);
            memset(out, 0, sizeof(out));
        }
        ind = 0;
        p = root;
    }
    return ;
}

void get_pattern(int n, int *freq, char **str) {
    for (int i = 0; i < n; ++i) {
        str[i] = (char*)malloc(sizeof(char) * MAXLINE);
        room += MAXLINE;
        scanf("%s", str[i]);
        for (int j = 0; str[i][j]; ++j) {
            freq[str[i][j] + 128]++;
        }
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

void get_HFcode(int *freq, char *huffman_code[]) {
    HFNode *arr[CHARMAX] = {0};
    int code_num = 0;
    for (int i = 0; i < CHARMAX; ++i) {
        if (!freq[i]) continue;
        HFNode *new_node = get_HFNode();
        new_node->ch = i;
        new_node->freq = freq[i];
        arr[code_num++] = new_node;
    }
    buildHF(code_num, arr);
    room += sizeof(HFNode*) * CHARMAX;

    char buff[MAXLINE] = {0};
    if (code_num != 1) extract(arr[0], buff, 0, huffman_code);
    else {
        huffman_code[arr[0]->ch] = (char*)malloc(sizeof(char) * 2);
        strcpy(huffman_code[arr[0]->ch], "0");
    }
    //show_huff(huffman_code);
    clear_hf(arr[0]);
    room += sizeof(char*) * CHARMAX;
    return ;
}

int main() {
    int n; 
    scanf("%d", &n);
    int freq[CHARMAX] = {0};
    char **str = (char**)malloc(sizeof(char*) * n);
    get_pattern(n, freq, str);
    room += sizeof(int) * CHARMAX + sizeof(char*) * n;

    long time1 = clock();
    char *huffman_code[CHARMAX] = {0};
    get_HFcode(freq, huffman_code);

    char buff[MAXLINE * 3] = {0};
    TNode *root = NULL;
    for (int i = 0; i < n; ++i) {
        memset(buff, 0, sizeof(buff));
        cntocode(str[i], buff, huffman_code);
        root = insert_trie(buff, root);
    }
    
    long time2 = clock();
    char arm[MAXLINE];
    scanf("%s", arm);
    long time3 = clock();
    cntocode(arm, buff, huffman_code);
    search(root, buff, huffman_code);
    clear_trie(root);
    clear(str, n);
    long time4 = clock();
    room += CHARMAX * 4;
    printf("run time:%ld, used room:%ld\n", time2 - time1 + time4 - time3, room);
    return 0;
}
