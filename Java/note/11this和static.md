<center><h1>this和static</h1></center>

[TOC]

# 一、static

`static `翻译为 “静态”，所有`static`关键字修饰的都是类相关的、类级别的。

所有`static`修饰的，都是采用“`类名.`”的方式访问

- 实例的：一定需要使用“**`引用.`**”来访问
- 静态的：建议使用“`类名.`”来访问，也可以使用“`引用.`”来访问（不建议后者，会让程序员产生困惑）。

## 1、静态变量和静态方法

`static`修饰的变量叫做：静态变量。

`static`修饰的方法叫做：静态方法

变量的分类，根据声明的位置分：

- 在方法体当中声明的变量叫做：局部变量
- 在方法体外声明的变量叫做：成员变量
- 成员变量又分为：静态变量、实例变量

静态变量在类加载的时候初始化，不需要new对象，静态变量的空间就开出来了，静态变量存储在方法区。

```java
class T{
    // 以下实例的都是对象相关的，访问时采用“对象.”方式访问，需要先new对象
    // 成员变量中的实例变量
    int i;
    // 实例方法
    public void m1(){}
    
    // 以下静态的都是类相关的，访问时采用“类名.”方式访问，不需要new对象
    // 成员变量中的静态变量
    static int j;
    // 静态方法
    public static void m2(){}
}
```

空引用访问静态变量不会空指针异常，因为静态变量不需要对象的存在。

![image](https://gitee.com/zsm666/image-bed/raw/master/img/%E7%A9%BA%E5%BC%95%E7%94%A8%E8%AE%BF%E9%97%AE%E9%9D%99%E6%80%81%E5%8F%98%E9%87%8F%E4%B8%8D%E4%BC%9A%E7%A9%BA%E6%8C%87%E9%92%88%E5%BC%82%E5%B8%B8.jpg)

空指针异常只有在“空引用”访问“实例”相关的情况下发生。	

----

## 2、静态的和实例的

一个对象一份的是实例变量，所有对象一份的是静态变量。

+ 如果这个类型的所有对象的某个属性值都是一样的，建议定义为类级别的、静态变量。

声明为实例变量

```java
public class Test{
    public static void main(String[] args){
        Chinese c1 = new Chinese();
        Chinese c2 = new Chinese();
    }
}
class Chinese{
    // 身份证号
    // 每一个人的身份证号不同，所以身份证号应该是实例变量，一个对象一份
    String idCard;
    
    // 姓名
    // 姓名也是实例变量，一个人一个姓名
    Stirng name;
    
    // 国籍
    // 对于“中国人”这个类来说，国籍都是中国，不会随着对象的改变而改变
    // 显然国籍不是对象级别的特征，是属于整个类的特征
    String country;
}
```

以上代码内存图：

![image-20230215155724937](https://gitee.com/zsm666/image-bed/raw/master/img/%E5%A3%B0%E6%98%8E%E4%B8%BA%E5%AE%9E%E4%BE%8B%E5%8F%98%E9%87%8F.png)

声明为静态变量

```java
public class Test{
    public static void main(String[] args){
        Chinese c1 = new Chinese();
        Chinese c2 = new Chinese();
    }
}
class Chinese{
    // 身份证号
    // 每一个人的身份证号不同，所以身份证号应该是实例变量，一个对象一份
    String idCard;
    
    // 姓名
    // 姓名也是实例变量，一个人一个姓名
    Stirng name;
    
    // 国籍
    // 加了static就是静态变量了
    // 静态变量在类加载的时候初始化，不需要new对象，静态变量的空间就开出来了
    // 静态变量存储在方法区
    String country = "China";
}
```

以上代码内存图

![image-20230215155952941](https://gitee.com/zsm666/image-bed/raw/master/img/i%E5%A3%B0%E6%98%8E%E4%B8%BA%E9%9D%99%E6%80%81%E5%8F%98%E9%87%8F.png)

---

## 3、实例方法

实例相关的都是需要new对象的，通过“`引用.`”访问；静态相关的都是采用“`类名.`”访问，不建议用“`引用.`”。

方法一般都是描述一个行为，如果说该行为必须由对象去触发，那么该方法定义为实例方法。

静态方法访问实例变量会报错

```java
class User{
    // id是实例变量，需要用对象访问
    private int id;
    // 错误：无法从静态上下文中引用非静态变量id
    public static void setId(int i){
        id = i;
    }
}
```

当这个方法体中直接访问了实例变量，这个方法一定是实例方法。

---

## 4、静态代码块

使用`static`可以定义静态代码块。

定义语法：

```java
static {
    java 语句;
    ...
}
```

静态代码块在类加载时并且在`main`方法执行之前执行，并只执行一次.

+ 在程序执行之前，凡是需要加载的类全部加载到JVM中，先完成加载后，才会执行`main`方法。

静态代码块一般是按照自上而下的顺序执行。

静态代码块的作用：

+ 不常用
+ 一个时机，类加载的时机

代码执行顺序：

```java
public class Test{
    static int i = 100;
    static {
        System.out.println(i);  // 100
    }
    int k = 200;  // 实例变量，在构造方法执行时内存空间才会开辟
    static {
        System.out.println(k);  // 错误：无法从静态上下文中引用非静态变量k
        // 类加载时，k的空间还没有开辟出来
    }
    static {
        System.out.println(j);  // 错误：非法向前引用
        // 静态代码块和静态变量都在类加载的时候执行，时间相同
        // 只能靠代码的顺序来决定先后
    }
    static int j = 300;
    public static void main(String[] args){
        
    }
}
```

---

## 5、实例代码块

除了静态方法块之外，还有一种语句块叫做：实例语句块。实力语句块在类加载时没有执行。

定义语法：

```java
{
    java语句;
    ...
}
```

实例语句块在什么时候执行？只要是构造方法执行，必然在构造方法之前自动执行实例语句块。

```java
public class Test{
    // 实例语句块
    {
        System.out.println("HelloWorld");
    }
    public Test(){
        System.out.println("无参构造方法");
    }
    public static void main(String[] args){
        Test t = new Test();
        /*
        输出：
        HelloWorld
        无参构造方法
        */
    }
}
```

作用：一个时机，创建对象时机。

---

# 二、this

`this`是一个关键字，全是小写。一个对象一个`this`。

## 1、this是什么

this是一个变量，是一个引用。this 保存当前对象的内存地址，指向自身。严格意义上，this代表的就是 “当前对象”，this存储在堆内存当中对象的内部。

this内存图

![image-20230215162211807](https://gitee.com/zsm666/image-bed/raw/master/img/this%E5%86%85%E5%AD%98%E5%9B%BE.png)

---

## 2、this的使用

this只能使用在实例方法中，谁调用这个实例方法，this就是谁，所以this代表的是：当前对象。

为什么this不能使用在静态方法中？因为静态方法是用“`类名.`”来访问的，不需要对象。

```java
public static void doSome(){
    // this代表的是当前对象，而静态方法的调用不需要对象
    System.out.println(this.name);  // 错误：无法从静态上下文中引用非静态变量this
}
```

this除了可以使用在实例方法中，还可以使用在构造方法中。通过当前的构造方法可以去调用另一个本类的构造方法，语法：t`his（实际参数列表）`。

```java
// 无参构造
public Date(){
 	// year  = 1970;
    // month = 1;
    // day = 1;
    this(1970, 1, 1);
}
// 有参构造
public Date(int year, int month, int day){
    this.year = year;
    this.day = day;
    this.month = month;
}
```

`this() `的作用是 代码复用

+ 通过“构造方法1”去“调用构造方法2”，可以做到代码复用。
+ 需要注意：构造方法1和构造方法2必须都是同一个类中。

`this()`的调用只能出现在构造方法的第一行。

```java
// 无参构造
public Date(){
    // 错误：对this的调用必须是构造器中的第一个语句
 	System.out.println();
    this(1970, 1, 1);
}
```

---

## 3、this的省略

this. 大部分情况下是可以省略的。

```java
public void shopping(){
    // this. 省略的话还是访问当前对象的name属性
    System.out.println(this.name + "正在购物");
    System.out.println(name + "正在购物");
}
```

在实例方法中或构造方法中，为了区分局部变量和实例变量时，this. 不能省略。

```java
// 有参构造
public Date(int year, int month, int day){
    this.year = year;
    this.day = day;
    this.month = month;
}
```

---

# 三、三大变量

Java中的三大变量：

![image-20230215163235163](https://gitee.com/zsm666/image-bed/raw/master/img/Java%E4%B8%AD%E7%9A%84%E4%B8%89%E5%A4%A7%E5%8F%98%E9%87%8F.png)

所有的实例相关的都是先创建对象，通过“`引用.`”来访问，所有的静态相关的都是直接采用“`类名.`”来访问。只要负责调用的方法a和被调用的方法b在同一个类中：`this. `和 `类名. `都可以省略。