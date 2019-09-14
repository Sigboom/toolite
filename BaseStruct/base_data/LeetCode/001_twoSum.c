/*************************************************************************
	> File Name: 001_twoSum.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 四  9/13 13:37:37 2018
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target) {
    int*ans = (int*)malloc(sizeof(int) * 2);
    for (int i = 0; i < numsSize; ++i) {
        for (int j = i + 1; j < numsSize; ++j) {
            if (nums[i] + nums[j] == target) {
                ans[0] = i;
                ans[1] = j;
                return ans;
            }
        }
    }
    return ans;
}
