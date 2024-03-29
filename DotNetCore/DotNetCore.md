配置系统和日志系统没有细看。

# .Net Core

官方文档：https://learn.microsoft.com/en-us/dotnet/

## 介绍

DotNet Core 是一个平台。

C# 运行在 .NET 平台上。



## .NET Standard

.NET Standard 只是标准，不是实现。

只有定义，没有实现。

.NET Standard 只是规范，一个 .NET Standard 类库可以被支持其版本的 .NET Framework、.NET Core、Xamarin 等引用。而 .NET Core 类库、.NET Framework 类库则不可以。

如果编写一个公用的类库，尽量选择 .NET Standard，并且尽量用低版本。

## 使用命令行

在命令行窗口中输入 `dotnet` 回车，如果 dotnet 已安装会有以下界面：

![image-20230616153843624](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230616153843624.png)

查看版本：`dotnet --version。`

在当前路径下新建一个 console 项目：`dotnet new console `。

构建并运行：`dotnet run`。

其他命令可以在 .NET 文档中查看 CLI 。

## 程序的发布

两种文件：

+ `.csproj`：记录项目的描述信息
+ `.cs`：源代码文件
+ 在 .NET Core 中，默认所有文件都配置在 `.csproj` 中，除非手动 remove 掉

发布：

+ 右键单击项目，选发布

部署模式：

+ 依赖框架：需要目标机安装 .NET
+ 独立（推荐）

目标运行时

生成单个文件

ReadyToRun：

+ AOT（ahead-of-time）
+ JIT

裁剪未使用的程序集



## NuGet

使用方式：

+ NuGet CLI
+ VS 图形界面



# 异步编程

不能提高 Web 服务器的处理效率，只能提高 Web 服务器的同时处理的数量。

传统多线程开发太麻烦，C# 关键字 async、await 不等于“多线程”。

“异步方法”：用关键字 `async` 修饰的方法。

+ 异步方法的返回值一般是 Task\<T\>，T 是真正的返回值类型。惯例：异步方法名字以 Async 结尾。
+ 即使方法没有返回值，也最好把返回值声明为非泛型的 Task。
+ 调用反省方法时，一般在方法前加上 `await` 关键字，这样拿到的返回值就是反省指定的 T 类型。
+ 异步方法的“传染性”：一个方法中如果有 `await` 调用，则这个方法也必须修饰为 `async` 。

比如：

```c#
static async Task Main(string[] args)
{
    string fileName = "d:/1.txt";
    File.Delete(fileName);
    File.WriteAllTextAsync(fileName, "hello async");
    string s = await File.ReadAllTextAsync(fileName);
    Console.WriteLine(s);
}
```

使用异步方法获取网站的 HTML 内容：

```C#
static async Task Main(string[] args) 
{
    await DownloadHtmlAsync("https://www.youzack.com", "D:\\MyNote\\DotNetCore\\code\\1.txt");
}
static async Task DownloadHtmlAsync(string url, string filename)
{
    using (HttpClient httpClient = new HttpClient())
    {
        string html = await httpClient.GetStringAsync(url);
        await File.WriteAllTextAsync(filename, html);
    }
}
```

如果同样的功能，既有同步方法，又有异步方法，那么首先使用异步方法。

对于不支持的异步方法怎么办？使用

+ Wait()：是 Task 的方法，适用于无返回值的时候
+ Result ：是 Task 的属性，适用于有返回值时候

比如使用 Result：

```C#
static void Main(string[] args)
{
    // Task<string> t = File.ReadAllTextAsync("D:\\MyNote\\DotNetCore\\code\\youzackTest.txt");
    // string s = t.Result;
    string s = File.ReadAllTextAsync("D:\\MyNote\\DotNetCore\\code\\youzackTest.txt").Result;
    Console.WriteLine(s);
}
```

比如使用 wait()：

```c#
File.WriteAllTextAsync("D:\\MyNote\\DotNetCore\\code\\WaitTest.txt", "This is a Test").Wait();
// 在 D:\MyNote\DotNetCore\code\WaitTest.txt 中写入了 This is a Test
```

但尽量不要使用这两种方法，因为有 死锁 的风险。

异步委托：

```c#
ThreadPool.QueueUserWorkItem(async (obj) => {
    while (true)
    {
        await File.WiteAllTextAsync("D:\\MyNote\\DotNetCore\\code\\WaitTest.txt", "This is a Test");
    }
});
```

## async await 原理

await、async 是“语法糖”，最终编译成“状态机调用”。

`async` 的方法会被 C# 编译器编译成一个类，会主要根据 `await` 调用进行切分为多个状态，对 `async` 方法的调用会被拆分为对 `MoveNext` 的调用。

用 `await` 看似是“等待”，经过编译后，其实没有“wait”。

## async 背后的线程切换

`await` 调用的等待期间，.NET 会把当前的线程返回给线程池，等异步方法调用执行完毕后，框架会从线程池再取出来一个线程执行后续的代码。

`Thread.CurrentThread.ManagedThreadId`：获得当前线程 ID。

比如：在耗时异步（写入大字符串）操作前后分别打印线程 ID。

```c#
static async Task Main(string[] args)
{
    Console.WriteLine(Thread.CurrentThread.ManagedThreadId);  // 1
    StringBuilder sb = new StringBuilder();  
    for (int i = 0; i < 10000; i++)
    {
        sb.Append("xxxxxxxxxxx");
    }
    await File.WriteAllTextAsync("D:\\MyNote\\DotNetCore\\code\\test.txt", sb.ToString());
    Console.WriteLine(Thread.CurrentThread.ManagedThreadId); 
}
```

## 异步方法不等于多线程

异步方法的代码并不会自动在新线程中执行，除非把代码放到新线程中执行。

## 没有 async 的异步方法

async 方法的缺点：

+ 异步方法会生成一个类，运行效率没有普通方法高。
+ 可能会占用非常多的线程

假设一个读取文件内容的异步方法，正常使用是这样：

```c#
static async Task Main(string[] args)
{
    string s = await ReadAsync(1);
    Console.WriteLine(s);
}
static async Task<string> ReadAsync(int num)
{
    if (num == 1)
    {
        string s = await File.ReadAllTextAsync("D:\\MyNote\\DotNetCore\\code\\test.txt");
        return s;
    }
    else
    {
        string s = await File.ReadAllTextAsync("D:\\MyNote\\DotNetCore\\code\\test.txt");
        return s;
    } 
}
```

不用 async 是这样：

```c#
static Task<string> ReadAsync(int num)
{
    if (num == 1)
        return File.ReadAllTextAsync("D:\\MyNote\\DotNetCore\\code\\test.txt");
    else
        return File.ReadAllTextAsync("D:\\MyNote\\DotNetCore\\code\\test.txt");
}
```

返回值为 Task 的不一定都要标注 async，标注 async 只是让我们可以更方便的 await 而已。

如果一个异步方法只是对别的异步方法调用的转发，并没有太多复杂的逻辑，那么就可以去掉 async 关键字。

## 不要用 Sleep()

如果想在异步方法中暂停一段时间，不要用 `Thread.Sleep()` ，因为它会阻塞调用线程，而要用 `await Task.Delay()` 。

## CancellationToken

有时需要提前终止任务，比如：请求超时、用户取消请求。

很多异步方法都有 CancellationToken 参数，用于获得提前终止执行的信号。

cancellationToken 结构体：

+ None：空
+ bool IsCancellationRequested：是否取消
+ Register(Action callback)：注册取消监听
+ ThrowIfCancellationRequested()：如果任务被取消，执行到这句话就抛异常。

通过 CancellationTookenSource 创建 CancellationTokenSource 对象。

+ CancelAfter()：超时后发出取消信号
+ Cancel()：发出取消信号
+ CancellationToken Token

为“下载一个网址 N 次”的方法增加取消功能。分别用 GetStringAsync + IsCancellationRequested、GetStringAsync + ThrowlfCancellationRequested()、带 CancellationToken 的 GetAsync() 分别实现。

取消分别用超时、用户敲按键（不能 await ）实现。

正常一直下载一个网页：

```C#
static async Task Main(string[] args)
{
    await DownloadAsync1("https://www.baidu.com", 200);
}
static async Task DownloadAsync1(string url, int n)
{
    using (HttpClient client = new HttpClient())
    {
        for (int i = 0; i < n; i++)
        {
            string html = await client.GetStringAsync(url);
            Console.WriteLine($"{DateTime.Now}:{html}");
        }
    }
}
```

手动响应取消：

```c#
static async Task Main(string[] args)
{
    CancellationTokenSource cts = new CancellationTokenSource();
    cts.CancelAfter(5000);  // 5秒后取消
    CancellationToken cToken = cts.Token;
    await DownloadAsync2("https://www.baidu.com", 200, cToken);
}
static async Task DownloadAsync2(string url, int n, CancellationToken cancellationToken)
{
    using (HttpClient client = new HttpClient())
    {
        for (int i = 0; i < n; i++)
        {
            string html = await client.GetStringAsync(url);
            Console.WriteLine($"{DateTime.Now}:{html}");
            if (cancellationToken.IsCancellationRequested)
            {
                Console.WriteLine("请求被取消");
                break;
            }
        }
    }
}
```

抛出异常取消：

```c#
static async Task DownloadAsync2(string url, int n, CancellationToken cancellationToken)
{
    using (HttpClient client = new HttpClient())
    {
        for (int i = 0; i < n; i++)
        {
            string html = await client.GetStringAsync(url);
            Console.WriteLine($"{DateTime.Now}:{html}");
            cancellationToken.ThrowIfCancellationRequested();
        }
    }
}
```

或者这样抛出异常：

```c#
static async Task DownloadAsync3(string url, int n, CancellationToken cancellationToken)
{
    using (HttpClient client = new HttpClient())
    {
        for (int i = 0; i < n; i++)
        {
            var resp = await client.GetAsync(url, cancellationToken);
            string html = await resp.Content.ReadAsStringAsync();
            Console.WriteLine($"{DateTime.Now}:{html}");
        }
    }
}
```

使用输入按键（q）的方式取消：

```c#
static async Task Main(string[] args)
{
    CancellationTokenSource cts = new CancellationTokenSource();
    CancellationToken cToken = cts.Token;
    await DownloadAsync3("https://www.baidu.com", 200, cToken);
    while (Console.ReadLine() != "q")
    {

    }
    cts.Cancel();
    Console.WriteLine();
}
```

ASP.NET Core 开发中，一般不需要自己处理 CancellationToken、CancellationTokenSource 这些，只要做到“能转发 CancellationToken 就转发”即可。ASP.NET Core 会对于用户请求终端进行处理。

## WhenAll

Task 类的重要方法：

+ `Task<Task> WhenAny(IEnumerable<Task> tasks)` ，任何一个 Task 完成，Task 就完成。
+ `Task<TResult[]> WhenAll<TResult>(paramsTask<Tresult>[] tasks)`，所有 Task 完成，Task 才完成。用于等待多个任务执行结束，但是不在乎它们的执行顺序。
+ `FromResult()`，创建普通数值的 Task 对象。

使用 WhenAll：

```c#
static async Task Main(string[] args)
{
    Task<string> t1 = File.ReadAllTextAsync(@"D:\MyNote\DotNetCore\code\1.txt");
    Task<string> t2 = File.ReadAllTextAsync(@"D:\MyNote\DotNetCore\code\2.txt");
    Task<string> t3 = File.ReadAllTextAsync(@"D:\MyNote\DotNetCore\code\test.txt");
    string[] strs = await Task.WhenAll(t1, t2, t3);
    string s1 = strs[0];
    string s2 = strs[1];
    string s3 = strs[2];
    Console.WriteLine(s1);
    Console.WriteLine(s2);
    Console.WriteLine(s3);
}
```

使用 WhenAll 计算一个文件夹内所有文件的字符数之和：

```c#
static async Task Main(string[] args)
{
    string[] files = Directory.GetFiles("D:\\MyNote\\DotNetCore\\code");  // 拿到文件夹下的所有文件名
    Task<int>[] count = new Task<int>[files.Length];  // 创建一个用来保存每一个文件字符数量的数组
    for (int i = 0; i < files.Length; i++)
    {
        string filename = files[i];
        Task<int> t = GetCharCount(filename);
        count[i] = t;
    }
    int[] counts = await Task.WhenAll(count);  // 将每个文件字符数放在一个数组里面
    int sum = counts.Sum();  // 计算数组的和
    Console.WriteLine(sum);
}
static async Task<int> GetCharCount(string filename)
{
    string s = await File.ReadAllTextAsync(filename);
    return s.Length;
}
```

## 其他问题

接口中的异步方法：

async 是提示编译器为异步方法中的 await 代码进行分段处理的，而一个异步方法是否修饰了 async 对于方法的调用者来讲没有区别的，因此对于接口中的方法或者抽象方法不能i修饰为 async。

异步与 yield：

yield return 不仅能够简化数据的返回，而且可以让数据处理“流水线化”，提升性能。

```c#
static IEnumerable<string> Test()
{
    yield return "hello"; 
    yield return "world";
}
```

在旧版 C# 中，async 方法中不能用 yield，从 C# 8.0 开始，把返回值声明为 IAsyncEnumerable（不要带Task），然后遍历的时候用 await foreach() 即可。

```C#
static async Task Main(string[] args)
{
    await foreach(var s in Test())
    {
        Console.WriteLine(s);
    }
}
static IEnumerable<string> Test()
{
    yield return "hello"; 
    yield return "world";
}
```

# LINQ

## 为啥要学 LINQ

让数据处理变得简单。

【例题】统计一个字符串中每个字母出现的频率（忽略大小写），然后按照从高到低的顺序输出出现频率高于 2 次的单词和其出现的频率。

```c#
var items = s.Where(c => charlsLetter(c))//过滤非字母
    .Select(c => char.ToLower(c))//大写字母转换为小写
    .GroupBy(c => c)//根据字母进行分组
    .Where(g => g.Count()>2)//过滤掉出现次数<=2
    .OrderByDescending(g => g.Count())//按次数排序
    .Select(g => new {Char=g.Key,Count=g.Count()});
```

## 委托

委托是可以指向方法的类型，调用委托变量时执行的就是变量指向的方法。

```c#
delegate void D1();
delegate int D2(int a, int b);
static void Main(string[] args)
{
    D1 d = F1;
    d();  // 我是方法F1
    d = F2;
    d();  // 我是方法F2

    D2 d2 = Add;
    Console.WriteLine(d2(10, 20));  // 30
}
static void F1()
{
    Console.WriteLine("我是方法F1");
}
static void F2()
{
    Console.WriteLine("我是方法F2");
}
static int Add(int i, int j)
{
    return i + j;
}
```

.NET 中定义了泛型委托 Action（无返回值）和 Func（有返回值），所以一般不用自定义委托类型。

```C#
static void Main(string[] args)
{
    Action a = F1;
    a();  // 我是方法F1

    Func<int, int, int> f = Add;
    Console.WriteLine(f(12, 2));  // 14
}
static void F1()
{
    Console.WriteLine("我是方法F1");
}
static int Add(int i, int j)
{
    return i + j;
}
```

`Func<int, int, int>` 的第三个 int 参数是返回值。

## Lambda

委托变量不仅可以指向普通方法，还可以指向匿名方法。

```C#
static void Main(string[] args)
{
    Action f1 = delegate ()
    {
        Console.WriteLine("Hello World"); 
    };
    f1();  // Hello World
    
    Action<string, int> f2 = delegate (string name, int age)
    {
        Console.WriteLine($"name={name}, age={age}");
    };
    f2("zsm",20);   // name=zsm, age=20
    
    Func<int, int, int> f3 = delegate (int a, int b)
    {
        return a + b;
    };
    Console.WriteLine(f3(10, 10));  // 20
}
```

匿名方法可以写成 lambda 表达式：

```c3
Func<int, int, int> f4 = (int a, int b) =>
{
	return a + b;
};
Console.WriteLine(f4(100,20));  // 120
```

可以省略参数数据类型，因为编译能根据委托类型推断出参数的类型，用 `=>` 引出来方法体。

```c#
Func<int, int, int> f4 = (a, b) =>
{
	return a + b;
};
Console.WriteLine(f4(100,20));  // 120
```

如果委托没有返回值，且方法体只有一行代码，可省略 `{}` ：

```c#
Action<int,int> f5 = (a, b) => Console.WriteLine($"a={a},b={b}");
f5(30, 29);  // a=30,b=29
```

如果 `=>` 之后的方法体中只有一行代码，且方法有返回值，那么可以省略方法体的 `{}` 以及`retrun` ：

```c#
Func<int, int, int> f6 = (a, b) => a + b;
Console.WriteLine(f6(23, 45));  // 68
```

如果只有一个参数，参数的 `()` 也可以省略：

```C# 
Action<int> f7 = a => Console.WriteLine(a);
f7(100);  // 100

Func<int, int> f8 = a => a + 10;
Console.WriteLine(f8(100));  // 110
```

## LINQ方法的背后

LINQ 中提供了很多集合的扩展方法，配合 lambda 能简化数据处理。

比如，求出一个数组里大于 10  的数：

```c#
int[] arr = { 12, 2, 4, 54, 3, 4, 23, 54, 54, 677, 98, 6, 45, 0, 0 };
IEnumerable<int> res = arr.Where(a => a > 10);
foreach(int i in res)
{
    Console.WriteLine(i);
}
```

`IEnumerable<>` 要 `using System.Collection.Generic;` ， `Where()` 方法必须要 `using System.Linq;` 

`Where` 方法会遍历集合中每个元素，对于每个元素都调用 lambda 表达式`a => a > 10` ，判断一下是否为 true，是则将这个数放到返回的集合中。

自己模拟实现一个 `Where` 方法：

```c#
static void Main(string[] args)
{
    int[] arr = { 12, 2, 4, 54, 3, 4, 23, 54, 54, 677, 98, 6, 45, 0, 0 };
    IEnumerable<int> res = MyWhere(arr, a => a > 10);
    foreach(int i in res)
    {
        Console.WriteLine(i);
    }
}
static IEnumerable<int> MyWhere(IEnumerable<int> items, Func<int, bool> f)
{
    List<int> res = new List<int>();
    foreach(int i in items)
    {
        if (f(i) == true)
        {
            res.Add(i);
        }
    }
    return res;
}
```

使用 `yield` 实现 `Where` 方法：

```C#
static IEnumerable<int> MyWhere(IEnumerable<int> items, Func<int, bool> f)
{
    foreach (int i in items)
    {
        if (f(i) == true)
        {
            yield return i;
        }
    }
}
```

可以使用 var 让编译器的“类型推断”来简化类型的声明，在LINQ中常用：

```c#
static void Main(string[] args)
{
    int[] arr = { 12, 2, 4, 54, 3, 4, 23, 54, 54, 677, 98, 6, 45, 0, 0 };
    // IEnumerable<int> res = MyWhere(arr, a => a > 10);
    var res = MyWhere(arr, a => a > 10);
    foreach(int i in res)
    {
        Console.WriteLine(i);
    }
}
```

C# 中的 var 和 JavaScript 中的 var 不一样，C# 中的 var 是强类型的，JavaScript 中的 var 是弱类型。比如以下代码在 JavaScript 中可以执行，但是在 C# 中不能执行：

```c#
var i = 10;
i = "abc";
```

C#  中的弱类型是 `dynamic` 。

## 常用的扩展方法

LINQ 中提供了大量类似 Where 的扩展方法，简化数据处理。大部分都在 System.Linq 命名空间中。这些扩展方法都是基于 IEnumerable\<T\> 的。

以下的方法都可以混合使用。

初始数据：

```c#
class Employee
{
    public long Id { get; set; }
    public string? Name { get; set; }
    public int Age { get; set; }
    public bool Gender { get; set; }
    public int Salary { get; set; }
    public override string ToString()
    {
        return $"id = {Id}, name = {Name}, age = {Age}, gender={Gender}, salary = {Salary}";
    }
}
static void Main(string[] args)
{
    List<Employee> list = new List<Employee>();
    list.Add(new Employee { Id = 1, Name = "Mary", Age = 19, Gender = false, Salary = 2147 });
    list.Add(new Employee { Id = 2, Name = "Jack", Age = 32, Gender = true, Salary = 1000 });
    list.Add(new Employee { Id = 3, Name = "Bob", Age = 21, Gender = true, Salary = 4521 });
    list.Add(new Employee { Id = 4, Name = "Tom", Age = 18, Gender = true, Salary = 9000 });
    list.Add(new Employee { Id = 5, Name = "Jerry", Age = 34, Gender = true, Salary = 1201 });
    list.Add(new Employee { Id = 6, Name = "Lucy", Age = 25, Gender = false, Salary = 3587 });
    list.Add(new Employee { Id = 7, Name = "Rose", Age = 32, Gender = false, Salary = 5470 });
    list.Add(new Employee { Id = 8, Name = "Jim", Age = 19, Gender = true, Salary = 8740 });
}
```

### Where 方法

```c#
public static IEnumerable<TSource> Where<TSource>(this IEnumerable<TSource> source, Func<TSource, bool> predicate)
```

每一项数据都会经过 predicate 的测试，如果针对一个元素，predicate 执行的返回值为 true，那么这个元素就会梵高返回值中。

Where 参数是一个 lambda 表达式格式的匿名方法，方法的参数 e 表示当前判断的元素对象。参数的名字不一定非要叫 e，不过一般 lambda 表达式中的变量名长度都不长。

```c#
IEnumerable<Employee> items = list.Where(e => e.Age > 20);
foreach(Employee e in items)
{
    Console.WriteLine(e);
}
```

### Count 方法

获取满足条件的数据个数。

```C#
Console.WriteLine(list.Count());  // 8（list里的数据总数）
Console.WriteLine(list.Count(e => e.Age > 30));  // 3（list里Age大于30的数据总数）
Console.WriteLine(list.Count(e => e.Age > 30 && e.Salary > 2000));  // 1（list里Age大于30且Salary大于2000的数据总数）
```

### Any 方法

判断集合中是否至少有一条数据满足条件。

```c#
Console.WriteLine(list.Any(e => e.Age < 18));  // False（集合里没有Age小于18的数据）
Console.WriteLine(list.Any(e => e.Salary > 2000));  // True（集合里至少有一条Salary大于2000的数据）
```

### 获取一条数据

这里有四个相关的方法（是否带有参数的两种写法）

`Single`：获取有且仅有一条满足要求的数据，如果集合中有多条或没有满足要求的数据，都会报错。

```C#
// list.Single();  
// Unhandled exception. System.InvalidOperationException: Sequence contains more than one element

Employee e =  list.Where(e => e.Name == "Jack").Single();
Console.WriteLine(e);  // id = 2, name = Jack, age = 32, gender=True, salary = 1000
Employee e1 = list.Single(e => e.Name == "Jack");
Console.WriteLine(e);  // id = 2, name = Jack, age = 32, gender=True, salary = 1000

// Employee e1 = list.Where(e => e.Name == "ZSM").Single();
// Unhandled exception. System.InvalidOperationException: Sequence contains no elements
```

`SingleOrDefault`：最多只有一条满足要求的数据，如果集合中有多条满足要去的数据，会报错；没有满足要求的数据，则会返回一个默认值（类型的默认值）。

```C#
Employee e = list.SingleOrDefault(e => e.Name == "ZSM");
Console.WriteLine(e == null);  // True
Employee e1 = list.SingleOrDefault(e => e.Name == "Jim");
Console.WriteLine(e1);  // id = 8, name = Jim, age = 19, gender=True, salary = 8740

int[] nums = new int[] { 1, 2, 43, 45, 76, 8, 6, 4, 9 };
int i = nums.SingleOrDefault(a => a > 100);
Console.WriteLine(i);  // 0
int j = nums.SingleOrDefault(a => a > 45);
Console.WriteLine(j);  // 76
// int k = nums.SingleOrDefault(a => a > 10);
// Unhandled exception. System.InvalidOperationException: Sequence contains more than one matching element
```

`First`：至少有一条满足要求的数据，返回第一条。如果没有满足要求的数据，会报错。

`FirstOrDefualt`：返回第一条满足要求的数据。如果没有满足要求的数据，则返回一个默认值。

```c#
Employee e = list.First(e => e.Age > 30);
Console.WriteLine(e);  // id = 2, name = Jack, age = 32, gender = True, salary = 1000
// Employee e1 = list.First(e => e.Age > 200);
// Unhandled exception. System.InvalidOperationException: Sequence contains no matching element
Employee e1 = list.FirstOrDefault(e => e.Age > 200);
Console.WriteLine(e1 == null);  // True
```

### 排序

```c#
public static IOrderedEnumerable<TSource> OrderBy<TSource, TKey>(this IEnumerable<TSource> source, Func<TSource, TKey> keySelector)
```

> * **public static**: 这意味着这是一个公开的静态方法。  
> * **IOrderedEnumerable<TSource>**: 是返回类型，表示一个已排序的序列。  
> * **OrderBy<TSource, TKey>**: 方法名称，表示我们正在对`TSource`类型的元素按照`TKey`类型的键进行排序。  
> * **this IEnumerable<TSource> source**: `this`关键字表示这是一个扩展方法，它可以在每个`IEnumerable<TSource>`上调用，就好像它是该类型的一个实例方法。  
> * **Func<TSource, TKey> keySelector**: 这是一个委托，用于从`TSource`中提取`TKey`类型的键，基于这个键进行排序。
>
> 这个`OrderBy`方法有两个类型参数，分别是`TSource`和`TKey`，但实际的方法参数只有一个，那就是`keySelector`。
>
> 这是因为`TSource`和`TKey`是类型参数，它们用于定义方法的泛型类型，而不是实际传递给方法的值。实际上，当你调用这个方法时，你不需要为这两个类型参数提供具体的值，编译器会根据你传递的`IEnumerable<TSource>`和`keySelector`函数的类型来推断它们。
>
> 因此，从实际使用的角度来看，你只需要提供一个参数，即`keySelector`函数。这个函数告诉`OrderBy`方法如何从你的序列中提取一个键来进行排序。

`OrderBy()`：对数据进行正序排序。对原数据不产生影响，会返回一个排序后的集合。

```c#
IEnumerable<Employee> items = list.OrderBy(e => e.Age);
foreach(Employee e in items)
{
    Console.WriteLine(e); 
}
```

`OrderByDescending()`：对数据进行倒序排序。

```C#
IEnumerable<Employee> items = list.OrderByDescending(e => e.Age);
foreach (Employee e in items)
{
    Console.WriteLine(e);
}
```

对于简单类型排序：

```C#
int[] nums = new int[] { 1, 2, 43, 45, 76, 8, 6, 4, 9 };
var items = nums.OrderByDescending(i => i);
foreach (int i in items)
{
    Console.WriteLine(i);
}
```

随机排序：

```c#
int[] nums = new int[] { 1, 2, 43, 45, 76, 8, 6, 4, 9 };
var items = nums.OrderByDescending(guid => Guid.NewGuid());
// Random rand = new Random();
// var items = nums.OrderByDescending(e => rand.Next());
foreach (int i in items)
{
    Console.WriteLine(i);
}
```

根据 Name 的最后一个字符排序：

```c#
IEnumerable<Employee> items = list.OrderBy(e => e.Name[e.Name.Length-1]);
foreach(Employee e in items)
{
    Console.WriteLine(e);
}
```

多规则排序

可以在 `OrderBy()`、`OrderByDescending()`后继续写 `ThenBy()`、`ThenByDescending()`。

比如：先按 Age 排序，Age 相同则按 Id 排序：

```C# 
IEnumerable<Employee> items = list.OrderBy(e => e.Age).ThenBy(e => e.Id);
foreach (var e in items)
{
    Console.WriteLine(e);
}
```

### 限制结果集

获取部分数据。

`Skip(n)`：跳过 n 条数据。如果 n 大于数据的总数，则全部跳过

`Take(n)`：获取 n 条数据。如果 n 大于数据的总数，则取到所有数据。

比如：跳过 2 条数据再取 3 条数据。

```c#
IEnumerable<Employee> items = list.Skip(2).Take(3);
foreach (var e in items)
{
    Console.WriteLine(e);
}
```

### 聚合函数

`Max()`：获取最大值

`Min()`：获取最小值

`Average()`：获取平均值

`Sum()`：获取总和

`Count()`：获取总个数

```c#
int maxAge = list.Max(e => e.Age);
Console.WriteLine($"最大年龄:{maxAge}");

long minId = list.Min(e => e.Id);
Console.WriteLine($"最小Id:{minId}");

double avgSalary = list.Average(e => e.Salary);
Console.WriteLine($"平均工资:{avgSalary}");

int sumSalary = list.Sum(e => e.Salary);
Console.WriteLine($"工资总和:{sumSalary}");

int count = list.Count();
Console.WriteLine($"总条数:{count}");

int minSalary2 = list.Where(e => e.Age > 30).Min(e => e.Salary);
Console.WriteLine($"大于30岁的人群中的最低工资:{minSalary2}");
```

LINQ 中的所有扩展方法几乎都是针对 IEnumerable 接口的，而几乎所有能返回集合的都返回 IEnumerable，所以是可以把几乎所有方法“链式使用”的。

### 分组

`GroupBy()`方法参数是分组条件表达式，返回值为 `IGrouping<Tkey, TSource>` 类型的泛型 IEnumerable，也就是每一组以一个 IGrouping 对象的形式返回。

IGrouping 是一个继承自 IEnumerable 的接口，IGrouping 中的 Key 属性表示这一组的分组数据的值。

比如：按 Age 分组，

```c#
IEnumerable<IGrouping<int, Employee>> items = list.GroupBy(e => e.Age);
foreach(IGrouping<int, Employee> g in items)
{
    Console.WriteLine(g.Key);
    foreach(Employee e in g)
    {
        Console.WriteLine(e);
    }
    Console.WriteLine("===========================");
}
```

用 var 可以简化代码：

```c#
var items = list.GroupBy(e => e.Age);
foreach (var g in items)
{
    Console.WriteLine(g.Key);
    foreach (var e in g)
    {
        Console.WriteLine(e);
    }
    Console.WriteLine("===========================");
}
```

输出结果：

```
28
Employee { Id = 1, Name = jerry, Age = 28, Gender = True, Salary = 5000 }
===========================
33
Employee { Id = 2, Name = jim, Age = 33, Gender = True, Salary = 3000 }
Employee { Id = 8, Name = jack, Age = 33, Gender = True, Salary = 8000 }
===========================
35
Employee { Id = 3, Name = lily, Age = 35, Gender = False, Salary = 9000 }
Employee { Id = 6, Name = nancy, Age = 35, Gender = False, Salary = 8000 }
Employee { Id = 7, Name = zack, Age = 35, Gender = True, Salary = 8500 }
===========================
16
Employee { Id = 4, Name = lucy, Age = 16, Gender = False, Salary = 2000 }
===========================
25
Employee { Id = 5, Name = kimi, Age = 25, Gender = True, Salary = 1000 }
===========================
```

### 投影

把集合中的每一项映射为另一种类型。

比如：拿出 list 中的所有 Age 数据

```c#
IEnumerable<int> ages = list.Select(e => e.Age);
foreach(var i in ages)
{
    Console.WriteLine(i);
}
```

也可以拿出多个数据：

```c#
IEnumerable<string> ages = list.Select(e => e.Age + "," + e.Name);
foreach(var i in ages)
{
    Console.WriteLine(i);
}
```

将人投影为狗类型：

```c#
var dogs = list.Select(e => new Dog { Age = e.Age, Name = e.Name });
foreach (var i in dogs)
{
    Console.WriteLine(i);
}
```

### 匿名类型

只能用 var。

```c#
var obj1 = new { Name = "zsm", Age = 19, Tel = "15760656503" };
Console.WriteLine($"{obj1.Name},{obj1.Age},{obj1.Tel}");  // zsm,19,15760656503
```

### 投影和匿名类型

```c#
var items = list.Select(e => new { Name = e.Name, Age = e.Age, Gender = e.Gender ? "男" : "女" });
foreach(var i in items)
{
    Console.WriteLine(i.Name + " " + i.Age + " " + i.Gender);
}
/*
Mary 19 女
Jack 32 男
Bob 21 男
Tom 18 男
Jerry 34 男
Lucy 25 女
Rose 32 女
Jim 19 男
*/
```

按年龄分组，输出每一组里的最大工资、最小工资以及人数。

```c#
var items = list.GroupBy(e => e.Age).Select(e => new
    {
        Age = e.Key,
        MaxSal = e.Max(e => e.Salary),
        MinSal = e.Min(e => e.Salary),
        Count = e.Count()
    }) ;
foreach (var i in items)
{
    Console.WriteLine($"年龄：{i.Age}, 最大工资：{i.MaxSal}, 最小工资：{i.MinSal}, 总人数：{i.Count}");
}
```

输出结果：

```
年龄：28, 最大工资：5000, 最小工资：5000, 总人数：1
年龄：33, 最大工资：8000, 最小工资：3000, 总人数：2
年龄：35, 最大工资：9000, 最小工资：8000, 总人数：3
年龄：16, 最大工资：2000, 最小工资：2000, 总人数：1
年龄：25, 最大工资：1000, 最小工资：1000, 总人数：1
```

### 集合转换

有一些地方需要数组类型或者 List 类型的变量，我们可以用 ToArray() 方法和 ToList() 分别把 IEnumerbale\<T\> 转换为数组类型和 List\<T\> 类型。

```c#
IEnumerable<Employee> items = list.Where(e => e.Age > 19);
List<Employee> list2 = items.ToList();
Employee[] array2 = items.ToArray();
```

## 链式调用

Where、Select、OrderBy、GroupBy、Take、Skip等返回值都是 IEnumerbale\<T\> 类型，所以可以使用链式调用。

比如：获取 Id 大于 2 的数据，按照 Age 分组，并按照 Age 排序，然后取出前 3 条，最后再投影取得年龄、人数、平均工资。

```c#
var items = list.Where(e => e.Id > 2)
    .GroupBy(e => e.Age)
    .OrderBy(e => e.Key)
    .Take(3)
    .Select(e => new {NL = e.Key, RS = e.Count(), PJ = e.Average(e => e.Salary)});
foreach(var i in items)
{
    Console.WriteLine(i);
}
/*
{ NL = 18, RS = 1, PJ = 9000 }
{ NL = 19, RS = 1, PJ = 8740 }
{ NL = 21, RS = 1, PJ = 4521 }
*/
```

在 `OrderBy(e => e.Key)` 这，因为前面 `GroupBy(e => e.Age)` 返回的是一个 `IEnumerable<IGrouping<int, Employee>>` ，所以 `GroupBy` 后的方法的参数都是 `IGrouping` 类型的，想要用 Age 来排序的话，只能用 IGrouping 的 Key。

## 查询语法

使用 Where、OrderBy、Select 等扩展方法进行数据查询的写法叫做“LINQ方法语法”。

比如：

```c#
var items = list.Where(e => e.Salary > 3000)
    .OrderBy(e => e.Age)
    .Select(e => new { e.Age, e.Name, Gender = e.Gender ? "男" : "女" });  // (1)
foreach(var i in items)
{
    Console.WriteLine(i);
}
/*
{ Age = 28, Name = jerry, Gender = 男 }
{ Age = 33, Name = jack, Gender = 男 }
{ Age = 35, Name = lily, Gender = 女 }
{ Age = 35, Name = nancy, Gender = 女 }
{ Age = 35, Name = zack, Gender = 男 }
*/
```

（1）：`Gender = e.Gender ? "男" : "女"` 必须要写 Gender= ，其他字段会自动以 . 后面的名字命名。

还有一种“查询语法”的写法。

```c#
var items = from e in list
    where e.Salary > 3000
    select new { e.Age, e.Name, Gender = e.Gender ? "男" : "女"  };
foreach (var i in items)
{
    Console.WriteLine(i);
}
```

以上两种写法的编译结果是一样的。

## 性能与面试

LINQ 大部分时候不会影响性能。

面试的时候算法题一般尽量避免使用正则表达式、LINQ 这些高级的类库，因为这些体现不出来水平。

【例题1】：有一个用逗号分隔的表示成绩的字符串，如：`"61,90,100,18,22,38,66,80,93,55,50,89"` ，计算这些成绩的平均值。

```c#
 string s = "61,90,100,18,22,38,66,80,93,55,50,89";
string[] ss = s.Split(",");
IEnumerable<int> nums = ss.Select(e => Convert.ToInt32(e));
double ave = nums.Average();
Console.WriteLine(ave);
```

可以简化成：

```c#
double ave = s.Split(',').Select(e => Convert.ToInt32(e)).Average();
Console.WriteLine(ave);
```

【例题2】：统计一个字符串中每个字母出现的频率（忽略大小写），然后按照从高到低的顺序输出出现频率高于 2 次的单词和其出现的频率。

```c#
string s = "HelloWorld, HHHaaa, java C# is nb.";
var items = s.Where(e => char.IsLetter(e))
    .Select(e => char.ToLower(e))
    .GroupBy(e => e)
    .Select(e => new { e.Key, Count = e.Count() })
    .OrderByDescending(e => e.Count)
    .Where(e => e.Count > 2);

foreach (var i in items)
{
    Console.WriteLine(i);
}
```

# 依赖注入

依赖注入（Dependency Injection，DI）是控制反转（Inversion of Control，IOC）思想的实现方式。依赖注入简化模块的组装过程，降低模块之间的耦合度。	

控制反转的两种实现：

+ 服务定位器（ServiceLocatior）
+ 依赖注入（Dependency Injection）

依赖注入几个概念：

+ 服务（service）：对象
+ 注册服务
+ 服务容器：负责管理注册的服务
+ 查询服务：创建对象及关联对象
+ 对象生命周期：Transient（瞬态）、Scoped（范围）、Singleton（单例）
  + Transient：获取一次就要 new 一个对象
  + Scoped：在指定的范围中，每次获取都是同一个对象
  + Singleton：无论谁获取这个服务，拿到的都是一个对象


## .NET 中使用 DI

根据类型来获取和注册服务。

可以分别指定服务类型（service type）和实现类型（implementation type）。这两者可能相同，也可能不同。服务类型可以是类，也可以是接口，建议面向接口编程，更灵活。

.NET 控制反转组件取名为 DependencyInjection，但它包含 ServiceLocator 的功能。

.NET 中使用 DI 的步骤：

1、Install-Package：Microsoft.Extensions.DependencyInjection

在 Package Manager Console 里输入：

```
Install-Package Microsoft.Extensions.DependencyInjection
```

2、using Microsoft.Extensions.DependencyInjection

```C#
using Microsoft.Extensions.DependencyInjection;
```

3、ServiceColletion 用来构造容器对象 IServiceProvider。调用 ServiceConllection 的 BuildServiceProvider() 创建的 ServiceProvider，可以用来获取 BuildServiceProvider() 之前 ServiceCollection 中的对象。

```c#
static void Main(string[] args)
{
    //ITestService it = new TestServiceImpl();
    //it.Name = "Tom";
    //it.SayHi();
    ServiceCollection service = new ServiceCollection();
    service.AddTransient<TestServiceImpl>();
    using (ServiceProvider sp = service.BuildServiceProvider())  // ServiceProvider == 服务定位器
    {
        TestServiceImpl t = sp.GetService<TestServiceImpl>();
        t.Name = "Tom";
        t.SayHi();
    }
}
public interface ITestService
{
    public string Name { get; set; }
    public void SayHi();
}
public class TestServiceImpl : ITestService
{
    public string Name { get; set; }
    public void SayHi()
    {
        Console.WriteLine($"Hi, I am {Name}");
    }
}
```

## 生命周期

给类构造函数中打印，看看不同生命周期的对象创建，使用 serviceProvider.CreateScope() 创建 Sco pe。

Transient：

```c#
ServiceCollection service = new ServiceCollection();
service.AddTransient<TestServiceImpl>();
using (ServiceProvider sp = service.BuildServiceProvider())  // ServiceProvider == 服务定位器
{
    TestServiceImpl t = sp.GetService<TestServiceImpl>();
    TestServiceImpl t1 = sp.GetService<TestServiceImpl>();
    Console.WriteLine(object.ReferenceEquals(t, t1));  // False
}
```

+ `object.ReferenceEquals(t, t1)`：该方法能比较两个引用是否是同一个对象

Singleton：

```c#
ServiceCollection service = new ServiceCollection();
service.AddSingleton<TestServiceImpl>();
using (ServiceProvider sp = service.BuildServiceProvider())  // ServiceProvider == 服务定位器
{
    TestServiceImpl t = sp.GetService<TestServiceImpl>();
    TestServiceImpl t1 = sp.GetService<TestServiceImpl>();
    Console.WriteLine(object.ReferenceEquals(t, t1));  // True
}
```

Scoped：

```c#
ServiceCollection service = new ServiceCollection();
service.AddScoped<TestServiceImpl>();
using (ServiceProvider sp = service.BuildServiceProvider())  // ServiceProvider == 服务定位器
{
    using (IServiceScope scope1 = sp.CreateScope())  // 这using就是一个 scope 范围
    {
        // 在 Scope 中获取相关的对象，用 scope1.ServiceProvider 而不是 sp
        TestServiceImpl t = scope1.ServiceProvider.GetService<TestServiceImpl>();
        TestServiceImpl t1 = scope1.ServiceProvider.GetService<TestServiceImpl>();
        Console.WriteLine(object.ReferenceEquals(t, t1));  // True
    }
}
```

如果一个类实现了 IDisposable 接口，则离开作用域之后容器会自动调用对象的 Dispose 方法。

不要在长生命周期的对象中引用比它短的生命周期的对象。在 ASP.NET Core 中，这样做默认会抛异常。

生命周期的选择：

+ 如果类无状态（没有成员变量、没有属性），建议为 Singleton；
+ 如果类有状态，且有 Scope 控制，建议为 Scoped，因为通常这种 Scope 控制下的代码都是运行在同一个线程中的，没有并发修改的问题；
+ 在使用 Transient 的时候要谨慎。

## 服务定位器

IServiceProvider 的服务定位器方法：

+ `T GetService<T>()` ：如果获取不到对象，则返回 null。
+ `object GetService(Type serviceType)` 
+ `T GetRequiredService<T>()` ：如果获取不到对象，则抛异常
+ `object GetRequiredService(Type serviceType)` 
+ `IEnumerable<T> GetServices<T>()` ：适用于可能有很多满足条件的服务
+ `IEnumerable<object> GetServices(Type serviceType)` 

## 依赖注入

依赖注入是有“传染性”的，如果一个类的对象是通过 DI 创建的，那么这个类的构造函数中声明的所有服务类型的参数都会被 DI 赋值；但是如果一个对象是程序员手动创建的，那么这个对象就和 DI 没有关系，它的构造函数中声明的服务类型参数就不会被自动赋值。

.NET 的 DI 默认是构造函数注入。

```c#
static void Main(string[] args)
{
    ServiceCollection services = new ServiceCollection();
    services.AddScoped<Controller>();
    services.AddScoped<ILog, LogImpl>();
    services.AddScoped<IStorage, StorageImpl>();
    services.AddScoped<IConfig, ConfigImpl>();

    using (var sp = services.BuildServiceProvider())
    {
        var c = sp.GetRequiredService<Controller>();
        c.Test();
    }
}

class Controller
{
    private readonly ILog log;
    private readonly IStorage storage;
    public Controller(ILog log, IStorage storage)
    {
        this.log = log;
        this.storage = storage;
    }
    public void Test()
    {
        log.Log("开始上传");
        storage.Save("helloWorld", "1.txt");
        log.Log("上传完毕");
    }
}

interface ILog
{
    public void Log(string msg);
}
class LogImpl : ILog
{

    void ILog.Log(string msg)
    {
        Console.WriteLine($"日志：{msg}");

    }
}

interface IConfig
{
    public string GetValue(string name);
}
class ConfigImpl : IConfig
{
    public string GetValue(string name)
    {
        return "hello";
    }
}

interface IStorage
{
    public void Save(string content, string name);
}
class StorageImpl : IStorage
{
    private readonly IConfig config;
    public StorageImpl(IConfig config)
    {
        this.config = config;
    }
    public void Save(string content, string name)
    {
        string server = config.GetValue("server");
        Console.WriteLine($"向服务器{server}的文件名为{name}上传{content}");
    }
}
```

输入结果是：

```
日志：开始上传
向服务器hello的文件名为1.txt上传helloWorld
日志：上传完毕
```

## 综合案例

需求说明

1、目的：演示 DI 的能力；

2、有配置服务、日志服务，然后再开发一个邮件发送器服务。可以通过配置服务来从文件、环境变量、数据库等地方读取配置，可以通过日志服务来将程序运行过程中的日志信息写入文件、控制台、数据库等。

3、说明：案例中开发了自己的日志、配置等接口，这只是在揭示原理，.NET 有线程的。

实现 1：

> 1、创建3个 .NET Core 类库项目，ConfigServices 是配置服务的项目，LogServices 是日志服务的项目，MailServices 是邮件发送器的项目，然后再建一个 .NET Core 控制台项目 MailServicesConsole 来调用 MailServices 。MailServices 项目引用 ConfigServices 项目和 LogServices 项目，而 MailServicesConsole 项目引用 MailServices 项目。
>
> 2、编写类库项目 LogServices，创建 ILogProvider 接口，编写实现类 ConsoleLogProvider。编写一个 ConsoleLogProviderExtensions 定义的扩展方法 AddConsoleLog，namespace 和 IServiceCollection 一致。

实现2：

> 1、编写配置服务的类库项目 ConfigServices。接口 IConfigProvider，方法：string GetValue(string name)。
>
> 2、环境变量读取配置类 EnvVarConfigProvider ：Environment.GetEnvironmentVariable(name)；编写一个类带扩展方法：AddEnvVarConfig。
>
> 3、编写从 ini 文件中读取配置的类 ConfigServices。

实现3：

> 1、“可覆盖的配置读取器”。配置中心服务器。可以本地的覆盖配置服务器的，或者配置文件覆盖环境变量的。例如，按照“配置中心服务器”、“本地环境变量”、“本地配置文件”的顺序添加了三个配置提供者，在“配置中心服务器”中提供了“a=1;b=2;c=3”这三个配置项，在“本地环境变量”中配置了“a=10;b=20;”，在“本地配置文件”中配置了“b=200”，那么最终我们读取的时候读到的就是a=10;b=200;c=3;
>
> 2、定义一个从各个ConfigProvider 中读取项的 IConfigReader 接口。编写实现类 LayeredConfigReader 。

创建 MailServicesConsole 控制台（Console App）项目；

在当前解决方案里，创建 LogServices 类库（Class Library）项目，Framework 选择 .NET Standard 2.1 ；然后右击该项目，选择 Add -> New Item -> Interface，创建 ILogProvider 接口；

![image-20230619172255120](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230619172255120.png)

然后再创建 MailServices 类库项目，需要在依赖项（Dependencies）中添加 LogServices 的引用：在 MailServices 下的 Dependencies 上右击，选择 Add Project Reference，勾选 LogServices 。在 MailServicesConsole 项目的依赖项中要添加 MailServices 引用。

![image-20230619173117114](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230619173117114.png)

然后在 MailServices 创建一个 IMailServices 接口，以及 MailServices 实现类。

创建 ConfigServices 类库项目，创建一个 IConfigServies 接口，然后 MailServices 的依赖项中也要添加 ConfigServices 。创建一个 EnvVarConfigServices 类实现 IConfigServices 接口。

在 MailServices 类中创建 ILogProvider 和 IConfigServices 的成员变量，并实现构造方法。

在 MailServicesConsole 中，安装：

```
Install-Package Microsoft.Extensions.DependencyInjection
```

再在 MailServicesConsole 中进行代码编写即可。



在 ConfigServices 中再实现一个配置文件的类 IniFileConfigService。在 MailServicesConsole 创建一个 mail.ini 配置文件，配置文件中内容如下：

```
SmtpServer=abc.mail.com
UserName=admin
Password=123456
```

在 IniFileConfigService 类中创建一个属性 FilePath，表示读取配置文件的路径。，

# 配置系统

.NET 中的配置系统支持丰富的配置源，包括文件(json、xml、ini等)、注册表、环境变量、命令行、Azure Key Vault 等，还可以配置自定义配置源。可以跟踪配置的改变，可以按照优先级覆盖。

## Json文件配置

1、创建一个 json 文件，文件名随意，比如 config.json，右击选择 Properties 属性，设置“如果较新则复制”。

![image-20230621154806934](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230621154806934.png)

2、NuGet 安装 Microsoft.Extensions.Configuration 和 Microsoft.Extensions.Configuration.Json 。

```
Install-Package Microsoft.Extensions.Configuration  # 配置框架的包
Install-Package Microsoft.Extensions.Configuration.Json  # 读json文件的包
```

3、编写代码，先用简单的方式读取配置。

读取配置原始方法：

```c#
 static void Main(string[] args)
 {
     ConfigurationBuilder configBuilder = new ConfigurationBuilder();
     configBuilder.AddJsonFile("config.json", optional: true, reloadOnChange: true);
     IConfigurationRoot configRoot = configBuilder.Build();
     string name = configRoot["name"];
     string proxyAddress = configRoot.GetSection("proxy:address").Value;
     Console.WriteLine(name);
     Console.WriteLine(proxyAddress);
 }
```

optional 参数表示这个文件是否可选。初学时，建议optional 设置为 true，这样写错了的话能够及时发现。

reloadOnchange 参数表示如果文件修改了，是否立即重新加载配置。

绑定读取配置：

1、可以绑定一个类，自动完成配置的读取。

```c#
class Proxy
{
    public string Address { get; set; }
    public int Port { get; set; }
}
```

2、NuGet 安装: Microsoft.Extensions.Configuration.Binder

```C#
Install-Package Microsoft.Extensions.Configuration.Binder
```

3、Server server = configRoot.GetSection("Proxy").Get<Server>()

```c#
static void Main(string[] args)
{
    ConfigurationBuilder configBuilder = new ConfigurationBuilder();
    configBuilder.AddJsonFile("config.json", optional: true, reloadOnChange: true);
    IConfigurationRoot configRoot = configBuilder.Build();
   
    Proxy p = configRoot.GetSection("proxy").Get<Proxy>();
    Console.WriteLine(p.Address);
    Console.WriteLine(p.Port);
}
```

## 选取方式配置

1、推荐使用选项方式读取，和 DI 结合更好，且更好利用 reloadonchange 机制

2、NuGet安装: `Microsoft.Extensions.Options`，`Microsoft.Extensions.Configuration.Binder`，当然也需要`Microsoft.Extensions.Configuration` ，`Microsoft.Extensions.Configuration.Json `.

3、读取配置的时候，DI要声明IOptions<T>、lOptionsMonitor<T>、IOptionsSnapshot<T>等类型。
Options<T>不会读取到新的值; 和IOptionsMonitor相比，IOptionsSnapshot会在同一个范围内 (比如ASP.NET Core一个请求中)保持一致。建议用IOptionsSnapshot。

在读取配置的地方，用IOptionsSnapshot<T>注入。不要在构造函数里直接读取IOptionsSnapshot.Value，而是到用到的地方再读取，否则就无法更新变化。

```c#
class Demo
{
    // private readonly Config optConfig;
	private readonly IOptionsSnapshot<DbSettings> optDbSettings;
	public Demo(IOptionsSnapshot<DbSettings> optDbSettings)
	{
         // this.optDbSettings = optDbSettings.Value;
		this.optDbSettings = optDbSettings;
	}
}
```

### 其他配置提供者

1、配置框架还支持从命令行参数、环境变量等地方读取。

```bash
a.exe name="zs" age=5
```

2、NuGet安装Microsoft.Extensions.Configuration.CommandLine.

3、configBuilder.AddCommandLine(args)

4、参数支持多种格式，比如: server=127.0.0.1、server=127.0.0.1、--server 127.0.0.1注意在键值之间加空格)、/server=127.0.0.1、/server 127.0.0.1 (注意在键值之间加空格)。格式不能混用

5、调试的时候，VS中简化命令行传参数的方法
右击项目，选择属性，选择调试，选择打开调试配置文件UI，可以配置参数。

**扁平化配置**

1、对于环境变量、命令行等简单的键值对结构，如果想要进行复杂结构的配置，需要进行“扁平化处理”。对于配置的名字需要采用“层级配置”。例如: a\:b\:e。对于数字这样配置: `a:b:c:0`、`a:b:c:1`、`a:b:c:2`。

2、演示一下。

```bash
a.exe proxy:address="ssss" proxy:ids:0=1 proxy:ids:1=2
```

3、这个知识点在自定义配置Provider中还会用到

**环境变量配置**

1、NuGet安装：Microsoft.Extensions.Configuration.EnvironmentVariables。

2、然后configurationBuilder. AddEnvironmentVariables()。AddEnvironmentVariables() 有无参数和有prefix参数的两个重载版本。无参数版本会把程序相关的所有环境变量都加载进来，由于有可能和系统中已有的环境变量冲突，因此建议用有prefix（前缀）参数的AddEnvironmentVariables()。读取配置的时候，prefix参数会被忽略。

3、VS中调试时，避免修改系统环境变量，直接在VS中设置环境变量的方法。

**其他配置源**

1、还支持ini、xml等格式的配置源，如果想用查询文档即号

2、还支持在运行时、调试时加载不同的json文件

3、还内置或者第三方支持中心化配置服务器，比如使用Apollo、Nacos等开源服务器，或者使用Azure、阿里云等的配置服务。具体看文档即可。

### 开发自己的配置提供者

步骤

1、开发一个直接或者间接实现IConfigurationProvider接口的类XXXConfigurationProvider，一般继承自ConfigurationProvider。如果是从文件读取，可以继承自FileConfigurationProvider。重写Load方法，把“扁平化数据设置到Data属性即可。

2、再开发一个实现了IConfigurationSource接口的类XXXConfigurationSource。如果是从文件读取，可以继承自FileConfigurationSource。在Build方法中返回上面的ConfigurationProvider对象

3、然后使用即可，configurationBuilder.Add(new ConfigurationSource())即可为了简化使用，一般提供一个IConfigurationBuilder的扩展方法。

整体流程: 编写ConfigurationProvider类实际读取配置;编写ConfigurationSource在Build中返回ConfigurationProvider对象;把ConfigurationSource对象加入IConfigurationBuilder。

开发web.config提供者：

1、.NET Core中不建议使用.NET Framework里的web.config，不过仍然继续提供了ConfigurationManager了，不过没有官方支持通过新的Configuration框架读取的方式。我们来实现一个，能够读取web.config里的connectionStrings和appSettings的内容。没用过web.config也没关系

2、这个项目主要意义还是展示如何编写自定义配置提供者，实用意义不大。主要为下一个更实用的配置提供者做知识准备。

web.config 的形式：

```xml
<?xml version="1.0" encoding="utf-8"?><configuration>
    <connectionStrings>  
        <add name="connstr1" connectionString="Data Source=;lnitialCatalog=DemoDB;User ID=sa;Password=123456"providerName="System.Data.SqlClient"/>
    </connectionStrings>
    <appSettings>
    	<add key="Smtp:Server" value="smtp.test.com"/>
        <add key="Smtp.Port" value="25" />
        <add key="RedisServer" value="127.0.0.1"/>
        <add key="RedisPassword" value="abc123"/>
    </appSettings>
</configuration>
```

+ ` <connectionStrings>`：配置连接字符串，多个字符串使用多个 `add` 子节点
+ `<appSettings>`：普通的配置

### 开发数据库配置提供者



### 多配置源的优先级

为什么多配置源
1、比如: 某个网站需要自定义配置;程序员的同一台机器上，开发调试环境和测试环境用不同的配置

2、按照注册到ConfigurationBuilder的顺序，“后来者居上”，后注册的优先级高，如果配置名字重复，用后注册的值。

3、实验: 控制台的覆盖环境变量的，自定义Provider的覆盖控制台的。

保命的UserSecrets

1、.NET 提供了user-secrets机制，user-secrets的配置不放到源代码中

2、Nuget安装:Microsoft.Extensions.Configuration.UserSecrets

3、在VS项目上点右键[管理用户机密] ，编辑这个配置文件。看看这个文件在哪里。会自动在csproj中的UserSecretsld就是文件夹的名字

4、configBuilder.AddUserSecrets<Program>()

# .NET 日志系统

## 什么是 LOGGING

基本概念：

1、日志级别: `Trace<Debug < Information <Warning < Error < Critical`

2、日志提供者 (LoggingProvider) : 把日志输出到哪里。控制台、文件、数据库等

3、.NET的日志非常灵活，对于业务代码只要注入日志对象记录日志即可，具体哪些日志输出到哪里、什么样的格式、是否输出等都有配置或者初始化代码决定。

输出到控制台

1、NuGet: Microsoft.Extensions.Logging（这是日志框架的基础包，无论往哪里输出日志都要装这个包）、Microsoft.Extensions.Logging.Console（将日志往控制台输出需要装这个包）.

```
 Install-Package Microsoft.Extensions.Logging
 Install-Package Microsoft.Extensions.Logging.Console
```

2、DI注入:services.AddLogging(logBuilder=>(logBuilder.AddConsole();//可多个Provider

3、需要记录日志的代码，注入ILogger<T>即可，T一般就用当前类，这个类的名字会输出到日志，方便定位错误。然后调用LogInformation()、LogError等方法输出不同级别的日志，还支持输出异常对象。

```c#
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;

namespace LogginDemo1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            ServiceCollection service = new ServiceCollection();
            service.AddLogging(logBuilder =>
            {
                logBuilder.AddConsole();
            });
            service.AddScoped<Test1>();
            using(var sp = service.BuildServiceProvider())
            {
                var test1 = sp.GetRequiredService<Test1>();
                test1.Test();
            }
        }
    }
} 
```

```c#
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LogginDemo1
{
    /*
     * 用来记录日志
     */
    public class Test1
    {
        private readonly ILogger<Test1> logger;
        public Test1(ILogger<Test1> logger)
        {
            this.logger = logger;
        }
        public void Test()
        {
            logger.LogDebug("开始执行数据库同步");
            logger.LogDebug("数据库链接成功");
            logger.LogWarning("数据查找失败");
            logger.LogError("数据库崩了");
        }
    }
}
```

控制台输出如下：

![image-20230623174536671](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230623174536671.png)

默认不会输出 Debug 级别的日志，可以设置最低级别：

```c#
logBuilder.SetMinimumLevel(LogLevel.Trace);  // 设置最低级别
```

其他日志提供者：

1、Console只适合开发阶段，why? 运行阶段需要输出到文件等。

2、采用和Configuration类似的扩展机制，不仅内置了Debug、事件查看器、文件、Azure日志等提供者，还可以扩展。Provider可以共存

3、Event Log: Windows Only。在Windows下部署的程序、网站运行出错、不正常，先去EventLog看看。NuGet安装:
Microsoft.Extensions.Logging.EventLog。然后logBuilder.AddEventLog()。

## NLOG

1、.NET没有内置文本日志提供者。第三方有Log4Net.NLog、Serilog等。老牌的Log4Net另搞一套，不考虑

2、NLog，NuGet安装: NLog.Extensions.Logging(using NLog.Extensions.Logging;)。

```c#
Install-Package NLog.Extensions.Logging
```

项目根目录下建nlog.config，注意文件名的大小写(考虑linux)也可以是其他文件名，但是需要单独配置。约定大于配置。内容见备注。讲解一下配置文件。

3、增加logBuilder.AddNLog()。

nlog.config 配置文件：在  NuGet 中搜索 NLog，在 NLog.Extensions.Logging 的 Project website 中去找

```xml
<?xml version="1.0" encoding="utf-8" ?>
<nlog xmlns="http://www.nlog-project.org/schemas/NLog.xsd"
      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      autoReload="true"
      internalLogLevel="Info"
      internalLogFile="c:\temp\internal-nlog-AspNetCore.txt">

	<!-- enable asp.net core layout renderers -->
	<extensions>
		<add assembly="NLog.Web.AspNetCore"/>
	</extensions>

	<!-- the targets to write to -->
	<targets>
		<!-- File Target for all log messages with basic details -->
		<target xsi:type="File" name="allfile" fileName="nlog-AspNetCore-all-${shortdate}.log"
				layout="${longdate}|${event-properties:item=EventId:whenEmpty=0}|${level:uppercase=true}|${logger}|${message} ${exception:format=tostring}" />

		<!-- File Target for own log messages with extra web details using some ASP.NET core renderers -->
		<target xsi:type="File" name="ownFile-web" fileName="nlog-AspNetCore-own-${shortdate}.log"
				layout="${longdate}|${event-properties:item=EventId:whenEmpty=0}|${level:uppercase=true}|${logger}|${message} ${exception:format=tostring}|url: ${aspnet-request-url}|action: ${aspnet-mvc-action}" />

		<!--Console Target for hosting lifetime messages to improve Docker / Visual Studio startup detection -->
		<target xsi:type="Console" name="lifetimeConsole" layout="${MicrosoftConsoleLayout}" />
	</targets>

	<!-- rules to map from logger name to target -->
	<rules>
		<!--All logs, including from Microsoft-->
		<logger name="*" minlevel="Trace" writeTo="allfile" />

		<!--Output hosting lifetime messages to console target for faster startup detection -->
		<logger name="Microsoft.Hosting.Lifetime" minlevel="Info" writeTo="lifetimeConsole, ownFile-web" final="true" />

		<!--Skip non-critical Microsoft logs and so log only own logs (BlackHole) -->
		<logger name="Microsoft.*" maxlevel="Info" final="true" />
		<logger name="System.Net.Http.*" maxlevel="Info" final="true" />

		<logger name="*" minlevel="Trace" writeTo="ownFile-web" />
	</rules>
</nlog>
```

+ `<target>` ：输出的目标
+ `<rules>` ：决定输出到哪个目标

将配置文件代码里面的路径盘符都删掉，这样默认为当前项目的根路径下；同时记得将 nlog.config 设置为 “如果较新就复制”。

在使用这句代码：

```c#
logBuilder.AddNLog();
```

再运行程序就会在 `LogginDemo1\bin\Debug\net6.0` 下生成文件日志。

## NLOG深入

日志分类、过滤

1、为什么要日志分类?不同级别或者不同模块的日志记录到不同的地方。

2、为什么要日志过滤? 项目不同阶段(比如刚上线和稳定后)需要记录的日志不同。严重错误可以调用短信Provider等

3、搞一个新的类，放到SvstemServices这个命名空间下，然后输出一些日志。然后调用很多次日志执行的代码。

参数解读：

1、archiveAboveSize为“单个日志文件超过多少字节就把日志存档”，单位为字节，这样可以避免单个文件太大，如果不设定maxArchiveFiles 参数，则文件日志存档文件的数量会一直增加，而如果设定maxArchiveFiles参数后，则最多保存maxArchiveFiles指定数量个数的存档文件，旧的会被删掉;当然也可以不设置maxArchiveFiles参数，而设置maxArchiveDavs参数，这样可以设定保存若干天的日志存档。

2、这些不同参数的起到什么作用?“滚动日志”策略。

rules：

1、rules节点下可以添加多个logger，每个logger都有名字 (name属性)，name是通配符格式的。

2、logger节点的minlevel属性和maxlevel属性，表示这个logger接受日志的最低级别和最高级别。

3、日志输出时，会从上往下匹配rules节点下所有的logger，若发现当前日志的分类名和 level 符合这个logger的name的通配符，就会把日志输出给这个logger。如果匹配多个logger，就把这条日志输出给多个logger。但是如果一个logger设置了final="true"，那么如果匹配到这个logger，就不继续向下匹配其他logger了。

NLOG 其他

1、NLog部分功能和.NET的Logging重复，比如分类分级、各种Provider。

2、为了避免冲突，如果用NLog，建议不要再配置.NET 的分级等 (具体用法见微软文档)

## 结构化日志和集中日志服务

结构化日志：比普通文本更利于日志的分析。

集中日志：集群化部署环境中，有N多服务器，如果每个服务器都吧日志记录到本地文件，不便于查询、分析。着要把日志保存到集中化的日志服务器中。

1、NLog也可以配置结构化日志，不过配置麻烦，推荐用Serilog

2、NuGet安装: Serilog.AspNetCore。

```
Install-Package  Serilog.AspNetCore
```

3、

```c#
Log.Logger = new LoggerConfiguration()
                .MinimumLevel.Debug()
                .Enrich.FromLogContext()
                .WriteTo.Console(new JsonFormatter())
                .CreateLogger();
logBuilder.AddSerilog();   
```

4、要记录的结构化数据通过占位符来输出:
logger.LogWarning("新增用户(@person)",newId=3,Name="zack”);

5、同样可以输出到文件、数据库、MongoDB等

集中日志服务

1、使用NLog、Serilog等可以把日志记录到数据库、MongoDB等地方，就可以实现“结构化、集中日志服务”，不过需要自己编写日志分析程序。

2、公有云厂商一般都提供了日志云服务，都带分析功能，都有对应Serilog插件，即使没有提供，开发一个插件也不麻烦

3、如果没有用云平台或者想自己控制日志服务，可以使用Exceptionless或者ELK等。

4、Exceptionless、ELK即提供了现成的云服务，也提供了自己部署(SelfHosting)的模式。由于网速等原因，云服务不符合中国的要求，不过可以试用一下，看是否满足要求，再自己部署

# EF Core

## 什么是EF Core

Entity Framework Core

什么是ORM

1、ORM:Object Relational Mapping。让开发者用对象操作的形式操作关系数据库。

比如插入：

```c#
User user = new User(Name="admin"Password="123");
orm.Save(user);
```

比如查询：

```c#
Book b = orm.Books.Single(b=>b.Id==3 || b.Name.Contains("NET"));
string bookName = b.Name;
string aName = b.Author.Name;
```

2、有哪些ORM: EF core、Dapper、SqlSugar、FreeSql等

EF Core 与其他 ORM 相比：

1、Entity Framework Core(EF Core)是微软官方的ORM框架

+ 优点:功能强大、官方支持、生产效率高、力求屏蔽底层数据库差异;
+ 缺点: 复杂、上手门槛高、不熟悉EFCore的话可能会进坑。

2、Dapper。优点:简单，N分钟即可上手，行为可预期性强;缺点:生产效率低，需要处理底层数据库差异。

3、EF Core是模型驱动(Model-Driven)的开发思想，Dapper是数据库驱动(DataBase-Driven)的开发思想的。没有优劣，只有比较。

4、性能: Dapper等≠性能高; EF Coref性能差。

5、EF Core是官方推荐、推进的框架，尽量屏蔽底层数据库差异，,NET开发者必须熟悉，根据的项目情况再决定用哪个。

## 搭建EF开发环境

用什么数据库：

1、EF Core是对于底层ADO.NET Core的封装，因此ADONET Core支持的数据库不一定被EF Cre支持

2、EF Core支持所有主流的数据库，包括MIS SQL ServerOracle、MySQL、PostgreSQL、SQLite等。可以自己实现Provider支持其他数据库。国产数据库支持问题。

3、对于SQLServer支持最完美， MySQL、PostgreSQL也不错 (有能解决的小坑) 。这三者是.NET圈中用的最多的二个。本课程主要用SOLServer讲，如果用其他数据库只要改行代码+绕一些小坑即可，大部分代码用法不变。EFCore能尽量屏蔽底层数据库差异。

### 开发环境搭建1

1、经典步骤

+ 建实体类；
+ 建配置类；
+ 建DbContext；
+ 生成数据库编写调用EF Core的业务代码。

2、Book.cs

```c#
public class Book
{
    public long Id { get; set;}//主键
    public string Title { get; set; }//标题
    public DateTime PubTime { get; set; }//发布日期
    public double Price { get; set;}//单价
}
```

Person.cs

```c#
public class Person
{
    public long Id { get; set; }
    public string Name { get; set; }
    public int Age { get; set; }
}
```

3、安装包

```c#
Install-Package Microsoft.EntityFrameworkCore.SqlServer  // SqlServer的
Install-Package Pomelo.EntityFrameworkCore.MySql  // MySQL的
```

### 开发环境搭建2

创建实现了 IEntityTypeConfiguration 接口的实体配置类，配置实体类和数据库表的对应关系。

也可以不创建配置类，那就是使用约定。

BookConfig.cs

```c#
public class BookConfig :IEntityTypeConfiguration<Book>
{
    public void Configure(EntityTypeBuilder<Book> builder)
    {
        builder.ToTable("T_Books");  // 表名：T_Boooks，表中字段就是Book类的属性
    }
}
```

PersonConfig.cs

```c#
public class PersonConfig : IEntityTypeConfiguration<Person>
{
    public void Configure(EntityTypeBuilder<Person> builder)
    {
        builder.ToTable("T_Persons");
    }
}
```

### 开发环境搭建3

创建继承自 DbContext 的类

```c#
class TestDbContext:DhContext
{
    // 实体
    public DbSet<Book> Books i { get; set }
    public DbSet<Person> Persons { get; set; }
    // 链接数据库
    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        base.OnConfiguring(optionsBuilder);
        // MySQL 数据库连接
        optionsBuilder.UseMySql("Server=localhost;Port=3306;Database=efcoretest;Uid=root;Pwd=123;",
				new MySqlServerVersion(new Version("8.0.30")));
    }
    // 加载所有的 IEntityTypeConfiguration
	protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        base.OnModelCreating(modelBuilder);
        // 从指定的程序集里面加载所有的IEntityTypeConfiguration
        modelBuilder.ApplyConfigurationsFromAssembly(this.GetType().Assembly);
    }
}
```

生成数据库：

概念: Migration数据库迁移

面向对象的ORM开发中，数据库不是程序员手动创建的，而是由Migration工具生成的。关系数据库只是盛放模型数据的一个媒介而已，理想状态下，程序员不用关心数据库的操作。

根据对象的定义变化，自动更新数据库中的表以及表结构的操作，叫做Migration (迁移)。迁移可以分为多步 (项目进化) ，也可以回滚。

### 开发环境搭建4

为了使用生成数据库的工具，Nuget安装Microsoft.EntityFrameworkCore.Tools，

```
Install-Package Microsoft.EntityFrameworkCore.Tools
```

1、再在“程序包管理器控制台”中执行如下命令

```
Add-Migration InitialCreate  // InitialCreate 可以为任意合法字符
```

会自动在项目的Migrations文件夹中中生成操作数据库的C#代码。

2、代码需要执行后才会应用对数据库的操作。“程序包管理器控制台”中执行

```c#
Update-Database
```

3、查看一下数据库，表建好了。

开发环境搭建5-修改表结构

1、项目开发中，根据需要，可能会在已有实体中修改、新增、删除表、列等。

2、想要限制Title的最大长度为50，Title字段设置为“不可为空”，并且想增加一个不可为空且最大长度为20的AuthorName (作者名字)属性。

首先在Book实体类中增加一个AuthorName属性

3、修改BookEntityConfig

```c#
builder.ToTable("T Books");
builder.Property(e => e.Title).HasMaxLength(50).IsRequired();
builder.Property(e => e.AuthorName).HasMaxLength(20).IsRequired();
```

4、执行Add-Migration AddAuthorName_ModifyTitle。取名字有意义

可能会提示：`An operation was scaffolded that may result in the loss of data. Please review the migration for accuracy.` ，意思是一个操作被搭建（scaffolded）出来，可能会导致数据丢失。请检查这次迁移的准确性。

因为这次给字段限制了长度，所以可能导致精度丢失。

5、Update-Database

## 增删改查

### 插入

1、只要操作Books属性，就可以向数据库中增加数据，但是通过C#代码修改Books中的数据只是修改了内存中的数据。对Books做修改后，需要调用DbContext的异步方法SaveChangesAsync()把修改保存到数据库。也有同步的保存方法SaveChanges()，但是用EF Core都推荐用异步方法

2、EF Core默认会跟踪(Track)实体类对象以及DbSet的改变。

```c#
// Program.cs

// ctx 相当于逻辑上的数据库
using (MyDbContext ctx = new MyDbContext())
{
    Person p = new Person();
    p.Name = "Trump";
    p.BirthPlaceP = "单独";
    p.Age = 23;
    ctx.Persons.Add(p);  // 把数据加入 Persons 这个逻辑的表里面
    ctx.SaveChanges();  // 相当于 Update-Databse
}
```

`ctx.Persons.Add(p);` 也可以不用写 `.Persons`，直接写成：`ctx.Add(p); ` 也可以，它会自动根据对象的类型来决定加入哪个表中。

`SaveChanges()` 方法在最后执行一次就可以了。

### 查询

1、DbSet实现了IEnumerable<T>接口，因此可以对DbSet实施Linq操作来进行数据查询。EF Core会把Linq操作转换为SOL语句。面向对象，而不是面向数据库(SQL)。

2、查询价格大于 80 的书

```java
// Program.cs

var books = ctx.Books.Where(b => b.Price > 80);
foreach (var book in books)
{
    Console.WriteLine(book.Title);
}
```

查询名字为“C语言”的书

```c#
// Program.cs

var book = ctx.Books.Single(b => b.Title == "C语言");
Console.WriteLine(book.Id + " " + book.Title + " " + book.Price);     
```

3、可以使用OrderBy操作进行数据的排序

```c#
// Program.cs

IEnumerable<Book> books = ctx.Books.OrderByDescending(b => b.Price);
foreach (var book in books)
{
    Console.WriteLine(book.Title);
}
```

大部分Linq操作都能用于EFCore。

### 修改、删除

1、要对数据进行修改，首先需要把要修改的数据查询出来，然后再对查询出来的对象进行修改，然后再执行SaveChangesAsync()
保存修改。

```c#
// Program.cs

var book = ctx.Books.Single(b => b.Title == "C语言");
book.AuthorName = "ZSM";
ctx.SaveChanges();
```

2、删除也是先把要修改的数据查询出来，然后再调用DbSet或者DbContext的Remove方法把对象删除，然后再执行SaveChangesAsync0保存修改。

```c#
// Program.cs

var book = ctx.Books.Single(b => b.Id == 2);
ctx.Books.Remove(book);
ctx.SaveChanges(); 
```

批量修改：将所有书的价格都上涨一块：

```c#
// Program.cs

foreach (var book in dc.Books)
{
    book.Price++;
}
```

这种目前批量修改、删除多条数据的方法在数据库里是进行了n次update操作，所以如果数据很多的话，效率很低。

+ 局限性：性能低：查出来，再一条条Update、Delete，而不能执行Update ... where；delete ... where；

一个开源的高效批量修改、删除的开源项目。Zack.EFCore.Batch https://github.com/yangzhongke/Zack.EFCore.Batch

## 实体的配置

### 约定配置

主要规则:

1：表名采用DbContext中的对应的DbSet的属性名。

2：数据表列的名字采用实体类属性的名字，列的数据类型采用和实体类属性类型最兼容的类型。

3：数据表列的可空性取决于对应实体类属性的可空性。

4：名字为Id的属性为主键，如果主键为short, int 或者 long类型，则默认采用自增字段，如果主键为Guid类型，则默认采用默认的Guid生成机制生成主键值。

两种配置方式

### Data Annotation

把配置以特性 (Annotation)的形式标注在实体类中。

```c#
[Table("T_Cats")]
public class Cat
{
    public long Id { get; set; }
    
    [Required]
    [MaxLength(22)]
    public string Name { get; set; }
}
```

优点。简单，缺点:耦合。

### Fluent API

```c#
builder ToTabre'T Books'):
```

把配置写到单独的配置类中。缺点:复杂;优点:解耦

3、大部分功能重叠。可以混用，但是不建议混用

Fluent API 

1、视图与实体类映射: 

```c#
modelBuilder.Entity<Blog>0.ToView("blogsView"):
```

2、排除属性映射:

```c#
modelBuilder.Entity<Blog>().lgnore(b => b. Name2)
```

3、配置列名:

```c#
modelBuilder.Entity<Blog>0.Property(b>b.BlogId).HasColumnName("blog_id");
```

4、配置列数据类型:

```c#
builder.Property(e => e.Title).HasColumnType("varchar(200)")
```

5、配置主键
默认把名字为Id或者“实体类型+Id“的属性作为主键，可以用HasKev()来配置其他属性作为主键。

```c#
modelBuilder.Entity<Student>0.HasKey(c =>cNumber);
```

支持复合主键，但是不建议使用。

6、生成列的值：

```c#
modelBuilder.Entity<Student>().Property(b =>b.Number).ValueGeneratedOnAdd();
```

7、设定默认值，可以用HasDefaultValue()为属性

```c#
modelBuilder.Entity<Student>0.Property(b =>b.Age).HasDefaultValue(6);
```

8、索引：

```c#	
modelBuilder.Entity<Blog>().HasIndex(b => b.Url);
```

复合索引：

```c#
modelBuilder.Entity<Person>().HasIndex(p => new { p.FirstName,p.LastName ));
```

唯一索引:

```c#
modelBilder.Entity<Book>().HasIndex(b => b.Title).IsUnique();
```

聚集索引: 

```c#
modelBilder.Entity<Book>().HasIndex(b => b.Title).IsClustered();
```

9、用EF Core太多高级特性的时候谨慎，尽量不要和业务逻辑混合在一起，以免“不能自拔”。比如Ignore、Shadow、Table Splitting等......

Fluent API众多方法

Fluent API中很多方法都有多个重载方法。比如HasIndex、Property()。

把Number属性定义为索引，下面两种方法都可以：

```c#
builder.HasIndex("Number");
builder.HasIndex(b=>b.Number);
```

推荐使用HasIndex(b=>b.Number)、Property(b => bNumber)这样的写法因为这样利用的是C#的强类型检查机制

### 所谓 Fluent

标准写法：

```c#
builder.ToTable("T_Books");
builder.HasIndex(b => b.Title);
builder.Ignore(b => b.PubTime);
```

可以合并写（链式编程代码风格）：

```c#
builder.ToTable("T_Books").HasIndex(b => b.Title);
builder.Ignore(b => b.PubTime);
```

因为 ToTable 的返回值是 EntityTableBuilder，而 HasIndex 就是 EntityTableBuilder 的方法。

但是不能这样合并写：

```c#
builder.ToTable("T_Books").HasIndex(b => b.Title).Ignore(b => b.PubTime);
```

因为 HasIndex 返回值是 IndexBuilder，而 Ignore 是属于 EntityTableBuilder 的方法。

## 主键不是小事

EF Core支持多种主键生成策略：自动增长；Guid；Hi/Lo算法等

### 自增主键

自动增长。优点：简单；缺点：数据库迁移以及分布式系统中比较麻烦；并发性能差。long、int等类型主键，默认是自增。因为是数据库生成的值，所以SaveChanges后会自动把主键的值更新到Id属性。

自增字段的代码中不能为Id赋值，必须保持默认值0，否则运行的时候就会报错。（MySQL中可以）

### Guid主键

Guid算法（或UUID算法）生成一个全局唯一的Id。适合于分布式系统，在进行多数据库数据合并的时候很简单。

+ 优点：简单，高并发，全局唯一；
+ 缺点：磁盘空间占用大。

创建Guid值：

```c#
Guid guid = Guid.NewGuid();
```

可以使用new的方法，但是结果不理想：

```c#
Guid guid1 = new Guid();
Console.WriteLine($"{guid1}");  // 00000000-0000-0000-0000-000000000000
```

Guid值不连续。使用Guid类型做主键的时候，不能把主键设置为聚集索引。因为聚集索引是按照顺序保存主键的，因此用Guid做主键性能差。

比如MySQL的InnoDB引擎中主键是强制使用聚集索引的。有的数据库支持部分的连续Guid，比如SQLServer中的NewSequentialId()，但也不能解决问题。在SQLServer等中，不要把Guid主键设置为聚集索引；在MySQL中，插入频繁的表不要用Guid做主键。

Guid即可以让EF Core赋值，也可以手动赋值（推荐）。

EF Core赋值：

```c#
Cat c = new Cat();
c.Name = "zsss";
Console.WriteLine(c.Id);  // 00000000-0000-0000-0000-000000000000
dc.Add(c);
Console.WriteLine(c.Id);  // 08dbdd11-c13b-4574-8c32-2c7caa7dae9a
await dc.SaveChangesAsync();
Console.WriteLine(c.Id);  // 08dbdd11-c13b-4574-8c32-2c7caa7dae9a
```

可以看到还没有更新到数据库中就已经赋值了，是EF Core赋值的。

手动赋值：

```c#
Cat c = new Cat();
c.Name = "zsss";
c.Id = Guid.NewGuid();
Console.WriteLine(c.Id);  // f11435aa-6df9-4bca-8ed7-2e3d8a133aff
dc.Add(c);
Console.WriteLine(c.Id);  // f11435aa-6df9-4bca-8ed7-2e3d8a133aff
await dc.SaveChangesAsync();
Console.WriteLine(c.Id);  // f11435aa-6df9-4bca-8ed7-2e3d8a133aff
```

### 其他方案

1、混合自增和Guid（非复合主键）。用自增列做物理的主键，而用Guid列做逻辑上的主键。把自增列设置为表的主键，而在业务上查询数据时候把Guid当主键用。在和其他表关联以及和外部系统通讯的时候（比如前端显示数据的标识的时候）都是使用Guid列。不仅保证了性能，而且利用了Guid的优点，而且减轻了主键自增性导致主键值可被预测带来的安全性问题。

2、Hi/Lo算法：EF Core支持Hi/Lo算法来优化自增列。主键值由两部分组成：高位（Hi）和低位（Lo），高位由数据库生成，两个高位之间间隔若干个值，由程序在本地生成低位，低位的值在本地自增生成。不同进程或者集群中不同服务器获取的Hi值不会重复，而本地进程计算的Lo则可以保证可以在本地高效率的生成主键值。但是HiLo算法不是EF Core的标准。

## 深入研究Migrations

1、使用迁移脚本，可以对当前连接的数据库执行编号更高的迁移，这个操作叫做“向上迁移”（Up），也可以执行把数据库回退到旧的迁移，这个操作叫“向下迁移”（Down）。

2、除非有特殊需要，否则不要删除Migrations文件夹下的代码。

3、进一步分析Migrations下的代码。分析Up、Down等方法。查看Migration编号。

4、查看数据库的__EFMigrationsHistory表：记录当前数据库曾经应用过的迁移脚本，按顺序排列。

### Migrations其他命令

1、把数据库回滚到Xx的状态，更新的是数据库，迁移脚本不动。

```
Update-Database Xxx
```

2、删除最后一次的迁移脚本

```
Remove-migration
```

3、生成迁移SQL代码

```
Script-Migration
```

有了 Update-Database 为什么还要生成SQL脚本。

+ 因为 Update-Database 只适合开发环境

可以生成版本D到版本F的SOL脚本:

```c#
Script-Migration D F
```

意思是，生成两个版本之间的差异的SQL脚本。

生成版本D到最新版本的SQL脚本: 

```c#
Script-Migration D
```

## 反向工程

根据数据库表来反向生成实体类。

```c#
Scaffold-DbContext 'Server=.;Database=demol;TrustedConnection=True;MultipleActiveResultSets=true' MicrosoftEntityFrameworkCore.SqlServer
```

`Scaffold-DbContext` 是一个在 Entity Framework Core 中用于根据数据库架构生成代码的命令。

- `'Server=.;Database=demol;TrustedConnection=True;MultipleActiveResultSets=true'` 是连接字符串，用于描述如何连接到数据库。
- `Microsoft.EntityFrameworkCore.SqlServer` 是你要用的提供程序。这是EF Core的SQL Server提供程序。
- `-OutputDir Models` 参数指定生成的模型文件的输出目录。这将在项目目录下创建一个名为 "Models" 的目录，并在其中生成代码文件。
- `-Context DemolContext` 参数用于指定生成的 DbContext 类的名称。在这里，生成的 DbContext 类将被命名为 "DemolContext"。

在运行这个命令之前，确保你的项目已经安装了`Microsoft.EntityFrameworkCore.SqlServer`和`Microsoft.EntityFrameworkCore.Design`这两个NuGet包。`Microsoft.EntityFrameworkCore.Design`包包含了`Scaffold-DbContext`这个命令。

1、生成的实体类可能不能满足项目的要求，可能需要手工修改或者增加配置。

2、再次运行反询工程工具，对文件所做的任何更改都将丢失。

3、不建议把反向工具当成了日常开发工具使用，不建议DBFirst.

## EF Core 底层如何操作数据库

![image-20230626164107226](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230626164107226.png)

查看生成的SQL语句

SOL Server Profiler查看SOLServer数据库当前执行的SOL语句（收费版的SQL Server才有）。

### 有哪些做不到的事

C#千变万化；SQL功能简单。存在合法的C#语句无法被翻译为SQL语句的情况。比如：

```c#
var books = dc.Books.Where(b => IsOK(b.Title));
foreach (var b in books)
{
    await Console.Out.WriteLineAsync(b.Title);
}

private static bool IsOK(string s)
{
    return s.Contains("张");
}
```

以上程序就会报错：

```
Unhandled exception. System.InvalidOperationException: The LINQ expression 'DbSet<Book>()
    .Where(b => Program.IsOK(b.Title))' could not be translated. 
```

![image-20230626170937915](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230626170937915.png)

### 通过代码查看 EF Core 生成的 SQL

#### 标准日志

```c#
// MyDbContext.cs

// 加个属性：
public static readonly ILoggerFactory MyLoggerFactory
					= LoggerFactory.Create(builder => { builder.AddConsole(); });

optionsBuilder.UseLoggerFactory(MyLoggerFactory);
```

AddConsole 需要安装一个 logging.console 包。

#### 简单日志

可以自己写代码过滤一些不需要的消息。

```c#
optionsBuilder.LogTo(msg =>
{
    if (!msg.Contains("CommandExecuting")) return;
    Console.WriteLine(msg);
});
```

#### ToQueryString

1、上面两种方式无法直接得到一个操作的SQL语句，而且在操作很多的情况下，容易混乱。

2、EF Core的Where方法返回的是IQueryable类型，DbSet也实现了IQueryable接口。 IQueryable有扩展方法ToQueryString()可以获得SQL。

```c#
IQueryable<Book> books = dc.Books.Where(b => b.Title.Contains("C"));
Console.WriteLine(books.ToQueryString());

/*
SELECT `t`.`Id`, `t`.`AuthorName`, `t`.`Price`, `t`.`PubTime`, `t`.`Title`
FROM `T_Books` AS `t`
WHERE `t`.`Title` LIKE '%C%'
*/
```

3、不需要真的执行查询才获取SQL语句；==只能获取查询操作的==。

## 同样的LINQ被翻译为不同的SQL语句

不同数据库方言不同。

比如，获取 t 表中前三条数据：

```
SQLServer:  select top(3) * from t
MySQL: select * from t LIMIT 3
Oracle: select * from t where ROWNUM<=3
```

同样的C#语句在不同数据库中被EF Core翻译成不同的SQL语句。

EF Core迁移脚本和数据库相关。因此迁移脚本不能跨数据库。通过给Add-Migration命令添加“-OutputDir”参数的形式来在同一个项目中为不同的数据库生成不同的迁移脚本。

## 一对多关系

数据库表之间的关系：一对一、一对多、多对多。

EF Core不仅支持单实体操作，更支持多实体的关系操作。

三部曲：实体类中关系属性；FluentAPI关系配置；使用关系操作。

### 配置

**实体类：**文章实体类Article，评论实体类Comment，一篇文章对应多条评论。

```c#
// Article.cs
public class Article
{
	public long Id { get; set; }
	public string Title { get; set; }
	public string Content { get; set; }
    // 建议给一个空的List
	public List<Comment> Comments { get; set; } = new List<Comment>();   // 这种写法在C#9以后有效
    
}

// Comment.cs
public class Comment
{
	public long Id { get; set; }
	public Article Article { get; set; }
	public string Message { get; set; }
}
```

**关系配置：**EF Core中实体之间关系的配置的套路：

```c#
HasXXX(…).WithXXX(…);
```

有XXX、反之带有XXX。XXX可选值One、Many。

```c#
一对多：HasOne(…).WithMany(…);
一对一：HasOne(…).WithOne (…);
多对多：HasMany (…).WithMany(…);
```

```c#
// ArticleConfig.cs
public class ArticleConfig : IEntityTypeConfiguration<Article>
{
    public void Configure(EntityTypeBuilder<Article> builder)
    {
        builder.ToTable("T_Articles");
        builder.Property(e => e.Title).HasMaxLength(20).IsRequired();
        builder.Property(e => e.Message).IsRequired();
    }
}

// CommentConfig.cs
public class CommentConfig : IEntityTypeConfiguration<Comment>
{
    public void Configure(EntityTypeBuilder<Comment> builder)
    {
        builder.ToTable("T_Comments");
        builder.Property(e => e.Message).IsRequired();
        builder.HasOne<Article>(c => c.TheArticle).WithMany(a => a.Comments).IsRequired();
    }
}

// MyDbContext.cs
using (MyDbContext dc = new MyDbContext())
{
    Article a1 = new Article();
    a1.Title = "震惊！";
    a1.Message = "荆楚理工一男子……";

    Comment c1 = new Comment { Message = "牛逼" };
    Comment c2 = new Comment { Message = "假的" };
    a1.Comments.Add(c1);
    a1.Comments.Add(c2);

    dc.Articles.Add(a1);
    dc.SaveChanges();
    
    /*
    也可以这样写，但是没有必要
    Article a1 = new Article();
    a1.Title = "震惊！";
    a1.Message = "荆楚理工一男子……";

    Comment c1 = new Comment { Message = "牛逼" , TheArticle = a1};
    Comment c2 = new Comment { Message = "假的" , TheArticle = a1};
    a1.Comments.Add(c1);
    a1.Comments.Add(c2);

    dc.Articles.Add(a1);
    dc.Comments.Add(c1);
    dc.Comments.Add(c2);
    dc.SaveChanges();
    */
}
```

`builder.HasOne<Article>(c => c.TheArticle).WithMany(a => a.Comments);`：有一个文章对应着多个评论。

不需要显式为Comment对象的Article属性赋值（当然赋值也不会出错），也不需要显式地把新创建的Comment类型的对象添加到DbContext中。只要添加了关系，EF Core会“顺竿爬”。

### 数据获取

假如按一般写法来获取一对多的数据：

```c#
Article a = dc.Articles.Single(a => a.Id == 1);
Console.WriteLine(a.Title);
Console.WriteLine(a.Message);
foreach (var c in a.Comments)
{
    Console.WriteLine(c.Id + ", " + c.Message);
}
```

输出的结果只会有 a 的数据，但是没有 a.Comments 的数据。

以上代码执行的SQL语句：

```mysql
SELECT `t`.`Id`, `t`.`Message`, `t`.`Title`
FROM `T_Articles` AS `t`
WHERE `t`.`Id` = 1
LIMIT 2
```

可以看出来，只涉及到了 Articles 表的查询，没有涉及到 Comments 表的查询。

所以在获取关联表的数据时，需要在前面加一个 Include() ：

```c#
Article a = dc.Articles.Include(a=>a.Comments).Single(a=>a.Id==1);
Console.WriteLine(a.Title);
foreach(Comment c in a.Comments)
{
	Console.WriteLine(c.Id+":"+c.Message);
}
```

Include定义在Microsoft.EntityFrameworkCore命名空间中。以上代码就可以将 a.Comments 查询出来。

查看一下生成的SQL语句：

```mysql
SELECT `t0`.`Id`, `t0`.`Message`, `t0`.`Title`, `t1`.`Id`, `t1`.`Message`, `t1`.`TheArticleId`
FROM (
  SELECT `t`.`Id`, `t`.`Message`, `t`.`Title`
  FROM `T_Articles` AS `t`
  WHERE `t`.`Id` = 1
  LIMIT 2
) AS `t0`
LEFT JOIN `T_Comments` AS `t1` ON `t0`.`Id` = `t1`.`TheArticleId`
ORDER BY `t0`.`Id`
```

同样，如果不使用 Include，也不能通过 Comment 来查到 Article：

```c#
Comment c = dc.Comments.Single(c => c.Id == 2);
Article a = c.TheArticle;
Console.WriteLine(c.Id + ", " + c.Message);
Console.WriteLine(a.Title + " , " + a.Message);

/*
2, 假的
Unhandled exception. System.NullReferenceException: Object reference not set to an instance of an object.
   at OneToMany.Program.Main(String[] args) in D:\MyCode\C#\一对多\Program.cs:line 42
*/
```

使用 Include：

```c#
Comment c = dc.Comments.Include(c => c.TheArticle).Single(c => c.Id == 2);
Article a = c.TheArticle;
Console.WriteLine(c.Id + ", " + c.Message);
Console.WriteLine(a.Title + " , " + a.Message);

/*
2, 假的
震惊！ , 荆楚理工一男子……
*/
```

如果不使用 Include 的话也可以，可以使用 Select 来操作：

```C#
var cm = dc.Comments.Select(c => new { Id = c.Id, AId = c.TheArticle.Id }).Single(c => c.Id == 2);
```

生成的SQL语句：

```mysql
SELECT `t`.`Id`, `t0`.`Id` AS `AId`
FROM `T_Comments` AS `t`
INNER JOIN `T_Articles` AS `t0` ON `t`.`TheArticleId` = `t0`.`Id`
WHERE `t`.`Id` = 2
LIMIT 2
```

### 额外的外键字段

假如现在只要 Article 的 Title 和 Id 属性，通过上面的方法，可以看到生成的 SQL 语句都是将 Article 的 Id、Title、Message 全部查询了出来，这样效率较慢，我们可以通过 Select 投影设定只查询哪几列：

```c#
var a = dc.Articles.Select(a => new {a.Id, a.Title}).First();
```

这样生成的SQL语句是：

```mysql
SELECT `t`.`Id`, `t`.`Title`
FROM `T_Articles` AS `t`
LIMIT 1
```

可以看到，只查询了指定的列，并没有将所有的列都查询出来。

那如果要通过 Comment 来查询到对应 Article 的 Id，就要用上面的两种方式，但是生成的 SQL 语句可以看到，使用了表的连接，所以效率也低。

正确的解决方法是：给实体类中显式声明一个外键属性，对应 TheArticle 列。

```c#
public class Comment
{
    public long Id { get; set; }
    public Article TheArticle { get; set; }
    public long TheArticleId { get; set; }  // 外键属性，对应TheArticle 
    public string Message { get; set; }
}
```

设置外键：

```c#
// CommentConfig.cs
builder.HasOne<Article>(c => c.TheArticle).WithMany(a => a.Comments)
        .HasForeignKey(c => c.TheArticleId)
        .IsRequired();
```

查询：

```c#
var cm = dc.Comments.Single(c => c.Id == 2);
Console.WriteLine(cm.Id + ", " + cm.TheArticleId);
```

生成的SQL语句：

```mysql
SELECT `t`.`Id`, `t`.`Message`, `t`.`TheArticleId`
FROM `T_Comments` AS `t`
WHERE `t`.`Id` = 2
LIMIT 2
```

这样就没有了表连接的操作，还可以使用 Select 来指定查询的列：

```c#
var cm = dc.Comments.Select(c => new { c.Id, c.TheArticleId }).Single(c => c.Id == 2);

/*mysql：
SELECT `t`.`Id`, `t`.`TheArticleId`
FROM `T_Comments` AS `t`
WHERE `t`.`Id` = 2
LIMIT 2
*/
```

除非有必要，否则不用声明，因为会引入重复。

### 单向导航属性

导航属性：由这个属性可以访问到另一个实体，这种属性叫导航属性。

Article 中的 Comments 属性是一个导航属性，Comment 中的 TheArticle 是一个导航属性。

**双向导航：**Article 中的 Comments 指向 Comment 类，Comment 类中的 TheArticle 指向 Article 类，这就是双向导航。

**单向导航：**A 指向 B，B 不指向 A。

创建两个实体类：

```c#
// User.cs
public class User
{
    public long Id { get; set; }
    public string Name { get; set; }
}

// Leave.cs
// 请假条
public class Leave
{
    public long Id { get; set; }
    public User Requester { get; set; }  // 申请人
    public User Approver { get; set; }  // 审批人
    public string Remarks { get; set; }  // 备注
}
```

配置方法：不设置反向的属性，然后配置的时候 WithMany() 不设置参数即可。

```c#
// UserConfig.cs
internal class UserConfig : IEntityTypeConfiguration<User>
{
    public void Configure(EntityTypeBuilder<User> builder)
    {
        builder.ToTable("T_Users");
    }
}

// LeaveConfig.cs
internal class LeaveConfig : IEntityTypeConfiguration<Leave>
{
    public void Configure(EntityTypeBuilder<Leave> builder)
    {
        builder.ToTable("T_Leaves");
        builder.HasOne<User>(l => l.Requester).WithMany().IsRequired();
        builder.HasOne<User>(l => l.Approver).WithMany();
    }
}
```

查询一下，查看生成的SQL语句：

```c#
var l = dc.Leaves.FirstOrDefault();
```

```mysql
SELECT `t`.`Id`, `t`.`ApproverId`, `t`.`Remarks`, `t`.`RequesterId`
FROM `T_Leaves` AS `t`
LIMIT 1
```

插入数据：

```c#
User u1 = new User { Name = "张总" };
User u2 = new User { Name = "李四" };
Leave l1 = new Leave { Requester = u2, Remarks = "回家" ,Approver = u1};
dc.Leaves.Add(l1);
dc.SaveChanges();
```

注意：这里插入的时候，Requester 和 Approver 都必须要赋值，如果不赋值的话，MySQL 会报错，因为外键约束。

对于主从结构的“一对多”表关系，一般是声明双向导航属性。

而对于其他的“一对多”表关系：如果表属于被很多表引用的基础表，则用单项导航属性，否则可以自由决定是否用双向导航属性。

### 关系配置在任何一方都可以

如果是双向导航属性，配置在哪一边都可以。

```c#
// CommentConfig：
builder.HasOne<Article>(c=>c.Article).WithMany(a => a.Comments).IsRequired();
					↓
// ArticleConfig：
builder.HasMany<Comment>(a => a.Comments).WithOne(c => c.Article).IsRequired();
```

### 自引用的组织结构树

#### 方法一

绑定父和子的关系，只用往数据库中添加根节点即可。

```c#
// Program.cs:
using Microsoft.EntityFrameworkCore;

namespace OneToManyTree
{
	internal class Program
	{
		static void Main(string[] args)
		{
			OrgUnit ouRoot = new OrgUnit { Name = "张三集团全球总部 " };
			
			OrgUnit ouAsia = new OrgUnit { Name = "张三集团亚太区总部" };
			ouAsia.Parent = ouRoot;
			ouRoot.Children.Add(ouAsia);

			OrgUnit ouAmerica = new OrgUnit { Name = "张三集团美州总部" };
			ouAmerica.Parent = ouRoot;
			ouRoot.Children.Add(ouAmerica);

			OrgUnit ouUSA = new OrgUnit { Name = "张三集团（美国）" };
			ouUSA.Parent = ouAmerica;
			ouAmerica.Children.Add(ouUSA);


			OrgUnit ouCan = new OrgUnit { Name = "张三集团（加拿大）" };
			ouCan.Parent = ouAmerica;
			ouAmerica.Children.Add(ouCan);


			OrgUnit ouChina = new OrgUnit { Name = "张三集团（中国）" };
			ouChina.Parent = ouAsia;
			ouAsia.Children.Add(ouChina);

			OrgUnit ouSg = new OrgUnit { Name = "张三集团（新加坡）" };
			ouSg.Parent = ouAsia;
			ouAsia.Children.Add(ouSg);

			using (MyDbContext dc = new MyDbContext())
			{
				dc.OrgUnits.Add(ouRoot);
				dc.SaveChanges();
			}
		}
	}
}

// MyContext.cs
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OneToManyTree
{
	internal class MyDbContext : DbContext
	{
		public DbSet<OrgUnit> OrgUnits { get; set; }

		protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
		{
			base.OnConfiguring(optionsBuilder);
			optionsBuilder.UseMySql("Server=localhost;Port=3306;Database=efcoretest2;Uid=root;Pwd=123;",
				new MySqlServerVersion(new Version("8.0.30")));

			optionsBuilder.LogTo(msg =>
			{
				if (!msg.Contains("CommandExecuting")) return;
				Console.WriteLine(msg);
			});
		}

		protected override void OnModelCreating(ModelBuilder modelBuilder)
		{
			base.OnModelCreating(modelBuilder);
			// 从指定的程序集里面加载所有的IEntityTypeConfiguration
			modelBuilder.ApplyConfigurationsFromAssembly(this.GetType().Assembly);
		}
	}
}

// OrgUnit.cs
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OneToManyTree
{
	internal class OrgUnitConfig : IEntityTypeConfiguration<OrgUnit>
	{
		public void Configure(EntityTypeBuilder<OrgUnit> builder)
		{
			builder.ToTable("T_OrgUnits");
			builder.Property(o => o.Name).IsRequired().IsUnicode().HasMaxLength(100);
			builder.HasOne<OrgUnit>(u => u.Parent).WithMany(p => p.Children);  // 根节点没有parent，所以这个不能修饰为非空的。

		}
	}
}

// OrgUnit.cs
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OneToManyTree
{
	public class OrgUnit
	{
		public long Id { get; set; }
		public string Name { get; set; }
		public OrgUnit Parent { get; set; }
		public List<OrgUnit> Children { get; set; } = new List<OrgUnit>();
	}

}
```

以上代码会报错，因为 MySQL 的外键约束，这种写法默认的外键是 ParentId，但是根节点可以没有parentId，而MySQL不允许。所以要解决这个问题，就需要现在数据库中添加一条数据，然后用这条数据的ID来作为根节点的ID即可。

先手动添加一个外键：

```c#
// OrgUnit.cs
public class OrgUnit
{
    public long Id { get; set; }
    public string Name { get; set; }
    public long ParentId { get; set; }
    public OrgUnit Parent { get; set; }
    public List<OrgUnit> Children { get; set; } = new List<OrgUnit>();
}

// OrgUnitConfig.cs
public void Configure(EntityTypeBuilder<OrgUnit> builder)
{
    builder.ToTable("T_OrgUnits");
    builder.Property(o => o.Name).IsRequired().IsUnicode().HasMaxLength(100);
    builder.HasOne<OrgUnit>(u => u.Parent).WithMany(p => p.Children)
        .HasForeignKey(o => o.ParentId);   // 使用ParentId作为外键  
}
```

然后在数据库中添加一条数据，将这条数据的 Id 值给根节点的 ParentId 即可：

```c#
static void Main(string[] args)
{
    // 将数据库中已有的数据的id给根节点的ParentId
    OrgUnit ouRoot = new OrgUnit { Name = "张三集团全球总部 ", ParentId = 1 };

    OrgUnit ouAsia = new OrgUnit { Name = "张三集团亚太区总部" };
    ouAsia.Parent = ouRoot;
    ouRoot.Children.Add(ouAsia);

    OrgUnit ouAmerica = new OrgUnit { Name = "张三集团美州总部" };
    ouAmerica.Parent = ouRoot;
    ouRoot.Children.Add(ouAmerica);

    OrgUnit ouUSA = new OrgUnit { Name = "张三集团（美国）" };
    ouUSA.Parent = ouAmerica;
    ouAmerica.Children.Add(ouUSA);


    OrgUnit ouCan = new OrgUnit { Name = "张三集团（加拿大）" };
    ouCan.Parent = ouAmerica;
    ouAmerica.Children.Add(ouCan);


    OrgUnit ouChina = new OrgUnit { Name = "张三集团（中国）" };
    ouChina.Parent = ouAsia;
    ouAsia.Children.Add(ouChina);

    OrgUnit ouSg = new OrgUnit { Name = "张三集团（新加坡）" };
    ouSg.Parent = ouAsia;
    ouAsia.Children.Add(ouSg);

    using (MyDbContext dc = new MyDbContext())
    {
        dc.OrgUnits.Add(ouRoot);  // 只需要添加根节点
        dc.SaveChanges();
    }
}
```

#### 方法二

只绑定每个节点的父亲关系，然后将所有节点都加入数据库中。

```c#
static void Main(string[] args)
{
    OrgUnit ouRoot = new OrgUnit { Name = "张三集团全球总部 ", ParentId = 1 };

    OrgUnit ouAsia = new OrgUnit { Name = "张三集团亚太区总部" };
    ouAsia.Parent = ouRoot;

    OrgUnit ouAmerica = new OrgUnit { Name = "张三集团美州总部" };
    ouAmerica.Parent = ouRoot;

    OrgUnit ouUSA = new OrgUnit { Name = "张三集团（美国）" };
    ouUSA.Parent = ouAmerica;

    OrgUnit ouCan = new OrgUnit { Name = "张三集团（加拿大）" };
    ouCan.Parent = ouAmerica;

    OrgUnit ouChina = new OrgUnit { Name = "张三集团（中国）" };
    ouChina.Parent = ouAsia;

    OrgUnit ouSg = new OrgUnit { Name = "张三集团（新加坡）" };
    ouSg.Parent = ouAsia;

    using (MyDbContext dc = new MyDbContext())
    {
        dc.OrgUnits.Add(ouRoot);
        dc.OrgUnits.Add(ouAsia);
        dc.OrgUnits.Add(ouAmerica);
        dc.OrgUnits.Add(ouCan);
        dc.OrgUnits.Add(ouChina);
        dc.OrgUnits.Add(ouSg);
        dc.SaveChanges();
    }
}
```

#### 递归缩进打印

输出以下图形：

![image-20231105155942714](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311051559813.png)

```c#
using(MyDbContext dc = new MyDbContext())

    // 数据库中的 Id 为 1 的数据不是根节点，根节点是以 1 为 ParentId 的节点
    var root = dc.OrgUnits.Single(o => o.ParentId == 1 && o.Id != 1);
    Console.WriteLine(root.Name);
    PrintChildren(1, dc, root);
}

static void PrintChildren(int level, MyDbContext dc, OrgUnit root)
{
    var chilren = dc.OrgUnits.Where(o => o.ParentId == root.Id);
    foreach (var cur in chilren)
    {
        Console.WriteLine(new string('\t', level) + cur.Name);
        PrintChildren(level + 1,new MyDbContext(), cur);
        // 下面这样写的话会抛异常：
        // Unhandled exception.System.InvalidOperationException: This MySqlConnection is already in use.
        // PrintChildren(level + 1,dc, cur);
    }
}
```

`new  string(字符, 个数)`：这种构造方法产生的字符串是：指定次数的字符。比如

+ `new string('a', 3)`：aaa

## 一对一关系

必须显式的在其中一个实体类中声明一个外键属性。

**实体类：**一个订单 Order 对应着一个快递单 Delivery。

```c#
// Order.cs
class Order
{
    public long Id { get; set; }
    public string Name { get; set; }
    public Delivery Delivery { get; set; }
}
// Delivery.cs
class Delivery
{
    public long Id { get; set; }
    public string CompanyName { get; set; }
    public String Number { get; set; }  // 订单号
    public Order Order { get; set; }
    public long OrderId { get; set; }  // 外键
}
```

**配置类：**

```c#
//DeliveryConfig
internal class DeliveryConfig : IEntityTypeConfiguration<Delivery>
{
    public void Configure(EntityTypeBuilder<Delivery> builder)
    {
        builder.ToTable("T_Delivery");
    }
}
// OrderConfig
internal class OrderConfig : IEntityTypeConfiguration<Order>
{
    public void Configure(EntityTypeBuilder<Order> builder)
    {
        builder.ToTable("T_Order");
        // 配置一对一关系，设置外键
        builder.HasOne<Delivery>(o => o.Delivery).WithOne(d => d.Order)
            .HasForeignKey<Delivery>(d => d.OrderId);
    }
}
```

插入数据：

```c#
static async Task Main(string[] args)
{
    using(MyDbContext dc = new MyDbContext())
    {
        Order o1 = new Order();
        o1.Name = "书";
        Delivery d1 = new Delivery();
        d1.CompanyName = "时髦快递";
        d1.Number = "sm1001";
        d1.Order = o1;
        // 不需要给外键OrderId赋值

        // 插入 d1 会自动插入 o1
        // 但插入 o1 不会自动插入 d1
        // 可能是因为 Deliveries 上有 Orders 的外键
        dc.Deliveries.Add(d1);
        await dc.SaveChangesAsync();
    }
}
```

## 多对多关系

EF Core 5.0 开始，才正式支持多对多关系。

需要中间表。

**实体类：**每个学生 Student 可以对应多个老师 Teacher，每个老师也可以对应多个学生。

```c#
// Student.cs
class Student
{
	public long Id { get; set; }
	public string Name { get; set; }
	public List<Teacher> Teachers { get; set; } = new List<Teacher>();
}

// Teacher.cs
class Teacher
{
	public long Id { get; set; }
	public string Name { get; set; }
	public List<Student> Students { get; set; } = new List<Student>();
}	
```

**配置类：**

```c#
// StudentConfig
internal class StudentConfig : IEntityTypeConfiguration<Student>
{
    public void Configure(EntityTypeBuilder<Student> builder)
    {
        builder.ToTable("T_Students");
        builder.HasMany<Teacher>(s => s.Teachers).WithMany(t => t.Students)
            .UsingEntity(j => j.ToTable("T_StudentsTeachers"));  // 多对多关系配置
    }
}
// TeacherConfig
internal class TeacherConfig : IEntityTypeConfiguration<Teacher>
{
    public void Configure(EntityTypeBuilder<Teacher> builder)
    {
        builder.ToTable("T_Teachers");
    }
}
```

插入数据：

```c#
static void Main(string[] args)
{
    using(MyDbContext dc = new MyDbContext())
    {
        Student s1 = new Student { Name = "张三" };
        Student s2 = new Student { Name = "李四" };
        Student s3 = new Student { Name = "王五" };

        Teacher t1 = new Teacher { Name = "Tom" };
        Teacher t2 = new Teacher { Name = "Jack" };
        Teacher t3 = new Teacher { Name = "Mike" };

        s1.Teachers.Add(t1);
        s1.Teachers.Add(t2);

        s2.Teachers.Add(t2);
        s2.Teachers.Add(t3);

        s3.Teachers.Add(t1);
        s3.Teachers.Add(t2);
        s3.Teachers.Add(t3);

        dc.Students.Add(s1);
        dc.Students.Add(s2);
        dc.Students.Add(s3);

        dc.Teachers.Add(t1);
        dc.Teachers.Add(t2);
        dc.Teachers.Add(t3);

        dc.SaveChanges();
    }
}
```

查询数据：

```c#
var ts = dc.Teachers.Include(t => t.Students);
foreach (var t in ts)
{
    Console.WriteLine(t.Name);
    foreach (var s in t.Students)
    {
        Console.WriteLine("\t" + s.Name);
    }
}
```

## 基于关系的复杂查询

查询评论中含有“微软”的所有的文章：

```C#
var articles = dc.Articles.Where(a => a.Comments.Any(c => c.Message.Contains("微软"))).Distinct();
```

`.Distinct()` 是去重的，防止一个文章的评论区有多个包含 “微软” 的评论。

生成的SQL语句：

```mysql
SELECT DISTINCT `t`.`Id`, `t`.`Message`, `t`.`Title`
FROM `T_Articles` AS `t`
WHERE EXISTS (
  SELECT 1
  FROM `T_Comments` AS `t0`
  WHERE (`t`.`Id` = `t0`.`TheArticleId`) AND (`t0`.`Message` LIKE '%微软%'))
```

换一种写法：

```c#
var articles = dc.Comments.Where(c => c.Message.Contains("微软")).Select(c => c.TheArticle).Distinct();
```

生成的SQL语句：

```mysql
SELECT DISTINCT `t0`.`Id`, `t0`.`Message`, `t0`.`Title`
FROM `T_Comments` AS `t`
INNER JOIN `T_Articles` AS `t0` ON `t`.`TheArticleId` = `t0`.`Id`
WHERE `t`.`Message` LIKE '%微软%'
```

查询“所有由蜗牛快递负责的订单信息”

```c#
dc.Orders.Where(o=>o.Delivery.CompanyName== "蜗牛快递");
```

## 有了IEnumerable还要IQueryable干什么

对普通集合和DbSet调用的Where方法，虽然用起来一样，但是“转到定义”后看到的是不同的方法。

+ 普通集合：是 Enumerable 的方法，返回的也是个 IEnumerable
+ DbSet：是 Queryable 的方法，返回的也是个 IQueryable

**差别**：普通集合的版本(IEnumerable)是在内存中过滤（客户端评估），而IQueryable版本则是把查询操作翻译成SQL语句（服务器端评估）。

**比较：**

IQueryable：

```c#
IQueryable<Comment> cm = dc.Comments.Where(c => c.Message.Contains("微软"));

/*
生成的SQL代码：
SELECT `t`.`Id`, `t`.`Message`, `t`.`TheArticleId`
FROM `T_Comments` AS `t`
WHERE `t`.`Message` LIKE '%微软%'
*/
```

IEnumerable：

在所有数据的取出来了，然后在内存中进行一条条比较

```c#
IEnumerable<Comment> comments = dc.Comments;
IEnumerable<Comment> cm = comments.Where(c => c.Message.Contains("微软"));

/*
SELECT `t`.`Id`, `t`.`Message`, `t`.`TheArticleId`
FROM `T_Comments` AS `t`
*/
```

## 客户端评估有时候也很可爱

需求：取出评论的前两个字。

服务器端评估：

```c#
var r = dc.Comments.Select(c => c.Message.Substring(0, 2) + "...");
/*
SQL:
SELECT CONCAT(COALESCE(SUBSTRING(`t`.`Message`, 0 + 1, 2), ''), '...')
FROM `T_Comments` AS `t`
```

客户端评估：

```c#
var r = ((IEnumerable<Comment>)(dc.Comments)).Select(c => c.Message.Substring(0, 2) + "...");
/*
SELECT `t`.`Id`, `t`.`Message`, `t`.`TheArticleId`
FROM `T_Comments` AS `t`
```

## IQueryable的延迟执行

正常情况下，我们执行以下代码可以在控制台看到生成的 SQL 语句：

```c#
IQueryable<Article> ats = dc.Articles.Where(a => a.Title.Contains("微软"));
foreach (var item in ats)
{
    Console.WriteLine(item.Title);
}

/*
SELECT `t`.`Id`, `t`.`Message`, `t`.`Title`
FROM `T_Articles` AS `t`
WHERE `t`.`Title` LIKE '%微软%'
```

但是如果不要下面这个 foreach 循环，就看不到生成的 SQL 语句：

```C#
IQueryable<Article> ats = dc.Articles.Where(a => a.Title.Contains("微软"));
//foreach (var item in ats)
//{
//    Console.WriteLine(item.Title);
//}
```

使用输出语句，查看执行顺序：

```c#
Console.WriteLine("准备 Where");
IQueryable<Article> ats = dc.Articles.Where(a => a.Title.Contains("微软"));
Console.WriteLine("准备 foreach");
foreach (var item in ats)
{
    Console.WriteLine(item.Title);
}
Console.WriteLine("结束 foreach");
```

输出结果是：

```
准备 Where
准备 foreach
dbug: 2023/11/5 19:03:59.457 RelationalEventId.CommandExecuting[20100] (Microsoft.EntityFrameworkCore.Database.Command)
      Executing DbCommand [Parameters=[], CommandType='Text', CommandTimeout='30']
      SELECT `t`.`Id`, `t`.`Message`, `t`.`Title`
      FROM `T_Articles` AS `t`
      WHERE `t`.`Title` LIKE '%微软%'
微软发布一首歌曲
微软倒闭了
结束 foreach
```

这说明只有遍历 IQueryable 的时候才会执行 Select 操作。

IQueryable 只是代表一个“可以放到数据库服务器去执行的查询”，它没有立即执行，只是“可以被执行”而已。

对于 IQueryable 接口调用非终结方法的时候不会执行查询，而调用终结方法的时候则会立即执行查询。

+ 终结方法：遍历、ToArray()、ToList()、Min()、Max()、Count()等；
+ 非终结方法：GroupBy()、OrderBy()、Include()、Skip()、Take()等。

一个方法的返回值类型如果是 IQueryable 类型，那么这个方法一般就是非终结方法，否则就是终结方法。

**为什么延迟执行**：可以在实际执行之前，分步构建IQueryable。

比如，查看以下语句生成的SQL：

```c#
IQueryable<Article> articles = dc.Articles.Where(a => a.Id > 1);
IQueryable<Article> articles1 = articles.Skip(2);
IQueryable<Article> articles2 = articles1.Take(3);
IQueryable<Article> articles3 = articles2.Where(a => a.Title.Contains("微软"));
articles3.ToArray();

/*
SELECT `t0`.`Id`, `t0`.`Message`, `t0`.`Title`
FROM (
  SELECT `t`.`Id`, `t`.`Message`, `t`.`Title`
  FROM `T_Articles` AS `t`
  WHERE `t`.`Id` > 1
  LIMIT @__p_1 OFFSET @__p_0
) AS `t0`
WHERE `t0`.`Title` LIKE '%微软%'
```

这样可以在实际执行（ToArray()）之前，分布构建SQL语句。

比如：定义一个方法根据给定的关键字 searchWords 来查询匹配的书；如果 searchAll 参数是 true，则书名或者作者名中含有给定的 searchWords 都匹配，否则只匹配书名；如果 orderByPrice 参数为 true，则按照价格排序，否则就自然排序；upperPrice 参数代表价格上限。

```c#
void QueryBooks(string searchWords, bool searchAll, bool orderByPrice,double upperPrice)
```

**结论：**

1、IQueryable代表一个对数据库中数据进行查询的一个逻辑，这个查询是一个延迟查询。我们可以调用非终结方法向IQueryable中添加查询逻辑，当执行终结方法的时候才真正生成SQL语句来执行查询。

2、可以实现以前要靠SQL拼接实现的动态查询逻辑。

## IQueryable的复用

IQueryable是一个待查询的逻辑，因此它是可以被重复使用的。

## 分页查询

**实现：**

+ 使用 Skip() 和 Take() 。最好显式的指定排序规则。

+ 需要知道满足条件的数据的总条数：用 IQueryable 的复用，LongCount()

  Count返回的是一个 int 型值，LongCount 返回的是一个 long 型值，都是数据条数

+ 页数计算：`long pageCount = (long)Math.Ceiling(count * 1.0 / pageSize);`

比如：

```c#
/// <summary>
/// 打印某一页的数据及总页数
/// </summary>
/// <param name="pageIndex">页码，从1开始</param>
/// <param name="pageSize">每一页的数据条数</param>
static void PrintPage(int pageIndex, int pageSize)
{
    using(MyDbContext dc = new MyDbContext())
    {
        IQueryable<Article> arts = dc.Articles.Where(a => a.Id >= 1);
        var items = arts.Skip((pageIndex - 1) * pageSize).Take(pageSize);
        foreach (var item in items)
        {
            Console.WriteLine(item.Title);
        }
        long count = arts.LongCount();
        long pageCount = (long)Math.Ceiling(count * 1.0 / pageSize);
        Console.WriteLine("总页数：" + pageCount);
    }
}
```

这里的 IQueryable 复用体现在：先 Where，再 Skip、Take，然后 LongCount。

## IQueryable底层是如何读取数据的

**对比：**（ADO.NET 中的两种方式）

+ DataReader：分批从数据库服务器读取数据。内存占用小、 DB连接占用时间长；
  + 优点：节省客户端内存。
  + 缺点：如果处理的慢，会长时间占用连接。
+ DataTable：把所有数据都一次性从数据库服务器都加载到客户端内存中。内存占用大，节省DB连接。

IQueryable内部就是在调用DataTable。

**验证IQueryable用什么方式：**

用insert into select多插入一些数据：

```mysql
INSERT into t_articles (Title, Message)
SELECT Title, Message from t_articles
```

这可以每次都插入一遍 t_articles 中所有的数据。

然后加上Delay/Sleep的遍历IQueryable：

```C#
foreach(var a in dc.Articles)
{
    Console.WriteLine(a.Title);
    Thread.Sleep(10);
}
```

在遍历执行的过程中，停止MySQL服务器。

但是程序还在运行，说明是像DataTable一样将数据一次性从数据库加载到客户端内存中。

何时需要一次性加载？

+ 遍历IQueryable并且进行数据处理的过程很耗时。
+ 如果方法需要返回查询结果，并且在方法里销毁DbContext的话，是不能返回IQueryable的。必须一次性加载返回。
+ 多个IQueryable的遍历嵌套。很多数据库的ADO.NET Core Provider是不支持多个DataReader同时执行的。把连接字符串（SQLServer）中的MultipleActiveResultSets=true删掉，其他数据库不支持这个。

## 异步方法

异步方法大部分是定义在 `Microsoft.EntityFrameworkCore` 这个命名空间下 `EntityFrameworkQueryableExtensions` 等类中的扩展方法，记得 `using`。

SaveChangesAsync()、AddAsync()、AddRangeAsync()、AllAsync()、AnyAsync、AverageAsync、ContainsAsync、CountAsync、FirstAsync、FirstOrDefaultAsync、ForEachAsync、LongCountAsync、MaxAsync、MinAsync、SingleAsync、SingleOrDefaultAsync、SumAsync等。

调用异步方法需要使用 `await` 调用，那么使用了 `await` 就要在方法声明上添加 `async` ，并将返回值类型变为 `Task`。

**有的方法没有异步方法：**

IQueryable的这些异步的扩展方法都是“立即执行”方法，而GroupBy、OrderBy、Join、Where等“非立即执行”方法则没有对应的异步方法。

为什么？因为异步方法常用于那些耗 IO 的操作，而“非立即执行”方法并没有实际执行SQL语句，并不是消耗IO的操作。

**如何异步遍历IQueryable：**

+ `ToListAsync()`、`ToArrayAsync()`。结果集不要太大。
+ `wait foreach (var a in dc.Articles.AsAsyncEnumerable())`

## EF Core执行非查询原生SQL语句

尽管EF Core已经非常强大，但是仍然存在着无法被写成标准EF Core调用方法的SQL语句，少数情况下仍然需要写原生SQL。且有时候可能无法跨数据库。

三种情况：非查询语句、实体查询、任意SQL查询。

### 执行非查询SQL语句

使用：`dc.Database.ExecuteSqlInterpolated("");`

```c#
int min = 1;
dc.Database.ExecuteSqlInterpolated(@$"
    INSERT into t_articles (Title, Message)
    SELECT Title, Message 
    From t_articles
    Where id >= {min}
");
```

+ 在字符串前使用 `@` 可以换行表示一个字符串，使用 `$` 可以使用插值语法。

直接执行 SQL 语句都不需要进行 SaveChanges 操作。

**使用插值语法是否有SQL注入漏洞风险？**

以上代码生成的SQL语句是：

```mysql
INSERT into t_articles (Title, Message)
SELECT Title, Message
From t_articles
Where id >= @p0
```

说明使用插值语法的部分会被占位符替代，而不是简单的字符串拼接，所以不会有SQL注入风险。

字符串内插如果赋值给 string 变量，就是字符串拼接；字符串内插如果赋值给 FormattableString 变量，编译器就会构造 FormattableString 对象。

ExecuteSqlInterpolatedAsync() 的参数是 FormattableString 类型。因此 ExecuteSqlInterpolatedAsync 会进行参数化SQL的处理。

```c#
FormattableString sql = @$"
    INSERT into t_articles (Title, Message)
    SELECT Title, Message 
    From t_articles
    Where id >= {min}
";

Console.WriteLine("Format: " + sql.Format);
Console.WriteLine("参数：" + string.Join(",", sql.GetArguments()));
// sql.GetArguments() 返回的是数组，使用 Join 连接起来好看点
```

输出结果：

```shell
Format:
    INSERT into t_articles (Title, Message)
    SELECT Title, Message
    From t_articles
    Where id >= {0}

参数：1
```

这个 `{0}` 就是占位符。

**ExecuteSqlRaw**

除了 ExecuteSqlInterpolated ()、ExecuteSqlInterpolatedAsync() ，还有 ExecuteSqlRaw()、ExecuteSqlRawAsync() 也可以执行原生SQL语句，但需要开发人员自己处理查询参数等了，因此不推荐使用。

### 执行实体相关查询原生SQL语句

如果要执行的原生SQL是一个查询语句，并且查询的结果也能对应一个实体，就可以调用对应实体的 DbSet 的 `FromSqlInterpolated() `方法来执行一个查询SQL语句，同样使用字符串内插来传递参数。

```c#
string titlePattern = "%微软%";
var arts = dc.Articles.FromSqlInterpolated(@$"
    select * from T_Articles 
    where Title like {titlePattern}
    order by id");
foreach (var item in arts)
{
    Console.WriteLine(item.Title);
}
```

`FromSqlInterpolated()` 方法的返回值是 IQueryable 类型的，因此我们可以在实际执行 IQueryable 之前，对 IQueryable 进行进一步的处理。

```c#
string titlePattern = "%微软%";
var arts = dc.Articles.FromSqlInterpolated(@$"
    select * from T_Articles 
    where Title like {titlePattern}
    order by id");
foreach (var item in arts.Skip(2).Take(2))
{
    Console.WriteLine(item.Title);
}
```

以上代码会在SQLServer中报错，因为SQLServer中不允许子查询中有排序语句，但是在MySQL中不会报错，生成的SQL代码是这样的：

```mysql
SELECT `o`.`Id`, `o`.`Message`, `o`.`Title`
FROM (
        select * from T_Articles
        where Title like @p0
        order by id
) AS `o`
LIMIT @__p_1 OFFSET @__p_1
```

**局限性：**

+ SQL 查询必须返回实体类型对应数据库表的所有列；
+ 结果集中的列名必须与属性映射到的列名称匹配。
+ 只能单表查询，不能使用Join语句进行关联查询。但是可以在查询后面使用Include()来进行关联数据的获取。

### 执行任意原生SQL查询语句

`FromSqlInterpolated()` 只能单表查询，但是在实现报表查询等的时候，SQL语句通常是非常复杂的，不仅要多表Join，而且返回的查询结果一般也都不会和一个实体类完整对应。因此需要一种执行任意SQL查询语句的机制。

EF Core中允许把视图或存储过程映射为实体，因此可以把复杂的查询语句写成视图或存储过程，然后再声明对应的实体类，并且在DbContext中配置对应的DbSet。

不推荐写存储过程；项目复杂查询很多，导致：视图太多；非实体的DbSet；DbSet膨胀。

**执行任意SQL:**

`dc.Database.GetDbConnection()` 获得ADO.NET Core的数据库连接对象。

```c#
DbConnection conn = dc.Database.GetDbConnection();
if (conn.State != System.Data.ConnectionState.Open)  // 判断当前连接是否打开了
    await conn.OpenAsync();
// conn 对象不需要手动释放
using (var cmd = conn.CreateCommand())
{
    cmd.CommandText = "select Price,Count(*) from T_Articles group by Price";
    using(var reader = await cmd.ExecuteReaderAsync())
    {
        while (await reader.ReadAsync())
        {
            double price = reader.GetDouble(0);
            int count = reader.GetInt32(1);
            await Console.Out.WriteLineAsync($"{price}元的有{count}个");
        }
    }
}
```

这种方式跳过了 EF Core ，所以控制台不会输出EF Core生成的SQL语句。
