/*************************************************************************
	> File Name: 234_isPalindrome.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 四  7/ 5 10:52:30 2018
 ************************************************************************/

#include <stdio.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool isPalindrome(struct ListNode* head) {
    if (head == NULL) return true;
    if (head->next == NULL) return true;
    struct ListNode*p = head, *q = head, *pre;
    for (pre = head; q && q->next; q = q->next, q = q->next, p = p->next) {
        if (p != head) {
            pre = pre->next;
        }
    }
    if (q) {
        pre->next = p->next;
        free(p);
    }
    p = pre;
    struct ListNode*qp, *qq, *temp;
    qp = p->next;
    qq = qp->next;
    if (qq) {
        temp = qq->next;
        qp->next = NULL;
        while (temp) {
            qq->next = qp;
            qp = qq;
            qq = temp;
            temp = temp->next;
        }
        qq->next = qp;
        p->next = qq;
    }
    for (q = p->next, p = head; q; p = p->next, q = q->next) {
        if (p->val != q->val) {
            return false;
        }
    }
    return true;
}
