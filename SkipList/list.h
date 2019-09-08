/*************************************************************************
	> File Name: list.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 五  9/ 6 18:20:05 2019
 ************************************************************************/

#ifndef _LIST_H
#define _LIST_H

#include <iostream>
#include <typeinfo>

using std::cout;
using std::cin;
using std::endl;

#ifndef _LISTNODE
#define _LISTNODE

class listNode {
public:
    virtual ~listNode(){}
    int key;
    int value;
    listNode *next;
};

#endif

/* list:
 * 已实现操作:
 *  initialize() 将链表初始化
 *  find(int key, listNode *node = NULL) 根据key查找节点位置: node->next指向所寻key的前一个节点, 另请看该函数前注释
 *  insert(int key, int val) 插入一个节点并自动排序(依据key从小到大)
 *  remove(int key) 根据key删除一个节点; 成功返回0, 失败返回-1
 *  show() 显示list基本信息
 */

class list {
public:
    list();
    virtual ~list();
    
    virtual void initialize();
    
    /* Define date: 2019.9.6
     * Author: Doni Daniel   
     * find():
     *  返回key是否存在，node->next指向所寻key的前一个节点
     *  若node->next == node 所寻key在头指针，即要操作头指针
     *  若node->next == NULL 所寻key在链表尾，即要操作的位置在链表后一个节点
     */
    virtual bool find(int key, listNode *);
    
    virtual void insert(int key, int val);
    int remove(int key);
    void show();
    
protected:
    listNode *getNewNode(int key = 0, int val = 0, listNode *next = NULL);
    void deleteListNode(listNode *node);
    void clean(listNode *_listNode);
    
protected:
    int length;
    listNode *_listHead;
    listNode *_listEnd;
};
    

#endif
