/*************************************************************************
	> File Name: skip_list.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 一  9/ 9 11:35:31 2019
 ************************************************************************/

#ifndef _SKIP_LIST_H
#define _SKIP_LIST_H

#include <iostream>
#include "list.h"

#define MAXSTEP 4

#ifndef SKIP_LIST_NODE
#define SKIP_LIST_NODE
class skipListNode : public listNode {
public:
    void show_node() {
        cout << count << " : " << key << " : "<< value;
        return ;
    }
    
public:
    int count;
    skipListNode *next;
    listNode *down;
};

#endif

class skipList : public list {
public:
    skipList(int step = MAXSTEP);
    ~skipList();
    void initialize();

    skipListNode *find_skipList(int key, skipListNode *node);
    listNode *find_list(int key, listNode *node);
    bool find(int key, listNode *node, skipListNode *skipNode);

    int update(int key, int val) final;
    int insert(int key, int val) final;
    
    template <typename T>
    void show_list(T *node);
    void show(); 
    
    template <typename T>
    void show_node(T *node = NULL);

    skipListNode *getSkipListHead();
    listNode *getListHead();

    void linkDownNode(skipListNode *skipNode, listNode *node);
    int remove(int key) final;

private:
    skipListNode *getNewSkipNode(int key = 0, int val = 0, 
            listNode *down = NULL, skipListNode *next = NULL);
    void deleteSkipListNode(skipListNode *skipNode);
    void skipClean(skipListNode *skipNode);
    void merge_skipNode(skipListNode *currentNode);

private:
    skipListNode *_skipListHead;
    int skipLength;
    int step;
};

#endif
