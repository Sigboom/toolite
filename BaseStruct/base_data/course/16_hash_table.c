/*************************************************************************
	> File Name: 11_hash_table.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 六  7/28 16:25:10 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

int main() {
    srand(time(0));
    char str1[50] = {0}, str2[50] = {0};
    for (int i = 0; i < 16; ++i) {
        str1[i] = (i & 1) ? 'a' : 'b';
    }
    for (int i = 0; i < 32; ++i) {
        str2[i] = (i & 1) ? 'a' : 'b';
    }
    printf("BKDRHash:\n");
    printf("str1(%s) = %d\n", str1, BKDRHash(str1));
    printf("str2(%s) = %d\n", str2, BKDRHash(str2));
    printf("APHash:\n");
    printf("str1(%s) = %d\n", str1, APHash(str1));
    printf("str2(%s) = %d\n", str2, APHash(str2));
    printf("zobristHash:\n");
    printf("str1(%s) = %d\n", str1, zobristHash(str1));
    printf("str2(%s) = %d\n", str2, zobristHash(str2));

    return 0;
}
