/*************************************************************************
	> File Name: RBTree4.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 日  2/17 18:02:10 2019
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    RED,
    BLACK,
    DOUBLEBLACK
} color_t;

typedef struct RBTNode {
    int key, color;
    struct RBTNode *lchild, *rchild;
} RBTNode;

RBTNode *NIL;

RBTNode *init(int key) {
    RBTNode *p = (RBTNode *)malloc(sizeof(RBTNode));
    p->lchild = p->rchild = NIL;
    p->key = key;
    p->color = RED;
    return p;
}

__attribute__((constructor)) void init_NIL() {
    NIL = init(-1);
    NIL->color = BLACK;
    return ;
}

int has_red_child(RBTNode *root) {
    return root->lchild->color == RED || root->rchild->color == RED;
}

RBTNode *left_rotate(RBTNode *node) {
    RBTNode *temp = node->rchild;
    node->rchild = temp->lchild;
    temp->lchild = node;
    return temp;
}

RBTNode *right_rotate(RBTNode *node) {
    RBTNode *temp = node->lchild;
    node->lchild = temp->rchild;
    temp->rchild = node;
    return temp;
}


RBTNode *insert_maintain(RBTNode *root) {
    if (!has_red_child(root)) return root;
    //if (root->lchild->color == RED && root->rchild->color == RED) {}
    if (root->lchild->color == 0) {
        if (root->lchild->rchild->color == 0) 
            root->lchild = left_rotate(root->lchild);
        root = right_rotate(root);
    } else if (root->rchild->color == 0) {
        if (root->rchild->rchild->color == 0)
            root->rchild = right_rotate(root->rchild);
        root = left_rotate(root);
    } else 
        return root;
    root->color = RED;
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}

RBTNode *__insert(RBTNode *root, int key) {
    if (root == NIL || root == NULL) return init(key);
    if (root->key == key) return root;
    if (root->key < key) root->rchild = __insert(root->rchild, key);
    else root->lchild = __insert(root->lchild, key);
    return insert_maintain(root);
}

RBTNode *insert(RBTNode *root, int key) {
    root = __insert(root, key);
    root->color = BLACK;
    return root;
}

RBTNode *predecessor(RBTNode *root) {
    RBTNode *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

RBTNode *erase_maintain(RBTNode *root) {//check out
    if (root->lchild->color != DOUBLEBLACK && root->rchild->color != DOUBLEBLACK) return root;
    if (root->lchild->color == 0 || root->rchild->color == 0) {
        root->color = 0;
        if (root->lchild->color == RED) {
            root->lchild->color = 1;
            root = right_rotate(root);
            root->rchild = erase_maintain(root->rchild);
        } else {
            root->rchild->color = 1;
            root = left_rotate(root);
            root->lchild = erase_maintain(root->lchild);
        }
    }
    #define UNBALANCE(a, b) (root->a->color == DOUBLEBLACK && !has_red_child(root->b))
    if (UNBALANCE(lchild, rchild) || UNBALANCE(rchild, lchild)) {
        root->color += 1;
        root->lchild->color -= 1;
        root->rchild->color -= 1;
        return root;
    }
    #undef UNBALANCE
    if (root->lchild->color == DOUBLEBLACK) {
        if (root->rchild->rchild->color != RED) {
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = 1;
            root->rchild->rchild->color = 0;
        }
        root->lchild->color = 1;
        root = left_rotate(root);
        root->color = root->lchild->color;
        root->lchild->color = root->rchild->color = 1;
    } else {
        if (root->lchild->lchild->color != RED) {
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = 1;
            root->lchild->lchild->color = 0;
        }
        root->rchild->color = 1;
        root = right_rotate(root);
        root->color = root->rchild->color;
        root->lchild->color = root->rchild->color = 1;
    }
    return root;
}

RBTNode *__erase(RBTNode *root, int key) {
    if (root == NULL || root == NIL) return NIL;
    if (root->key < key)
        root->lchild = __erase(root->lchild, key);
    else if (root->key > key)
        root->rchild = __erase(root->rchild, key);
    else if (root->lchild == NIL ||root->rchild == NIL) {
        RBTNode *temp = root->lchild == NIL ? root->rchild : root->lchild;
        temp->color +=root->color;
        free(root);
        return temp;
    } else {
        RBTNode *temp = predecessor(root);
        root->key = temp->key;
        root->lchild = __erase(root->lchild, temp->key);
    }
    return erase_maintain(root);
}

RBTNode *erase(RBTNode *root, int key) {
    root = __erase(root, key);
    root->color = 1;
    return root;
}

void clear(RBTNode *node) {
    if (node == NIL || node == NULL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
    return ;
}

void output(RBTNode *root) {
    if (root == NIL) return ;
    printf("(%d | %d, %d, %d)\n", root->color, root->key, root->lchild->key, root->rchild->key);
    output(root->lchild);
    output(root->rchild);
    return ;
}

int main() {
    int op, value;
    RBTNode *root = NIL;
    while (scanf("%d%d", &op, &value) != EOF) {
        switch (op) {
            case 0: 
                printf("\ninsert %d\n", value);
                root = insert(root, value); break;
            case 1: 
                printf("\ndelete %d\n", value);
                root = erase(root, value); break;
            default: printf("error\n");
        }
        printf("----------\n");
        output(root);
    }
    return 0;
}
