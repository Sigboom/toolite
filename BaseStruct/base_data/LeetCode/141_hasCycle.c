/*************************************************************************
	> File Name: 141_hasCycle.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 日  7/ 8 22:03:52 2018
 ************************************************************************/

#include <stdio.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool hasCycle(struct ListNode *head) {
    if (head == NULL) return false;
    struct ListNode*p, *q;
    p = head;
    q = p;
    while(p) {
        p = p->next;
        if (p == q) return true;
        if (!p) return false;
        p = p->next;
        q = q->next;
        if (p == q) return true;
    }
    return false;
}
