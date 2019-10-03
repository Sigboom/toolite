/*************************************************************************
	> File Name: 220_DuplicateElementExists_III.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 五  3/ 1 16:14:59 2019
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1
#define bool int

typedef struct Queue {
    double *data;
    int *ind;
    int size, head, tail;
} Queue;

Queue *init(int size) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (double *)malloc(sizeof(double) * size);
    q->ind = (int *)malloc(sizeof(int) *size);
    q->size = size;
    q->tail = q->head = 0;
    return q;
}

void clear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q->ind);
    free(q);
    return ;
}

double top(Queue *q) {
    if (q->head == q->tail) return 0;
    return q->data[q->head];
}

int top_ind(Queue *q) {
    if (q->head == q->tail) return 0;
    return q->ind[q->head];
}

void pop(Queue *q) {
    q->head++;
}

int min_push(Queue *q, double val, int ind) {
    if (q->tail > q->size) return 0;
    while (q->head != q->tail && top(q) > val) pop(q);
    q->data[q->tail] = val;
    q->ind[q->tail++] = ind;
    return 1;
}

int max_push(Queue *q, double val, int ind) {
    if (q->tail > q->size) return 0;
    while (q->head != q->tail && top(q) <= val) pop(q);
    q->data[q->tail] = val;
    q->ind[q->tail++] = ind;
    return 1;
}

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int k, int t) {
    printf("qmax - qmin <= %d, qmax.ind - qmin.ind <= %d\n", t, k);
    Queue *qmin = init(numsSize), *qmax = init(numsSize);
    int res = false;
    for (int i = 0; i < numsSize; ++i) {
        min_push(qmin, nums[i], i);
        max_push(qmax, nums[i], i);
        printf("top_ind(qmax) = %d, top(qmax) = %.0f\n", top_ind(qmax), top(qmax));
        printf("top_ind(qmin) = %d, top(qmin) = %.0f\n", top_ind(qmin), top(qmin));
        if (top_ind(qmax) != top_ind(qmin) &&
            top(qmax) - top(qmin) <= t &&
            (res = true)) break;
        if (i > k && nums[i] == top(qmin)) pop(qmin);
        if (i > k && nums[i] == top(qmax)) pop(qmax);
    }
    clear(qmin);
    clear(qmax);
    return res;
}

int main() {
    int nums[4] = {1, 2, 3, 1};
    int k = 3, t = 0;
    if(containsNearbyAlmostDuplicate(nums, 4, k, t)) printf("true\n");
    else printf("false\n");
    return 0;
}
