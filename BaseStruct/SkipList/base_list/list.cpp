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
 *  返回key是否存在，node->get_next()指向所寻key的前一个节点
 *  若node->get_next() == node 所寻key在头指针，即要操作头指针
 *  若node->get_next() == NULL 所寻key在链表尾，即要操作的位置在链表后一个节点
 */
bool list::find(int key, listNode *node = NULL) {
    listNode vir;
    vir.set_next(_listHead);
    listNode *p;
    for (p = &vir; p->get_next(); p = p->get_next()) {
        if (p->get_next()->get_key() >= key) {
            if(node) {
                if (p != &vir) node->set_next(p);
                else node->set_next(node);
            }
            return p->get_next()->get_key() == key;
        } 
    }
    node->set_next(p);
    return false; 
}

int list::update(int key, int val) {
    if (length == 0) return -1;
    listNode *node = getNewNode(key, val);
    
    if(find(key, node)) {
        if (node->get_next() == node) {
            _listHead->set_value(val);
        } else node->get_next()->get_next()->set_value(val); 
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
        if (node->get_next() == node) {
            node->set_next(_listHead);
            _listHead = node;
        } else {
            listNode *temp = node->get_next();
            node->set_next(temp->get_next());
            temp->set_next(node);
        }
    }
    return 0;
}

int list::remove(int key) {
    listNode *node = getNewNode();
    if (find(key, node)) {
        listNode *temp = node->get_next();
        if (node->get_next() == node) {
            node->set_next(_listHead);
            _listHead = _listHead->get_next();
        } else {
            node->set_next(temp->get_next());
            temp->set_next(temp->get_next()->get_next());
        }
        deleteListNode(node->get_next());
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
    for (listNode *node = _listHead; node; node = node->get_next()) {
        if (node == _listHead) cout << "(" << node->get_key() << " : " << node->get_value() << ")";
        else cout << ", (" << node->get_key() << " : " << node->get_value() << ")";
    }
    cout << " ]" << endl;
    return ;
}

listNode *list::getNewNode(int key, int val, listNode *next) {
    listNode *new_node = new listNode(key, val, next);
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
    if (node->get_next()) {
        clean(node->get_next());
    }
    deleteListNode(node);
    return ;
}

#ifdef DEBUG
int main() {
    list *num_list = new list;
    for (int i = 9; i >= 0; --i) {
        num_list->insert(i, rand());
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
