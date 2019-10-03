/*************************************************************************
	> File Name: 237_deleteNode.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 四  7/ 5 10:51:14 2018
 ************************************************************************/

#include <stdio.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void deleteNode(struct ListNode* node) {
    struct ListNode*p = node, *q = node->next;
    for (; q->next; p = p->next, q = q->next) {
        p->val = q->val;
    }
    p->val = q->val;
    p->next = NULL;
    free(q);
}
