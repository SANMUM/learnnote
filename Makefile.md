# Makefile

[参考链接](https://seisman.github.io/how-to-write-makefile/overview.html)

# 一、概述

makefile关系到整个工程的编译规则。一个工程中的源文件不计其数，按照功能、类型、模块分别放在若干目录中，makefile定义了一系列规则来指定，哪些文件需要先编译，哪些文件需要后编译，哪些文件需要重新编译，甚至于更复杂的功能操作，因为makefile就像一个shell脚本一样，其中也可以执行操作系统的命令

## 关于程序的编译和链接

编译期将源文件编译成中间代码`.o`文件，链接将大量的中间文件合成执行文件。编译期主要检查语法是否正确，函数与变量的声明是否正确如果函数未被声明，编译器会给出一个警告，但可以生成目标文件，在大多时候，源文件太多，编译的中间目标文件太多，而在链接的时候要显示的指出中间目标文件的文件名，所以很不方便，因此要给目标文件打包成`.a`文件。链接器主要链接函数和全局变量，会在所有的目标文件中寻找函数的实现

# 二、makefile介绍

编译规则：

1. 如果这个工程没有编译过，那么我们的所有c文件都要编译并被链接。
2. 如果这个工程的某几个c文件被修改，那么我们只编译被修改的c文件，并链接目标程序。
3. 如果这个工程的头文件被改变了，那么我们需要编译引用了这几个头文件的c文件，并链接目标程序。

## makefile规则

```c
target ... : prerequisites ...
    command
    ...
    ...
```

target

​	可以是一个目标文件，也可以是一个执行文件，也可以是一个label

prerequisities

​	生成target所依赖的文件或target

command

​	该target要执行的命令

这是一个文件依赖关系，也就是说，target这一个或多个目标文件依赖于prerequisites中文件，其生成规则定义在command中。

```c
prerequisites中如果有一个以上的文件比target文件要新的话，command所定义的命令就会被执行。
```

## 实例

```c
edit : main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
    cc -o edit main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
//依赖关系
main.o : main.c defs.h
    cc -c main.c
kbd.o : kbd.c defs.h command.h
    cc -c kbd.c
command.o : command.c defs.h command.h
    cc -c command.c
display.o : display.c defs.h buffer.h
    cc -c display.c
insert.o : insert.c defs.h buffer.h
    cc -c insert.c
search.o : search.c defs.h buffer.h
    cc -c search.c
files.o : files.c defs.h buffer.h command.h
    cc -c files.c
utils.o : utils.c defs.h
    cc -c utils.c
clean :
    rm edit main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
```

`make`执行后生成可执行文件edit和一些列中间文件，执行可`make clean`即可删除所有生成文件

在定义好依赖关系后，后续的那一行定义了如何生成目标文件的操作系统命令，一定要以`Tab`键开头。记住，make并不管命令是怎么工作的，他只管执行所定义的命令。make会比较targets文件和prerequisites文件的修改日期，如果prerequisites文件的日期要比targets文件的日期要新，或者target不存在的话，那么，make就会执行后续定义的命令。

`clean`是一个动作名，make不会去自动找他的依赖关系，也就不会自动执行后定义的命令，要想执行其后的命令，就要显示的指出这个label的名字

## make是如何工作的

执行`make`命令后

1. make会在当前目录下找名字叫“Makefile”或“makefile”的文件。
2. 如果找到，它会找文件中的第一个目标文件（target），在上面的例子中，他会找到“edit”这个文件，并把这个文件作为最终的目标文件。
3. 如果edit文件不存在，或是edit所依赖的后面的 `.o` 文件的文件修改时间要比 `edit` 这个文件新，那么，他就会执行后面所定义的命令来生成 `edit` 这个文件。
4. 如果 `edit` 所依赖的 `.o` 文件也不存在，那么make会在当前文件中找目标为 `.o` 文件的依赖性，如果找到则再根据那一个规则生成 `.o` 文件。（这有点像一个堆栈的过程）
5. 当然，你的C文件和H文件是存在的啦，于是make会生成 `.o` 文件，然后再用 `.o` 文件生成make的终极任务，也就是执行文件 `edit` 了

## 让make自动推导

`make`工作能很强大，它会自动推导文件及文件依赖后面的命令，没必要在每一个`.o`文件后写操作系统命令，会自动识别并且自动推导命令。只要make看到一个`.o`文件，他会把`.c`文件加载依赖关系中，如果make找到一个 `whatever.o` ，那么 `whatever.c` 就会是 `whatever.o` 的依赖文件。并且 `cc -c whatever.c` 也会被推导出来

```c
objects = main.o kbd.o command.o display.o \
    insert.o search.o files.o utils.o

edit : $(objects)
    cc -o edit $(objects)

main.o : defs.h
kbd.o : defs.h command.h
command.o : defs.h command.h
display.o : defs.h buffer.h
insert.o : defs.h buffer.h
search.o : defs.h buffer.h
files.o : defs.h buffer.h command.h
utils.o : defs.h

.PHONY : clean
clean :
    rm edit $(objects)
```

这种方法，也就是make的`隐晦规则`，上面内容中，`.PHONY`表示`clean`是个伪目标文件

## 另类风格的makefiles

```c
objects = main.o kbd.o command.o display.o \
    insert.o search.o files.o utils.o

edit : $(objects)
    cc -o edit $(objects)

$(objects) : defs.h
kbd.o command.o files.o : command.h
display.o insert.o search.o files.o : buffer.h

.PHONY : clean
clean :
    rm edit $(objects)
```

这种风格将makefile简单化，但是文件依赖关系就十分凌乱

## 清空目标文件的规则

稳健做法

```c
.PHONY : clean
clean :
    -rm edit $(objects)
```

在rm命令前面加上一个小减号的意思是，即使某些文件出现问题，但不要管，继续做后面的事，`clean`不应该放在文件开头，不然就会变成make的默认目标

## makefile文件有什么

Makefile里主要包含了五个东西：显式规则、隐晦规则、变量定义、文件指示和注释。

1. 显式规则。显式规则说明了如何生成一个或多个目标文件。这是由Makefile的书写者明显指出要生成的文件、文件的依赖文件和生成的命令。
2. 隐晦规则。由于我们的make有自动推导的功能，所以隐晦的规则可以让我们比较简略地书写 Makefile，这是由make所支持的。
3. 变量的定义。在Makefile中我们要定义一系列的变量，变量一般都是字符串，这个有点像你C语言中的宏，当Makefile被执行时，其中的变量都会被扩展到相应的引用位置上。
4. 文件指示。其包括了三个部分，一个是在一个Makefile中引用另一个Makefile，就像C语言中的include一样；另一个是指根据某些情况指定Makefile中的有效部分，就像C语言中的预编译#if一样；还有就是定义一个多行的命令。有关这一部分的内容，我会在后续的部分中讲述。
5. 注释。Makefile中只有行注释，和UNIX的Shell脚本一样，其注释是用 `#` 字符，这个就像C/C++中的 `//` 一样。如果你要在你的Makefile中使用 `#` 字符，可以用反斜杠进行转义，如： `\#` 

## 引用其他Makefile文件

在makefile使用`include`关键字可以把Makefile文件包含进来，被包含的文件会原模原样的放在当前文件的包含位置

```c
include <filename>
```

`filename`可以是当前操作系统Shell的文件模式(包含路径和通配符)

make命令开始时，会搜寻include所指出的其他Makefile，并把其内容安装在当前位置，如果没有指定路径的情况下，会优先在当前目录下寻找，找不到后会向下面的几个目录下去找：

1. 如果make执行时，有 `-I` 或 `--include-dir` 参数，那么make就会在这个参数所指定的目录下去寻找。
2. 如果目录 `<prefix>/include` （一般是： `/usr/local/bin` 或 `/usr/include` ）存在的话，make也会去找。

## 环境变量MAKEFILES

如果当前环境定义了环境变量，那么make会把这个变量中的值做一个类似于`inlcude`的动作，这个变量中的值是其它的Makefile，用空格分隔。只是，它和 `include` 不同的是，从这个环境变量中引入的Makefile的“目标”不会起作用，如果环境变量中定义的文件发现错误，make也会不理。

这个变量一被定义，那么当你使用make时，所有的Makefile都会受到它的影响,也许有时候Makefile出现了怪事，那么你可以看看当前环境中有没有定义这个变量。

## make的工作方式

GNU的make工作时的执行步骤如下：（想来其它的make也是类似）

1. 读入所有的Makefile。
2. 读入被include的其它Makefile。
3. 初始化文件中的变量。
4. 推导隐晦规则，并分析所有规则。
5. 为所有的目标文件创建依赖关系链。
6. 根据依赖关系，决定哪些目标要重新生成。
7. 执行生成命令。

# 三、书写规则

规则包含两个部分，一个是关系依赖，另一个是生成目标的方法

## 在规则中使用通配符

make支持三种通配符`*`，`?`，和`~`，与shell是相同的

## 文件搜寻

Makefile文件中的特殊变量`VPATH`用来告诉make搜寻路径，

`VPATH = src:../headers`

指定两个目录 "src"和"../headers"，make会按照这个顺序搜索，目录由"冒号"分隔，当前目永远是最高优先搜索的地方。

另一个设置文件搜索路径的方法是使用make的“vpath”关键字（注意，它是全小写的），这不是变量，这是一个make的关键字，这和上面提到的那个VPATH变量很类似，但是它更为灵活。它可以指定不同的文件在不同的搜索目录中。这是一个很灵活的功能。它的使用方法有三种：

```
vpath <pattern> <directories>
```

为符合模式<pattern>的文件指定搜索目录<directories>。

```
vpath <pattern>
```

清除符合模式<pattern>的文件的搜索目录。

```
vpath
```

清除所有已被设置好了的文件搜索目录

```c
vpath %.h ../headers
```

该句表示，要求make在"../headers"目录下搜索以`.h`结尾的文件。（如果在当前目录没有找到的话）

```
vpath %.c foo
vpath %   blish
vpath %.c bar
```

其表示 `.c` 结尾的文件，先在“foo”目录，然后是“blish”，最后是“bar”目录。

```
vpath %.c foo:bar
vpath %   blish
```

而上面的语句则表示 `.c` 结尾的文件，先在“foo”目录，然后是“bar”目录，最后才是“blish”目录。

## 伪命令

“伪目标”并不是一个文件，只是一个标签，由于“伪目标”不是文件，所以make无法生成它的依赖关系和决定它是否要执行。我们只有通过显式地指明这个“目标”才能让其生效。当然，“伪目标”的取名不能和文件名重名，不然其就失去了“伪目标”的意义了。

当然，为了避免和文件重名的这种情况，我们可以使用一个特殊的标记“.PHONY”来显式地指明一个目标是“伪目标”，向make说明，不管是否有这个文件，这个目标就是“伪目标”。

伪目标一般没有依赖的文件。但是，我们也可以为伪目标指定所依赖的文件。伪目标同样可以作为“默认目标”，只要将其放在第一个。一个示例就是，如果你的Makefile需要一口气生成若干个可执行文件，但你只想简单地敲一个make完事，并且，所有的目标文件都写在一个Makefile中，那么你可以使用“伪目标”这个特性：

```
all : prog1 prog2 prog3
.PHONY : all

prog1 : prog1.o utils.o
    cc -o prog1 prog1.o utils.o

prog2 : prog2.o
    cc -o prog2 prog2.o

prog3 : prog3.o sort.o utils.o
    cc -o prog3 prog3.o sort.o utils.o
```

Makefile中的第一个目标会被作为其默认目标。我们声明了一个“all”的伪目标，其依赖于其它三个目标。由于默认目标的特性是，总是被执行的，但由于“all”又是一个伪目标，伪目标只是一个标签不会生成文件，所以不会有“all”文件产生。于是，其它三个目标的规则总是会被决议。也就达到了我们一口气生成多个目标的目的。 `.PHONY : all` 声明了“all”这个目标为“伪目标”。（注：这里的显式“.PHONY : all” 不写的话一般情况也可以正确的执行，这样make可通过隐式规则推导出， “all” 是一个伪目标，执行make不会生成“all”文件，而执行后面的多个目标。建议：显式写出是一个好习惯。）

## 多目标

Makefile的规则中目标可以不止一个，可以支持多目标，有可能我们的多目标同时依赖于一个文件，并且其生成的命令大体相似。可以将其合并起来，当然，多个目标生成规则的执行命令不是同一个，这可能会给带来麻烦，可以使用一个自动化变量`$@`，这个变量表示目前规则中所有目标的集合，例子

```c
bigoutput littleoutput : text.g
    generate text.g -$(subst output,,$@) > $@
```

等价于

```
bigoutput : text.g
    generate text.g -big > bigoutput
littleoutput : text.g
    generate text.g -little > littleoutput
```

其中， `-$(subst output,,$@)` 中的 `$` 表示执行一个Makefile的函数，函数名为subst，后面的为参数。关于函数，将在后面讲述。这里的这个函数是替换字符串的意思， `$@` 表示目标的集合，就像一个数组， `$@` 依次取出目标，并执于命令。

## 静态模式

更加容易定义多目标的规则，语法如下

```
<targets ...> : <target-pattern> : <prereq-patterns ...>
    <commands>
    ...
```

targets定义了一系列目标文件，可以有通配符。是一个目标的集合

targets-pattern是指明了targets的模式，也是目标集模式

preq-patterns是目标依赖模式，对targeu-pattern形成的模式再进行一次依赖目标定义

例子

```c
objects = foo.o bar.o

all: $(objects)

$(objects): %.o: %.c
    $(CC) -c $(CFLAGS) $< -o $@
```

上面的例子中，指明了我们的目标从$object中获取，`%.o`表明要所有以 `.o` 结尾的目标，也就是 `foo.o bar.o` ，也就是变量 `$object` 集合的模式，而依赖模式 `%.c` 则取模式 `%.o` 的 `%` ，也就是 `foo bar` ，并为其加下 `.c` 的后缀，于是，我们的依赖目标就是 `foo.c bar.c` 。而命令中的 **`$<` 和 `$@` 则是自动化变量**， **`$<` 表示第一个依赖文件**， **`$@` 表示目标集（也就是“foo.o bar.o”）**。于是，上面的规则展开后等价于下面的规则：

```
foo.o : foo.c
    $(CC) -c $(CFLAGS) foo.c -o foo.o
bar.o : bar.c
    $(CC) -c $(CFLAGS) bar.c -o bar.o
```

试想`%.o`有几百个，这要用这种很简单的"静态模式规则"就可以写完一堆规则，十分有效率

```
files = foo.elc bar.o lose.o

$(filter %.o,$(files)): %.o: %.c
    $(CC) -c $(CFLAGS) $< -o $@
$(filter %.elc,$(files)): %.elc: %.el
    emacs -f batch-byte-compile $<
```

$(filter %.o,$(files))表示调用Makefile的filter函数，过滤“$files”集，只要其中模式为“%.o”的内容

## 自动生成依赖

在Makefile中，依赖关系可能会需要包含一系列头文件，比如，如果main.c中有一局#include "defs.h"，那么依赖关系应该是

```
main.o : main.c defs.h
```

在大型文件中，查清c文件包含哪些头文件是十分麻烦的，可以使用

```c
gcc -MM mian.c
输出：main.o : main.c defs.h
```

编译器如何利用这个功能和Makefile联系在一起？编译器为每个源文件的自动生成依赖关系放到每一个文件中，为每一个name.c的文件都生成一个name.d的Makefile文件，`.d`文件就存放对应`.c`文件的依赖关系

于是，我们可以写出`.c`文件和`.d`文件的依赖关系，并让make自动更新或生成`.d`文件，并把其包含在主Makefile文件中，这样就可以自动化生成每个文件的依赖关系，一个模式规则来产生`.d`文件

```
%.d: %.c
    @set -e; rm -f $@; \
    $(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
    rm -f $@.$$$$
```

这个规则的意思是，所有的 `.d` 文件依赖于 `.c` 文件， `rm -f $@` 的意思是删除所有的目标，也就是 `.d` 文件，第二行的意思是，为每个依赖文件 `$<` ，也就是 `.c` 文件生成依赖文件， `$@` 表示模式 `%.d` 文件，如果有一个C文件是name.c，那么 `%` 就是 `name` ， `$$$$` 意为一个随机编号，第二行生成的文件有可能是“name.d.12345”，第三行使用sed命令做了一个替换，关于sed命令的用法请参看相关的使用文档。第四行就是删除临时文件

```c
main.o : main.c defs.h
//转换
main.o main.d : main.c defs.h
```

于是，我们的 `.d` 文件也会自动更新了，并会自动生成了，当然，你还可以在这个 `.d` 文件中加入的不只是依赖关系，包括生成的命令也可一并加入，让每个 `.d` 文件都包含一个完赖的规则。一旦我们完成这个工作，接下来，我们就要把这些自动生成的规则放进我们的主Makefile中。我们可以使用Makefile的“include”命令，来引入别的Makefile文件（前面讲过），例如：

```
sources = foo.c bar.c

include $(sources:.c=.d)
```

上述语句中的(sources:.c=.d)` 中的 `.c=.d` 的意思是做一个替换，把变量 `$(sources)` 所有 `.c` 的字串都替换成 `.d，include是按次序来载入文件，最先载入的 `.d` 文件中的目标会成为默认目标。

# 四、书写命令

每条规则中的命令和操作系统Shell命令行是一致的。make命令的开头必须以`Tab`键开头

## 显示命令

make用@字符在命令行前，用来向屏幕显示一些信息。如：

```
@echo 正在编译XXX模块......
```

make参数 `-n` 或 `--just-print` ，那么其只是显示命令，但不会执行命令

## 命令执行

make命令会一条一条执行，当你要让上一条命令的结果应用在下一条命令时，你应该用分号分隔

```
exec:
    cd /home/hchen
    pwd
exec:
    cd /home/hchen; pwd
```

第二种合理。make一般是使用环境变量SHELL中所定义的系统Shell来执行命令，默认情况下使用UNIX的标准Shell——/bin/sh来执行命令

## 命令出错

忽略错误的全局办法，给make加上 `-i` 或是 `--ignore-errors` 参数，那么，Makefile中所有命令都会忽略错误。还有一个要提一下的make的参数的是 `-k` 或是 `--keep-going` ，这个参数的意思是，如果某规则中的命令出错了，那么就终止该规则的执行，但继续执行其它规则。

## 嵌套执行make

大工程中，每个目录中都书写一个Makefile，有利于Makefile更简洁。例如，子目录叫subdir，这个目录下有个Makefile文件，来指明这个目录下的编译规则

```
subsystem:
    cd subdir && $(MAKE)
等价于
subsystem:
    $(MAKE) -C subdir
```

定义$(MAKE)宏变量的意思是，可以为make传递一些参数，定义成一个变量比较易于维护。把这个Makefile叫做"总控Makefile"，可以将变量传递到下级Makefile文件中，不会覆盖下层的Makefile中所定义的变量，除非指定`-e`参数

```
export <variable ...>; //传递变量到下级Makefile中
unexport <variable ...>;//不想传递变量到Makefile中
```

如果你要传递所有的变量，那么，只要一个export就行了。后面什么也不用跟，表示传递所有的变量。还有一个在“嵌套执行”中比较有用的参数， `-w` 或是 `--print-directory` 会在make的过程中输出一些信息，让你看到目前的工作目录。比如，如果我们的下级make目录是“/home/hchen/gnu/make”，如果我们使用 `make -w` 来执行，那么当进入该目录时，我们会看到:

```
make: Entering directory `/home/hchen/gnu/make'.//进入时会看到
make: Leaving directory `/home/hchen/gnu/make' //离开时会看到
```

## 定义命令包

如果Makefile中出现一些相同命令序列，那么我们可以为这些相同的命令序列定义一个变量。定义这种命令序列的语法以 `define` 开始，以 `endef` 结束，如:

```
define run-yacc
yacc $(firstword $^)
mv y.tab.c $@
endef
```

这里，“run-yacc”是这个命令包的名字，这个命令包中的第一个命令是运行Yacc程序，因为Yacc程序总是生成“y.tab.c”的文件，所以第二行的命令就是把这个文件改改名字。

```
foo.c : foo.y
    $(run-yacc)
```

命令包“run-yacc”中的 `$^` 就是 `foo.y` ， `$@` 就是 `foo.c` （有关这种以 `$` 开头的特殊变量，我们会在后面介绍），make在执行命令包时，命令包中的每个命令会被依次独立执行。

# 五、使用变量

Makefile中变量的名字可以包含字符、数字，下划线（可以是数字开头），但不应该含有 `:` 、 `#` 、 `=` 或是空字符（空格、回车等）。变量是大小写敏感的，“foo”、“Foo”和“FOO”是三个不同的变量名。在Makefile中的定义的变量，就像是C/C++语言中的宏一样，与C/C++所不同的是，你可以在Makefile中改变其值

## 变量的基础

变量在声明时需要给予初值，而在使用时，需要给在变量名前加上 `$` 符号，但最好用小括号 `()` 或是大括号 `{}` 把变量给包括起来。如果你要使用真实的 `$` 字符，那么你需要用 `$$` 来表示

```
foo = c
prog.o : prog.$(foo)
    $(foo)$(foo) -$(foo) prog.$(foo)
等同于
prog.o : prog.c
    cc -c prog.c
```

## 变量中的变量

除了用`=`来定义变量，还可以使用后面定义的值，如：

```
foo = $(bar)
bar = $(ugh)
ugh = Huh?

all:
    echo $(foo)
```

我们执行“make all”将会打出变量 `$(foo)` 的值是 `Huh?` （ `$(foo)` 的值是 `$(bar)` ， `$(bar)` 的值是 `$(ugh)` ， `$(ugh)` 的值是 `Huh?` ）可见，变量是可以使用后面的变量来定义的。

这种方式好处在于把变量的真实值推到后面来定义，不好的情况是递归定义

```
CFLAGS = $(CFLAGS) -O
A = $(B)
B = $(A)
```

会使make陷入无限的变量展开过程中去，使make运行非常缓慢，更糟糕的是，会发生不可知的错误

为了避免出错，可以利用`:=`操作符，如

```c
x := foo
y := $(x) bar
x := later
等价于
y := foo bar
x := later
```

值得一提的是，这种方法，前面的变量不能使用后面的变量，只能使用前面已定义好了的变量。如果是这样

```
y := $(x) bar
x := foo
```

那么，y的值是“bar”，而不是“foo bar”。

复杂例子，包括make函数、条件表达式和系统变量"MAKELEVEL"

```
ifeq (0,${MAKELEVEL})
cur-dir   := $(shell pwd)
whoami    := $(shell whoami)
host-type := $(shell arch)
MAKE := ${MAKE} host-type=${host-type} whoami=${whoami}
endif
```

定义一个变量，其值为空格

```
nullstring :=
space := $(nullstring) # end of the line
```

nullstring是一个Empty变量，其中什么也没有，而我们的space的值是一个空格。因为在操作符的右边很难描述一个空格，注释符"#"知道注意

```
dir := /foo/bar    # directory to put the frobs in
```

dir这个变量的值是“/foo/bar”，后面还跟了4个空格，如果我们这样使用这个变量来指定别的目录——“$(dir)/file”那么就完蛋了。

还有一个比较有用的操作符是 `?=` ，先看示例

```
FOO ?= bar
```

其含义是，如果FOO没有被定义过，那么变量FOO的值就是“bar”，如果FOO先前被定义过，那么这条语将什么也不做，其等价于

```
ifeq ($(origin FOO), undefined)
    FOO = bar
endif
```

## 变量高级用法

变量值替换：其格式是 `$(var:a=b)` 或是 `${var:a=b}` ，其意思是，把变量“var”中所有以“a”字串“结尾”的“a”替换成“b”字串。这里的“结尾”意思是“空格”或是“结束符”。

```
foo := a.o b.o c.o
bar := $(foo:.o=.c)
```

这个示例中，我们先定义了一个 `$(foo)` 变量，而第二行的意思是把 `$(foo)` 中所有以 `.o` 字串“结尾”全部替换成 `.c` ，所以我们的 `$(bar)` 的值就是“a.c b.c c.c”。

另一种形式

```
foo := a.o b.o c.o
bar := $(foo:%.o=%.c)
```

第二种高级用法是----把变量的值再当成变量

```
x = y
y = z
a := $($(x))
```

在这个例子中，\$(x)的值是“y”，所以\$(\$(x))就是\$(y)，于是\$(a)的值就是“z”。（注意，是“x=y”，而不是“x=$(y)”）

加函数复杂例子

```
x = variable1
variable2 := Hello
y = $(subst 1,2,$(x))
z = y
a := $($($(z)))
```

这个例子中， `$($($(z)))` 扩展为 `$($(y))` ，而其再次被扩展为 `$($(subst 1,2,$(x)))` 。 `$(x)` 的值是“variable1”，subst函数把“variable1”中的所有“1”字串替换成“2”字串，于是，“variable1”变成 “variable2”，再取其值，所以，最终， `$(a)` 的值就是 `$(variable2)` 的值——“Hello”。（喔，好不容易）

```
a_objects := a.o b.o c.o
1_objects := 1.o 2.o 3.o

sources := $($(a1)_objects:.o=.c)
```

这个例子中，如果 `$(a1)` 的值是“a”的话，那么， `$(sources)` 的值就是“a.c b.c c.c”；如果 `$(a1)` 的值是“1”，那么 `$(sources)` 的值是“1.c 2.c 3.c”。

再来看一个这种技术和“函数”与“条件语句”一同使用的例子：

```
ifdef do_sort
    func := sort
else
    func := strip
endif

bar := a d b g q c

foo := $($(func) $(bar))
```

这个示例中，如果定义了“do_sort”，那么： `foo := $(sort a d b g q c)` ，于是 `$(foo)` 的值就是 “a b c d g q”，而如果没有定义“do_sort”，那么： `foo := $(strip a d b g q c)` ，调用的就是strip函数。

当然，“把变量的值再当成变量”这种技术，同样可以用在操作符的左边:

```
dir = foo
$(dir)_sources := $(wildcard $(dir)/*.c)
define $(dir)_print
lpr $($(dir)_sources)
endef
```

这个例子中定义了三个变量：“dir”，“foo_sources”和“foo_print”。

## 追加变量

使用 `+=` 操作符给变量追加值

```
objects = main.o foo.o bar.o utils.o
objects += another.o
//$(objects) 值变成：“main.o foo.o bar.o utils.o another.o”
```

## override指示符

如果有变量是通常make的命令行参数设置的，那么Makefile中对这个变量的赋值会被忽略。如果你想在Makefile中设置这类参数的值，那么，你可以使用“override”指示符。其语法是:

```
override <variable>; = <value>;

override <variable>; := <value>;

override <variable>; += <more text>; //追加

```

对于多行的变量定义，我们用define指示符，在define指示符前，也同样可以使用override指示符，如:

```
override define foo
bar
endef
```

## 多行变量

使用define关键字设置变量的值可以有换行，有利于定义一系列命令。

define指示符后面跟的是变量的名字，而重起一行定义变量的值，定义是以endef 关键字结束。其工作方式和“=”操作符一样。变量的值可以包含函数、命令、文字，或是其它变量。因为命令需要以[Tab]键开头，所以如果你用define定义的命令变量中没有以 `Tab` 键开头，那么make 就不会把其认为是命令。

```
define two-lines
echo foo
echo $(bar)
endef
```

## 环境变量

make运行时的系统环境变量可以在make开始运行时被载入到Makefile文件中，但是如果Makefile中已定义了这个变量，或是这个变量由make命令行带入，那么系统的环境变量的值将被覆盖。（如果make指定了“-e”参数，那么，系统环境变量将覆盖Makefile中定义的变量）

因此，如果我们在环境变量中设置了 `CFLAGS` 环境变量，那么我们就可以在所有的Makefile中使用这个变量了。这对于我们使用统一的编译参数有比较大的好处。如果Makefile中定义了CFLAGS，那么则会使用Makefile中的这个变量，如果没有定义则使用系统环境变量的值，一个共性和个性的统一，很像“全局变量”和“局部变量”的特性。

当make嵌套调用时（参见前面的“嵌套调用”章节），上层Makefile中定义的变量会以系统环境变量的方式传递到下层的Makefile 中。当然，默认情况下，只有通过命令行设置的变量会被传递。而定义在文件中的变量，如果要向下层Makefile传递，则需要使用export关键字来声明。（参见前面章节）

不推荐把许多的变量都定义在系统环境中，这样，在我们执行不用的Makefile时，拥有的是同一套系统变量，这可能会带来更多的麻烦。

## 目标变量

前面我们所讲的在Makefile中定义的变量都是“全局变量”，在整个文件，我们都可以访问这些变量。当然，“自动化变量”除外，如 `$<` 等这种类量的自动化变量就属于“规则型变量”，这种变量的值依赖于规则的目标和依赖目标的定义，当然也可以为某个目标设置局部变量，这种变量被称为“Target-specific Variable”，它可以和“全局变量”同名，因为它的作用范围只在这条规则以及连带规则中，所以其值也只在作用范围内有效。而不会影响规则链以外的全局变量的值。

语法

```
<target ...> : <variable-assignment>;

<target ...> : overide <variable-assignment>
```

<variable-assignment>;可以是前面讲过的各种赋值表达式，如 `=` 、 `:=` 、 `+=` 或是 `?=` 。第二个语法是针对于make命令行带入的变量，或是系统环境变量，这个特性非常的有用，当我们设置了这样一个变量，这个变量会作用到由这个目标所引发的所有的规则中去。如：

```
prog : CFLAGS = -g
prog : prog.o foo.o bar.o
    $(CC) $(CFLAGS) prog.o foo.o bar.o

prog.o : prog.c
    $(CC) $(CFLAGS) prog.c

foo.o : foo.c
    $(CC) $(CFLAGS) foo.c

bar.o : bar.c
    $(CC) $(CFLAGS) bar.c
```

在这个示例中，不管全局的 `$(CFLAGS)` 的值是什么，在prog目标，以及其所引发的所有规则中（prog.o foo.o bar.o的规则）， `$(CFLAGS)` 的值都是 `-g`

## 模式变量

在GNU的make中，还支持模式变量（Pattern-specific Variable），通过上面的目标变量中，我们知道，变量可以定义在某个目标上。模式变量的好处就是，我们可以给定一种“模式”，可以把变量定义在符合这种模式的所有目标上。

make的“模式”一般是至少含有一个 `%` 的，所以，我们可以以如下方式给所有以 `.o` 结尾的目标定义目标变量：

```
%.o : CFLAGS = -O
```

同样，模式变量的语法和“目标变量”一样：

```
<pattern ...>; : <variable-assignment>;

<pattern ...>; : override <variable-assignment>;
```

override同样是针对于系统环境传入的变量，或是make命令行指定的变量。

# 六、使用条件判断

使用条件判断，可以让make根据运行时的不同情况选择不同的执行分支。条件表达式可以是比较变量的值，或是比较变量和常量的值。

## 示例

```
libs_for_gcc = -lgnu
normal_libs =

foo: $(objects)
ifeq ($(CC),gcc)
    $(CC) -o foo $(objects) $(libs_for_gcc)
else
    $(CC) -o foo $(objects) $(normal_libs)
endif
```

我们可以从上面的示例中看到三个关键字： `ifeq` 、 `else` 和 `endif` 。 `ifeq` 的意思表示条件语句的开始，并指定一个条件表达式，表达式包含两个参数，以逗号分隔，表达式以圆括号括起。 `else` 表示条件表达式为假的情况。 `endif` 表示一个条件语句的结束，任何一个条件表达式都应该以 `endif` 结束。

更简洁的写法

```
libs_for_gcc = -lgnu
normal_libs =

ifeq ($(CC),gcc)
    libs=$(libs_for_gcc)
else
    libs=$(normal_libs)
endif

foo: $(objects)
    $(CC) -o foo $(objects) $(libs)
```

## 语法

```
<conditional-directive>
<text-if-true>
endif
###########
<conditional-directive>
<text-if-true>
else
<text-if-false>
endif
```

其中 `<conditional-directive>` 表示条件关键字，如 `ifeq` 。这个关键字有四个。

第一个是我们前面所见过的 `ifeq`

```
ifeq (<arg1>, <arg2>)
ifeq '<arg1>' '<arg2>'
ifeq "<arg1>" "<arg2>"
ifeq "<arg1>" '<arg2>'
ifeq '<arg1>' "<arg2>"
```

比较参数 `arg1` 和 `arg2` 的值是否相同。当然，参数中我们还可以使用make的函数

比较参数 `arg1` 和 `arg2` 的值是否相同。当然，参数中我们还可以使用make的函数。如:

```
ifeq ($(strip $(foo)),)
<text-if-empty>
endif
```

这个示例中使用了 `strip` 函数，如果这个函数的返回值是空（Empty），那么 `<text-if-empty>` 就生效。

第二个条件关键字是 `ifneq` 。语法是：

```
ifneq (<arg1>, <arg2>)
ifneq '<arg1>' '<arg2>'
ifneq "<arg1>" "<arg2>"
ifneq "<arg1>" '<arg2>'
ifneq '<arg1>' "<arg2>"
```

其比较参数 `arg1` 和 `arg2` 的值是否相同，如果不同，则为真。和 `ifeq` 类似。

第三个条件关键字是 `ifdef` 。语法是：

```
ifdef <variable-name>
```

如果变量 `<variable-name>` 的值非空，那到表达式为真。否则，表达式为假。当然， `<variable-name>` 同样可以是一个函数的返回值。注意， `ifdef` 只是测试一个变量是否有值，其并不会把变量扩展到当前位置。还是来看两个例子：

示例一：

```
bar =
foo = $(bar)
ifdef foo
    frobozz = yes
else
    frobozz = no
endif
```

示例二：

```
foo =
ifdef foo
    frobozz = yes
else
    frobozz = no
endif
```

第一个例子中， `$(frobozz)` 值是 `yes` ，第二个则是 `no`。

第四个条件关键字是 `ifndef` 。其语法是：

```
ifndef <variable-name>
```

这个我就不多说了，和 `ifdef` 是相反的意思。

在 `<conditional-directive>` 这一行上，多余的空格是被允许的，但是不能以 `Tab` 键作为开始（不然就被认为是命令）。而注释符 `#` 同样也是安全的。 `else` 和 `endif` 也一样，只要不是以 `Tab` 键开始就行了。

特别注意的是，make是在读取Makefile时就计算条件表达式的值，并根据条件表达式的值来选择语句，所以，你最好不要把自动化变量（如 `$@` 等）放入条件表达式中，因为自动化变量是在运行时才有的。

# 七、使用函数

使用函数来处理变量，使命令或规则更为灵活和具有智能

## 函数的调用语法

函数的调用于变量使用相送，也是`$`来标识，其语法如下

```c
$(<function> <arguments>)
或是
${<function> <arguments>}
```

<function>是函数名，make支持函数不多。<arguments>为函数参数，参数间以逗号分隔，函数名和参数之间以空格分隔。函数调用以`$`开头，以圆括号或花括号把函数名和参数括起。

示例

```
comma:= ,
empty:=
space:= $(empty) $(empty)
foo:= a b c
bar:= $(subst $(space),$(comma),$(foo))
```

在这个示例中， `$(comma)` 的值是一个逗号。 `$(space)` 使用了 `$(empty)` 定义了一个空格， `$(foo)` 的值是 `a b c` ， `$(bar)` 的定义用，调用了函数 `subst` ，这是一个替换函数，这个函数有三个参数，第一个参数是被替换字串，第二个参数是替换字串，第三个参数是替换操作作用的字串。这个函数也就是把 `$(foo)` 中的空格替换成逗号，所以 `$(bar)` 的值是 `a,b,c` 。

## 字符串处理函数

### subst

```c
$(subst <from>,<to>,<text>)
```

- 名称：字符串替换函数

- 功能：把字串 `<text>` 中的 `<from>` 字符串替换成 `<to>` 。

- 返回：函数返回被替换过后的字符串。

- 示例：

  ```c
  $(subst ee,EE,feet on the street)
  ```

把feet on the street` 中的 `ee` 替换成 `EE` ，返回结果是 `fEEt on the strEEt

### patsubst

```
$(patsubst <pattern>,<replacement>,<text>)
```

- 名称：模式字符串替换函数。

- 功能：查找 `<text>` 中的单词（单词以“空格”、“Tab”或“回车”“换行”分隔）是否符合模式 `<pattern>` ，如果匹配的话，则以 `<replacement>` 替换。这里， `<pattern>` 可以包括通配符 `%` ，表示任意长度的字串。如果 `<replacement>` 中也包含 `%` ，那么， `<replacement>` 中的这个 `%` 将是 `<pattern>` 中的那个 `%` 所代表的字串。（可以用 `\` 来转义，以 `\%` 来表示真实含义的 `%` 字符）

- 返回：函数返回被替换过后的字符串。

- 示例：

  > ```
  > $(patsubst %.c,%.o,x.c.c bar.c)
  > ```

>把字串 `x.c.c bar.c` 符合模式 `%.c` 的单词替换成 `%.o` ，返回结果是 `x.c.o bar.o`

- 备注：这和我们前面“变量章节”说过的相关知识有点相似。如 `$(var:<pattern>=<replacement>;)` 相当于 `$(patsubst <pattern>,<replacement>,$(var))` ，而 `$(var: <suffix>=<replacement>)` 则相当于 `$(patsubst %<suffix>,%<replacement>,$(var))` 。

  例如有:

  ```
  objects = foo.o bar.o baz.o，
  ```

  那么， `$(objects:.o=.c)` 和 `$(patsubst %.o,%.c,$(objects))` 是一样的。

### strip

```
$(strip <string>)
```

- 名称：去空格函数。

- 功能：去掉 `<string>` 字串中开头和结尾的空字符。

- 返回：返回被去掉空格的字符串值。

- 示例：

  > ```
  > $(strip a b c )
  > ```

  把字串 `a b c ` 去掉开头和结尾的空格，结果是 `a b c`。

### findstring

```
$(findstring <find>,<in>)
```

- 名称：查找字符串函数

- 功能：在字串 `<in>` 中查找 `<find>` 字串。

- 返回：如果找到，那么返回 `<find>` ，否则返回空字符串。

- 示例：

  > ```
  > $(findstring a,a b c)
  > $(findstring a,b c)
  > ```

第一个函数返回 `a` 字符串，第二个返回空字符串

### filter

```
$(filter <pattern...>,<text>)
```

- 名称：过滤函数

- 功能：以 `<pattern>` 模式过滤 `<text>` 字符串中的单词，保留符合模式 `<pattern>` 的单词。可以有多个模式。

- 返回：返回符合模式 `<pattern>` 的字串。

- 示例：

  > ```
  > sources := foo.c bar.c baz.s ugh.h
  > foo: $(sources)
  >     cc $(filter %.c %.s,$(sources)) -o foo
  > ```

  `$(filter %.c %.s,$(sources))` 返回的值是 `foo.c bar.c baz.s` 。

### filter-out

```
$(filter-out <pattern...>,<text>)
```

- 名称：反过滤函数

- 功能：以 `<pattern>` 模式过滤 `<text>` 字符串中的单词，去除符合模式 `<pattern>` 的单词。可以有多个模式。

- 返回：返回不符合模式 `<pattern>` 的字串。

- 示例：

  > ```
  > objects=main1.o foo.o main2.o bar.o
  > mains=main1.o main2.o
  > ```

  `$(filter-out $(mains),$(objects))` 返回值是 `foo.o bar.o` 

### sort

```
$(sort <list>)
```

- 名称：排序函数
- 功能：给字符串 `<list>` 中的单词排序（升序）。
- 返回：返回排序后的字符串。
- 示例： `$(sort foo bar lose)` 返回 `bar foo lose` 。
- 备注： `sort` 函数会去掉 `<list>` 中相同的单词。

### word

```
$(word <n>,<text>)
```

- 名称：取单词函数
- 功能：取字符串 `<text>` 中第 `<n>` 个单词。（从一开始）
- 返回：返回字符串 `<text>` 中第 `<n>` 个单词。如果 `<n>` 比 `<text>` 中的单词数要大，那么返回空字符串。
- 示例： `$(word 2, foo bar baz)` 返回值是 `bar` 。

### wordlist

```
$(wordlist <ss>,<e>,<text>)
```

- 名称：取单词串函数
- 功能：从字符串 `<text>` 中取从 `<ss>` 开始到 `<e>` 的单词串。 `<ss>` 和 `<e>` 是一个数字。
- 返回：返回字符串 `<text>` 中从 `<ss>` 到 `<e>` 的单词字串。如果 `<ss>` 比 `<text>` 中的单词数要大，那么返回空字符串。如果 `<e>` 大于 `<text>` 的单词数，那么返回从 `<ss>` 开始，到 `<text>` 结束的单词串。
- 示例： `$(wordlist 2, 3, foo bar baz)` 返回值是 `bar baz` 。

### words

```
$(words <text>)
```

- 名称：单词个数统计函数
- 功能：统计 `<text>` 中字符串中的单词个数。
- 返回：返回 `<text>` 中的单词数。
- 示例： `$(words, foo bar baz)` 返回值是 `3` 。
- 备注：如果我们要取 `<text>` 中最后的一个单词，我们可以这样： `$(word $(words <text>),<text>)` 。

### firstword

```
$(firstword <text>)
```

- 名称：首单词函数——firstword。
- 功能：取字符串 `<text>` 中的第一个单词。
- 返回：返回字符串 `<text>` 的第一个单词。
- 示例： `$(firstword foo bar)` 返回值是 `foo`。
- 备注：这个函数可以用 `word` 函数来实现： `$(word 1,<text>)` 。

## 文件操作函数

### dir

```
$(dir <names...>)
```

- 名称：取目录函数——dir。
- 功能：从文件名序列 `<names>` 中取出目录部分。目录部分是指最后一个反斜杠（ `/` ）之前的部分。如果没有反斜杠，那么返回 `./` 。
- 返回：返回文件名序列 `<names>` 的目录部分。
- 示例： `$(dir src/foo.c hacks)` 返回值是 `src/ ./` 。

### notdir

```
$(notdir <names...>)
```

- 名称：取文件函数——notdir。
- 功能：从文件名序列 `<names>` 中取出非目录部分。非目录部分是指最後一个反斜杠（ `/` ）之后的部分。
- 返回：返回文件名序列 `<names>` 的非目录部分。
- 示例: `$(notdir src/foo.c hacks)` 返回值是 `foo.c hacks` 。

### suffix

```
$(suffix <names...>)
```

- 名称：取後缀函数——suffix。
- 功能：从文件名序列 `<names>` 中取出各个文件名的后缀。
- 返回：返回文件名序列 `<names>` 的后缀序列，如果文件没有后缀，则返回空字串。
- 示例： `$(suffix src/foo.c src-1.0/bar.c hacks)` 返回值是 `.c .c`。

### basename

```
$(basename <names...>)
```

- 名称：取前缀函数——basename。
- 功能：从文件名序列 `<names>` 中取出各个文件名的前缀部分。
- 返回：返回文件名序列 `<names>` 的前缀序列，如果文件没有前缀，则返回空字串。
- 示例： `$(basename src/foo.c src-1.0/bar.c hacks)` 返回值是 `src/foo src-1.0/bar hacks`

### addsuffix

```
$(addsuffix <suffix>,<names...>)
```

- 名称：加后缀函数——addsuffix。
- 功能：把后缀 `<suffix>` 加到 `<names>` 中的每个单词后面。
- 返回：返回加过后缀的文件名序列。
- 示例： `$(addsuffix .c,foo bar)` 返回值是 `foo.c bar.c` 。

### addprefix

```
$(addprefix <prefix>,<names...>)
```

- 名称：加前缀函数——addprefix。
- 功能：把前缀 `<prefix>` 加到 `<names>` 中的每个单词前面。
- 返回：返回加过前缀的文件名序列。
- 示例： `$(addprefix src/,foo bar)` 返回值是 `src/foo src/bar` 。

### join

```
$(join <list1>,<list2>)
```

- 名称：连接函数——join。
- 功能：把 `<list2>` 中的单词对应地加到 `<list1>` 的单词后面。如果 `<list1>` 的单词个数要比 `<list2>` 的多，那么， `<list1>` 中的多出来的单词将保持原样。如果 `<list2>` 的单词个数要比 `<list1>` 多，那么， `<list2>` 多出来的单词将被复制到 `<list1>` 中。
- 返回：返回连接过后的字符串。
- 示例： `$(join aaa bbb , 111 222 333)` 返回值是 `aaa111 bbb222 333` 。

## foreach函数

用来做循环，几乎仿照shell语句中的for语句

```
$(foreach <var>,<list>,<text>)
```

这个函数的意思是，把参数 `<list>` 中的单词逐一取出放到参数 `<var>` 所指定的变量中，然后再执行 `<text>` 所包含的表达式。每一次 `<text>` 会返回一个字符串，循环过程中， `<text>` 的所返回的每个字符串会以空格分隔，最后当整个循环结束时， `<text>` 所返回的每个字符串所组成的整个字符串（以空格分隔）将会是foreach函数的返回值。

所以， `<var>` 最好是一个变量名， `<list>` 可以是一个表达式，而 `<text>` 中一般会使用 `<var>` 这个参数来依次枚举 `<list>` 中的单词。举个例子：

```
names := a b c d

files := $(foreach n,$(names),$(n).o)
```

上面的例子中， `$(name)` 中的单词会被挨个取出，并存到变量 `n` 中， `$(n).o` 每次根据 `$(n)` 计算出一个值，这些值以空格分隔，最后作为foreach函数的返回，所以， `$(files)` 的值是 `a.o b.o c.o d.o` 。

注意，foreach中的 `<var>` 参数是一个临时的局部变量，foreach函数执行完后，参数 `<var>` 的变量将不在作用，其作用域只在foreach函数当中。

## if函数

if函数很像GNU的make所支持的条件语句——ifeq（参见前面所述的章节），if函数的语法是：

```
$(if <condition>,<then-part>)
```

或是

```
$(if <condition>,<then-part>,<else-part>)
```

可见，if函数可以包含“else”部分，或是不含。即if函数的参数可以是两个，也可以是三个。 `<condition>` 参数是if的表达式，如果其返回的为非空字符串，那么这个表达式就相当于返回真，于是， `<then-part>` 会被计算，否则 `<else-part>` 会被计算。

而if函数的返回值是，如果 `<condition>` 为真（非空字符串），那个 `<then-part>` 会是整个函数的返回值，如果 `<condition>` 为假（空字符串），那么 `<else-part>` 会是整个函数的返回值，此时如果 `<else-part>` 没有被定义，那么，整个函数返回空字串。

所以， `<then-part>` 和 `<else-part>` 只会有一个被计算。

## call函数

call函数是唯一一个可以用来创建新的参数化的函数。你可以写一个非常复杂的表达式，这个表达式中，你可以定义许多参数，然后你可以call函数来向这个表达式传递参数。其语法是：

```
$(call <expression>,<parm1>,<parm2>,...,<parmn>)
```

当make执行这个函数时， `<expression>` 参数中的变量，如 `$(1)` 、 `$(2)` 等，会被参数 `<parm1>` 、 `<parm2>` 、 `<parm3>` 依次取代。而 `<expression>` 的返回值就是 call 函数的返回值。例如：

```
reverse =  $(1) $(2)

foo = $(call reverse,a,b)
```

那么， `foo` 的值就是 `a b` 。当然，参数的次序是可以自定义的，不一定是顺序的，如：

```
reverse =  $(2) $(1)

foo = $(call reverse,a,b)
```

此时的 `foo` 的值就是 `b a` 。

需要注意：在向 call 函数传递参数时要尤其注意空格的使用。call 函数在处理参数时，第2个及其之后的参数中的空格会被保留，因而可能造成一些奇怪的效果。因而在向call函数提供参数时，最安全的做法是去除所有多余的空格。

## origin函数

origin函数不像其它的函数，他并不操作变量的值，他只是告诉你你的这个变量是哪里来的？其语法是：

```
$(origin <variable>)
```

注意， `<variable>` 是变量的名字，不应该是引用，最好不要在`<variable>` 中使用`$` 字符。Origin函数会以其返回值来告诉你这个变量的“出生情况”，

`undefined`

如果 `<variable>` 从来没有定义过，origin函数返回这个值 `undefined`

`default`

如果 `<variable>` 是一个默认的定义，比如“CC”这个变量，

`environment`

如果 `<variable>` 是一个环境变量，并且当Makefile被执行时， `-e` 参数没有被打开。

`file`

如果 `<variable>` 这个变量被定义在Makefile中。

`command line`

如果 `<variable>` 这个变量是被命令行定义的。

`override`

如果 `<variable>` 是被override指示符重新定义的。

`automatic`

如果 `<variable>` 是一个命令运行中的自动化变量。

这些信息对于我们编写Makefile是非常有用的，例如，假设我们有一个Makefile其包了一个定义文件 Make.def，在 Make.def中定义了一个变量“bletch”，而我们的环境中也有一个环境变量“bletch”，此时，我们想判断一下，如果变量来源于环境，那么我们就把之重定义了，如果来源于Make.def或是命令行等非环境的，那么我们就不重新定义它。于是，在我们的Makefile中，我们可以这样写：

```
ifdef bletch
    ifeq "$(origin bletch)" "environment"
        bletch = barf, gag, etc.
    endif
endif
```

当然，你也许会说，使用 `override` 关键字不就可以重新定义环境中的变量了吗？为什么需要使用这样的步骤？是的，我们用 `override` 是可以达到这样的效果，可是 `override` 过于粗暴，它同时会把从命令行定义的变量也覆盖了，而我们只想重新定义环境传来的，而不想重新定义命令行传来的。

## shell函数

shell函数也不像其他函数。顾名思义，它的参数应该就是操作系统Shell的命令。它和反引号"`"是相同的功能。这就是说，shell函数把执行操作系统命令后的输出作为函数返回，于是，我们可以用操作系统命令以及字符串处理命令awk，sed等等命令来生成一个变量，如：

```c
contents := $(shell cat foo)
files := $(shell echo *.c)
```

注意，这个函数会新生成一个Shell程序来执行命令，所以你要注意其运行性能，如果你的Makefile中有一些比较复杂的规则，并大量使用了这个函数，那么对于你的系统性能是有害的。特别是Makefile的隐晦的规则可能会让你的shell函数执行的次数比你想像的多得多

## 控制make的函数

make提供了一些函数来控制make的运行。通常，只需要检测一些运行Makefile时的运行时信息，并且根据这些信息来决定，你是让make继续执行，还是停止

```
$(error <text ...>)
```

产生一个致命错误，`<text ...>` 是错误信息。注意，error函数不会在一被使用就会产生错误信息，所以如果你把其定义在某个变量中，并在后续的脚本中使用这个变量，那么也是可以的。例如：

示例一：

```
ifdef ERROR_001
    $(error error is $(ERROR_001))
endif
```

示例二：

```
ERR = $(error found an error!)

.PHONY: err

err: $(ERR)
```

示例一会在变量ERROR_001定义了后执行时产生error调用，而示例二则在目录err被执行时才发生error调用。

```
$(warning <text ...>)
```

这个函数很像error函数，只是它并不会让make退出，只是输出一段警告信息，而make继续执行。



# 八、make的运行

一般来说，最简单的就是直接在命令行下输入make命令，make命令会找当前目录的makefile来执行，一切都是自动的。但也有时你也许只想让make重编译某些文件，而不是整个工程，而又有的时候你有几套编译规则，你想在不同的时候使用不同的编译规则，

## make的退出码

make的执行后有三个退出码：

- 0

  表示成功执行。

- 1

  如果make运行时出现任何错误，其返回1。

- 2

  如果你使用了make的“-q”选项，并且make使得一些目标不需要更新，那么返回2。

  GNU make找寻默认的Makefile的规则是在当前目录下依次找三个文件——“GNUmakefile”、“makefile”和“Makefile”。其按顺序找这三个文件，一旦找到，就开始读取这个文件并执行。

  当前，我们也可以给make命令指定一个特殊名字的Makefile。要达到这个功能，我们要使用make的 `-f` 或是 `--file` 参数（ `--makefile` 参数也行）。例如，我们有个makefile的名字是“hchen.mk”，那么，我们可以这样来让make来执行这个文件：

  ```
  make –f hchen.mk
  ```

## 指定目标

一般来说，make的最终目标是makefile中的第一个目标，而其它目标一般是由这个目标连带出来的。这是make的默认行为。当然，一般来说，你的makefile中的第一个目标是由许多个目标组成，你可以指示make，让其完成你所指定的目标。要达到这一目的很简单，需在make命令后直接跟目标的名字就可以完成（如前面提到的“make clean”形式）

有一个make的环境变量叫 `MAKECMDGOALS` ，这个变量中会存放你所指定的终极目标的列表，如果在命令行上，你没有指定目标，那么，这个变量是空值。这个变量可以让你使用在一些比较特殊的情形下。比如下面的例子：

```
sources = foo.c bar.c
ifneq ( $(MAKECMDGOALS),clean)
    include $(sources:.c=.d)
endif
```

基于上面的这个例子，只要我们输入的命令不是“make clean”，那么makefile会自动包含“foo.d”和“bar.d”这两个makefile。

使用指定终极目标的方法可以很方便地让我们编译我们的程序，例如下面这个例子：

```
.PHONY: all
all: prog1 prog2 prog3 prog4
```

即然make可以指定所有makefile中的目标，那么也包括“伪目标”，于是我们可以根据这种性质来让我们的makefile根据指定的不同的目标来完成不同的事。在Unix世界中，软件发布时，特别是GNU这种开源软件的发布时，其makefile都包含了编译、安装、打包等功能。我们可以参照这种规则来书写我们的makefile中的目标。

- all:这个伪目标是所有目标的目标，其功能一般是编译所有的目标。
- clean:这个伪目标功能是删除所有被make创建的文件。
- install:这个伪目标功能是安装已编译好的程序，其实就是把目标执行文件拷贝到指定的目标中去。
- print:这个伪目标的功能是例出改变过的源文件。
- tar:这个伪目标功能是把源程序打包备份。也就是一个tar文件。
- dist:这个伪目标功能是创建一个压缩文件，一般是把tar文件压成Z文件。或是gz文件。
- TAGS:这个伪目标功能是更新所有的目标，以备完整地重编译使用。
- check和test:这两个伪目标一般用来测试makefile的流程。

## 检查规则

有时候，我们不想让我们的makefile中的规则执行起来，我们只想检查一下我们的命令，或是执行的序列。于是我们可以使用make命令的下述参数：

-n, --just-print, --dry-run, --recon
不执行参数，这些参数只是打印命令，不管目标是否更新，把规则和连带规则下的命令打印出来，但不执行，这些参数对于我们调试makefile很有用处。

-t, --touch
这个参数的意思就是把目标文件的时间更新，但不更改目标文件。也就是说，make假装编译目标，但不是真正的编译目标，只是把目标变成已编译过的状态。

-q, --question
这个参数的行为是找目标的意思，也就是说，如果目标存在，那么其什么也不会输出，当然也不会执行编译，如果目标不存在，其会打印出一条出错信息。

-W <file>, --what-if=<file>, --assume-new=<file>, --new-file=<file>
这个参数需要指定一个文件。一般是是源文件（或依赖文件），Make会根据规则推导来运行依赖于这个文件的命令，一般来说，可以和“-n”参数一同使用，来查看这个依赖文件所发生的规则命令。

## make参数

```
-b`, `-m
```

这两个参数的作用是忽略和其它版本make的兼容性。

```
-B`, `--always-make
```

认为所有的目标都需要更新（重编译）。

`-C` *<dir>*, `--directory`=*<dir>*

指定读取makefile的目录。如果有多个“-C”参数，make的解释是后面的路径以前面的作为相对路径，并以最后的目录作为被指定目录。如：“make -C ~hchen/test -C prog”等价于“make -C ~hchen/test/prog”。

`-debug`[=*<options>*]

输出make的调试信息。它有几种不同的级别可供选择，如果没有参数，那就是输出最简单的调试信息。下面是<options>的取值：

- a: 也就是all，输出所有的调试信息。（会非常的多）
- b: 也就是basic，只输出简单的调试信息。即输出不需要重编译的目标。
- v: 也就是verbose，在b选项的级别之上。输出的信息包括哪个makefile被解析，不需要被重编译的依赖文件（或是依赖目标）等。
- i: 也就是implicit，输出所有的隐含规则。
- j: 也就是jobs，输出执行规则中命令的详细信息，如命令的PID、返回码等。
- m: 也就是makefile，输出make读取makefile，更新makefile，执行makefile的信息。

```
-d
```

相当于“–debug=a”。

```
-e`, `--environment-overrides
```

指明环境变量的值覆盖makefile中定义的变量的值。

`-f`=*<file>*, `--file`=*<file>*, `--makefile`=*<file>*

指定需要执行的makefile。

```
-h`, `--help
```

显示帮助信息。

```
-i` , `--ignore-errors
```

在执行时忽略所有的错误。

`-I` *<dir>*, `--include-dir`=*<dir>*

指定一个被包含makefile的搜索目标。可以使用多个“-I”参数来指定多个目录。

`-j` [*<jobsnum>*], `--jobs`[=*<jobsnum>*]

指同时运行命令的个数。如果没有这个参数，make运行命令时能运行多少就运行多少。如果有一个以上的“-j”参数，那么仅最后一个“-j”才是有效的。（注意这个参数在MS-DOS中是无用的）

```
-k`, `--keep-going
```

出错也不停止运行。如果生成一个目标失败了，那么依赖于其上的目标就不会被执行了。

`-l` *<load>*, `--load-average`[=*<load>*], `-max-load`[=*<load>*]

指定make运行命令的负载。

```
-n`, `--just-print`, `--dry-run`, `--recon
```

仅输出执行过程中的命令序列，但并不执行。

`-o` *<file>*, `--old-file`=*<file>*, `--assume-old`=*<file>*

不重新生成的指定的<file>，即使这个目标的依赖文件新于它。

```
-p`, `--print-data-base
```

输出makefile中的所有数据，包括所有的规则和变量。这个参数会让一个简单的makefile都会输出一堆信息。如果你只是想输出信息而不想执行makefile，你可以使用“make -qp”命令。如果你想查看执行makefile前的预设变量和规则，你可以使用 “make –p –f /dev/null”。这个参数输出的信息会包含着你的makefile文件的文件名和行号，所以，用这个参数来调试你的 makefile会是很有用的，特别是当你的环境变量很复杂的时候。

```
-q`, `--question
```

不运行命令，也不输出。仅仅是检查所指定的目标是否需要更新。如果是0则说明要更新，如果是2则说明有错误发生。

```
-r`, `--no-builtin-rules
```

禁止make使用任何隐含规则。

```
-R`, `--no-builtin-variabes
```

禁止make使用任何作用于变量上的隐含规则。

```
-s`, `--silent`, `--quiet
```

在命令运行时不输出命令的输出。

```
-S`, `--no-keep-going`, `--stop
```

取消“-k”选项的作用。因为有些时候，make的选项是从环境变量“MAKEFLAGS”中继承下来的。所以你可以在命令行中使用这个参数来让环境变量中的“-k”选项失效。

```
-t`, `--touch
```

相当于UNIX的touch命令，只是把目标的修改日期变成最新的，也就是阻止生成目标的命令运行。

```
-v`, `--version
```

输出make程序的版本、版权等关于make的信息。

```
-w`, `--print-directory
```

输出运行makefile之前和之后的信息。这个参数对于跟踪嵌套式调用make时很有用。

```
--no-print-directory
```

禁止“-w”选项。

`-W` *<file>*, `--what-if`=*<file>*, `--new-file`=*<file>*, `--assume-file`=*<file>*

假定目标<file>;需要更新，如果和“-n”选项使用，那么这个参数会输出该目标更新时的运行动作。如果没有“-n”那么就像运行UNIX的“touch”命令一样，使得<file>;的修改时间为当前时间。

```
--warn-undefined-variables
```

只要make发现有未定义的变量，那么就输出警告信息

# 九、隐含规则

"隐含规则"会使用一些我们系统变量，可以改变这些系统变量的值来定制隐含规则的运行时的参数。如系统变量`CFLAGS`可以控制编译时的编译器参数

## 使用隐含规则

如果要使用隐含规则生成你需要的目标，你所需要做的就是不要写出这个目标的规则。那么，make会试图去自动推导产生这个目标的规则和命令，如果 make可以自动推导生成这个目标的规则和命令，那么这个行为就是隐含规则的自动推导。

```
foo : foo.o bar.o
    cc –o foo foo.o bar.o $(CFLAGS) $(LDFLAGS)
```

这个Makefile中并没有写下如何生成 `foo.o` 和 `bar.o` 这两目标的规则和命令。因为make的“隐含规则”功能会自动为我们自动去推导这两个目标的依赖目标和生成命令。

make会在自己的“隐含规则”库中寻找可以用的规则，如果找到，那么就会使用。如果找不到，那么就会报错。在上面的那个例子中，make调用的隐含规则是，把 `.o` 的目标的依赖文件置成 `.c` ，并使用C的编译命令 `cc –c $(CFLAGS) foo.c` 来生成 `foo.o` 的目标。也就是说，我们完全没有必要写下下面的两条规则

```
foo.o : foo.c
    cc –c foo.c $(CFLAGS)
bar.o : bar.c
    cc –c bar.c $(CFLAGS)
```

还有，在make的“隐含规则库”中，每一条隐含规则都在库中有其顺序，越靠前的则是越被经常使用的，所以，这会导致我们有些时候即使我们显示地指定了目标依赖，make也不会管。如下面这条规则（没有命令）：

```
foo.o : foo.p
```

依赖文件 `foo.p` （Pascal程序的源文件）有可能变得没有意义。如果目录下存在了 `foo.c` 文件，那么我们的隐含规则一样会生效，并会通过 `foo.c` 调用C的编译器生成 `foo.o` 文件。因为，在隐含规则中，Pascal的规则出现在C的规则之后，所以，make找到可以生成 `foo.o` 的C的规则就不再寻找下一条规则了。如果你确实不希望任何隐含规则推导，那么，你就不要只写出“依赖规则”，而不写命令。

## 隐含规则一览

make内建的隐含规则，如果不明确的写下规则，那么，make就会在这些规则中寻找所需要规则和命令。也可以使用make的参数`-r`或`--no-builtin-rules`选项来取消所有的预设置的隐含规则

1. 编译C程序的隐含规则。

   `<n>.o` 的目标的依赖目标会自动推导为 `<n>.c` ，并且其生成命令是 `$(CC) –c $(CPPFLAGS) $(CFLAGS)`

2. 编译C++程序的隐含规则。

   `<n>.o` 的目标的依赖目标会自动推导为 `<n>.cc` 或是 `<n>.C` ，并且其生成命令是 `$(CXX) –c $(CPPFLAGS) $(CXXFLAGS)` 。（建议使用 `.cc` 作为C++源文件的后缀，而不是 `.C` ）

3. 编译Pascal程序的隐含规则。

   `<n>.o` 的目标的依赖目标会自动推导为 `<n>.p` ，并且其生成命令是 `$(PC) –c $(PFLAGS)` 。

4. 编译Fortran/Ratfor程序的隐含规则。

   `<n>.o` 的目标的依赖目标会自动推导为 `<n>.r` 或 `<n>.F` 或 `<n>.f` ，并且其生成命令是:

   - `.f` `$(FC) –c $(FFLAGS)`
   - `.F` `$(FC) –c $(FFLAGS) $(CPPFLAGS)`
   - `.f` `$(FC) –c $(FFLAGS) $(RFLAGS)`

5. 预处理Fortran/Ratfor程序的隐含规则。

   `<n>.f` 的目标的依赖目标会自动推导为 `<n>.r` 或 `<n>.F` 。这个规则只是转换Ratfor 或有预处理的Fortran程序到一个标准的Fortran程序。其使用的命令是：

   - `.F` `$(FC) –F $(CPPFLAGS) $(FFLAGS)`
   - `.r` `$(FC) –F $(FFLAGS) $(RFLAGS)`

6. 编译Modula-2程序的隐含规则。

   `<n>.sym` 的目标的依赖目标会自动推导为 `<n>.def` ，并且其生成命令是： `$(M2C) $(M2FLAGS) $(DEFFLAGS)` 。 `<n>.o` 的目标的依赖目标会自动推导为 `<n>.mod` ，并且其生成命令是： `$(M2C) $(M2FLAGS) $(MODFLAGS)` 。

7. 汇编和汇编预处理的隐含规则。

   `<n>.o` 的目标的依赖目标会自动推导为 `<n>.s` ，默认使用编译器 `as` ，并且其生成命令是： `$ (AS) $(ASFLAGS)` 。 `<n>.s` 的目标的依赖目标会自动推导为 `<n>.S` ，默认使用C预编译器 `cpp` ，并且其生成命令是： `$(AS) $(ASFLAGS)` 。

8. 链接Object文件的隐含规则。

   `<n>` 目标依赖于 `<n>.o` ，通过运行C的编译器来运行链接程序生成（一般是 `ld` ），其生成命令是： `$(CC) $(LDFLAGS) <n>.o $(LOADLIBES) $(LDLIBS)` 。这个规则对于只有一个源文件的工程有效，同时也对多个Object文件（由不同的源文件生成）的也有效。例如如下规则:

   ```
   x : y.o z.o
   ```

   并且 `x.c` 、 `y.c` 和 `z.c` 都存在时，隐含规则将执行如下命令:

   ```
   cc -c x.c -o x.o
   cc -c y.c -o y.o
   cc -c z.c -o z.o
   cc x.o y.o z.o -o x
   rm -f x.o
   rm -f y.o
   rm -f z.o
   ```

   如果没有一个源文件（如上例中的x.c）和你的目标名字（如上例中的x）相关联，那么，你最好写出自己的生成规则，不然，隐含规则会报错的。

9. Yacc C程序时的隐含规则。

   `<n>.c` 的依赖文件被自动推导为 `n.y` （Yacc生成的文件），其生成命令是： `$(YACC) $(YFALGS)` 。（“Yacc”是一个语法分析器，关于其细节请查看相关资料）

10. Lex C程序时的隐含规则。

    `<n>.c` 的依赖文件被自动推导为 `n.l` （Lex生成的文件），其生成命令是： `$(LEX) $(LFALGS)` 。（关于“Lex”的细节请查看相关资料）

11. Lex Ratfor程序时的隐含规则。

    `<n>.r` 的依赖文件被自动推导为 `n.l` （Lex生成的文件），其生成命令是： `$(LEX) $(LFALGS)` 。

12. 从C程序、Yacc文件或Lex文件创建Lint库的隐含规则。

    `<n>.ln` （lint生成的文件）的依赖文件被自动推导为 `n.c` ，其生成命令是： `$(LINT) $(LINTFALGS) $(CPPFLAGS) -i` 。对于 `<n>.y` 和 `<n>.l` 也是同样的规则。

## 隐含规则使用的变量

在隐含规则中的命令中，基本上都是使用了一些预先设置的变量。可以在makefile中改变这些变量的值，或是在make的命令行中传入这些值，或是在你的环境变量中设置这些值，无论怎么样，只要设置了这些特定的变量，那么其就会对隐含规则起作用。当然，你也可以利用make的 `-R` 或 `--no–builtin-variables` 参数来取消你所定义的变量对隐含规则的作用。

例如，第一条隐含规则——编译C程序的隐含规则的命令是 `$(CC) –c $(CFLAGS) $(CPPFLAGS)` 。Make默认的编译命令是 `cc` ，如果你把变量 `$(CC)` 重定义成 `gcc` ，把变量 `$(CFLAGS)` 重定义成 `-g` ，那么，隐含规则中的命令全部会以 `gcc –c -g $(CPPFLAGS)` 的样子来执行了。

### 关于命令的变量

- `AR` : 函数库打包程序。默认命令是 `ar`
- `AS` : 汇编语言编译程序。默认命令是 `as`
- `CC` : C语言编译程序。默认命令是 `cc`
- `CXX` : C++语言编译程序。默认命令是 `g++`
- `CO` : 从 RCS文件中扩展文件程序。默认命令是 `co`
- `CPP` : C程序的预处理器（输出是标准输出设备）。默认命令是 `$(CC) –E`
- `FC` : Fortran 和 Ratfor 的编译器和预处理程序。默认命令是 `f77`
- `GET` : 从SCCS文件中扩展文件的程序。默认命令是 `get`
- `LEX` : Lex方法分析器程序（针对于C或Ratfor）。默认命令是 `lex`
- `PC` : Pascal语言编译程序。默认命令是 `pc`
- `YACC` : Yacc文法分析器（针对于C程序）。默认命令是 `yacc`
- `YACCR` : Yacc文法分析器（针对于Ratfor程序）。默认命令是 `yacc –r`
- `MAKEINFO` : 转换Texinfo源文件（.texi）到Info文件程序。默认命令是 `makeinfo`
- `TEX` : 从TeX源文件创建TeX DVI文件的程序。默认命令是 `tex`
- `TEXI2DVI` : 从Texinfo源文件创建军TeX DVI 文件的程序。默认命令是 `texi2dvi`
- `WEAVE` : 转换Web到TeX的程序。默认命令是 `weave`
- `CWEAVE` : 转换C Web 到 TeX的程序。默认命令是 `cweave`
- `TANGLE` : 转换Web到Pascal语言的程序。默认命令是 `tangle`
- `CTANGLE` : 转换C Web 到 C。默认命令是 `ctangle`
- `RM` : 删除文件命令。默认命令是 `rm –f`

### 关于命令参数的变量

下面的这些变量都是相关上面的命令的参数。如果没有指明其默认值，那么其默认值都是空

- `ARFLAGS` : 函数库打包程序AR命令的参数。默认值是 `rv`
- `ASFLAGS` : 汇编语言编译器参数。（当明显地调用 `.s` 或 `.S` 文件时）
- `CFLAGS` : C语言编译器参数。
- `CXXFLAGS` : C++语言编译器参数。
- `COFLAGS` : RCS命令参数。
- `CPPFLAGS` : C预处理器参数。（ C 和 Fortran 编译器也会用到）。
- `FFLAGS` : Fortran语言编译器参数。
- `GFLAGS` : SCCS “get”程序参数。
- `LDFLAGS` : 链接器参数。（如： `ld` ）
- `LFLAGS` : Lex文法分析器参数。
- `PFLAGS` : Pascal语言编译器参数。
- `RFLAGS` : Ratfor 程序的Fortran 编译器参数。
- `YFLAGS` : Yacc文法分析器参数。

## 隐含规则链

在默认情况下，对于中间目标，它和一般的目标有两个地方所不同：第一个不同是除非中间的目标不存在，才会引发中间规则。第二个不同的是，只要目标成功产生，那么，产生最终目标过程中，所产生的中间目标文件会被以 `rm -f` 删除。

通常，一个被makefile指定成目标或是依赖目标的文件不能被当作中介。然而，你可以明显地说明一个文件或是目标是中介目标，你可以使用伪目标 `.INTERMEDIATE` 来强制声明。（如： `.INTERMEDIATE : mid` ）

在“隐含规则链”中，禁止同一个目标出现两次或两次以上，这样一来，就可防止在make自动推导时出现无限递归的情况。

Make会优化一些特殊的隐含规则，而不生成中间文件。如，从文件 `foo.c` 生成目标程序 `foo` ，按道理，make会编译生成中间文件 `foo.o` ，然后链接成 `foo` ，但在实际情况下，这一动作可以被一条 `cc` 的命令完成（ `cc –o foo foo.c` ），于是优化过的规则就不会生成中间文件。

## 定义模式规则

可以使用模式规则来定义一个隐含规则。一个模式规则就好像一个一般的规则，只是在规则中，目标的定义需要有 `%` 字符。 `%` 的意思是表示一个或多个任意字符。在依赖目标中同样可以使用 `%` ，只是依赖目标中的 `%` 的取值，取决于其目标。

有一点需要注意的是， `%` 的展开发生在变量和函数的展开之后，变量和函数的展开发生在make载入 Makefile时，而模式规则中的 `%` 则发生在运行时。

### 模式规则介绍

模式规则中，至少在规则的目标定义中要包含 `%` ，否则，就是一般的规则。目标中的 `%` 定义表示对文件名的匹配， `%` 表示长度任意的非空字符串。例如： `%.c` 表示以 `.c` 结尾的文件名（文件名的长度至少为3），而 `s.%.c` 则表示以 `s.` 开头， `.c` 结尾的文件名（文件名的长度至少为5）。

如果 `%` 定义在目标中，那么，依赖中的 `%` 的值决定了目标中的 `%` 的值，也就是说，依赖中的模式的 `%` 决定了目标中 `%` 的样子。例如有一个模式规则如下：

```
%.o : %.c ; <command ......>;
```

其含义是，指出了怎么从所有的 `.c` 文件生成相应的 `.o` 文件的规则。如果要生成的目标是 `a.o b.o` ，那么 `%c` 就是 `a.c b.c` 。

一旦依赖目标中的 `%` 模式被确定，那么，make会被要求去匹配当前目录下所有的文件名，一旦找到，make就会规则下的命令，所以，在模式规则中，目标可能会是多个的，如果有模式匹配出多个目标，make就会产生所有的模式目标，此时，make关心的是依赖的文件名和生成目标的命令这两件事。

### 模式规则示例

下面这个例子表示了,把所有的 `.c` 文件都编译成 `.o` 文件.

```
%.o : %.c
    $(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
```

其中， `$@` 表示所有的目标的挨个值， `$<` 表示了所有依赖目标的挨个值。这些奇怪的变量我们叫“自动化变量”，后面会详细讲述。

下面的这个例子中有两个目标是模式的：

```
%.tab.c %.tab.h: %.y
    bison -d $<
```

这条规则告诉make把所有的 `.y` 文件都以 `bison -d <n>.y` 执行，然后生成 `<n>.tab.c` 和 `<n>.tab.h` 文件。（其中， `<n>` 表示一个任意字符串）。如果我们的执行程序 `foo` 依赖于文件 `parse.tab.o` 和 `scan.o` ，并且文件 `scan.o` 依赖于文件 `parse.tab.h` ，如果 `parse.y` 文件被更新了，那么根据上述的规则， `bison -d parse.y` 就会被执行一次，于是， `parse.tab.o` 和 `scan.o` 的依赖文件就齐了。（假设， `parse.tab.o` 由 `parse.tab.c` 生成，和 `scan.o` 由 `scan.c` 生成，而 `foo` 由 `parse.tab.o` 和 `scan.o` 链接生成，而且 `foo` 和其 `.o` 文件的依赖关系也写好，那么，所有的目标都会得到满足）

### 自动化变量

所谓自动化变量，就是这种变量会把模式中所定义的一系列文件自动地挨个取出，直至所有的符合模式的文件都取完了。这种自动化模式只应出现在规则的命令中。

自动化变量说明：

- `$@` : 表示规则中的目标文件集。在模式规则中，如果有多个目标，那么， `$@` 就是匹配于目标中模式定义的集合。
- `$%` : 仅当目标是函数库文件中，表示规则中的目标成员名。例如，如果一个目标是 `foo.a(bar.o)` ，那么， `$%` 就是 `bar.o` ， `$@` 就是 `foo.a` 。如果目标不是函数库文件（Unix下是 `.a` ，Windows下是 `.lib` ），那么，其值为空。
- `$<` : 依赖目标中的第一个目标名字。如果依赖目标是以模式（即 `%` ）定义的，那么 `$<` 将是符合模式的一系列的文件集。注意，其是一个一个取出来的。
- `$?` : 所有比目标新的依赖目标的集合。以空格分隔。
- `$^` : 所有的依赖目标的集合。以空格分隔。如果在依赖目标中有多个重复的，那么这个变量会去除重复的依赖目标，只保留一份。
- `$+` : 这个变量很像 `$^` ，也是所有依赖目标的集合。只是它不去除重复的依赖目标。
- `$*` : 这个变量表示目标模式中 `%` 及其之前的部分。如果目标是 `dir/a.foo.b` ，并且目标的模式是 `a.%.b` ，那么， `$*` 的值就是 `dir/foo` 。这个变量对于构造有关联的文件名是比较有效。如果目标中没有模式的定义，那么 `$*` 也就不能被推导出，但是，如果目标文件的后缀是make所识别的，那么 `$*` 就是除了后缀的那一部分。例如：如果目标是 `foo.c` ，因为 `.c` 是make所能识别的后缀名，所以， `$*` 的值就是 `foo` 。这个特性是GNU make的，很有可能不兼容于其它版本的make，所以，你应该尽量避免使用 `$*` ，除非是在隐含规则或是静态模式中。如果目标中的后缀是make所不能识别的，那么 `$*` 就是空值。

当你希望只对更新过的依赖文件进行操作时， `$?` 在显式规则中很有用，例如，假设有一个函数库文件叫 `lib` ，其由其它几个object文件更新。那么把object文件打包的比较有效率的Makefile规则是：

```
lib : foo.o bar.o lose.o win.o
    ar r lib $?
```

在上述所列出来的自动量变量中。四个变量（ `$@` 、 `$<` 、 `$%` 、 `$*` ）在扩展时只会有一个文件，而另三个的值是一个文件列表。这七个自动化变量还可以取得文件的目录名或是在当前目录下的符合模式的文件名，只需要搭配上 `D` 或 `F` 字样。这是GNU make中老版本的特性，在新版本中，我们使用函数 `dir` 或 `notdir` 就可以做到了。 `D` 的含义就是Directory，就是目录， `F` 的含义就是File，就是文件。

下面是对于上面的七个变量分别加上 `D` 或是 `F` 的含义：

- `$(@D)`

  表示 `$@` 的目录部分（不以斜杠作为结尾），如果 `$@` 值是 `dir/foo.o` ，那么 `$(@D)` 就是 `dir` ，而如果 `$@` 中没有包含斜杠的话，其值就是 `.` （当前目录）。

- `$(@F)`

  表示 `$@` 的文件部分，如果 `$@` 值是 `dir/foo.o` ，那么 `$(@F)` 就是 `foo.o` ， `$(@F)` 相当于函数 `$(notdir $@)` 。

- `$(*D)`, `$(*F)`

  和上面所述的同理，也是取文件的目录部分和文件部分。对于上面的那个例子， `$(*D)` 返回 `dir` ，而 `$(*F)` 返回 `foo`

- `$(%D)`, `$(%F)`

  分别表示了函数包文件成员的目录部分和文件部分。这对于形同 `archive(member)` 形式的目标中的 `member` 中包含了不同的目录很有用。

- `$(<D)`, `$(<F)`

  分别表示依赖文件的目录部分和文件部分。

- `$(^D)`, `$(^F)`

  分别表示所有依赖文件的目录部分和文件部分。（无相同的）

- `$(+D)`, `$(+F)`

  分别表示所有依赖文件的目录部分和文件部分。（可以有相同的）

- `$(?D)`, `$(?F)`

  分别表示被更新的依赖文件的目录部分和文件部分。

最后想提醒一下的是，对于 `$<` ，为了避免产生不必要的麻烦，我们最好给 `$` 后面的那个特定字符都加上圆括号，比如， `$(<)` 就要比 `$<` 要好一些。

还得要注意的是，这些变量只使用在规则的命令中，而且一般都是“显式规则”和“静态模式规则”。其在隐含规则中并没有意义。

### 模式匹配

一般来说，一个目标的模式有一个有前缀或是后缀的 `%` ，或是没有前后缀，直接就是一个 `%` 。因为 `%` 代表一个或多个字符，所以在定义好了的模式中，我们把 `%` 所匹配的内容叫做“茎”，例如 `%.c` 所匹配的文件“test.c”中“test”就是“茎”。因为在目标和依赖目标中同时有 `%` 时，依赖目标的“茎”会传给目标，当做目标中的“茎”。

当一个模式匹配包含有斜杠（实际也不经常包含）的文件时，那么在进行模式匹配时，目录部分会首先被移开，然后进行匹配，成功后，再把目录加回去。在进行“茎”的传递时，我们需要知道这个步骤。例如有一个模式 `e%t` ，文件 `src/eat` 匹配于该模式，于是 `src/a` 就是其“茎”，如果这个模式定义在依赖目标中，而被依赖于这个模式的目标中又有个模式 `c%r` ，那么，目标就是 `src/car` 。（“茎”被传递）

### 重载内荐隐含规则

你可以重载内建的隐含规则（或是定义一个全新的），例如你可以重新构造和内建隐含规则不同的命令，如：

```
%.o : %.c
    $(CC) -c $(CPPFLAGS) $(CFLAGS) -D$(date)
```

你可以取消内建的隐含规则，只要不在后面写命令就行。如：

```
%.o : %.s
```

同样，你也可以重新定义一个全新的隐含规则，其在隐含规则中的位置取决于你在哪里写下这个规则。朝前的位置就靠前。

## 老式风格的"后缀规则"

后缀规则是一个比较老式的定义隐含规则的方法。后缀规则会被模式规则逐步地取代。因为模式规则更强更清晰。为了和老版本的Makefile兼容，GNU make同样兼容于这些东西。后缀规则有两种方式：“双后缀”和“单后缀”。

双后缀规则定义了一对后缀：目标文件的后缀和依赖目标（源文件）的后缀。如 `.c.o` 相当于 `%o : %c` 。单后缀规则只定义一个后缀，也就是源文件的后缀。如 `.c` 相当于 `% : %.c` 。

后缀规则中所定义的后缀应该是make所认识的，如果一个后缀是make所认识的，那么这个规则就是单后缀规则，而如果两个连在一起的后缀都被make所认识，那就是双后缀规则。例如： `.c` 和 `.o` 都是make所知道。因而，如果你定义了一个规则是 `.c.o` 那么其就是双后缀规则，意义就是 `.c` 是源文件的后缀， `.o` 是目标文件的后缀。如下示例：

```
.c.o:
    $(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<
```

后缀规则不允许任何的依赖文件，如果有依赖文件的话，那就不是后缀规则，那些后缀统统被认为是文件名，如：

```
.c.o: foo.h
    $(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<
```

这个例子，就是说，文件 `.c.o` 依赖于文件 `foo.h` ，而不是我们想要的这样：

```
%.o: %.c foo.h
    $(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<
```

后缀规则中，如果没有命令，那是毫无意义的。因为他也不会移去内建的隐含规则。

而要让make知道一些特定的后缀，我们可以使用伪目标 `.SUFFIXES` 来定义或是删除，如：

```
.SUFFIXES: .hack .win
```

把后缀 `.hack` 和 `.win` 加入后缀列表中的末尾。

```
.SUFFIXES:              # 删除默认的后缀
.SUFFIXES: .c .o .h   # 定义自己的后缀
```

先清除默认后缀，后定义自己的后缀列表。

make的参数 `-r` 或 `-no-builtin-rules` 也会使用得默认的后缀列表为空。而变量 `SUFFIXE` 被用来定义默认的后缀列表，你可以用 `.SUFFIXES` 来改变后缀列表，但请不要改变变量 `SUFFIXE` 的值。

## 隐含规则搜索算法

比如有一个目标叫 T。下面是搜索目标T的规则的算法。请注意，没有提到后缀规则，原因是，所有的后缀规则在Makefile被载入内存时，会被转换成模式规则。如果目标是 `archive(member)` 的函数库文件模式，那么这个算法会被运行两次，第一次是找目标T，如果没有找到的话，那么进入第二次，第二次会把 `member` 当作T来搜索。

1. 把T的目录部分分离出来。叫D，而剩余部分叫N。（如：如果T是 `src/foo.o` ，那么，D就是 `src/` ，N就是 `foo.o` ）
2. 创建所有匹配于T或是N的模式规则列表。
3. 如果在模式规则列表中有匹配所有文件的模式，如 `%` ，那么从列表中移除其它的模式。
4. 移除列表中没有命令的规则。
5. 对于第一个在列表中的模式规则：
   1. 推导其“茎”S，S应该是T或是N匹配于模式中 `%` 非空的部分。
   2. 计算依赖文件。把依赖文件中的 `%` 都替换成“茎”S。如果目标模式中没有包含斜框字符，而把D加在第一个依赖文件的开头。
   3. 测试是否所有的依赖文件都存在或是理当存在。（如果有一个文件被定义成另外一个规则的目标文件，或者是一个显式规则的依赖文件，那么这个文件就叫“理当存在”）
   4. 如果所有的依赖文件存在或是理当存在，或是就没有依赖文件。那么这条规则将被采用，退出该算法。
6. 如果经过第5步，没有模式规则被找到，那么就做更进一步的搜索。对于存在于列表中的第一个模式规则：
   1. 如果规则是终止规则，那就忽略它，继续下一条模式规则。
   2. 计算依赖文件。（同第5步）
   3. 测试所有的依赖文件是否存在或是理当存在。
   4. 对于不存在的依赖文件，递归调用这个算法查找他是否可以被隐含规则找到。
   5. 如果所有的依赖文件存在或是理当存在，或是就根本没有依赖文件。那么这条规则被采用，退出该算法。
   6. 如果没有隐含规则可以使用，查看 `.DEFAULT` 规则，如果有，采用，把 `.DEFAULT` 的命令给T使用。

一旦规则被找到，就会执行其相当的命令，而此时，我们的自动化变量的值才会生成。

# 十、使用make更新函数库文件

函数库文件是对object文件(程序编译的中间文件)的打包文件。在linux下，一般是由命令`ar`来完成打包工作

## 函数库文件的成员

一个函数库文件有多个文件组成。可以使用如下格式指定函数库文件及其组成：

```
archive(member)
```

这个不是一个命令，而是一个目标和依赖的定义。一般来说，这种用法基本上就是为了`ar`命令来服务。如

```
foolib(hack.o) : hack.o
    ar cr foolib hack.o
```

如果要指定多个member，那就以空格分开，如:

```
foolib(hack.o kludge.o)
```

其等价于:

```
foolib(hack.o) foolib(kludge.o)
```

还可以使用Shell的文件通配符来定义，如:

```
foolib(*.o)
```

## 函数库成员的隐含规则

当make搜索一个目标的隐含规则时，一个特殊的特性是，如果这个目标是 `a(m)` 形式的，其会把目标变成 `(m)` 。于是，如果我们的成员是 `%.o` 的模式定义，并且如果我们使用 `make foo.a(bar.o)` 的形式调用Makefile时，隐含规则会去找 `bar.o` 的规则，如果没有定义 `bar.o` 的规则，那么内建隐含规则生效，make会去找 `bar.c` 文件来生成 `bar.o` ，如果找得到的话，make执行的命令大致如下:

```
cc -c bar.c -o bar.o
ar r foo.a bar.o
rm -f bar.o
```

还有一个变量要注意的是 `$%` ，这是专属函数库文件的自动化变量。

## 函数库文件的后缀规则

你可以使用“后缀规则”和“隐含规则”来生成函数库打包文件，如：

```
.c.a:
    $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $*.o
    $(AR) r $@ $*.o
    $(RM) $*.o
```

其等效于：

```
(%.o) : %.c
    $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $*.o
    $(AR) r $@ $*.o
    $(RM) $*.o
```

## 注意事项

在进行函数库打包文件生成时，请小心使用make的并行机制（ `-j` 参数）。如果多个 `ar` 命令在同一时间运行在同一个函数库打包文件上，就很有可以损坏这个函数库文件。所以，在make未来的版本中，应该提供一种机制来避免并行操作发生在函数打包文件上。

但就目前而言，尽量不要使用 `-j` 参数。