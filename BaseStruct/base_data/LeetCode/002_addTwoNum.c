/*************************************************************************
	> File Name: 002_addTwoNum.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 四  9/13 13:39:38 2018
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *p, *q;
    int temp = 0;
    for (p = l1, q = l2; p->next && q->next; p = p->next, q = q->next) {
        p->val += temp;
        temp = (p->val + q->val) / 10;
        p->val = (p->val + q->val) % 10;
    }
    p->val += temp;
    temp = (p->val + q->val) / 10;
    p->val = (p->val + q->val) % 10;
    if (p->next || q->next) {
        if (!p->next) {
            p->next = q->next;
        }
        p = p->next;
        while (p->next) {
            p->val += temp;
            temp = p->val / 10;
            p->val %= 10;
            p = p->next;
        }
        p->val += temp;
        temp = p->val / 10;
        p->val = p->val % 10;
    } 
    if (temp) {
        q = (struct ListNode*)malloc(sizeof(struct ListNode));
        q->val = temp;
        q->next = NULL;
        p->next = q;
    }
    return l1;
}
