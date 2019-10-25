/*************************************************************************
	> File Name: 10_binary_search.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 六  7/28 15:29:47 2018
 ************************************************************************/

#include <stdio.h>


int binary_search1(int *num, int n, int x) {
    int head = 0, tail = n - 1, mid;
    while (head <= tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == x) return mid;
        if (num[mid] < x) {
            head = mid + 1;
        } else {
            tail = mid - 1;
        }
    }
    return -1;
}

//111111110000000求最后一个1
int binary_search2(int*num, int n) {
    int head = -1, tail = n - 1, mid;
    while (head < tail) {
        mid = (head + tail + 1) >> 1;
        if (num[mid] == 1) {
            head = mid;
        } else {
            tail = mid - 1;
        }
    }
    return head;
}

//000000000011111111求第一个1
int binary_search3(int *num, int n) {
    int head = 0, tail = n - 1, mid;
    while (head < tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == 1) {
            tail = mid;
        } else {
            head = mid + 1;
        }
    }
    return head == n ? -1 : head;
}

int main() {
    int num1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int num2[10] = {1, 1, 1, 1, 1, 0, 0, 0, 0 ,0};
    int num3[10] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
    printf("binary_search1(num1[], 10, 8) = %d\n", binary_search1(num1, 10, 8));
    printf("binary_search2(num2[], 10) = %d\n", binary_search2(num2, 10));
    printf("binary_search2(num3[], 10) = %d\n", binary_search3(num3, 10));
    return 0;
}
