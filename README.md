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