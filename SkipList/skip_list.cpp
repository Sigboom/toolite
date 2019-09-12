/*************************************************************************
	> File Name: skip_list.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 五  9/ 6 18:18:02 2019
 ************************************************************************/

#include "skip_list.h"

skipList::skipList(int step) :
    step(step), skipLength(0),
    _skipListHead(NULL) {
    }

skipList::~skipList() {    
    skipClean(_skipListHead);
}

void skipList::initialize() {
    skipClean(_skipListHead);
    _skipListHead = NULL;
    _listHead = NULL;
    step = MAXSTEP;
    length = 0;
    return ;
}

void skipList::merge_skipNode(skipListNode *currentNode) {
        while (currentNode->next && currentNode->count + currentNode->next->count <= step) {
            skipListNode *deleteNode = currentNode->next;
            currentNode->next = deleteNode->next;
            currentNode->count += deleteNode->count;
            deleteSkipListNode(deleteNode);
        }
}

skipListNode *skipList::find_skipList(int key, skipListNode *node) {
    while (node->next) {
        //是否有更好的代码结构?
        if (node->next->key >= key) break;
        merge_skipNode(node->next);
        node = node->next;
    }
    return node; 
}

listNode *skipList::find_list(int key, listNode *node) {
    while (node->next) {
        if (node->next->key >= key) break;
        node = node->next;
    }
    return node;
}

bool skipList::find(int key, listNode *node, skipListNode *skipNode) {
    if (_skipListHead == NULL) return false;
    skipListNode vir;
    vir.next = _skipListHead;
    
    skipNode->next = find_skipList(key, &vir);
    if (skipNode->next == &vir) {
        skipNode->next = skipNode;
        return _skipListHead->key == key;
    } 
    //(skipNode->next->next->key == key) 情况需优化
    
    node->next = find_list(key, skipNode->next->down);
    if (node->next->next)
        return node->next->next->key == key;
    else return false;
}

int skipList::update(int key, int val) {
    if (skipLength == 0) return -1;
    int res = -1;
    skipListNode *skipNode = getNewSkipNode(key, val);
    listNode *node = getNewNode(key, val);
    if (find(key, node, skipNode)) {
        if (skipNode->next == skipNode) {
            _skipListHead->value = val;
            _skipListHead->down->value = val;
        } else {
            if (skipNode->next->next &&
                    skipNode->next->next->down == node->next->next)
                skipNode->next->next->value = val;
            node->next->next->value = val;
        }
        res = 0;
    }
    deleteSkipListNode(skipNode);
    deleteListNode(node);
    return res;
}

int skipList::insert(int key, int val) {
    if (skipLength == 0) {
        _listHead = getNewNode(key, val);
        _skipListHead = getNewSkipNode(key, val, _listHead);
        return 0;
    }
    
    skipListNode *skipNode = getNewSkipNode(key, val);
    listNode *node = getNewNode(key, val);
    if (find(key, node, skipNode)) {
        deleteSkipListNode(skipNode);
        deleteListNode(node);
        return -1;
    } 
    /*
     * 将跳跃节点前移一位，该处理方法遇顺序插入易退化，需要优化
     * 已使用merge_skipNode优化
     */
    if (skipNode->next == skipNode) {
        //待插入节点为头结点
        if (_skipListHead->count < step) {
            _skipListHead->count++;
            _skipListHead->key = key;
            _skipListHead->value = val;
            _skipListHead->down = node;
            deleteSkipListNode(skipNode);
        } else {
            skipNode->next = _skipListHead;
            _skipListHead = skipNode;
            skipNode->down = node;
        }
        node->next = _listHead;
        _listHead = node;
    } else {
        //待插入节点不是头结点  
        if (skipNode->next->count < step) {
            skipNode->next->count++;
            deleteSkipListNode(skipNode);
        } else {
            skipNode->count = skipNode->next->count;
            skipNode->next->count = 1;
            skipNode->key = skipNode->next->down->next->key;
            skipNode->value = skipNode->next->down->next->value;
            skipNode->down = skipNode->next->down->next;
            skipListNode *skipTemp = skipNode->next;
            skipNode->next = skipTemp->next;
            skipTemp->next = skipNode;
        }
        listNode *temp = node->next;
        node->next = temp->next;
        temp->next = node;
    }
    return 0;
}

template <typename T>
void skipList::show_list(T *node) {
    cout << "[ ";
    for (T *p = node; p; p = p->next) {
        if (p == node) cout << "(";
        else cout << ", (";
        p->show_node();
        cout << ")";
    }
    cout << " ]" << endl;
    return ;
}

void skipList::show() {
    cout << "type : skipList";
    cout << ", step : " << step;
    cout << ", skipLength : " << skipLength << endl;
    show_list(_skipListHead);
    cout << "type: list";
    cout << ", length : " << length << endl;
    show_list(_listHead);
    return ;
}

template <typename T>
void skipList::show_node(T *node) {
    if (node == NULL) node = _listHead;
    cout << "node address: " << node << endl;
    cout << "type : " << typeid(*node).name() << endl;
    cout << node->key << " : " << node->value << endl;
    cout << "node->next : ";
    cout << node->next << endl;
    return ;
}

skipListNode *skipList::getSkipListHead() {
    return this->_skipListHead;
}

listNode *skipList::getListHead() {
    return this->_listHead;
}

void skipList::linkDownNode(skipListNode *skipNode, listNode *node) {
    if (skipNode == NULL || node == NULL) return ;
    skipNode->down = node;
    skipNode->key = node->key;
    skipNode->value = node->value;
    return ;
}

int skipList::remove(int key) {
    listNode *node = getNewNode();
    skipListNode *skipNode = getNewSkipNode();
    int res = -1;
    if (find(key, node, skipNode)) {
        listNode *temp = node->next;
        skipListNode *skipTemp = skipNode->next;
        if (skipNode->next == skipNode) {
            //删除的是头结点
            skipNode->next = _skipListHead;
            if (!--_skipListHead->count) {
                _skipListHead = _skipListHead->next;
                deleteSkipListNode(skipNode->next);
            }  else
                linkDownNode(_skipListHead, _skipListHead->down->next);
            node->next = _listHead;
            _listHead = _listHead->next;
        } else {
            //删除的不是头结点
            if (skipTemp->next->down == temp->next) {
                if(!--skipTemp->next->count) {
                    skipListNode *skipDeleteNode = skipTemp->next;
                    skipTemp->next = skipDeleteNode->next;
                    deleteSkipListNode(skipDeleteNode);
                } else {
                    linkDownNode(skipTemp->next, skipTemp->next->down->next);
                }
            } else skipTemp->count--;
            node->next = temp->next;
            temp->next = temp->next->next;
        }
        deleteListNode(node->next);
        res = 0;
    }
    deleteSkipListNode(skipNode);
    deleteListNode(node);
    return res;
}

skipListNode *skipList::getNewSkipNode(
        int key, int val, listNode *down, skipListNode *next) {
    skipListNode *new_node = new skipListNode;
    new_node->key = key;
    new_node->value = val;
    new_node->count = 1;
    new_node->down = down;
    new_node->next = next;
    skipLength++;
    return new_node;
}

void skipList::deleteSkipListNode(skipListNode *skipNode) {
    skipLength--;
    delete skipNode;
    skipNode = NULL;
    return ;
}

void skipList::skipClean(skipListNode *skipNode) {
    if (skipNode == NULL) return ;
    if (skipNode->next) {
        skipClean(skipNode->next);
    }
    deleteSkipListNode(skipNode);
    return ;
}

int main() {
    skipList *num_skip = new skipList;
    for (int i = 10; i >= 0; --i) {
        num_skip->insert(i, rand());
        num_skip->remove(i);
    }
    //num_skip->show_node(num_skip->getListHead());
    num_skip->show();
    int key = 7;
    cout << "remove : " << num_skip->remove(key) << endl;
    num_skip->show();
    delete num_skip;
    return 0;
}
