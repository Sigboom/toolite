/*************************************************************************
	> File Name: 22_double_array_trie.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 六  8/ 4 17:15:33 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BASE 26
#define BEGIN_LETTER 'a'
#define max(a, b) ((a) > (b) ? (a) : (b)) 
#define has_child(data, ind, i) (abs(data[data[ind]]))

typedef struct DANode {
    int base, check, fail; 
    char*str; 
} DANode;

typedef struct Node {
    int flag;
    struct Node*next[BASE];
    char*str;
} Node, *Trie;

int node_cnt = 0;

Node* get_new_node() {
    Node *p = (Node*)calloc(sizeof(Node), 1);
    node_cnt++;
    return p;
}

void clear(Trie root) {
    if(root == NULL) return ;
    for (int i = 0; i < BASE; ++i) {
        clear(root->next[i]);
    }
    free(root);
    return ;
}

Node *insert(Trie root, const char*str) {
    if (root == NULL) {
        root = get_new_node();
    }
    Node*p = root;
    for (int i = 0; str[i]; ++i) {
        int ind = str[i] - BEGIN_LETTER;
        if (p->next[ind] == NULL) p->next[ind] = get_new_node();
        p = p->next[ind];
    }
    p->flag = 1;
    p->str = strdup(str);
    return root;
}

void get_random_string(char *str) {
    int len = rand() % 10;
    for (int i = 0; i < len; ++i) {
        str[i] = BEGIN_LETTER + rand() % BASE;
    }
    str[len] = 0;
    return ;
}

int get_base(Node *node, DANode *data) {
    int base = 2, flag = 0;
    while (!flag) {
        flag = 1;
        for (int i = 0; i < BASE; ++i) {
            if (node->next[i] == NULL) continue;
            if (data[base + i].check == 0) continue;
            flag = 0;
            break;
        }
        base += (!flag);
    }
    return base;
}

int build(Node *node, DANode* data, int ind) {
    if (node == NULL) return 0;
    if (node->flag) data[ind].check = -data[ind].check, data[ind].str = node->str;
    int max_ind = ind;
    data[ind].base = get_base(node, data);
    for (int i = 0; i < BASE; ++i) {
        if (node->next[i] == NULL) continue;
        data[data[ind].base + i].check = ind;
    }
    for (int i = 0; i < BASE; ++i) {
        if (node->next[i] == NULL) continue;
        int temp = build(node->next[i], data, data[ind].base + i);
        max_ind = max_ind < temp ? temp : max_ind;
    }
    return max_ind;
}

void build_ac(DANode *data) {
    #define MAX_N 100000
    int *queue = (int*)malloc(sizeof(int) * MAX_N);
    int head = 0, tail = 0;
    queue[tail++] = 1;
    while (head < tail) {
        int ind = queue[head++];
        for (int i = 0; i < BASE; ++i) {
            if (!has_child(data, ind, i)) continue;
            int p = data[ind].fail;
            while (p & !has_child(data, p, i)) p = data[p].fail;
            if (p == 0) p = 1;
            else p = data[p].base + i;
            data[data[ind].base + i].fail = p;
            queue[tail++] = data[ind].base + i;
        }
    }
    return ;
    #undef MAX_N
}

void search_ac(DANode *data, const char *str) {
    int p = 1;
    for (int i = 0; str[i]; ++i) {
        while (p && !has_child(data, p, i)) p = data[p].fail;
        if (p == 0) p =1;
        else p = data[p].base + i;
        int q = p;
        while (q) {
            if (data[q].check) {
                printf("%s", )
            }
        }
    }
}

int main() {
    srand(time(0));
    #define INSERT_CNT 1000
    Trie root = NULL;
    char str[50];
    int word_cnt = 0;
    for (int i = 0; i < INSERT_CNT; i++) {
        get_random_string(str);
        root = insert(root, str);
        word_cnt += strlen(str);
        printf("insert %s to Trie\n", str);
    }
    output(root, str, 0);
    DANode *data = (DANode *)calloc(sizeof(DANode), (INSERT_CNT * 100));
    int da_cnt = build(root, data, 1);
    build_ac();
    #undef INSERT_CNT 
    return 0;
}


