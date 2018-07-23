/*************************************************************************
	> File Name: diff.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 一  7/23 23:27:22 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXFILENAME 60
#define MAXLINE 120

void showLine(FILE*, FILE*);
void showDiff(char*, char*);
void mkfile(char*, char*);

int main(int argc,char *argv[])
{
    int opt=0;
    char oneFile[MAXFILENAME], twoFile[MAXFILENAME];
    while((opt=getopt(argc,argv,"c"))!=-1)
    {
        switch(opt)
        {
            case 'c':mkfile(argv[2], argv[3]);break;
        }
    }
    showDiff(argv[1], argv[2]);
    return 0;
}

void showLine(FILE*armHead, FILE*modelHead) {
    char arm = fgetc(armHead);
    char model = fgetc(modelHead);
    while (arm != '\n') {
        printf("%c", arm);
        arm = fgetc(armHead);
    }
    printf("\n");
    while (model != '\n') {
        printf("%c", model);
        model = fgetc(modelHead);
    }
    printf("\n");
}

void showDiff(char*oneFile, char*twoFile) {
    printf("read File %s and %s.\n", oneFile, twoFile);
    FILE*one = fopen(oneFile, "r");
    FILE*two = fopen(twoFile, "r");
    FILE*temp = NULL;
    FILE*armHead = one;
    FILE*modelHead = two;
    char arm = fgetc(one);
    char model = fgetc(two);
    int i = 0;
    while (!feof(one) && !feof(two)) {
        if (arm != model) {
            showLine(armHead, modelHead);//输出字符不同的该行；
            while ((arm = fgetc(one)) != '\n');
            while ((model = fgetc(two)) != '\n');
        }
        //这里好像有问题
        if (arm == '\n' && model == '\n') {
            armHead = one;
            modelHead = two;
        }
        arm = fgetc(one);
        model = fgetc(two);
        //printf("%c", arm);
        //printf("%c", model);
    }
    if (feof(one) && feof(two)) printf("Line is all right!");
    else if (!feof(two)) printf("model have no end!\n");
    else {
        printf("you code lines is longer than model\n");
    }
}

void mkfile(char*oneFile, char*twoFile) {
    
}
