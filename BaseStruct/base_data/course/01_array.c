/*************************************************************************
	> File Name: 01_array_re.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 一  8/13 16:44:30 2018
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Vector {
    int *data;
    int length, size;
} Vector;

Vector *init(int n) {
    Vector *p = (Vector *)malloc(sizeof(Vector));
    p->data = (int *)malloc(sizeof(int) * n);
    p->size = n;
    p->length = 0;
    return p;
}

int expend(Vector *p) {
    int new_size = p->size;
    int *new;
    while (new_size) {
        new = (int *)realloc(p->data, sizeof(int) * (p->size + new_size));
        if (new == NULL) {
            new_size /= 2;
            continue;
        }
        break;
    }
    if (new_size == 0) {
        return 0;
    }
    //memcpy(new, p->data, sizeof(int) * p->length);
    //free(p->data);
    p->data = new;
    p->size += new_size;
    return 1;
}

int insert(Vector *p, int val, int ind) {
    if (p->length >= p->size) {
        if (!expend(p)) {
            return 0;
        }
    } 
    if (ind < 0 || p->length < ind) return 0;
    for (int i = p->length; i > ind; --i) {
        p->data[i] = p->data[i - 1];
    }
    p->data[ind] = val;
    p->length++;
    return 1;
}

int delete_val(Vector *p, int ind) {
    if (p->length <= 0) return 0;
    if (ind <= 0 || ind >= p->length) return 0;
    for (int i = ind + 1; i < p->length; ++i) {
        p->data[i - 1]  = p->data[i];
    }
    p->length--;
    return 1;
}

void clear(Vector *p) {
    if (p == NULL) return ;
    free(p->data);
    free(p);
    return ;
}

void output(Vector *p) {
    printf("[");
    for (int i = 0; i < p->length; ++i) {
        if (i == 0) {
            printf("%d", p->data[i]);    
        } else {
            printf(" %d", p->data[i]);
        }
    }
    printf("]\n");
}

int main() {
    srand(time(0));
    Vector *p = init(20);
    for (int i = 0; i < 10; ++i) {
        int value = rand() % 101, ind = rand() % (p->length + 1); 
        printf("%d:insert(%d, %d) = ", i + 1, value, ind);
        insert(p, value, ind);
        output(p);
    }
    for (int i = 0; i < 5; ++i) {
        int ind = rand() % (p->length + 1);
        delete_val(p, ind);
        printf("%d:delete_val(%d) = ", i, ind);
        output(p);
    }
    clear(p);
    return 0;
}
