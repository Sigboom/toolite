/*************************************************************************
	> File Name: 8_stable_sort.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 四  7/26 17:11:21 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rand_test.h"



void insert_sort(int *, int);
void bubble_sort(int *, int);
void merge_sort(int *, int, int);

int main() {
    srand(time(0));
    TEST(30, insert_sort(num, 30));
    TEST(30, bubble_sort(num, 30));
    TEST(30, merge_sort(num, 0, 29));
    return 0;
}

void insert_sort(int *num, int n) {
    for (int i = 1; i < n; ++i) {
        for(int j = i - 1; j >= 0; --j) {
            if (num[j + 1] >= num[j]) break;
            swap(num[j], num[j + 1]);
        }
    }
    return;
}

void bubble_sort(int *num, int n) {
    for (int i = 1; i < n; ++i) {
        int flag = 0;
        for(int j = 0; j < n - i; ++j) {
            if (num[j] <= num[j + 1]) continue;
            swap(num[j], num[j + 1]);
            flag = 1;
        }
        if (flag == 0) break;
    }
    return ;
}

void merge_sort(int *num, int l, int r) {
    if (r - l <= 16) {
        insert_sort(num + l, r - l + 1);
        return ;
    }
    int mid = (l + r) >> 1;
    merge_sort(num, l, mid);
    merge_sort(num, mid + 1, r);
    int *temp = (int*)malloc(sizeof(int) * (r - l + 1));
    int p1 = l, p2 = mid + 1, k = 0;
    while (p1 <= mid || p2 <= r) {
        if ((p2 > r) || (p1 <= mid && num[p1] <= num[p2])) {
            temp[k++] = num[p1++];
        } else {
            temp[k++] = num[p2++];
        }
    }
    memcpy(num + l, temp, sizeof(int) * (r - l + 1));
    free(temp);
    return ;
}
