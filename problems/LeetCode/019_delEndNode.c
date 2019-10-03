/*************************************************************************
	> File Name: dele_end_node.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 二  6/12 15:37:59 2018
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node*next;
} ListNode;

ListNode* creatlist(int n) {
    if (n <= 0) {
        return NULL;
    }
    ListNode *head, *p, *tail;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; ++i) {
        p = (ListNode*)malloc(sizeof(ListNode));
        p->data = rand() % 100;
        p->next = NULL;
        
        if (i == 0) {
            head = p;
            tail = p;
            continue;
        }
        tail->next = p;
        tail = tail->next;
    }
    return head;
}

int output(ListNode*head) {
    ListNode*p = head;
    int n = 0;
    while (p) {
        if (n == 0) {
            printf("%d", p->data);
        } else {
            printf(" %d", p->data);
        }
        p = p->next;
        n++;
    }
    printf("\n");
    return n;
}

ListNode*dele_end_node(ListNode*head, int n) {
    if (n <= 0) {
        return head;
    }
    ListNode*p = head, *q = NULL;
    int m = 0;
    while (p) {
        if (m == n) {
            q = head;
        } else if (m > n) {
            q = q->next;
        }
        p = p->next;
        m++;
    }
    if (q) {
        p = q->next;
        q->next=p->next;
    } else {
            if (n == m) {
            p = head;
            head = head->next;
        }
    }
    free(p);
    return head;
}

int main() {
    int m, n = 5;
    ListNode*head;
    head = creatlist(n);
    output(head);
    scanf("%d", &m);
    head = dele_end_node(head, m);
    output(head);
    return 0;
}
