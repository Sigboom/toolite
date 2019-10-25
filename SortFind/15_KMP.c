/*************************************************************************
	> File Name: 18_KMP.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 四  8/ 2 16:47:20 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100010

int find(char*arm, char*model, int*next) {
    for (int i = 0, match = -1; i < strlen(arm); ++i) {
        while (match >= 0 && model[match + 1] != arm[i]) {
            match = next[match];
        }
        if (model[match + 1] == arm[i]) {
            match++;
        }
        if (match == strlen(model) - 1) {
            return i - match;
        }
    }
    return -1;
}

void get_next(char *pattern, int *next) {
    next[0] = -1;
    for (int i = 1, match = -1;pattern[i]; ++i) {
        while (match >= 0 && pattern[match + 1] != pattern[i]) {
            match = next[match];
        }
        if (pattern[match + 1] == pattern[i]) {
            match++;
        }
        next[i] = match;
    }
}

int main() {
    char arm[MAX_LEN], model[MAX_LEN];
    //scanf("%s", arm);
    scanf("%s", model);
    int *next = (int*)calloc(sizeof(int), strlen(model));
    get_next(model, next);
    for (int i = 0; model[i]; ++i) {
        printf("%d ", next[i]);
    }
    printf("\n");
    /*int ans = find(arm, model, next);
    if (ans != -1) {
        printf("Yes\n%d\n", ans);
    } else {
        printf("No\n");
    }*/
    return 0;
}
