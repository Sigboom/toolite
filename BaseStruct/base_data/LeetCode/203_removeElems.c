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
    int val;
    struct ListNode*next;
};

struct ListNode* creatlist(int n) {
    if (n <= 0) {
        return NULL;
    }
    struct ListNode *head, *p, *tail;
    int val[100];
    //srand((unsigned int)time(NULL));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &val[i]);
    }
    for (int i = 0; i < n; ++i) {
        p = (struct ListNode*)malloc(sizeof(struct ListNode));
        p->val = val[i];
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
            printf("%d", p->val);
        } else {
            printf(" %d", p->val);
        }
        p = p->next;
        n++;
    }
    printf("\n");
    return n;
}

struct ListNode* removeElements(struct ListNode* head, int val) {
    if (head == NULL) return NULL;
    struct ListNode*p = head, *pre;
    while (p && p->val == val) {
        head = head->next;
        free(p);
        p = head;
    }
    while (p) {
        pre = p;
        p = p->next;
        while (p && p->val == val) {//解决 1 2 2 1的情况。
            pre->next = p->next;
            free(p);
            p = pre->next;
        }
    }
    return head;
}

int main() {
    int m, n = 6;
    int val;
    struct ListNode*head;
    head = creatlist(n);
    output(head);
    printf("请输入要删除的数值：");
    scanf("%d", &val);
    head = removeElements(head, val);
    output(head);
    return 0;
}
