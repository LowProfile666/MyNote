<center><h1>spuer</h1></center>

[TOC]

# 一、概述

`super` 是一个关键字，全部小写

`super`的原理：

![image-20230215114120421](https://gitee.com/zsm666/image-bed/raw/master/img/super%E7%9A%84%E5%8E%9F%E7%90%86.png)

super的使用：

+ `super(实参)`【调用父类的构造方法】

+ `super.属性名`【访问父类的属性】

+ `super.方法名(实参)`【访问父类的方法】

---

# 二、super和this

## 1、this

- `this ` 能出现在实例方法中和构造方法中。
- `this  `的语法是：`this.`  和  `this()。`
- `this  `不能使用在静态方法中。
- `this`.  大部分情况下是能省略的。
- `this.`  在区分局部变量和实例变量的时候不能省略。
- `this()`  只能出现在构造方法的第一行，通过当前的构造方法去调用本类中其他的构造方法，目的是：代码复用。

---

## 2、super

- `super  `能出现在实例方法中和构造方法中。
- `super  `的语法是：`super.`  和 ` super()。`
- `super  `不能使用在静态方法中。
- `super. ` 大部分情况下是能省略的。
- `super` 在区分父类和子类同名属性或方法时不能省略。
- `super() ` 只能出现在构造方法的第一行，通过当前的构造方法去调用父类中其他的构造方法，目的是：创建子类的时候，先初始化父类型特征。

注意：`this()` 和 `super()`  不能共存，他们都是只能出现构造方法第一行。

`super  `什么时候不能省略？父类和子类中有同名属性，或者说有同样的方法，想在子类中访问父类的时候，`super`不能省略。

```java
class Customer{
	String name;
	public Customer(){}
	public Customer(String name){
		this.name = name;
	}
}
class Vip extends Customer{
	public Vip(){}
	public Vip(String name){
		super(name);
	}
	// super 和 this 都不能出现在静态方法中
	public void shop(){
		// this表示的当前对象
		System.out.println(this.name + "shopping");
		// super表示的是当前对象的父类型特征
		System.out.println(super.name + "shopping");
		System.out.println(name + "shopping");
	}
}
```

---

# 三、super()

==当一个构造方法第一行既没有`this()`又没有`super()`的话，默认有一个`super()`==。表示通过当前子类的构造方法调用父类的无参构造方法，所以必须保证父类的无参构造方法是存在的。

在构造方法执行过程中一连串调用了父类的构造方法，父类的构造方法又继续调用他的父类构造方法，但实际上只创建了一个对象。

## 1、无实参

`super()`：表示通过子类的构造方法调用父类的构造方法。

模拟现实世界中的这种场景：想要有儿子，需要先有父亲。

```java
public class Super01{
	public static void main(String[] args){
		new B();
		/*
			A的构造方法
			B的构造方法
		*/
	}
}

class A{
	/*
	public A(){
		System.out.println("A的构造方法");
	}*/
	// 一个类如果没有手动提供任何构造方法，系统会默认提供一个无参构造方法
	// 一个类如果手动提供了一个构造方法，那么系统就不会提供无参构造方法
	public A(int i){
		
	}
}
class B extends A{
	public B(){
		// 这里默认有一行：super();
		// this(1);
		System.out.println("B的构造方法");
	}
}
```

无论怎样，父类的构造方法必执行。在Java中不管new什么对象，最后老祖宗的`Object`类的无参构造方法一定会执行（`Object`类的无参构造方法是处于“栈顶部”）。

---

## 2、带实参

作用：初始化当前对象的父类型特征，并不是创建新对象，实际上对象只创建了一个。

`super`关键字代表的就是“当前对象”的那部分父类特征

- 我继承了我父亲的一部分特征，例如：眼睛、皮肤，`super`代表的就是“眼睛、皮肤”。

- 虽然是继承父亲的，但是这部分都在我身上。

调用父类有参构造方法，在恰当的时间使用。

```java
/*  举个例子：在恰当的时间使用：super(实参列表)  */
public class Super02{
	public static void main(String[] args){
		CreditAccount ca = new CreditAccount();
	}
}
class Account{
	private String name;
	private double balance;

	public Account(){}
	public Account(String name, double balance){
		this.name = name;
		this.balance = balance;
	}
}
class CreditAccount extends Account{
	// 子类特有的特征属性：诚信值
	private double credit;

	public CreditAccount(){}
	public CreditAccount(String name, double balance, double credit){
		// 私有属性只能在本类中访问
		/*
		this.name = name;
		this.balance = balance;
		*/
		// 以上两行代码在恰当的位置，正好可以使用super(实参列表)
		// 通过 子类的构造方法调用父类的构造方法
		super(name, balance);
		this.credit = credit;
	}
}
```

---

# 四、结论

`super `不是引用，`super`也不保存内存地址，`super`也不指向任何对象，`super `只是代表当前对象内部的那一块父类型的特征。

```java
/*
	结论：
		super 不是引用，super也不保存内存地址，super也不指向任何对象
		super 只是代表当前对象内部的那一块父类型的特征
*/
public class Super05{

	public void doSome(){
		// 输出 引用 的时候，会自动调用引用的toString方法
		System.out.println(this);  // Super05@5ca881b5

		// 编译错误: 需要'.'
		// System.out.println(super); 
	}

	/* this 和 super 不能使用在static中
	public static void doOther(){
		// 错误: 无法从静态上下文中引用非静态 变量 this/super
		System.out.println(this);
		System.out.println(super.xx);
	}
	*/
	public static void main(String[] args){
		Super05 s = new Super05();
		s.doSome();
	}
}
```

