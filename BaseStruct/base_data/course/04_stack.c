/*************************************************************************
	> File Name: 04_stack_re.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 一  8/13 23:50:41 2018
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define data_type int

typedef struct Stack {
    data_type *data;
    int top, size;
} Stack;

Stack *init(int );
int push(Stack *, data_type );
int pop(Stack *);
data_type get_top(Stack *);
void clear(Stack *);
int is_empty(Stack *);

void output(Stack *s) {
    if (is_empty(s)) return ;
    printf("Stack:[");
    for (int i = 0; i <= s->top; ++i) {
        printf("%d ", s->data[i]);
    }
    printf("]\n");
    return ;
}

int main() {
    srand(time(0));
    Stack *s = init(10);
    for (int i = 0; i < 20; ++i) {
        int op = rand() % 2;
        data_type data = rand() % 100;
        switch (op) {
            case 0:
            printf("push(%d):\n", data);
            push(s, data);
            output(s);
            break;
            case 1:
            printf("pop():%d\n", get_top(s));
            pop(s);
            output(s);
            break;
            default:printf("error\n");
        }
    }
    clear(s);
    return 0;
}

Stack *init(int n) {
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->data = (data_type*)malloc(sizeof(data_type) * n);
    s->size = n;
    s->top = -1;
    return s;
}

int push(Stack *s, data_type data) {
    if (s->top >= s->size) return 0;
    s->data[++s->top] = data;
    return 1;
}

int pop(Stack *s) {
    if (!s || is_empty(s)) return 0;
    s->top--;
    return 1;
}

data_type get_top(Stack *s) {
    return s->data[s->top];
}

void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

int is_empty(Stack *s) {
    return s->top == -1;
}
