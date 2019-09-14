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

struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode *cat, *bigcat, *littlecat;
    cat = head;
    while(cat) {
        littlecat = cat;
        bigcat = littlecat->next;
        while(bigcat) {
            if (bigcat->val == cat->val) {
                littlecat->next = bigcat->next;
                free(bigcat);
                bigcat = littlecat->next;
                continue;
            }
            littlecat = bigcat;
            bigcat = littlecat->next;
        }
        cat = cat->next;
    }
    return head;
}

int main() {
    int m, n = 5;
    struct ListNode*head;
    head = creatlist(n);
    output(head);
    head = deleteDuplicates(head);
    output(head);
    return 0;
}
