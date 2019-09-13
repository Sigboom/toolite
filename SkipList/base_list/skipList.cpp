/*************************************************************************
	> File Name: skip_list.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 五  9/ 6 18:18:02 2019
 ************************************************************************/

#include "skipList.h"

skipList::skipList(int step) :
    _skipListHead(NULL), skipLength(0), step(step) {
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
        while (currentNode->get_next() &&
                currentNode->get_count() + currentNode->get_next()->get_count() <= step) {
            skipListNode *deleteNode = currentNode->get_next();
            currentNode->set_next(deleteNode->get_next());
            currentNode->set_count(currentNode->get_count() + deleteNode->get_count());
            deleteSkipListNode(deleteNode);
        }
}

skipListNode *skipList::find_skipList(int key, skipListNode *node) {
    while (node->get_next()) {
        //是否有更好的代码结构?
        if (node->get_next()->get_key() >= key) break;
        merge_skipNode(node->get_next());
        node = node->get_next();
    }
    return node; 
}

listNode *skipList::find_list(int key, listNode *node) {
    while (node->get_next()) {
        if (node->get_next()->get_key() >= key) break;
        node = node->get_next();
    }
    return node;
}

bool skipList::find(int key, listNode *node, skipListNode *skipNode) {
    if (_skipListHead == NULL) return false;
    skipListNode vir;
    vir.set_next(_skipListHead);
    
    skipNode->set_next(find_skipList(key, &vir));
    if (skipNode->get_next() == &vir) {
        skipNode->set_next(skipNode);
        return _skipListHead->get_key() == key;
    } 
    //(skipNode->get_next()->get_next()->get_key() == key) 情况需优化
    
    node->set_next(find_list(key, skipNode->get_next()->get_down()));
    if (node->get_next()->get_next())
        return node->get_next()->get_next()->get_key() == key;
    else return false;
}

int skipList::update(int key, int val) {
    if (skipLength == 0) return -1;
    int res = -1;
    skipListNode *skipNode = getNewSkipNode();
    listNode *node = getNewNode(key, val);
    if (find(key, node, skipNode)) {
        if (skipNode->get_next() == skipNode) {
            _skipListHead->set_value(val);
            _skipListHead->get_down()->set_value(val);
        } else {
            if (skipNode->get_next()->get_next() &&
                    skipNode->get_next()->get_next()->get_down() == node->get_next()->get_next())
                skipNode->get_next()->get_next()->set_value(val);
            node->get_next()->get_next()->set_value(val);
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
        _skipListHead = getNewSkipNode(_listHead);
        return 0;
    }
    
    skipListNode *skipNode = getNewSkipNode();
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
    if (skipNode->get_next() == skipNode) {
        //待插入节点为头结点
        if (_skipListHead->get_count() < step) {
            _skipListHead->add_count();
            _skipListHead->set_down(node);
            deleteSkipListNode(skipNode);
        } else {
            skipNode->set_next(_skipListHead);
            _skipListHead = skipNode;
            skipNode->set_down(node);
        }
        node->set_next(_listHead);
        _listHead = node;
    } else {
        //待插入节点不是头结点  
        if (skipNode->get_next()->get_count() < step) {
            skipNode->get_next()->add_count();
            deleteSkipListNode(skipNode);
        } else {
            skipNode->set_count(skipNode->get_next()->get_count());
            skipNode->get_next()->set_count();
            skipNode->set_down(skipNode->get_next()->get_down()->get_next());
            skipListNode *skipTemp = skipNode->get_next();
            skipNode->set_next(skipTemp->get_next());
            skipTemp->set_next(skipNode);
        }
        listNode *temp = node->get_next();
        node->set_next(temp->get_next());
        temp->set_next(node);
    }
    return 0;
}

template <typename T>
void skipList::show_list(T *node) {
    cout << "[ ";
    for (T *p = node; p; p = p->get_next()) {
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
    cout << node->get_key() << " : " << node->value << endl;
    cout << "node->get_next() : ";
    cout << node->get_next() << endl;
    return ;
}

skipListNode *skipList::getSkipListHead() {
    return this->_skipListHead;
}

listNode *skipList::getListHead() {
    return this->_listHead;
}

int skipList::remove(int key) {
    listNode *node = getNewNode();
    skipListNode *skipNode = getNewSkipNode();
    int res = -1;
    if (find(key, node, skipNode)) {
        listNode *temp = node->get_next();
        skipListNode *skipTemp = skipNode->get_next();
        if (skipNode->get_next() == skipNode) {
            //删除的是头结点
            skipNode->set_next(_skipListHead);
            if (!_skipListHead->minus_count()) {
                _skipListHead = _skipListHead->get_next();
                deleteSkipListNode(skipNode->get_next());
            }  else
                _skipListHead->set_down(_skipListHead->get_down()->get_next());
            node->set_next(_listHead);
            _listHead = _listHead->get_next();
        } else {
            //删除的不是头结点
            if (skipTemp->get_next()->get_down() == temp->get_next()) {
                if(!skipTemp->get_next()->minus_count()) {
                    skipListNode *skipDeleteNode = skipTemp->get_next();
                    skipTemp->set_next(skipDeleteNode->get_next());
                    deleteSkipListNode(skipDeleteNode);
                } else {
                    skipTemp->get_next()->set_down(skipTemp->get_next()->get_down()->get_next());
                }
            } else skipTemp->minus_count();
            node->set_next(temp->get_next());
            temp->set_next(temp->get_next()->get_next());
        }
        deleteListNode(node->get_next());
        res = 0;
    }
    deleteSkipListNode(skipNode);
    deleteListNode(node);
    return res;
}

skipListNode *skipList::getNewSkipNode(
        listNode *down, skipListNode *next) {
    skipListNode *new_node = new skipListNode(down, next);
    new_node->set_count();
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
    if (skipNode->get_next()) {
        skipClean(skipNode->get_next());
    }
    deleteSkipListNode(skipNode);
    return ;
}

int main() {
    skipList *num_skip = new skipList;
    for (int i = 0; i < 10; ++i) {
        num_skip->insert(i, rand());
    }
    //num_skip->show_node(num_skip->getListHead());
    num_skip->show();
    int key = 7;
    //remove函数出现段错误，待改正
    //cout << "remove : " << num_skip->remove(key) << endl;
    num_skip->show();
    delete num_skip;
    return 0;
}
