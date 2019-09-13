/*************************************************************************
	> File Name: list_node.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 五  9/13 11:45:33 2019
 ************************************************************************/

#ifndef _LIST_NODE_H
#define _LIST_NODE_H

#include <iostream>

class listNode {
public:
    listNode(int key = 0, int value = 0, listNode *next = NULL);
    virtual ~listNode(){}
    void show_node();
    
    virtual int get_key();
    virtual int get_value();
    virtual listNode *get_next();

    virtual void set_key(int key);
    virtual void set_value(int value);
    virtual void set_next(listNode *next);
    
protected:
    listNode *next;

private:
    int key;
    int value;
};

#endif
