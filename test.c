/*************************************************************************
	> File Name: test.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 一  7/30 22:28:09 2018
 ************************************************************************/

#include <stdio.h>

int main() {
    FILE*p = fopen("a", "r");
    FILE*q = fopen("a", "r");
    char ch;
    ch = fgetc(p);
    printf("fgetc(p) = %c\n", ch);
    ch = fgetc(p);
    printf("fgetc(p) = %c\n", ch);
    ch = fgetc(q);
    printf("fgetc(q) = %c\n", ch);
    ch = fgetc(q);
    printf("fgetc(q) = %c\n", ch);
    fclose(p);
    fclose(q);
    return 0;

}
