/*************************************************************************
	> File Name: 02_list_re.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 一  8/13 18:08:12 2018
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

ListNode *init(int val) {
    ListNode *p = (ListNode*)malloc(sizeof(ListNode));
    p->data = val;
    p->next = NULL;
    return p;
}

ListNode *insert(ListNode* head, int val, int ind) {
    ListNode ret, *p;
    ret.next = head;
    p = &ret;
    while (p && ind--) {
        p = p->next;
    }
    if (p == NULL) {
        return head;
    }
    ListNode *new = init(val);
    new->next = p->next;
    p->next = new;
    return ret.next;
}

void clear(ListNode *head) {
    if (head == NULL) return ;
    while (head) {
        ListNode *next = head->next;
        free(head);
        head = next;
    }
    return ;
}

void output(ListNode*head) {
    ListNode *p = head;
    while (p) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("\n");
    return ;
}

int main() {
    srand(time(0));
    ListNode *head = NULL;
    for (int i = 0; i < 10; ++i) {
        int val = rand() % 100, ind = rand() % (i + 1);
        printf("%d:insert(%d, %d):", i, val, ind);
        head = insert(head, val, ind);
        output(head);
    }
    clear(head);
    return 0;
}
