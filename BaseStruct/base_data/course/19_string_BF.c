/*************************************************************************
	> File Name: 19_string_BF.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 四  8/ 2 20:35:48 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int BF(const char*text, const char*pattern) {
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    int cnt = 0;
    for (int i = 0; i < len1 - len2 + 1; ++i, cnt++) {
        int flag = 1;
        for (int j = 0; pattern[i] && flag; ++j, cnt++) {
            if (text[i + j] == pattern[j]) continue;
            flag = 0;
        }
        if (flag) return cnt; 
    }
    return 0;
}

int KMP(const char*text, const char*pattern) {
    #define RETURN(a) { \
        free(next); \
        return a; \
    }
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    int *next = (int*)malloc(sizeof(int) * strlen(pattern));
    int j = -1;
    int cnt = 0;
    next[0] = -1;
    for (int i = 1; i < len2; ++i, cnt++) {
        int j = next[i - 1] + 1;
        while (j != -1 && pattern[j + 1] != pattern[i]) {
            j = next[j];
            cnt++;
        }
        if (pattern[j + 1] == pattern[i]) {
            j++; 
        } 
        next[i] = j;
    }
    j = -1;
    for (int i = 0; text[i]; ++i, cnt++) {
        while (j >= 0 && pattern [j + 1] != text[i]) {
            j = next[j];
            cnt++;
        }
        if (pattern[j + 1] == text[i]) {
            j++;
        }
        if (pattern[j + 1] == 0) RETURN(cnt);
    }
    RETURN(0);
}

int main() {
    char str1[] = "Hello world";
    char str2[] = "wor";
    printf("BF(%s, %s)'s cnt: %d\n", str1, str2, BF(str1, str2));
    printf("KMP(%s, %s)'s cnt: %d\n", str1, str2, KMP(str1, str2));
    return 0;
}
