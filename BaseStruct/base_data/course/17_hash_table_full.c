/*************************************************************************
	> File Name: 17_hash_table_full.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 六  7/28 16:25:10 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Data {
    char *str;
    struct Data *next;
} Data;

typedef struct HashTable {
    Data *data;
    int size;
    int count;
    int (*Hash_func)(const char*);
} HashTable;


int APHash(const char* str) {
    int hash = 0;
    for (int i = 0; str[i]; ++i) {
        if (i & 1) {
            hash ^= (hash << 7) ^ str[i] ^ (hash >> 3);
        } else {
            hash ^= (~((hash << 11) ^ str[i] ^ (hash >> 5)));
        }
    }
    return (hash & 0x7fffffff);
}

int BKDRHash(const char *str) {
    int hash = 0, seed = 131;
    for (int i = 0; str[i]; ++i) {
        hash = hash * seed + str[i];
    }
    
    return hash & 0x7fffffff;
}

int zobrist_table[50][156] = {0};

void init_zobrist() {
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 256; ++j) {
            zobrist_table[i][j] = rand();
        }
    }
    return;
}

int zobristHash(const char* str) {
    static int flag = 1;
    if (flag) {
        flag = 0;
        init_zobrist();
    }
    int hash = 0;
    for (int i =0; str[i]; ++i) {
        hash ^= zobrist_table[i][str[i]];
    }
    return hash & 0x7fffffff;
}
int __APHash(Data*data) {
    return APHash(data->str);
}

int __BKDRHash(Data*data) {
    return BKDRHash(data->str);
}

int __zobristHash(Data*data) {
    return zobristHash(data->str);
}

HashTable *init(int size, int (*func)(const char*)) {
    HashTable*p = (HashTable*)malloc(sizeof(HashTable));
    p->data = (Data*)calloc(sizeof(Data), size);
    p->size = size;
    p->count = 0;
    p->Hash_func = func;
    return p;
}

void clear(HashTable*h) {
    if (h == NULL) return ;
    free(h->data);
    free(h);
}

//如果找到str返回-1，否则
int query(HashTable*h, const char *str) {
    int ind = h->Hash_func(str) % h->size;
    Data *p = h->data[ind].next;
    while (p) {
        if (strcmp(p->str, str) == 0) return -1;
        p = p->next;
        h->count++;
    }
    return ind;
}

void insert(HashTable *h, const char*str) {
    int ind = query(h,str);
    if (ind == -1) return ;
    Data *data = (Data*)malloc(sizeof(Data));
    data->str = strdup(str);
    data->next = h->data[ind].next;
    h->data[ind].next = data;
    return ;
}

int main() {
    HashTable *apHashTable = init(10000, APHash);
    HashTable *bkdrHashTable = init(10000, BKDRHash);
    HashTable *zobristHashTable = init(10000, zobristHash);
    #define MAX_N 100000
    for (int i = 0; i < MAX_N; ++i) {
        char str[7] = {0};
        for (int j = 0; j < 6; ++j) {
            str[j]= rand() % 26 + 'a';
        }
        str[6] = 0;
        insert(apHashTable, str);
        insert(bkdrHashTable, str);
        insert(zobristHashTable, str);
    }
    printf("APHash(%d) = %d\n", MAX_N, apHashTable->count);
    printf("BKDRHash(%d) = %d\n", MAX_N, bkdrHashTable->count);
    printf("zobristHash(%d) = %d\n", MAX_N, zobristHashTable->count);
    #undef MAX_N
    return 0;
}
