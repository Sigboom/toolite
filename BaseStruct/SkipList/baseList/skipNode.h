/*************************************************************************
	> File Name: skipListNode.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 五  9/13 21:14:00 2019
 ************************************************************************/

#ifndef _SKIPLISTNODE_H
#define _SKIPLISTNODE_H

#include <iostream>
#include "listNode.h"

class skipListNode : public listNode {
public:
    skipListNode(listNode *down = NULL, skipListNode *next = NULL);

    void show_node();

    int get_key();
    int get_value();
    int get_count();
    listNode *get_down();
    skipListNode *get_next();
        
    void set_key(int key);
    void set_value(int value);
    void set_count(int count = 1);
    int add_count();
    int minus_count();
    void set_down(listNode *down);
    
private:
    int count;
    listNode *down;
};
#endif
