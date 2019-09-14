/*************************************************************************
	> File Name: 206_reverseList.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 日  7/ 8 22:06:25 2018
 ************************************************************************/

#include <stdio.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head) {
    while (head == NULL || head->next == NULL) return head;
    struct ListNode *p = head, *q = head->next, *temp;
    temp = q->next;
    if (p == head) {
        p->next = NULL;
    }
    while (temp) {
        q->next = p;
        p = q;
        q = temp;
        temp = temp->next; 
    }
    q->next = p;
    head = q;
    return head;
}
