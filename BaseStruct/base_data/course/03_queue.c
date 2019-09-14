/*************************************************************************
	> File Name: 03_queue_re.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 一  8/13 22:56:24 2018
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define data_type int

typedef struct Queue {
    data_type *data;
    int head, tail;
    int length, size;
} Queue;

Queue *init(int );
void clear(Queue *);
int push(Queue *, data_type val);
int pop(Queue *);
data_type get_head(Queue *);
int is_empty(Queue *);
void output(Queue *q) {
    printf("Queue:[");
    for (int i = 0, head = q->head; i < q->length; ++i, head = (head + 1) % q->size) {
        printf("%d ", q->data[head]);
    }
    printf("]\n");
    return ;
}

int main() {
    srand(time(0));
    Queue *q = init(10);
    for (int i = 0; i < 30; ++i) {
        int op = rand() % 2;
        data_type value = rand() % 100;
        switch (op) {
            case 0:
            printf("push(%d):\n", value);
            push(q, value);
            output(q);
            break;
            case 1:
            printf("pop():%d\n", get_head(q));
            pop(q);
            output(q);
            break;
            default:printf("error\n");
        }
    }
    clear(q);
    return 0;
}

Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (data_type *)malloc(sizeof(data_type) * n);
    q->length = 0;
    q->size = n;
    q->head = 0;
    q->tail = -1;
    return q;
}

void clear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

int push(Queue *q, data_type val) {
    if (q == NULL) return 0;
    if (q->length >= q->size) return 0;
    q->tail = (q->tail + 1) % q->size;
    q->length++;
    q->data[q->tail] = val;
    return 1;
}

int pop(Queue *q) {
    if (!q || is_empty(q)) return -1;
    q->head = (q->head + 1) % q->size;
    q->length--;
    return 1;
}

data_type get_head(Queue *q) {
    if (is_empty(q)) return -1;
    return q->data[q->head];    
}

int is_empty(Queue *q) {
    return q->length == 0;
}
