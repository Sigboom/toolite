/*************************************************************************
	> File Name: gtest.h
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 六  6/30 20:06:03 2018
 ************************************************************************/

#ifndef _GTEST_H
#define _GTEST_H

#include <stdlib.h>
#include <stdio.h>

struct TEST_CASE_DATA;
typedef void (*TEST_FUNC)(struct TEST_CASE_DATA *);

struct TEST_CASE {
    char *case_name;
    char *func_name;
    TEST_FUNC func;
};

struct TEST_CASE_DATA {
    int expect_cnt;
    int total;
};

struct TEST_CASE_LINK_NODE {
    struct TEST_CASE data;
    struct TEST_CASE_LINK_NODE *next;
};

struct TEST_CASE_LINK_NODE __head = {0, 0}, *__tail = &__head;

int RUN_ALL_TEST() {
    struct TEST_CASE_LINK_NODE *head = __head.next;
    while (head != NULL) {
        struct TEST_CASE_DATA data = {0, 0};
        printf("[%s, %s]\n", head->data.case_name, head->data.func_name);
        head->data.func(&data);
        printf("[ PASS ] total : %d, expect_cnt : %d\n", data.total, data.expect_cnt);
        head = head->next;
    }
    return 0;
}

#define TEST(a, b)\
void a##_##b(struct TEST_CASE_DATA *);\
__attribute__((constructor)) void ADD##a##_##b() {\
    struct TEST_CASE_LINK_NODE *temp = \
    (struct TEST_CASE_LINK_NODE *)malloc(sizeof(struct TEST_CASE_LINK_NODE)); \
    temp->data.case_name = #a; \
    temp->data.func_name = #b; \
    temp->data.func = a##_##b; \
    temp->next = NULL; \
    __tail->next = temp; \
    __tail = temp; \
} \
void a##_##b(struct TEST_CASE_DATA *__data)

#define EXPECT(a, b) { \
    __data->total += 1; \
    printf("%s == %s %s\n", #a, #b, a == b ? "True" : "False");\
    __data->expect_cnt += 1; \
}
#endif

