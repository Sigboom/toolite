/*************************************************************************
	> File Name: skip_list.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 五  9/ 6 18:18:02 2019
 ************************************************************************/

#include <iostream>
#include "list.h"

#define MAXSTEP 4

class skipListNode : public listNode {
public:
    int count;
    //TODO next与基类出现冲突，建议采用函数模板或改成访问者模式
    //暂时采用的是函数模板，未完美解决该问题（变量依然被覆盖）
    skipListNode *next;
    listNode *down;
};

class skipList : public list {
public:
    skipList(int step = MAXSTEP) :
        step(step), skipLength(0),
        _skipListHead(NULL) {
        }
    
    ~skipList() {    
        skipClean(_skipListHead);
    }

    void initialize() {
        skipClean(_skipListHead);
        _skipListHead = NULL;
        _listHead = _listEnd = NULL;
        step = MAXSTEP;
        length = 0;
        return ;
    }

    listNode *find_list(int key, listNode *node) {
        while (node->next) {
            if (node->next->key >= key) break;
            node = node->next;
        }
        return node;
    }
    
    bool find(int key, listNode *node, skipListNode *skipNode) {
        skipListNode vir;
        vir.next = _skipListHead;
        
        skipNode->next = dynamic_cast<skipListNode *>(find_list(key, &vir));
        if (skipNode->next == NULL) {
            cout << "find err" << endl;
            return false;
        }
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

    void insert(int key, int val) final {
        if (skipLength == 0) {
            _listHead = getNewNode(key, val);
            _listEnd = _listHead;
            _skipListHead = getNewSkipNode(key, val, _listHead);
            return ;
        }
        
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
            deleteSkipListNode(skipNode);
            deleteListNode(node);
            return ;
        } else {
            //将跳跃节点前移一位，该处理方法遇顺序插入易退化，需要优化
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
                    skipNode->down = skipNode->next->down->next;
                    skipListNode *skipTemp = skipNode->next;
                    skipNode->next = skipTemp->next;
                    skipTemp->next = skipNode;
                }
                listNode *temp = node->next;
                node->next = temp->next;
                temp->next = node;
            }
        }
        return ;
    }
    
    template <typename T>
    void show_list(T *node) {
        cout << "[ ";
        for (T *p = node; p; p = p->next) {
            if (p == node) cout << "(";
            else cout << ", (";
            cout << node->key <<" : "<< node->value << ")";
        }
        cout << " ]" << endl;
        return ;
    }

    void show() {
        cout << "type : skipList";
        cout << ", step : " << step;
        cout << ", skipLength : " << skipLength << endl;
        show_list(_skipListHead);
        cout << "type: list";
        cout << ", length : " << length << endl;
        show_list(_listHead);
        return ;
    }
   
    void show_node(listNode *node = NULL) {
        if (node == NULL) {
            node = _listHead;
            cout << "_listHead->next : " << _listHead->next << endl;
            cout << node->next << endl;
        }
        cout << "type : " << typeid(*node).name() << endl;
        cout << node->key << " : " << node->value << endl;
        cout << "node->next : ";
        cout << node->next << endl;
        return ;
    }
private:
    skipListNode *getNewSkipNode(int key = 0, int val = 0, 
            listNode *down = NULL, skipListNode *next = NULL) {
        skipListNode *new_node = new skipListNode;
        new_node->key = key;
        new_node->value = val;
        new_node->count = 1;
        new_node->down = down;
        new_node->next = next;
        skipLength++;
        return new_node;
    }

    void deleteSkipListNode(skipListNode *skipNode) {
        skipLength--;
        delete skipNode;
        return ;
    }
    
    void skipClean(skipListNode *skipNode) {
        if (skipNode == NULL) return ;
        if (skipNode->next) {
            skipClean(skipNode->next);
        }
        deleteSkipListNode(skipNode);
        return ;
    }

private:
    skipListNode *_skipListHead;
    int skipLength;
    int step;
};

int main() {
    skipList *num_skip = new skipList;
    for (int i = 0; i < 1; ++i) {
        num_skip->insert(i, rand());
    }
    //num_skip->show_node();
    num_skip->show();
    delete num_skip;
    return 0;
}
