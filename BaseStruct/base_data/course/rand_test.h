/*************************************************************************
	> File Name: rand_test.h
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 六  7/28 12:16:12 2018
 ************************************************************************/
    
#ifndef _RAND_TEST_H
#define _RAND_TEST_H

#include <stdio.h>

#define swap(a, b) { \
    __typeof(a) temp; \
    temp = a; \
    a = b; \
    b = temp; \
}

#define TEST(n, func) { \
    int num[n] = {0}; \
    printf("source data:\n["); \
    for (int i = 0; i < n; ++i) { \
        num[i] = rand() % 100000; \
        if (i == 0) printf("%d", num[i]); \
        printf(" %d", num[i]); \
    } \
    printf("]\n"); \
    func; \
    output(num, n, #func); \
    printf("\n"); \
}

void output(int *num, int n, const char *str) {
    printf("%s:\n[", str);
    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            printf("%d", num[i]);
        }
        printf(" %d", num[i]);
    }
    printf("]\n");
}

#endif
