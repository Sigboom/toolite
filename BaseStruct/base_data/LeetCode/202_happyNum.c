/*************************************************************************
	> File Name: happyNum.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 二  6/12 20:06:37 2018
 ************************************************************************/

#include <stdio.h>

int isHappyNum(int n) {
    int a = n, b;
    int nexta = n;
    int sum = 0;
    while (sum != 1) {
        for (sum = 0; a; a /= 10) {
            b = a % 10;
            sum += b * b;
        }
        a = sum;
        if (a == 1) {
            break;
        }
        for (sum = 0; a; a /= 10) {
            b = a % 10;
            sum += b * b;
        }
        a = sum;
        for (sum = 0; nexta; nexta /= 10) {
            b = nexta % 10;
            sum += b * b;
        }
        nexta = sum;
        if (nexta == a) {
            return 0;
        }
    }
    return 1;
}
int main() {
    int n;
    scanf("%d", &n);
    if (isHappyNum(n)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    return 0;
}
