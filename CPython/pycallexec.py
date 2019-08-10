#!/usr/bin/env python
# coding=utf-8
import commands
import os

//first method 
main = "./C++_exe.o"
if os.path.exists(main):
    rc, out = commands.getstatusoutput(main)
    print('rc = %d, out = %s' % (rc, out))

//second method
print('*' * 10)
f = os.popen(main)
data = f.readlines()
f.close()
print(data)

//third method
print('*' * 10)
os.system(main)
