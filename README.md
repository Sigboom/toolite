# toolite
some little tool for work.

##开发文本对比工具
###解决问题
1. 课堂上存在跟不上打代码速度的问题，勉强跟上又发现产生很多小问题，100左右行的代码找起来很麻烦，想开发这个工具。 
- github的 diff 一样, 能够对比两个文件的不同信息。
###功能描述
- diff [-c] fileName1 fileName2
    对于file2, 在file1中的不同字符。输出提示信息.
    -c 生成合并文件（文件内不同的地方用注释标识出来）

##实现日志（18.7.30）
- fopen函数打开一个文件后，将文件指针赋值给另一文件指针无法记录位置,即打开一次文件只能获取一个文件读取（写入）指针，变换文件指针位置使用fseek()函数

##发现命令（18.7.31）
- 了解到调整文件指针使用fseek()/fwind()两个函数<br>
记录文件指针位置使用fgetpos(stream, &filepos)/fsetpos(stream, &filepos)/ftell(stream).<br>使用的类型是fpos_t.
- 发现存在diff命令可以直接对文件和文件行与行进行对比并显示。
- 至此暂停（推迟）实现diff

#使用百度思维导图
##记录平时学习(18.8.31)
- 在大学中的课程

#开始新的征程
##学习Cmake(19.7.15)
- 前段时间进行了实习，虽然编译代码遇到了很多挫折，但是看到了大型工程使用的一些成型的工具，就比如声称跨平台的CMake工具。在网上也找到了一些好资源进行了尝试
- 这个git project就决定做一些工具的测试，小型Demo的集结
##学习并尝试使用C++的STL(19.8.4)

##尝试使用CPython和C/C++静态库的一套东西(19.8.10)
1. C/C++ 生成静态库方法
	1. 编译要生成静态库的函数文件(api.cpp)
			
			g++ -c api.cpp  
		生成api.o, 然后使用ar命令生成静态库文件(libapi.o)
			
			ar crv libapi.a api.o
	2. C/C++调用时第一步首先要包含对应函数的声明，其次链接静态库
		
			g++ -o output main.cpp libapi.a
2. C/C++ 生成动态库方法
	- 纯C程序可直接执行命令来生成动态库
		
			g++ -shared -fPIC -o libpuerC.so pureC.c
		生成.so动态链接库, C/C++使用时直接链接就好
			
			g++ -o output main.cpp libpureC.so
3. python 调用.so 动态链接库方法
	
	```py
	import ctypes
	
	libcaller = ctypes.cdll.LoadLibrary
	lib = libcaller("./libpuerC.so")
	lib.hello() #调用动态库中方法
	```	
	生成动态库时， c++源文件需要使用
	
	```c
	 extend "C"{
		//将要调用的方法实现
		int add(int a, int b) {
			return a + b;
		}
	}
	```
4. python 调用C/C++可执行程序, 需要使用os与commands模块，main为C/C++编译后文件
	> import os<br>
	> import commands
	
	1. 使用获取返回值与输出的方式：
		
		```py
		if os.path.exists(main):
			rc, out = commands.getstatusoutput(main)
			print("rc = %d, out = %s" % (rc, out)
		```	 
	2. 使用管道方式
		
		```py
		f = os.popen(main)
		data = f.readlines()
		f.close()
		print(data)
		```
	3. 使用系统调用
		
		```py
		os.system(main)
		```
##尝试实现SkipList（19.9.12）
###第一个目的是要将过去使用C的习惯改为使用C++
- 习惯使用面对对象的思维来考虑问题
###实现一层跳表
- 实现基本功能：remove initialize insert ...
- 使用makefile