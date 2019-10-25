/*************************************************************************
	> File Name: 20_shift_and.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 六  8/ 4 11:54:41 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHARNUM 127
#define BASE 30

#define TEST(func) { \
    printf("%s = %d\n", #func, func); \
}

typedef struct BitData {
    int *data;
    int cnt;
} BitData;

BitData *init(int n) {
    BitData* pdata = (BitData*)malloc(sizeof(BitData));
    pdata->data = (int*)calloc(sizeof(int), n / BASE + 1);
    pdata->cnt = n / BASE + 1;
    return pdata;
}

void clear(BitData *d) {
    if (d == NULL) return ;
    free(d->data);
    free(d);
}

void operator_or(BitData *d, int n) {
    int x = n / BASE;
    int y = n % BASE;
    d->data[x] |= (1 << y); 
    return ;
}

void operator_and(BitData *d1, BitData *d2) {
    int len = d1->cnt < d2->cnt ? d1->cnt : d2->cnt;
    for (int i = 0; i < len; ++i) {
        d1->data[i] &= d2->data[i];
    }
    for (int i = len; i < d1->cnt; ++i) {
        d1->data[i] = 0;
    }
    return ;
}

int operator_get(BitData *d, int n) {
    int x = n / BASE;
    int y = n % BASE;
    return d->data[x] & (1 << y);
}

int operator_left(BitData *d) {
    for (int i = d->cnt - 1; i >= 0; --i) {
        if (i != d->cnt - 1) {
            d->data[i + 1] |= (d->data[i] >> (BASE - 1));
        }
        d->data[i] <<= 1;
    }
    return 0;
}


int shift_and(const char *text, const char *pattern) {
    int len = strlen(pattern);
    BitData *d[127] = {0};
    for (int i = 0; i < CHARNUM; ++i) {
        d[i] = init(len);
    }
    for (int i = 0; i < len; ++i) {
        operator_or(d[pattern[i]], i);
    }
    BitData *p = init(len);
    for (int i = 0; text[i]; ++i) {
        operator_left(p);
        operator_or(p, 0);
        operator_and(p, d[text[i]]);
        if (operator_get(p, len - 1)) return 1;
    }
    return 0;
}


int main() {
    TEST(shift_and("hello world", "hello"));
    return 0;
}
