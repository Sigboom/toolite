#!/usr/bin/env python
# coding=utf-8
place = 100000
b = 10**(place + 10)
x1 = b * 4 // 5
x2 = b // -239
he = x1 + x2

for i in range(3, place * 2, 2):
    x1 //= -25
    x2 //= -57121
    x = (x1 + x2) // i
    he += x
pai = he * 4 // (10 * 10)
print(str(pai))
