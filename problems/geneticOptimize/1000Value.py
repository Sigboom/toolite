#!/usr/bin/env python
# coding=utf-8

import matplotlib.pyplot as plt
import numpy as np
import random 

y = []
num = 3
x = np.linspace(0, num, num)
volatilityRate = 0.5
randTemp = 9999999

i = 1
while True:
    randNum = random.random()
    randValue = randNum * np.log(num / i)  * volatilityRate + 10000
    if i == 1:
        y.append(randValue)
        randTemp = randValue
        print(randTemp)
    elif randTemp < randValue:
        y.append(randValue)
        randTemp = randValue
        print(randTemp)
    else:
        print(randTemp)
        continue
    i += 1
    if (len(y) >= num): break;

plt.plot(x, y)
plt.show()

print(y)
