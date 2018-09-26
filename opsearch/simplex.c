/*************************************************************************
	> File Name: simplex.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 二  9/11 08:29:50 2018
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VARMAX 100
#define CONMAX 1000

int arm[VARMAX] = {0};

void get_arm() {
    char min_max[4];
    char constraint[CONMAX];
    printf("input objective function:");
    scanf("%s", min_max);
    getline(constraint);
    return ;
}

int main() {
    get_arm();
    return 0;
}
