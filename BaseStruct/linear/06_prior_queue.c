/*************************************************************************
	> File Name: prior_queue.c
	> Author: 
	> Mail: 
	> Created Time: 二 10/30 19:22:54 2018
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(a, b) {\
                    __typeof(a) _a = a;\
                    a = b; b = _a;\
                   }

typedef struct p_Queue {
    int *data;
    int size, count;
} p_Queue;

p_Queue *init(int n) {
    p_Queue *p = (p_Queue *)malloc(sizeof(p_Queue));
    p->data = (int *)malloc(sizeof(int) * n);
    p->size = n;
    p->count = 0;
    return p;
}

int is_empty(p_Queue *p) {
    return p->count == 0;
}

void clear(p_Queue *p) {
    if (p == NULL) return ;
    free(p->data);
    free(p);
    return ;
}

int push(p_Queue *q, int value) {
    if (q->count == q->size) return 0;
    q->data[q->count++] = value;
    int ind = q->count;
    while (ind > 1) {
        if (q->data[ind] <= q->data[ind / 2]) break;
        swap(q->data[ind], q->data[ind >> 1]);
        ind >>= 1;
    }
    return 1;
}

void pop(p_Queue *q) {
    if (is_empty(q)) return ;
    q->data[1] = q->data[q->count--];
    int ind = 1;
    while (ind * 2 <= q->count) {
        int temp = ind;
        if (q->data[temp] < q->data[ind << 1]) ind = ind << 1;
        if (q->data[temp] < q->data[ind << 1] && q->data[temp] < q->data[(ind << 1) + 1]) ind = (ind << 1) + 1;
        if (temp == ind) break;
        swap(q->data[temp], q->data[ind]);
    }
    return ;
}

int top(p_Queue *p) {
    if (is_empty(p)) return 0;
    return p->data[1];
}

void output(p_Queue *p) {
    printf("Queue = [");
    for (int i = 0; i < p->count; ++i) {
        i && printf(",");
        printf("%d", p->data[i]);
    }
    printf("]\n");
    return ;
}

int main() {
    #define MAX_OP 20
    srand(time(0));
    p_Queue *p = init(20);
    for (int i = 0; i < MAX_OP; ++i) {
        int op = rand() % 4, value = rand() % 100;
        switch(op) {
            case 0:
            case 1:
            case 2:
                printf("push a num!\n");
                push(p, value);
                break;
            case 3:
                printf("pop a num~\n");
                pop(p);
                break;
            default:
                printf("p_Queue's top is %d!\n", top(p));
                break;
        }
        output(p);
    }
    return 0;
}
