/*************************************************************************
	> File Name: list.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 四  9/ 5 13:46:51 2019
 ************************************************************************/

#include "list.h"

list::list() : length(0), _listHead(NULL) {}

list::~list() {
        clean(_listHead);
    }
    
void list::initialize() {
    clean(_listHead);
    _listHead = NULL;
    length = 0;
    return ;
}

/* Define date: 2019.9.6
 * Author: Doni Daniel   
 * find():
 *  返回key是否存在，node->next指向所寻key的前一个节点
 *  若node->next == node 所寻key在头指针，即要操作头指针
 *  若node->next == NULL 所寻key在链表尾，即要操作的位置在链表后一个节点
 */
bool list::find(int key, listNode *node = NULL) {
    listNode vir;
    vir.next = _listHead;
    listNode *p;
    for (p = &vir; p->next; p = p->next) {
        if (p->next->key >= key) {
            if(node) {
                if (p != &vir) node->next = p;
                else node->next = node;
            }
            return p->next->key == key;
        } 
    }
    node->next = p;
    return false; 
}

int list::update(int key, int val) {
    if (length == 0) return -1;
    listNode *node = getNewNode(key, val);
    
    if(find(key, node)) {
        if (node->next == node) {
            _listHead->value = val;
        } else node->next->next->value = val; 
        deleteListNode(node);
    } else return -1;
    return 0;
}

int list::insert(int key, int val) {
    if (length == 0) {
        _listHead = getNewNode(key, val);
        return 0;
    }
    listNode *node = getNewNode(key, val);
    
    if(find(key, node)) {
        deleteListNode(node);
        return -1;
    } else {
        if (node->next == node) {
            node->next = _listHead;
            _listHead = node;
        } else {
            listNode *temp = node->next;
            node->next = temp->next;
            temp->next = node;
        }
    }
    return 0;
}

int list::remove(int key) {
    listNode *node = getNewNode();
    if (find(key, node)) {
        listNode *temp = node->next;
        if (node->next == node) {
            node->next = _listHead;
            _listHead = _listHead->next;
        } else {
            node->next = temp->next;
            temp->next = temp->next->next;
        }
        deleteListNode(node->next);
        deleteListNode(node);
    } else {
        deleteListNode(node);
        return -1;
    }
    return 0;
}

void list::show() {
    // if use $./a.out | c++filt -t 
    // cout << "type : " << typeid(*this).name();
    cout << "type : list";
    cout << ", length : " << length << endl;
    cout << "[ ";
    for (listNode *node = _listHead; node; node = node->next) {
        if (node == _listHead) cout << "(" << node->key << " : " << node->value << ")";
        else cout << ", (" << node->key << " : " << node->value << ")";
    }
    cout << " ]" << endl;
    return ;
}

listNode *list::getNewNode(int key, int val, listNode *next) {
    listNode *new_node = new listNode;
    new_node->key = key;
    new_node->value = val;
    new_node->next = next;
    length++;
    return new_node;
}

void list::deleteListNode(listNode *node) {
    length--;
    delete node;
    return ; 
}

void list::clean(listNode *node) {
    if (node == NULL) return ;
    if (node->next) {
        clean(node->next);
    }
    deleteListNode(node);
    return ;
}

#ifdef DEBUG
int main() {
    list *num_list = new list;
    for (int i = 9; i >= 0; --i) {
        num_list->insert(i, rand());
        num_list->remove(i);
    }
    num_list->show();
    
    cout << "update: " << num_list->update(1, 1) << endl;
    num_list->insert(1, 2);
    num_list->show();

    int key = 5;
    if (num_list->remove(key)) {
        cout << "num_list remove error!" << endl;    
    }
    num_list->show();
    delete num_list;
    return 0;
}
#endif
