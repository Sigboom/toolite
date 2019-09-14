/*************************************************************************
    > File Name: 10_2.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 日  4/ 1 10:52:34 2018
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define MAX 2000000

int32_t prime[MAX + 5] = {0};

int main() {
    int64_t sum = 0;
    for (int32_t i = 2; i <= MAX; ++i) {
        if (!prime[i]) {
            prime[++prime[0]] = i;
            sum += i;
        }
        for (int32_t j = 1; j <= prime[0] && prime[j] * i <= MAX; ++j) {
            prime[i * prime[j]] = 1;
            if(i % prime[j] == 0) break;
        }
    }
    printf("%"PRId64"\n", sum);
    return 0;
}
