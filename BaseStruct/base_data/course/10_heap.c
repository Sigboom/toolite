/*************************************************************************
	> File Name: 10_heap_re.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 二  8/14 17:09:00 2018
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct heap {
    int *data;
    int size, length;
} heap;

heap *init(int n) {
    heap *h = (heap *)malloc(sizeof(heap));
    h->data = (int *)malloc(sizeof(int) * n);
    h->size = n;
    h->length = 0;
    return h;
}

void clear(heap *h) {
    if (h == NULL) return ;
    free(h->data);
    free(h);
    return ;
}

int push(heap *h, int data) {
    if (h == NULL) return 0;
    if (h->length == h->size) return 0;
    h->data[++h->length] = data;
    int i = h->length;
    while (i > 1) {
        if (h->data[i] <= h->data[i / 2]) break;
        h->data[i] ^= h->data[i / 2];
        h->data[i / 2] ^= h->data[i];
        h->data[i] ^= h->data[i / 2];
        i /= 2;
    }
    return 1;
}

int pop(heap *h) {
   if (h->length <= 1)  {
        h->length = 0;
       return 0;
    }
    h->data[1] ^= h->data[h->length];
    h->data[h->length] ^= h->data[1];
    h->data[1] ^= h->data[h->length];
    h->length--;
    int swap_ind = 1, ind = 1;
    while (ind * 2 <= h->length) {
        if (h->data[swap_ind] < h->data[ind * 2]) swap_ind = ind * 2;
        if ((ind * 2 + 1) <= h->length && h->data[swap_ind] < h->data[ind * 2 + 1]) swap_ind = ind * 2 + 1;
        if (swap_ind == ind) break;
        h->data[swap_ind] ^= h->data[ind];
        h->data[ind] ^= h->data[swap_ind];
        h->data[swap_ind] ^= h->data[ind];
        ind = swap_ind;
    }
    return 1;
}

int get_top(heap *h) {
    return h->data[1];
}

int main() {
    srand(time(0));
    heap *h = init(100);
    for (int i = 0; i < 20; ++i) {
        int val = rand() % 100;
        push(h, val);
    }
    for (int i = 1; i < 20; ++i) {
        pop(h);
        printf("top = %d\n", get_top(h));
    }
    printf("[");
    for (int i = 1; i < 20; ++i) {
        printf("%d ", h->data[i]);
    }
    printf("]\n");
    return 0;
}
