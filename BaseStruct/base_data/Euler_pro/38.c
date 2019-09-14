/*************************************************************************
	> File Name: 38.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 三  8/22 21:09:22 2018
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int ispandigit(int n, int *ans) {
    int i = 1, num = 0, a[10] = {0};
    int ret = 0, x;
    while (num < 9) {
        x = n * i;
        while (x) {
            if (x % 10 == 0) return 0;
            if (a[x % 10]) return 0;
            a[x % 10] = (++num);
            x /= 10;
        }
        ret *= (int)pow(10, floor(log10(n * i)) + 1);
        ret += n * i;
        ++i;
    }
    (*ans) = ret;
    return 1;
}

int main() {
    int ans, max = 0;
    for (int i = 1; i <= 10000; ++i) {
        if (ispandigit(i, &ans)) {
            if (max < ans) max = ans;
            printf("%d\n", ans);
        }
    }
    printf("max = %d\n", max);
    return 0;
}
