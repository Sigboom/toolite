/*************************************************************************
	> File Name: dele_end_node.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 二  6/12 15:37:59 2018
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode*next;
};

struct ListNode* creatlist(int n) {
    if (n <= 0) {
        return NULL;
    }
    struct ListNode *head, *p, *tail;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; ++i) {
        p = (struct ListNode*)malloc(sizeof(struct ListNode));
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

int output(struct ListNode*head) {
    struct ListNode*p = head;
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

struct ListNode* swapPairs(struct ListNode* head) {
    if (head == NULL || head->next == NULL) return head;
    struct ListNode*first, *second, *thrid;
    struct ListNode*temp;
    temp = head;
    first = head; 
    do {
        second = first->next;
        thrid = second->next;
        for (int i = 0; i < 3 && temp; ++i) {
            temp = temp->next;
        }
        second->next = first;
        if (first == head) {
            head = second;
        }
        if (!temp) {
            first->next = thrid;
            break;
        }
        first->next = temp;
        temp = thrid;
        first = thrid; 
    }while (first);
    return head;
}
int main() {
    int m, n = 6;
    struct ListNode*head;
    head = creatlist(n);
    output(head);
    head = swapPairs(head);
    output(head);
    return 0;
}
