/*************************************************************************
	> File Name: list_node.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 五  9/13 11:47:00 2019
 ************************************************************************/

#include "listNode.h"

using std::cout;

listNode::listNode(int key, int value, listNode *next) : 
    key(key), value(value) {
        this->next = next;
}

void listNode::show_node() {
    cout << key  << ":" << value;
    return ;
}

int listNode::get_key() {
    return this->key;
}

int listNode::get_value() {
    return this->value;
}

listNode *listNode::get_next() {
    return this->next;
}

void listNode::set_key(int key) {
    this->key = key;
    return ;
}

void listNode::set_value(int value) {
    this->value = value;
    return ;
}

void listNode::set_next(listNode *next) {
    this->next = next;
    return ;
}
