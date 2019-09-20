/*************************************************************************
	> File Name: skipsList.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 六  9/14 22:28:47 2019
 ************************************************************************/

#ifndef _SKIPSLIST_H
#define _SKIPSLIST_H

#include <iostream>
#include "baseList/list.h"
#include "baseList/skipNode.h"

#define MAXSTEP 4

class skipsList : public list {
public:
    skipsList(int step = MAXSTEP);
    ~skipsList();
    void initialize();

    bool find(int key, listNode *node, skipListNode **skipNode = NULL);
    int update(int key, int val);
    int insert(int key, int val);
    int remove(int key);
    
    template <typename T>
    void show_list(T *node);
    void show(); 
    
    template <typename T>
    void show_node(T *node = NULL);

    skipListNode *getSkipListHead();
    listNode *getListHead();

private:
    skipListNode **getNewSkips();
    skipListNode *getNewSkipNode( 
            int level = 1, 
            listNode *down = NULL, 
            skipListNode *next = NULL
            );
    void deleteSkips(skipListNode **, int end = 0);
    void deleteSkipListNode(skipListNode *skipNode, int level);
    void skipsClean(skipListNode *skipNode);
    skipListNode *find_skipList(int key, skipListNode *node, int level);
    listNode *find_list(int key, listNode *node, int level = 0);
    bool merge_skipNode(skipListNode *currentNode, int level);
    int add_level();
    void minus_level();

private:
    skipListNode *_skipListHead;
    int *skipLength;
    int level;
    int step;
};

#endif
