/*************************************************************************
	> File Name: skipsList.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 六  9/14 22:28:01 2019
 ************************************************************************/

#include "skipsList.h"

using std::cout;
using std::endl;

skipsList::skipsList(int step) :
    _skipListHead(NULL), skipLength(NULL), step(step), level(0) {}

skipsList::~skipsList() {    
    skipsClean(_skipListHead);
    delete[] skipLength;
}

void skipsList::initialize() {
    skipsClean(_skipListHead);
    _skipListHead = NULL;
    _listHead = NULL;
    step = MAXSTEP;
    length = 0;
    return ;
}

bool skipsList::merge_skipNode(skipListNode *currentNode, int level) {
    bool flag = false;
    while (currentNode->get_next() && 
            currentNode->get_count() + currentNode->get_next()->get_count() <= step) {
        skipListNode *deleteNode = currentNode->get_next();
        currentNode->set_next(deleteNode->get_next());
        currentNode->set_count(currentNode->get_count() + deleteNode->get_count());
        deleteSkipListNode(deleteNode, level);
        flag = true;
    }
    return flag;
}
skipListNode *skipsList::find_skipList(int key, skipListNode *node, int level) {
    while (node->get_next()) {
        merge_skipNode(node->get_next(), level);
        if (node->get_next()->get_key() >= key) break;
        node = node->get_next();
    }
    return node; 
}

listNode *skipsList::find_list(int key, listNode *node, int level) {
    if (level) return  find_skipList(key, dynamic_cast<skipListNode *>(node), level);
    while (node->get_next()) {
        if (node->get_next()->get_key() >= key) break;
        node = node->get_next();
    }
    return node;
}

bool skipsList::find(int key, listNode *node, skipListNode **skips) {
    if (_listHead == NULL) return false;
    if (_skipListHead == NULL) {
        listNode vir;
        vir.set_next(_listHead);
        node->set_next(find_list(key, &vir));
        if (node->get_next() == &vir) {
            node->set_next(node);
        } else if (node->get_next()->get_next())
            return node->get_next()->get_next()->get_key() == key;
        return false;
    }
    skipListNode vir;
    vir.set_next(_skipListHead);
   
    for (int i = level - 1; i >= 0; --i) {
        if (i == level - 1) {
            skips[i]->set_next(find_list(key, &vir, level));
            if (skips[i]->get_next() == &vir) {
                //如果返回最上层跳点指向自己，则需更新头结点
                skips[i]->set_next(skips[i]);
                return _skipListHead->get_key() == key; 
            }
        } else skips[i]->set_next(find_list(key, skips[i + 1]->get_next()->get_down(), i + 1));
    }
    //(skipNode->get_next()->get_next()->get_key() == key) 情况需优化
    
    node->set_next(find_list(key, skips[0]->get_next()->get_down()));
    if (node->get_next()->get_next())
        return node->get_next()->get_next()->get_key() == key;
    
    return false;
}

int skipsList::update(int key, int val) {
    if (length == 0) return -1;
    int res = -1;
    skipListNode **skips = getNewSkips();
    listNode *node = getNewNode(key, val);
    if (find(key, node, skips)) {
        if (skips[level - 1]->get_next() == skips[level - 1]) {
            skipListNode *skipNode = _skipListHead;
            for (int i = 0; i < level; ++i) {
                skipNode->set_value(val);
                ++i;
                if (i >= level) break;
                skipNode = dynamic_cast<skipListNode *>(skipNode->get_down());
            }
            _listHead->set_value(val);
        } else {
            for (int i = 0; i < level; ++i) {
                if (skips[i]->get_next()->get_next() &&
                        skips[i]->get_next()->get_next()->get_key() == key) {
                    skips[i]->get_next()->get_next()->set_value(val);
                }
            }
            node->get_next()->get_next()->set_value(val);
        }
        res = 0;
    }
    deleteSkips(skips);
    deleteListNode(node);
    return res;
}
skipListNode **skipsList::getNewSkips() {
    skipListNode **newSkips = new skipListNode*[level];
    for (int i = 0; i < level; ++i) {
        newSkips[i] = getNewSkipNode(i + 1);
    }
    return newSkips;
}

//应该0对应最底层（1层）跳表。
void skipsList::deleteSkips(skipListNode **skips, int end) {
    for (int i = level - 1; i >= end; --i)  {
        deleteSkipListNode(skips[i], i + 1);
    }
    delete skips;
    return ;
}

int skipsList::add_level() {
    for (skipListNode *skipNode = _skipListHead; skipNode; skipNode = skipNode->get_next()) {
        merge_skipNode(skipNode, level);
    }
    //存在合并应该就可以返回
    if (skipLength && skipLength[level - 1] < step) return level;
    int *newSkipLength = new int[level + 1]();
    for (int i = 0; i < level; ++i) {
        newSkipLength[i] = skipLength[i];
    }
    level++;
    if (skipLength) delete skipLength;
    skipLength = newSkipLength;
    
    skipListNode *skipsNode = getNewSkipNode(level, _skipListHead);
    if (_skipListHead == NULL) skipsNode->set_down(_listHead);
    else skipsNode->set_down(_skipListHead); 
    _skipListHead = skipsNode;
    _skipListHead->set_count(step);
    return level;
}

int skipsList::insert(int key, int val) {
    listNode *node = getNewNode(key, val);
    if (length == 1) {
        _listHead = node;
        return 0;
    }
    
    if (length <= step) {
        if (find(key, node)) {
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
            if (length == step) add_level();
            return 0;
        }
    }
    
    skipListNode **skips = getNewSkips();
    if (find(key, node, skips)) {    
        deleteSkips(skips);
        deleteListNode(node);
        return -1;
    } 
    /*
     * 将跳跃节点前移一位，该处理方法遇顺序插入易退化，需要优化
     * 已使用merge_skipNode优化
     */
    int end = 0;
    if (skips[level - 1]->get_next() == skips[level - 1]) {
        //待插入节点为头结点
        node->set_next(_listHead);
        _listHead = node;
        skips[level - 1]->set_next(_skipListHead);
        
        for (int i = level - 2; i >= 0; --i) {
            skips[i]->set_next(skips[i + 1]->get_next()->get_down());
        }
        
        if (skips[0]->get_next()->get_count() < step) {
            skips[0]->get_next()->add_count();
            skips[0]->get_next()->set_down(node);
        } else {
            skips[0]->set_down(node);
            int j = 1;
            for (; j < level && skips[j]->get_next()->get_count() >= step; ++j) {
                skips[j]->set_down(skips[j - 1]);
            }
            if (j == level) {
                _skipListHead = skips[level - 1];
                end = level;
            } else {
                skips[j]->get_next()->add_count();
                skips[j]->get_next()->set_down(skips[j - 1]);
                end = j;
            }
        }
    } else {
        //待插入节点不是头结点
        listNode *temp = node->get_next();
        node->set_next(temp->get_next());
        temp->set_next(node);
        
        int i = 0;
        for (; i < level && skips[i]->get_next()->get_count() >= step; ++i) {
            skipListNode *skipTemp = skips[i]->get_next();
            listNode *skipDown = skipTemp->get_down();
            for (int i = 0; i < skipTemp->get_count(); ++i) 
                skipDown = skipDown->get_next();
            skips[i]->set_down(skipDown);
            skips[i]->set_next(skipTemp->get_next());
            skipTemp->set_next(skips[i]);
        }
        end = i;
        if (end != level) skips[i]->get_next()->add_count();
    }
    deleteSkips(skips, end);
    //加判断应该能提速
    if (skipLength[level - 1] >= step) add_level();
    return 0;
}

template <typename T>
void skipsList::show_list(T *node) {
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

void skipsList::show() {
    skipListNode *skipNode = _skipListHead;
    for (int i = 0;
            i < level && skipNode;
            ++i, skipNode = dynamic_cast<skipListNode *>(skipNode->get_down())) {
        cout << "type : skipList";
        cout << ", level : " << level - i;
        cout << ", step : " << step;
        cout << ", skipLength["<< level - i - 1 << "] : " << skipLength[level - i - 1] << endl;
        show_list(skipNode);
    }
    cout << "type: list";
    cout << ", length : " << length << endl;
    show_list(_listHead);
    return ;
}

template <typename T>
void skipsList::show_node(T *node) {
    if (node == NULL) node = _listHead;
    cout << "node address: " << node << endl;
    cout << "type : " << typeid(*node).name() << endl;
    cout << node->get_key() << " : " << node->value << endl;
    cout << "node->get_next() : ";
    cout << node->get_next() << endl;
    return ;
}

skipListNode *skipsList::getSkipListHead() {
    return this->_skipListHead;
}

listNode *skipsList::getListHead() {
    return this->_listHead;
}

//删除未完成
int skipsList::remove(int key) {
    listNode *node = getNewNode();
    skipListNode **skips = getNewSkips();
    int res = -1;
    if (find(key, node, skips)) {
        listNode *temp = node->get_next();
        skipListNode *skipTemp = skips[level - 1]->get_next();
        if (skipTemp == skips[level - 1]) {
            //TODO 删除的是头结点
            skips[level - 1]->set_next(_skipListHead);
            skipTemp = skips[level - 1]->get_next();
            if (!_skipListHead->minus_count()) {
                _skipListHead = _skipListHead->get_next();
                deleteSkipListNode(skipTemp);
            }  else
                _skipListHead->set_down(_skipListHead->get_down()->get_next());
            node->set_next(_listHead);
            _listHead = _listHead->get_next();
        } else {
            //删除的不是头结点
            if (skipTemp->get_next() && skipTemp->get_next()->get_down() == temp->get_next()) {
                if(!skipTemp->get_next()->minus_count()) {
                    skipListNode *skipDeleteNode = skipTemp->get_next();
                    skipTemp->set_next(skipDeleteNode->get_next());
                    deleteSkipListNode(skipDeleteNode);
                } else {
                    skipTemp->get_next()->set_down(skipTemp->get_next()->get_down()->get_next());
                }
            } else {
                skipTemp->minus_count();
            }
            node->set_next(temp->get_next());
            temp->set_next(temp->get_next()->get_next());
        }
        deleteListNode(node->get_next());
        res = 0;
    }
    deleteSkips(skips);
    deleteListNode(node);
    return res;
}

skipListNode *skipsList::getNewSkipNode( 
        int level, listNode *down, skipListNode *next) {
    skipListNode *new_node = new skipListNode(down, next);
    new_node->set_count();
    skipLength[level - 1]++;
    return new_node;
}

void skipsList::deleteSkipListNode(skipListNode *skipNode, int level) {
    skipLength[level - 1]--;
    delete skipNode;
    skipNode = NULL;
    return ;
}

void skipsList::skipsClean(skipListNode *skipNode) {
    if (skipNode == NULL) return ;
    skipListNode *deleteNode;
    for (; skipNode; ) {
        while (skipNode->get_next()) {
            deleteNode = skipNode->get_next();
            skipNode->set_next(skipNode->get_next()->get_next());
            deleteSkipListNode(deleteNode, level);
        }
        deleteNode = skipNode;
        skipNode = dynamic_cast<skipListNode *>(skipNode->get_down());
        deleteSkipListNode(deleteNode, level);
        level--;
    }
    return ;
}

int main() {
    skipsList *num_skip = new skipsList;
    for (int i = 17; i > 0; --i) {
        num_skip->insert(i, rand());
    }
    num_skip->show();
    
    cout << "update: " << num_skip->update(14, 5) << endl;
    num_skip->show();
    
    int key = 7;
    cout << "remove : " << num_skip->remove(key) << endl;
    num_skip->show();
    
    delete num_skip;
    return 0;
}
