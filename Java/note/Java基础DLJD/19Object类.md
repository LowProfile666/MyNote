<center><h1>Object类</h1></center>

[TOC]

# 一、概述

Object类的方法都是所有子类通用的，任何一个类默认继承Object，就算没有直接继承，最终也会间接继承。关于Object类中的方法，可以去源代码中或者查阅Java的类库的帮助文档来学习这些方法。

什么是API？

应用程序编程接口（Application Program Interface）：整个JDK 的类库就是一个`javase `的API，每一个API都会配置一套API帮助文档。SUN公司提前写好的这套类库就是API，一般每一份API都对应一份API帮助文档。

---

# 二、常用方法

## 1、toString

`String toString()`：返回对象的字符串表示形式。

默认实现方式：`类名@对象的内存地址转换为十六进制的形式`。

源代码样式：

```java
public String toString(){
	return getClass().getName() + "@" + Integer.toHexString(hashCode());
}
```

所以以后所有的类都要重写`toString()`方法，重写得越简单明了越好。

`System.out.println(引用) `这里会自动调用`引用`的`toString`方法。`String`类是SUN写的，`toString`方法已经重写了。

```java
package code.Object类;

public class Test01{
	public static void main(String[] args){
		MyTime mt = new MyTime(1970,1,1);
		String t1 = mt.toString();

		// 没有重写toString方法时
		System.out.println(t1);  // MyTime@4517d9a3

		// 重写toString方法吼
		System.out.println(t1);  // 1970年1月1日

		// 直接输出引用会自动调用toString方法
		System.out.println(mt);  // 1970年1月1日
	}
}

class MyTime{
	int year;
	int month;
	int day;

	public MyTime(){
		
	}

	public MyTime(int year, int month, int day){
		this.year = year;
		this.month = month;
		this.day = day;
	}

	// 重写toString方法
	public String toString(){
		return this.year + "年" + this.month + "月"+ this.day + "日";
	}
}
```

---

## 2、equals

`boolean equals(Object obj) `：指示其他对象是否“等于”此对象（判断两个对象是否相等）。

设计`equals`方法的目的：通过该方法判断两个对象是否相等。

源代码样式：

```java
public boolean equals(Object obj){
    return (this == obj);
}
```

在Object类中的`equals`方法当中，默认采用的是`==`判断两个Java对象是否相等，而`==`判断的是两个Java对象的内存地址，我们应该判断两个Java对象的内容是否相等，所以Object类的`equals`方法不够用，需要子类重写。

Java中什么类型的数据可以使用`==`判断？Java中**基本数据类型**比较是否相等，使用`==`。

Java中什么类型的数据需要使用`equals`判断？Java中所有的**引用数据类型**统一使用`equals`方法来判断是否相等。

判断两个Java对象是否相等不能使用`==`，因为`==`比较的是两个对象的内存地址：

```java
package code.Object类;

public class Test02{
	public static void main(String[] args){
		// 判断两个基本类型的数据是否相等，直接用 == 就行
		int i = 100;
		int j = 100;
		// 这个 == 判断i中保存的100和j中保存的100是否相等
		System.out.println(i == j);  // true相等，false不等

        // 判断两个对象相等不能直接使用 == 
		MyTime t1 = new MyTime(2008,8,8);  // 创建一个MyTime对象，MyTime t1 = 0x1234
		MyTime t2 = new MyTime(2008,8,8);  // 再创建一个MyTime对象，MyTime t2 = 0x4567

		//  这里的 == 判断的是：t1中保存的对象内存地址和t2中保存的对象内存地址是否相等
        System.out.println(t1 == t2);  // false

		// 使用 qeuals 方法比较对象是否相等
		System.out.println(t1.equals(t2));  // true
	}
}

class MyTime{
	int year;
	int month;
	int day;

	public MyTime(){
		
	}

	public MyTime(int year, int month, int day){
		this.year = year;
		this.month = month;
		this.day = day;
	}
	public boolean equals(Object obj){
		if(obj == null) return false;
		if(obj instanceof MyTime){
			MyTime m = (MyTime)obj;
			return this.year == m.year 
				&& this.month == m.month 
				&& this.day == m.day;
		}
		return false;
	}
}
```

### 2.1、String类

已经重写了`equals`方法，比较两个字符串不能使用`==`，必须使用`equals`，`equals`是通用的。

```java
package code.Object类;

public class Test03{
	public static void main(String[] args){
		// 大部分情况下采用这样的方式创建字符串对象
		String s1 = "hello";
		String s2 = "abc";

		// 实际上String是一个类，不属于基本数据类型，所以存在构造方法
		String s3 = new String("Test1");
		String s4 = new String("Test1");
		// new两次，两个对象的内存地址不同
        // == 判断的是内存地址，不是内容
		// System.out.println(s3 == s4);  // false

		// 比较两个字符串不能使用 == ，必须调用equals方法（String类已经重写）
        System.out.println(s3.equals(s4));  // true
	} 
}
```

---

## 3、finalize

`protected void finalize()`：垃圾回收器负责调用的方法。

源代码样式：

```java
@Deprecated(since="9")
protected void finalize() throws Throwable { }
```

该方法已被弃用。

`finalize`方法只有一个方法体，里面没有代码，而且这个方法是`protected`修饰的。这个方法不需要程序员手动调用，由JVM的垃圾回收器负责调用。

`finalize`方法实际上是SUN公司为Java程序员准备的一个时机，垃圾销毁时机。如果希望在对象销毁时机执行一段代码的话，这段代码要写到`finalize`方法当中。Java中的垃圾回收器不是轻易启动的，垃圾太少或者时间不到，有可能启动也有可能不启动。

```java
package code.Object类;

public class Test06{
	public static void main(String[] args){
//		Person p = new Person();
//
//		// 怎么把p变成垃圾
//		p = null;

		// 多造点垃圾
		/*for(int i = 0; i <= 1000000000; i++){
			Person p = new Person();
			p = null;
		}
		*/
		
		for(int i = 0; i <= 1000; i++){
			Person p = new Person();
			p = null;
			// 这一段代码可以建议启动垃圾回收器
			System.gc();  // 只是建议启动垃圾回收器，可能启动，也可能不启动
        }
	}
}
class Person{
	// 重写finalize方法
	// Person对象被回收时，垃圾回收器负责调用p.finalize()
	protected void finalize() throws Throwable{
		System.out.println(this + "即将被销毁");
	}
}
```

---

## 4、hashCode

`int hashCode()`：返回对象的哈希值。

源代码样式：

```java
@IntrinsicCandidate
public native int hashCode();
```

不是抽象方法，带有`native`关键字，底层调用C++程序。

`hashCode`方法返回的是哈希码：实际上就是一个Java对象的内存地址经过哈希算法得出的一个值，所以hashCode方法的执行结果可以等同看作一个Java对象的内存地址。

```java
public class Test07{
	public static void main(String[] args){
		Object o = new Object();
		int hashCodeValue = o.hashCode();

		// 对象内存地址经过哈希算法转换的一个值，可以等同看作内存地址。
		System.out.println(hashCodeValue);  // 617901222

		MyClass m = new MyClass();
		hashCodeValue = m.hashCode();
		System.out.println(hashCodeValue);  // 925858445
	}
}

class MyClass
{
}
```

---

## 5、clone

`protected Object clone() `：创建并返回对象的副本。

---

# 三、匿名内部类

什么是内部类？在类的内部又定义了一个新的类，被称为内部类。

内部类的分类：

+ 静态内部类：类似于静态变量
+ 实例内部类：类似于实例变量
+ 局部内部类：类似于局部变量

匿名内部类是局部内部类的一种。

```java
package code.Object匿名内部类

public class Test01{
	// 静态变量
	static String name;

	// 该类在类的内部，被称为内部类
	// 由于前面有static，所以该类是静态内部类
	static class Inner1	{
	}
	
	// 实例变量
	int age;
	// 没有static，是实例内部类
	class Inner2{
	}
	
	public void doSome(){
		// 局部变量
		int i = 100; 
		// 局部内部类
		class Inner3{
		}
	}
	public static void main(String[] args){
		// 调用MyMath中的mySum方法
		MyMath mm = new MyMath();
		// 这种写法表示这种类名是有的，类名是：ComputeImpl
		// mm.mySum(new ComputeImpl(), 100, 20);

		// 使用匿名内部类，表示这个ComputeImpl没名字了
		// 这里表面上看好像是可以直接new接口了，但实际上并不是new接口，后面的()代表了对接口的实现
		// 不建议直接使用匿名内部类，因为一个类没有名字没办法重复使用，而且代码太乱
		mm.mySum(new Compute(){
			public int sum(int a, int b){
				return a + b;
			}
		}, 100, 20);
	}
}

// 负责计算的接口
interface Compute{
	// 抽象方法
	int sum(int a, int b);
}

// 编写一个Compute接口的实现类
/*class ComputeImpl implements Compute{
	public int sum(int a, int b){
		return a + b;
	}
}
*/

// 数学类
class MyMath{
	// 求和方法
	public void mySum(Compute c, int x, int y){
		System.out.println(x + "+" + y + "=" + c.sum(x, y));
	}
}
```

