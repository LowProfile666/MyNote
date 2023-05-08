<center><h1>
    final
    </h1></center>

[TOC]

# 一、概述

`final`是Java中的一个关键字，表示最终的，不可变的，不可改的。

`final`可以修饰变量以及方法，还有类等。

+ `final`修饰的类无法被继承。
+ `final`修饰的方法无法被重写、覆盖。
+ `final`修饰的局部变量，只能赋一次值。
+ `final`修饰的引用只能指向一个对象。

```java
public class Final01{
	public static void main(String[] args){
		// 局部变量
		int i = 100;
		// 重新赋值
		i = 200;

		// 局部变量
		final int k = 100;
		// 重新赋值
		// 错误: 无法为最终变量k分配值
		// k = 200;

		final int m;
		// 第一次赋值
		m = 1000;
		// 重新赋值
        // 错误：可能已分配变量m
		m = 200;
	}
}

/*final class A{
}

// B类继承A类，相当于对A类的功能进行扩展，如果不希望对A类进行扩展，可以给A加final关键字
// 错误: 无法从最终A进行继承
class B extends A{

}*/	

/*class C{
	public final void method(){
		System.out.println("C");
	}
}

class D extends C{
	/*
		错误: D中的method()无法覆盖C中的method()
		被覆盖的方法为final
	
	public void method(){
		System.out.println("D");
	}
}*/
```

---

# 二、修饰引用

`final`修饰的引用只能指向一个对象，并且只能永远指向该对象，无法再指向其他对象，并且在该方法执行过程中，该引用指向对象之后，该对象不会被垃圾回收器回收，直到当前方法结束，才会释放空间.

```java
public class Final02{
	public static void main(String[] args){
		Person p1 = new Person(12);
		System.out.println(p1.age);  // 12
		// ==============================================
		// 代码不管怎么变化，p2也是一个变量，只不过是一个引用
		final Person p2 = new Person(30);
        // 以下都错，错误: 无法为最终变量p2分配值
		// p2 = new Person(30);
		// p2 = null;
		p2.age = 40;
		System.out.println(p2.age);  // 40
	}
}

class Person{
	int age;
	public Person(){}
	public Person(int age){ this.age = age; }
}
```

虽然`final`的引用指向对象A后，不能再指向对象B，但是对象A内部的数据可以 被修改。

![image-20230215111850481](https://gitee.com/zsm666/image-bed/raw/master/img/final%E4%BF%AE%E9%A5%B0%E7%9A%84%E5%BC%95%E7%94%A8.png)

---

# 三、修饰实例变量

`final`修饰的实例变量，要求程序员必须手动赋值(在变量后赋值可以，在构造器里赋值也可以；实例变量有默认值，局部变量没有默认值)。

```java
/*
	结论：
		final修饰的实例变量，系统不管赋默认值，要求程序员必须手动赋值
		在变量后赋值可以，在构造器里赋值也可以
		（实例变量有默认值，局部变量没有默认值）
	实例变量在什么时候赋值（初始化）
		构造方法过程中赋值，new 的时候赋值
*/
public class Final03{
	public static void main(String[] args){
		User u = new User();
	}
}

class User{
	// 实例变量
	// 错误: 变量 age 未在默认构造器中初始化
	// final int age;

	// 实例变量
	// 可以，手动赋值了
	final double height = 1.0;

	// 实例变量
	// 可以
	final double weight;
	// 构造方法
	public User(){
		weight = 80.0;  // 只要赶在系统赋默认值之前赋值就行
		// weight = 80.0;  //  错误: 可能已分配变量weight
	}
}
```

---

# 四、常量

`final`修饰的实例变量一般和`static`联合使用，称为**常量**。

常量实际上和静态变量一样，区别在于：

+ 常量的值不能变
+ 常量和静态变量都存储在方法区，并且都是在类加载时初始化
+ 常量一般是公开的

```java
/*

	final修饰的实例变量一般添加static修饰
	结论：
		static final 联合修饰的变量被称为“常量”
		常量名建议全部大写，每个单词之间采用下划线连接
	常量：实际上和静态变量一样，区别在于：
		常量的值不能变
		常量和静态变量都存储在方法区，并且都是在类加载时初始化
	常量一般是公开的
*/
public class Final04{
	public static void main(String[] args){
		System.out.println(Chinese.COUNTRY);
	}
}

class Chinese{
	// 身份证号和姓名每个人都不一样，对象级别的
	String id;
	String name;
	// 国家是一个固定值
	// 实例变量在堆中，一个对象一份
	// 实例变量既然使用final 修饰了，说明该实例变量值不会随着对象的变化而变化
	// 改实例变量前面应该添加：static关键字，变为静态的，存储在方法区，节省内存
	// final static String country = "中国";
	static final String COUNTRY = "中国";
}
```

