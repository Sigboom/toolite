/*************************************************************************
	> File Name: test.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 一  7/30 22:28:09 2018
 ************************************************************************/
#include <stdlib.h>
#include <stdio.h>

void showpos(FILE *stream);
int main(void)
{
    FILE *stream;
    fpos_t filepos;
    stream = fopen("a", "w+");
    fgetpos(stream, &filepos);
    fprintf(stream, "This is a test");
    showpos(stream);
    if (fsetpos(stream, &filepos) == 0)
        showpos(stream);
    else {
        fprintf(stderr, "Error setting file pointer.\n");
        exit(1);
    }
    fclose(stream);
    return 0;
}
void showpos(FILE *stream)
{
    fpos_t pos;
    fgetpos(stream, &pos);
    printf("File position: %lld\n", pos);
    return ;
}
