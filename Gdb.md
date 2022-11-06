# 信息显示

[100个gdb小技巧（v1.0）.pdf - LiuYanYGZ - 博客园 (cnblogs.com)](https://www.cnblogs.com/LiuYanYGZ/p/14247052.html)

1. 版本信息

   - type `gdb`	进入gdb环境
   - `gdb -q`启动时关闭提示信息`alias gdb="gdb -q"`
   - `set height 0`或者`set pagination off`使gdb全部输出

2. 函数

   - 列出函数名字

     `info functions`可列出可执行文件的所有函数名称，`info functions thre*`可列出正则表达式的函数名称

     *gcc编译时需要-g才可显示*

   - 是否进入带调试信息的函数

     `start`开始调试程序，`next`执行下一条语句，不进入函数，gdb会等函数执行完，再显示下一行要执行的代码，`step`可以进入函数(被调用)。由于一些函数不带调试信息，step无法进入，例如`printf`函数，可以执行`set step-mode on`命令

   - 退出正在调试的函数

     `finish`，函数会正常执行完并且打印返回值

     `return value`命令退出并且谢盖函数的返回值为value

   - 直接执行函数

     `call`或者`print`命令直接调用函数执行

   - 打印函数堆栈帧信息

     `i frame`，输出当前函数堆栈帧的地址，指令寄存器（pc）的值，局部变量地址及值等信息

     `i registers`查看当前函数寄存器的值

     `disassemble func`查看func函数对应的汇编代码

   - 选择函数堆栈帧

     `frame n`选择函数堆栈帧，其中n是层数，使用该命令可以知道`0x7fffffffffffffffffe568`可以知道是`func2`的函数堆栈帧地址，使用`frame 0x7fffffffffffffe568`可以切换到func2的栈帧

   - 向上想下切换栈帧

     `up value`和`down value`切换上下文栈帧

3. 断点

   - 在匿名空间设置断点

     ```c
     b (anonymous namespace)::bar //匿名空间打断点
     b *0x400522					//汇编地址打断点
     tb a.c:15 //程序断住后，用'i b’查看后，断点就没有了
     b 10 if i==101  //在第十行令i=101返回结果
     ignore 1 5    // ignore bnum count 意思是接下来count次编号为bnum的断点触发都不会让程序中断，只有第count + 1次断点触发才会让程序中断
     ```

4. 观察点

   ```c
   watch a //当a值变化，程序都会停下来
   watch *(datatype*) address //watch *(int *) 0x6009c8同上
   wa a thread 2 //只有线程2改变a的值才会让程序停下来
   rw a //每次访问a的值就会让程序停下来
   aw a //每次读取或改变a的值都会让程序停下来
   tcatch fork //设置catchpoint只触发一次
   ```

5. catchpoint

6. 打印

   ```c
   x/s str1 //打印str的内容。x/s 0x7ddddddddd 也行
   p func2::b  //打印栈帧中的值 也可通过f 1进入栈帧1,然后p b
   
   
   ```

   

7. 多线程/多进程

8. core/dump文件

9. 汇编

   ```c
   disas /m main //将函数代码和汇编指令银蛇起来
   i line 13  //指向查看某一行对应的地址范围
   disaassemble 0x4004e9, 0x40050c //查看该范围内对应是汇编代码
   display /i $pc  //当显示当前程序停止时，将要执行的汇编指令
   i registers //查看寄存器中的值
   set var v=value //修改变量v中的值为value
   j 15 //跳转到15行再执行
   ```

   

10. 改变程序的执行

