/*************************************************************************
	> File Name: 9_raddix_sort.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 六  7/28 11:48:39 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rand_test.h"

#define lowbit(x) (x & 0xffff)
#define heightbit(x) ((x >> 16) & 0xffff)


void raddix_sort(int *num, int n);

int main() {
    TEST(20, raddix_sort(num, 20));
    return 0;
}

void raddix_sort(int *num, int n) {
    #define MAX_N 65536
    int *temp = (int *)malloc(sizeof(int) * n);
    int cnt[MAX_N] = {0};
    for(int i = 0; i < n ;++i)  cnt[lowbit(num[i])]++;
    for(int i = 1; i < MAX_N; ++i) cnt[i] += cnt[i - 1];   
    for(int i = n -1; i >= 0; i--) 
        temp[--cnt[lowbit(num[i])]] = num[i];
     
   memset(cnt, 0, sizeof(int) * MAX_N); 
    for(int i = 0; i < n ;++i) cnt[heightbit(temp[i])]++;
    for(int i = 1; i < MAX_N; ++i) cnt[i] += cnt[i - 1];
    for(int i = n -1; i >= 0; i--) 
        num[--cnt[heightbit(temp[i])]] = temp[i];
    free(temp);
}
