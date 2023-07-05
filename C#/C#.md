下载 MSDN 文档：

在 VS2022 中，点击菜单栏的搜索框，搜索“Help Viewer”，下载安装“Help Viewer”，然后点开“Help”菜单，选择“Add and Remove Help Content”，就可以下载文档了。

VS 2022 配置：

![image-20230531171306785](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230531171306785.png)

# 1

Solution 和 Project：

Solution：解决方案，是 VS 里面的最高级别。是针对客户需求的总的解决方案。

Project：项目，一个 Solution 里面可以有多个 Project。解决具体的某个问题。



Console App：

![image-20230531165100593](C:/Users/20620/AppData/Roaming/Typora/typora-user-images/image-20230531165100593.png)

WindowsForms App（.NET Framwork）：

![image-20230531165225725](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230531165225725.png)

WinForms App：

![image-20230531165301141](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230531165301141.png)

WPF App：

![image-20230531165023148](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230531165023148.png)

---

# 类和名称空间

类（class），名称空间（namespace）

类（class）构成程序的主体

名称空间（namespace）以树型结构组织类（和其他类型）

类库引用是使用名称空间的物理基础，不同技术类型的项目会默认引用不同的类库

DLL引用（黑盒引用，无源代码）

项目引用（白盒引用，有源代码 ）

## 类、对象、类成员

类 是现实世界事物的模型。

类与对象的关系：

对象也叫实例，是类经过“实例化”后得到的内存中的实体。依照类，可以创建对象，这就是“实例化”。

类的三大成员：

+ 属性（Property）：存储数据，组合起来表示类或对象当前的状态
+ 方法（Mothed）：表示类和对象“能做什么”
+ 事件（Event）：类或对象通知其他类或对象的机制，为 C# 特有。

静态（Static）成员在语义上表示它是“类的成员”

实例（非静态）成员在语义表示它是“对象的成员”

绑定（Binding）指的是编译器如何把一个成员与类或对象关联起来

# 基本元素

构成 C# 语言的基本元素

+ 关键字（Keyword）
+ 操作符（Operator）
+ 标识符（Identifier）
+ 标点符号
+ 文本（字面值）
+ 注释与空白

# 类型、变量、方法

类型（Type）：数据类型（Data Type），是数据在内存中存储时的“型号”。

类型包含的信息：

+ 存储此类型变量所需的内存空间大小
+ 此类型的值可表示的最大、最小值范围
+ 此类型所包含的成员（方法、属性、事件等）
+ 此类型由何基类派生而来
+ 程序运行的时候，此类型的变量在分配在内存的什么位置
+ 此类型允许的操作（运算）

使用 `var` 声明变量由编译器自己判断数据类型：

```c#
var x = 3.0;
Console.WriteLine(x.GetType().Name); 
```

使用 `dynamic` 声明的变量类型可以改变：

```c#
dynamic y = 100;
Console.WriteLine(y);  // 100
y = "nb";
Console.WriteLine(y);  // nb
```

变量是存放数据的地方，简称“数据”

方法（旧称：函数）是处理数据的逻辑，又称算法



C# 语言的类型系统

C# 的五大数据类型：

+ 类（Class）：如Windows、Form、Console、String
+ 结构体（Structures）：如Int32、Int64、Single、Double
+ 枚举（Enumerations）
+ 接口（Interfaces）
+ 委托（Delegates）

C# 类型的派生谱系：

![image-20230604141222859](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230604141222859.png)

什么是变量：

+ 表面上来看：变量的用途是存储数据
+ 实际上：变量表示了存储位置，并且每个变量都有一个类型，以决定什么样的值能够存入变量
+ 变量一共有 7 种
  + 静态变量、实例变量（成语变量、字段）、数组元素、值参数、引用参数、输出形参、局部变量
+ 狭义的变量只局部变量，因为其它种类的变量都有自己的约定名称

变量的声明：

<span style="color:#4679bd">【有效的修饰符组合】 类型 变量名 【初始化器】</span>

值类型的变量：

+ 值类型没有实例，所谓的“实例”与变量合二为一

引用类型的变量与实例：

+ 引用类型变量里存储的数据是对象的内存地址

<span style="color:red">变量 = 以变量名所对应的内存地址为起点、以其数据类型所要求的存储空间为长度的一块内存区域</span>。

 局部变量是在 stack 中分配内存。

变量的默认值：本地变量必须要赋初始值。

常量：值不可修改的变量。

装箱与拆箱（Boxing & Unboxing）

+ 装箱：把栈上的变量实例到堆上
+ 拆箱：把堆上的变量拿到栈上

# 方法的定义、调用与调试

方法永远都是类（或结构体）的成员：

+ C# 语言中的函数不可能独立于类（或结构体）之外
+ 只有作为类（结构体）的成员时才被称为方法

方法是类（或结构体）最基本的成员之一：

+ 最基本的成员只有两个——字段与方法（成员变量与成员函数），本质还是数据 + 算法
+ 方法表示类（或结构体）“能做什么事”

构造器：

构造器（constructor）是类型的成员之一。

狭义的构造器指的是“实例构造器”（instance constructor）。

方法的重载（Overload）：

方法签名（method signature）由方法的名称、类型、形参的个数和它的每一个形参（按从左到右的顺序）的类型和种类（值、引用或输出）组成。方法签名不包括返回类型。

实例构造函数签名由它的每一个形参（按从左到右的顺序）的类型和种类（值、引用或输出）组成。

重载决策（到底调用哪一个重载）：用于在给定了参数列表和一组候选函数成员的情况下，选择一个最佳函数成员来实施调用。

如何对方法进行 debug：

+ 设置断点（breakpoint）
+ 观察方法调用时的 call stack：查看当前方法的调用者![image-20230604163757087](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230604163757087.png)
+ Step-in（F11）、Step-over（F10）、Step-out（Shift+F11）
  + F11：进入方法内部
  + F10：不进入方法内部，直接将该方法执行完毕
  + Shift+F11：返回调用方法处
+ 观察局部变量的值与变化

方法的调用与栈：

stack frame：一个方法在被调用的时候，它在内存中的布局。

# 操作符

操作符（Operator），也叫“运算符”。

操作符是用来操作数据的，被操作符操作的数据称为操作数（Operand）。

![image-20230605133234710](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230605133234710.png)

操作符本质：

本质是函数（即算法）的“简记法”

操作符不能脱离与它关联的数据类型。

操作符就是与固定数据类型相关联的一套基本算法的简记法。

优先级与运算顺序：

上图中优先级从高到低依次减小。

可以使用圆括号提高被括起来表达式的优先级；圆括号可以嵌套。

除了带有赋值功能的操作符，同优先级操作符都是由左向右进行运算；带有赋值功能的操作符由右向左运算。

new ：创建一个实例，并调用实例构造器，也可以调用实例的初始化器。

```c#
Form f = new Form();  // 调用构造器
Form F = new Form(){ Text = "Hello" };  // 调用初始化器
```

匿名类型：

```c#
var p = new { Name = "Jack" , Age = 12};
Console.WriteLine(p.Name);  // Jack
Console.WriteLine(p.Age);  // 12
Console.WriteLine(p.GetType().Name);  // <>f__AnonymousType0`2
```

子类使用 new 关键字隐藏父类方法:

```c#
Student stu = new Student();
CsStudent csStu = new CsStudent();
stu.Report();  // I am a student
csStu.Report();  // I am a CS student

class Student
{
    public void Report()
    {
        Console.WriteLine("I am a student");
    }
    public string Name;
    public int Score;
}
class CsStudent : Student
{
    new public void Report()
    {
        Console.WriteLine("I am a CS student");
    }
}
```

default ：给变量赋类型默认值：

```c#
int x = default(int);
int y = default;
double d = default(double);
Form f = default;  // null
Level l = default;  // 获取的是枚举类型里的 0 的值，若没有 0 对应的值，就返回 0
Console.WriteLine(x);  // 0
Console.WriteLine(y);  // 0
Console.WriteLine(d);  // 0
Console.WriteLine(f == null);  // true
Console.WriteLine(l);  // Low

enum Level
{
    Low,  // 自动为 0
    Mid,  // 1
    High  // 2
}
```

checked、unchecked：检查一个值在内存中是否有溢出

```c#
try
{
    uint x = uint.MaxValue;
    uint y = checked(x + 1);  // 会抛出异常
    uint y = unchecked(x + 1);  // 不会抛出异常，结果不正常
    Console.WriteLine(y);
}
catch (OverflowException ex)
{
    Console.WriteLine("There's overflow");
}
```

或者这样写：

```c#
checked
{
    uint x = uint.MaxValue;
    uint y = checked(x + 1);
}
```

delegate ：关键字，声明 委托 / 匿名方法

sizeof：获取对象在内存中占的字节数

+ 默认情况下，sizeof 只能获取基本类型
+ 非默认情况下，可以获取自定义的结构体类型的字节大小，但是要在不安全的环境中

-> ：操作指针

```c#
Student s = new Student();
s.Name = "J";
s.Score = 99;
Console.WriteLine(s.Score);  // 99
Student* stu = &s;
stu->Score = 100;
Console.WriteLine(s.Score);  // 100
Console.WriteLine(stu->Score);  // 100
```

\* ：

```c#
Student s = new Student();
s.Name = "J";
s.Score = 99;
Console.WriteLine(s.Score);
Student* stu = &s;
(*stu).Score = 100;
Console.WriteLine(s.Score);
```

?? ：null 值合并：

可空类型：

```c#
Nullable<int> x = null;
x = 100;
Console.WriteLine(x);  // 100
Console.WriteLine(x.HasValue);  // true
```

Nullable 可以用 ? 代替，

```c#
int? x = null;
int y = x ?? 1;  // x 如果是 null，y 就是 1；x 不是 null，y 就是 x
Console.WriteLine(y);
```

# 类型转换

 隐式（implicit）类型转换

+ 不丢失精度的转换
+ 子类向父类德转换
+ 装箱

显式（explicit）类型转换

+ 有可能丢失精度（甚至发生错误）德转换，即 cast
+ 拆箱
+ 使用 Convert 类
+ ToString 方法与各数据类型德 Parse/TryParse 方法

# 表达式、语句

语句是高级语言的语法——汇编语言和机器语言只有指令（高级语言中的表达式对应低级语言中的指令），语句等价于一个或一组有明显逻辑关联的指令。

语句的作用：陈述算法思想，控制逻辑走向，完成有意义的动作。

C# 语句由分号结尾，但是由分号结尾的不一定都是语句。语句一定都是出现在方法体内的。

# 字段、属性、索引、常量

字段（field）是一种表示与对象或类型（类与结构体）关联的变量

+ 字段是类型的成员，旧称”成员变量“
+ 与对象关联的字段称为”实例字段“
+ 与类型关联的字段称为”静态字段“，由 static 修饰

字段声明：带有分号，但不是语句。

字段的初始值：

+ 无显式初始化时，字段获得其类型的默认值，所以字段”永远都不会未被初始化“
+ 实例字段初始化时机——对象创建时
+ 静态字段初始化时机——类型被加载（load）时

属性（property）是一种用于访问对象或类型的特征的成员，特征反映了状态

属性是字段的自然扩展：

常量（constant）是表示常量值（即可以在编译时计算的值）的类成员

常量属于类型而不是对象，即没有”实例常量“

# 参数

# 委托

委托（delegate）是函数指针的”升级版“。

直接调用：通过函数名来调用函数，CPU 通过函数名直接获得函数所在地址并开始执行

间接调用：通过函数指针来调用函数，CPU 通过读取函数指针存储的值获得函数所在地址并开始执行

委托的声明（自定义委托）

委托是一种类 ，类是数据类型所以委托也是一种数据类型

它的声明方式与一般的类不同

委托与封装的方法必须”类型兼容“

委托的使用

实例把方法当作参数传给另一个方法

+ 模板方法
+ 回调（callback）方法

委托的高级使用

+ 多播（multicast）委托
+ 隐式异步调用

# 事件

定义：单词 Event，

角色：使对象或类具备通知能力的成员

+ ”对象 O 有一个事件 E “想表达的是：当事件 E 发生的时候，O 有能力通知别的对象

使用：用于对象或类间的动作协调与信息传递（消息推送）

原理：事件模型（event model）中的两个 5

+ 发生 -> 响应 中的 5 个部分
+ 发生 -> 响应 中的 5 个动作

提示：

事件模型的组成部分：

+ 事件的拥有者（event source，对象）
+ 事件成员（event，成员）
+ 事件的响应者（event subscriber，对象）
+ 事件处理器（event handler，成员）——本质上是一个回调方法
+ 事件订阅——把事件处理器与事件关联在一起，本质上是一种以委托类型为基础的”约定“
