/*************************************************************************
	> File Name: skipListNode.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 五  9/13 21:07:42 2019
 ************************************************************************/

#include "skipNode.h"

using std::cout;

skipListNode::skipListNode(listNode *down, skipListNode *next) :
    down(down) {
    set_next(next);
}

void skipListNode::show_node() {
    cout << count << " : " << get_key() << " : "<< get_value();
    return ;
}

int skipListNode::get_key() {
    if (!down) return -1;
    return this->down->get_key();
}

int skipListNode::get_value() {
    if (!down) return -1;
    return this->down->get_value();
}

int skipListNode::get_count() {
    return this->count;
}

listNode *skipListNode::get_down() {
    return this->down;
}

skipListNode *skipListNode::get_next() {
    return dynamic_cast<skipListNode *>(this->next);
}

void skipListNode::set_key(int key) {
    if(!down) return ;
    this->down->set_key(key);
    return ;
}

void skipListNode::set_value(int value) {
    if(!down) return ;
    this->down->set_value(value);
    return ;
}

void skipListNode::set_count(int count) {
    this->count = count;
    return ;
}

int skipListNode::add_count() {
    return ++count;
}

int skipListNode::minus_count() {
    return --count;
}

void skipListNode::set_down(listNode *down) {
    this->down = down;
}
