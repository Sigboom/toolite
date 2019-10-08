#toolite
some tools for work.

<table>
	<tr>
		<th>基本分类</th>
		<th colspan=10>分类内容</th>
	</tr>
	<tr align="center">
		<td rowspan=4>基础结构</td>
		<td>linear</td>
		<td><a href="#skiplist">skiplist</td>
	</tr>
	<tr  align="center">
		<td>tree</td>
	</tr>
	<tr  align="center">
		<td>map</td>
	</tr>
	<tr  align="center">
		<td>STL</td>
		<td>string</td>
	</tr>
	<tr align="center">
		<td>工具开发</td>
		<td><a href="#diff">diff</a></td>
		<td><a href="#dictTree_CN">DictTree_CN</a></td>
		<td><a href="#testToolkit">TestToolkit</a></td>
	</tr>
	<tr align="center">
		<td>开发工具使用</td>
		<td><a href="#cmake">cmake</a></td>
		<td><a href="#cpython">Cpython</a></td>
		<td><a href="#github">Github</a></td>
		<td><a href="#jekyll">Jekyll</a></td>
	</tr>
	<tr align="center">
		<td>应用工具使用</td>
		<td><a href="#macdown">MacDown</a></td>
		<td><a href="#baidunaotu">百度脑图</a></td>
	</tr>
	<tr align="center">
		<td>特殊处理</td>
		<td><a href="#ds_store">.DS_Store</a></td>		<td><a href="#algorithm">Algorithm</a></td>
		<td><a href="#sortFind">SortFind</a></td>
		<td><a href="#problems">Problems</a></td>
	</tr>

</table>

#简介
&nbsp;&nbsp;这个仓库是用来一些个人工具使用或者制作的记录<br>
&nbsp;&nbsp;可以点击表格中的连接来跳转到您关心的内容<br>
&nbsp;&nbsp;如果无法跳转，说明我没有记录，但存在源码<br>
<center>**以下简介只包括基础结构与工具开发**</center>
##skiplist
1. skiplist节点继承list
2. 在list的基础上，建立跳表索引
3. 达到step则增加跳点层，每层跳点跳跃跨度由该层变量step控制

##diff
1. 系统自带的diff命令的属性
2. 实现对比两个文本文件区别并格式化的显示出来


#toolite个人记录
<a name="github">
##熟悉github操作（18.6.27）
</a>

1. 在web上登录官网，创建一个project。
- 复制git路径，在命令框指定文件夹下执行命令

        git clone git@github.com:Sigboom/base_data.git
- 进入目标文件，进行测试操作
        
        vim test.c
        git add test.c
        git commit -m "add a test file"
        git push
- 查看仓库状态
        
        git status

<a name="ds_store">
##.DS_Store（18.6.28）
</a>

1. 想首先查看仓库的状态却偶然发现 .DS_Store 文件。大体了解了一些知识，它的产生和macOS系统密切相关，类似于Windows系统里的desktop.ini。具体了解及处理方式参考
<https://www.jianshu.com/p/fdaa8be7f6c3>
- 执行步骤
    
    > 删除项目中的所有.DS_Store。这会跳过不在项目中的 .DS_Store <br>
    > find . -name .DS_Store -print0 | xargs -0 git rm -f --ignore-unmatch <br>
    > 将 .DS_Store 加入到 .gitignore <br>
    > echo .DS_Store >> ~/.gitignore <br>
    >更新项目 <br>
    > git add --all <br>
    > git commit -m '.DS_Store banished!' <br>
- 执行以上步骤为在已上传的工程中。

##进行头文件封装操作（18.6.29）
1. 将昨天编写的函数封装进 arr_base.h 文件，并使用main.c对其进行调用
- 查找C/C++编程规范，得到如下结果：
<https://blog.csdn.net/wr132/article/details/65635003>
- 参考文章对头文件进行拆分
- 编写Makefile文件

###进行数组的基本操作整理
1. 编写测试的主函数文件
- 编写增删改查操作函数     

##Google测试框架学习（18.6.30）
- 写gtest.c代码,测试通过
- 封装到头文件，并尝试使用宏定义
- 将多个函数再次封装，并使用动态分配空间，进行函数使用次数的记录  

##思考搭建一个框架来实现我的想法（18.7.3）
- 希望把所有基础数据结构的操作包含进去，同时根据不同的数据类型操作，进入题目的列表中。（或许描述的不太清楚）。
- 之后再细细分析。

##尝试着开始搭建DTing(18.7.5)
- 已经尝试着写菜单的框架
- 希望能把数据结构的东西融入到这个项目中，能帮助我更好的学习数据结构
- 文件与文件的连接关系还没有想好
- 之后会接着尝试着更好的框架

##完善框架（18.7.6）
1. 从前向后一步步测试自己的框架。
- extern 关键字表明该处只做申明
- 注意变量和函数定义的位置，很容易就重复定义了。
- 新增 DT 交互的感觉
- 头文件和源文件的分离操作基本熟悉了
- 框架基本确定，开始增进其他功能，同时尽量想一些新的更好的框架（如果可能的话）

##再次测试框架（18.7.8）
1. 添加几个LeetCode的题解
2. 尝试着添加一些简单的对话。
3. **修改变量名、函数名和文件名**统一使用“驼峰式”标记
4. 组建命令结构体，调整数据结构和函数依赖关系

##实现框架内函数(18.7.9)
- 发现包含错误，上次函数名没有改完，导致编译不通过
- 对于单个函数生成的数组是临时的，返回地址是源空间已被释放，导致内存泄漏
- 完善了部分函数

##连接对话文件(18.7.10)
1. 将对话文件添加至工程中并进行字符串匹配与答复
- 完善修饰函数的调用结构
- 熟悉并开始思考如何增加程序可扩展性，想到了数据库的连接与使用的问题
- 创建一个智能对话系统，可以进行教与学，如果可以的话之后加入模糊匹配。

##添加完善功能（18.7.11）
1. 添加不断更新的功能
- 进行语法定义与逻辑字符串匹配
- 更新桌面
- 能够手动添加提问对应的回答

##添加与改善框架（18.7.12）
1. 分离出对话模块
- 准备对命令的记录表使用文件存储
- 从命令原文件中分离出基础操作函数
- 修改基础操作文件名为"fundamental.c/~.h"

##统一使用文件存储方式（18.7.13）
1. 增加使用函数指针
- 统一使用文件存储命令和对话，且命令和对话分别只使用一个文件存储
- 修改基本数据结构（未完成）

##整体更改框架结构（18.7.15）
1. 使用c的函数指针尝试将函数挂到结构体上，变相的使用面向对象编程
2. 遇到了很多问题，函数指针的定义使用以及函数指针数组的定义，还有函数返回值是函数指针的情况下的结构
- 最后还是出现了内存泄漏的问题，不知道是哪出的问题
- 整体来看还是应该使用结构体指针来进行主文件与次文件的交互

##经过几天的休息（18.7.20）
1. 将这个仓库的代码慢慢搬运到DXTing_pro工程中
2. 同时开始添加数据结构基本操作代码
3. 将DXTing变为一个单独的工程

##学习数据结构（18.7.29）
1. 在/course/ 下增加很多文件，都是在学习时学习的编程方法，这段时间主要更新课上的文件了。
- 在前期数组链表栈和队列掌握还好，一到树时，递归操作让我措不及防。
- 查找与排序操作还好，尽量详细的记录下来了。

<a name="diff">
##开发文本对比工具
</a>
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

<a name="baidunaotu">
##使用百度思维导图
</a>
###记录平时学习(18.8.31)
- 在大学中的课程

<a name="cmake">
##学习Cmake(19.7.15)
</a>

- 前段时间进行了实习，虽然编译代码遇到了很多挫折，但是看到了大型工程使用的一些成型的工具，就比如声称跨平台的CMake工具。在网上也找到了一些好资源进行了尝试
- 这个git project就决定做一些工具的测试，小型Demo的集结

##学习并尝试使用C++的STL(19.8.4)

<a name="cpython">
##尝试使用CPython和C/C++静态库的一套东西(19.8.10)
</a>

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

<a name="skiplist">
##尝试实现skiplist（19.9.12）
</a>
###实现目的：将过去使用C的习惯改为使用C++
- 尝试习惯使用面对对象的思维来考虑问题
- 实现一个基础的数据结构

###实现日志
####实现基础list
- 将所有操作封装入list类中

####实现一层跳表
- 继承list，重写相应方法
- 实现基本功能：remove initialize insert ...
- 使用makefile
- 实现与声明分离

####基本实现了跳表的增删改查（19.9.23）
- 实现这些功能还是有些问题。
- 最底层的结构使用的是最基础的链表，导致一些访问会不太灵活
	+ 每次查找需要使用一个新申请的空间指向待操作的前一个节点的位置。
	+ 最底层节点无法做到不检索，需要用到向前访问（由于基础数据结构的限制）
	+ 空间进行了优化（减少了向前的指针域），代价是灵活度，个人认为这种设计是不太好的。
- 使用了继承的属性，重写相应的方法。
- 决定节点提升策略，由step来决定，当前是一个跳表一个step来决定。
- 后期可以考虑其他的优化或者改进
	+ 空间换时间，增加向前的指针作用域
	+ 增加类层，减小粒度，增加该数据结构的灵活性
	+ 参考redis的基础数据结构进行改进

###思考点
####充分使用与适应面对对象的思考方法
- 将对象变量优先使用private，并使用set, get方法
- 优化相关数据结构，除去冗余空间

###合并base_date仓库(19.9.14)
- 理由：数据结构应该是编程的一种工具即“轮子”
- toolite仓库是一个个人工具箱，所有的轮子应该放在这个工具箱中
- 工具箱中的工具应该足够基础，并且提供给其他项目简单的接口

<a name="macdown">
##macdown（19.9.24）
</a>

- jekyll: 支持头信息
	
	> 偏好设置 -->Rendering -->检测Jekyll头部参数 
- toc标签：markdown自动生成目录
	- 一开始使用 Macdown 中[toc] 标签是无法生成目录的，需要打开
	
	> 偏好设置 -->Rendering 勾选Detect table contents token

<a name="jekyll">
##jekyll
</a>

```jekyll
---
layout: post
title: Blogging Like a Hacker
---
```
<p style="text-indent:2em">
在这两行的三虚线之间，你可以设置一些预定义的变量（下面这个例子可以作为参考）或者甚至创建一个你自己定义的变量。这样在接下来的文件和任意模板中或者在包含这些页面或博客的模板中都可以通过使用 Liquid 标签来访问这些变量。
</p>
具体细节连接：
[YAML头信息](http://wiki.jikexueyuan.com/project/jekyll/frontmatter.html)