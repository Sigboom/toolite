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
    unsigned char ch;
    int freq;
    struct HFNode *lchild, *rchild;
} HFNode;

typedef struct TNode {
    int flag;
    struct TNode *child[BASE];
} TNode;

typedef struct Pattern {
    unsigned char *str;
    int freq;
} Pattern;

long room = 0;

HFNode *getNode();
void build(int n, HFNode *arr[]);
void extract(HFNode *root, char *buff, char (*huffman_code)[100], int n);
void get_freq(FILE *fp, int *freq);
void search(TNode *root, const char *arm, Pattern *p, int n,char huffman_code[][100]);
void clear_trie(TNode *root);
TNode *get_TNode();
void get_pattern(int n, Pattern *p);
void clear(Pattern *p, int n);
TNode *insert_trie(TNode *root, const char *str);
void output(Pattern*p, int n);
void get_HFcode(FILE *fp, char (*huffman_code)[100]);
void cntocode(const unsigned char *chinese, char *code, char (*huffman_code)[100]);
void codetocn(char *chinese, char *code, char huffman_code[][100]);

int main() {
    FILE *fp = NULL;
    char filename[MAXLINE];
    char huffman_code[CHARMAX][100] = {0};
    printf("亲，请输入已存在的初始化文件名：");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    get_HFcode(fp, huffman_code);

    int n; 
    printf("请输入模式串的个数：");
    scanf("%d", &n);
    Pattern *pattern = (Pattern*)malloc(sizeof(Pattern) * n);
    printf("请输入%d个模式串【以回车结尾】:\n", n);
    get_pattern(n, pattern);
    room += (sizeof(Pattern*) * n);

    long time1 = clock();
    char buff[MAXLINE * 10] = {0};
    TNode *root = NULL;
    for (int i = 0; i < n; ++i) {
        memset(buff, 0, sizeof(buff));
        cntocode(pattern[i].str, buff, huffman_code);
        root = insert_trie(root, buff);
    }
    printf("字典树已建立完成！\n");
    
    long time2 = clock();
    unsigned char arm[MAXLINE * 2];
    printf("亲，请输入要查找模式串的文本：\n");
    scanf("%[^\n]s", arm);
    long time3 = clock();
    memset(buff, 0, sizeof(buff));
    cntocode(arm, buff, huffman_code);
    search(root, buff, pattern, n, huffman_code);
    printf("查找结束!\n");
    output(pattern, n);

    clear_trie(root);
    clear(pattern, n);
    long time4 = clock();
    room += CHARMAX * 4;
    
    printf("run time:%ld, used room:%ld\n", time2 - time1 + time4 - time3, room);
    return 0;
}

void cntocode(const unsigned char *chinese, char *code, char (*huffman_code)[100]) {
    for (int i = 0; chinese[i]; ++i) {
        //printf("%d\n", chinese[i]);;
        strcat(code, huffman_code[chinese[i]]);
    }
}

void codetocn(char *chinese, char *code, char huffman_code[256][100]){
    int len = 0, k = 0;
    for (int i = 0; i < 256; ++i) {
        if(strncmp(code + len, huffman_code[i], strlen(huffman_code[i])) == 0) {
            chinese[k++] = i;
            if (!(code + len)) {
                return;
            }
            len += strlen(huffman_code[i]);
            i = 0;
        }
    }
}

void get_freq(FILE *fp, int *freq){
    unsigned char c;
    if (fp == NULL) {
        return ;
    }
    while (!feof(fp)) {
        c = fgetc(fp);
        if (!feof(fp)) {
            freq[c] += 1;
        }
    }
    fclose(fp);
}

HFNode *getNode() {
    HFNode *p = (HFNode *)malloc(sizeof(HFNode));
    p->freq = p->ch = 0;
    p->lchild = p->rchild = NULL;
    return p;
}

void build(int n, HFNode *arr[]) {
    for (int times = 0; times < n - 1; times++) {
        HFNode *minNode = arr[0];
        int ind = 0;

        for (int i = 1; i < n - times; i++) {

            if (arr[i]->freq >= minNode->freq) continue;

            minNode = arr[i];
            ind = i;
        }

        swap(arr[ind], arr[n - times - 1]);
        minNode = arr[0];
        ind = 0;
        for (int i = 1; i < n - times - 1; i++) {
            if (arr[i]->freq >= minNode->freq) continue;
            minNode = arr[i];
            ind = i;
        }
        swap(arr[ind], arr[n - times - 2]);
        HFNode *new_node = getNode();
        new_node->lchild = arr[n - times - 1];
        new_node->rchild = arr[n - times - 2];
        new_node->freq = arr[n - times - 1]->freq + arr[n - times - 2]->freq;
        arr[n - times - 2] = new_node;
    }
    return ;
}

void extract(HFNode *root, char *buff, char (*huffman_code)[100], int n) {
    buff[n] = '\0';

    if (root->lchild == NULL && root->rchild == NULL) {
        strcpy(huffman_code[root->ch], buff);
        //printf("%d ", root->ch);
        return ;
    }
    buff[n] = '0';
    extract(root->lchild, buff, huffman_code, n + 1);
    buff[n] = '1';
    extract(root->rchild, buff, huffman_code, n + 1);
    return ;
}

void get_HFcode(FILE *fp, char (*huffman_code)[100]) {
    int freq[CHARMAX] = {0};
    get_freq(fp, freq);
    for (int i = 0; i < CHARMAX; ++i) {
        if (!freq[i]){
            continue;
        }
        printf("%d %d \n", i, freq[i]);
    }

    HFNode *arr[CHARMAX] = {0};
    char buff[100];
    for (int i = 0; i < CHARMAX; ++i) {
        HFNode *new_node = getNode();
        new_node->ch = (char)i;
        if(freq[i] == 0){
            new_node->freq = 1;
        } else {
            new_node->freq = freq[i];
        }
        arr[i] = new_node;
    }

    build(CHARMAX, arr);
    extract(arr[0], buff, huffman_code, 0);
    for (int i = 0; i < 256; ++i) {
        if (huffman_code[i][0] == 0) continue;
        printf("%d : %s\n", i, huffman_code[i]);
    }

}

void output(Pattern*p, int n) {
    printf("已为您查找完成~~\n");
    for (int i = 0; i < n; ++i) {
        printf("%-4d%s 出现的次数:%d\n", i + 1, p[i].str, p[i].freq);
    }
    return ;
}

void search(TNode *root, const char *arm, Pattern *pa, int n, char huffman_code[][100]) {
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
        if(p->flag) {
            codetocn(out, buff, huffman_code);
            for (int i = 0; i < n; ++i) {
                if (strcmp(out, (char*)pa[i].str) == 0) {
                    pa[i].freq++;
                }
            }
            memset(out, 0, sizeof(out));
        }
        ind = 0;
        p = root;
    }
    return ;
}


void clear_trie(TNode *root) {
    if (root == NULL) return ;
    for (int i = 0; i < BASE; ++i) {
        clear_trie(root->child[i]);
    }
    free(root);
    return ;
}

TNode *get_TNode() {
    room += sizeof(TNode);
    return (TNode*)calloc(sizeof(TNode), 1);
}


TNode *insert_trie(TNode *root, const char *str) {
    if (root == NULL) root = get_TNode();
    TNode *p = root;
    for (int i = 0; str[i]; ++i) {
        if (p->child[str[i] - '0'] == NULL) p->child[str[i] - '0'] = get_TNode();
        p = p->child[str[i] - '0'];
    }
    p->flag = 1;
    return root;
} 

void get_pattern(int n, Pattern *p) {
    char temp[MAXLINE] = {0};
    for (int i = 0; i < n; ++i) {
        scanf("%s", temp);
        p[i].str = (unsigned char*)malloc(sizeof(unsigned char) * (strlen(temp) + 1));
        room += sizeof(char) * strlen((char *)p[i].str);
        strcpy((char*)p[i].str, temp);
        p[i].freq = 0;
    }
    return ;
}

void clear(Pattern *p, int n) {
    if (p == NULL) return ;
    for (int i = 0; i < n; ++i) {
        free(p[i].str);
    }
    free(p);
    return ;
}

