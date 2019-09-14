/*************************************************************************
	> File Name: 160_getIntersectionNode.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 日  7/ 8 22:05:12 2018
 ************************************************************************/

#include <stdio.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    if (headA == NULL || headB == NULL) return NULL;
    struct ListNode*a = headA, *b = headB;
    int len_a = 0, len_b = 0, beh = 0;
    for (a = headA; a; a = a->next, len_a++);
    for (b = headB; b; b = b->next, len_b++);
    beh = len_a - len_b;
    if (beh < 0) {
        for (b = headB; beh++; b = b->next);
        for (a = headA; a != b; a = a->next, b = b->next);
    } else {
        for (a = headA; beh--; a = a->next);
        for (b = headB; a != b; a = a->next, b = b->next);
    }
    return a;
}
