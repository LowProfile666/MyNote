<center><h1>package&import</h1></center>

[TOC]

# 一、概述

`package`是Java中包机制，包机制的作用是为了方便程序的管理。

不同功能的类分别存放在不同的包下。（按照功能划分的，不同的软件包具有不同功能）。

---

# 二、package

`package`是一个关键字，后面加包名。例如：`package com.xxx.xxx.xxx`。

注意：`package`语句只允许出现在==Java源代码的第一行==。

## 1、命名规范

一般都采用==公司域名倒序==的方式（因为公司域名具有全球唯一性）：`公司域名倒序 + 项目名 + 模块名 + 功能名`。

以后说类名的时候，如果带着包名描述表示完整类名；如果没有带包名描述的话，表示简类名。

---

## 2、编译运行

带有`package`的Java程序的编译和运行：

编译：`javac -d . test1.java`

+ `javac  `负责编译的命令
+ `-d`  带包编译
+ `. `  代表编译之后生成的东西放到当前目录下（点代表当前目录）
+ `test1.java ` 被编译的Java文件名
+ 会自动生成目录(`com/javaTest/code/test`)

运行：`java com.javaTest.code.test.test1`

```java
package com.javaTest.code.test;

public class test1{
	public static void main(String[] args){
		System.out.println("Hello world");
	}
}
```

---

# 三、import

`import`语句只能出现在`package`语句之下，`class`声明语句之上。

## 1、使用方法

语法格式：`import 完整类名;`或者`import 包名.*;`。

`import java.util.* ` 这个效率不比`import java.util.具体类名`低，因为编译器在编译的时候，会自动把`*`变成具体的类名。

`import java.* ` 这是不允许的，因为在Java语言中规定，这里的`*`指代表某些类的名字。

使用不同`package`内的方法，`import`时必须要把包名全部写下来。

```java
package com;

// 将需要的类引入
//import com.javaTest.code.test.test1;
import com.javaTest.code.test.*;

public class test03{
	public static void main(String[] args){
		/*
			test03不在com包下
			test1在com.javaTest.code.test下
			不在同一个package里，包名不可以省略。
		*/
		//  错误：找不到符号
		/*
		test1 t = new test1();
		System.out.println(t);
		*/
		/*
		com.javaTest.code.test.test1 t = new com.javaTest.code.test.test1();
		System.out.println(t);  // com.javaTest.code.test.test1@6483f5ae
		*/
		test1 t = new test1();
		System.out.println(t);  // com.javaTest.code.test.test1@80169cf
	}
}
```

---

## 2、使用时机

A类中使用B类，A和B都在同一个包下，不需要`import`；A和B不在同一个包下，需要使用`import`，并且`import`时必须将类名写全。

`java.lang.*`  这个包下的类不需要使用`import`导入。
