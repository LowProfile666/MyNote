using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Channels;
using System.Xml.Linq;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;

namespace ConsoleTest
{
    internal class Program
    {
        //static async Task Main(string[] args)
        //{
        //    string fileName = "D:\\MyNote\\DotNetCore\\1.txt";
        //    File.Delete(fileName);
        //    await File.WriteAllTextAsync(fileName, "hello async");
        //    string s = await File.ReadAllTextAsync(fileName);
        //    Console.WriteLine(s);
        //}

        //static async Task Main(string[] args)
        //{
        //    await DownloadHtmlAsync("https://www.youzack.com", "D:\\MyNote\\DotNetCore\\code\\youzackTest.txt");
        //}
        //static async Task DownloadHtmlAsync(string url, string filename)
        //{
        //    using (HttpClient httpClient = new HttpClient())
        //    {
        //        string html = await httpClient.GetStringAsync(url);
        //        await File.WriteAllTextAsync(filename, html);
        //    }
        //}

        //static void Main(string[] args)
        //{
        //    //Task<string> t = File.ReadAllTextAsync("D:\\MyNote\\DotNetCore\\code\\youzackTest.txt");
        //    //string s = t.Result;
        //    // string s = File.ReadAllTextAsync("D:\\MyNote\\DotNetCore\\code\\youzackTest.txt").Result;
        //    //Console.WriteLine(s)
        //    File.WriteAllTextAsync("D:\\MyNote\\DotNetCore\\code\\WaitTest.txt", "This is a Test").Wait();

        //}   

        //static async Task Main(string[] args)
        //{
        //    Console.WriteLine(Thread.CurrentThread.ManagedThreadId);
        //    StringBuilder sb = new StringBuilder();
        //    for (int i = 0; i < 10; i++)
        //    {
        //        sb.Append("xxxxxxxxxxx");
        //    }
        //    await File.WriteAllTextAsync("D:\\MyNote\\DotNetCore\\code\\test.txt", sb.ToString());
        //    Console.WriteLine(Thread.CurrentThread.ManagedThreadId);
        //}

        // 异步方法不等于多线程

        // 没有 async 的异步方法
        //static async Task Main(string[] args)
        //{
        //    string s = await ReadAsync(1);
        //    Console.WriteLine(s);
        //}
        //static async Task<string> ReadAsync(int num)
        //{
        //    if (num == 1)
        //    {
        //        string s = await File.ReadAllTextAsync("D:\\MyNote\\DotNetCore\\code\\test.txt");
        //        return s;
        //    }
        //    else
        //    {
        //        string s = await File.ReadAllTextAsync("D:\\MyNote\\DotNetCore\\code\\test.txt");
        //        return s;
        //    } 
        //}
        //static Task<string> ReadAsync(int num)
        //{
        //    if (num == 1)
        //        return File.ReadAllTextAsync("D:\\MyNote\\DotNetCore\\code\\test.txt");
        //    else
        //        return File.ReadAllTextAsync("D:\\MyNote\\DotNetCore\\code\\test.txt");
        //}

        // 不要使用 Sleep


        // 取消
        //static async Task Main(string[] args)
        //{
        //    // await DownloadAsync1("https://www.baidu.com", 200);
        //    CancellationTokenSource cts = new CancellationTokenSource();
        //    cts.CancelAfter(5000);  // 5秒后取消
        //    CancellationToken cToken = cts.Token;
        //    // await DownloadAsync2("https://www.baidu.com", 200, cToken);
        //    await DownloadAsync3("https://www.baidu.com", 200, cToken);
        //}
        //static async Task Main(string[] args)
        //{
        //    CancellationTokenSource cts = new CancellationTokenSource();
        //    CancellationToken cToken = cts.Token;
        //    await DownloadAsync3("https://www.baidu.com", 200, cToken);
        //    while (Console.ReadLine() != "q")
        //    {

        //    }
        //    cts.Cancel();
        //    Console.WriteLine();
        //}
        //static async Task DownloadAsync1(string url, int n)
        //{
        //    using (HttpClient client = new HttpClient())
        //    {
        //        for (int i = 0; i < n; i++)
        //        {
        //            string html = await client.GetStringAsync(url);
        //            Console.WriteLine($"{DateTime.Now}:{html}");
        //        }
        //    }
        //}
        //static async Task DownloadAsync2(string url, int n, CancellationToken cancellationToken)
        //{
        //    using (HttpClient client = new HttpClient())
        //    {
        //        for (int i = 0; i < n; i++)
        //        {
        //            string html = await client.GetStringAsync(url);
        //            Console.WriteLine($"{DateTime.Now}:{html}");
        //            //if (cancellationToken.IsCancellationRequested)
        //            //{
        //            //    Console.WriteLine("请求被取消");
        //            //    break;
        //            //}
        //            cancellationToken.ThrowIfCancellationRequested();
        //        }
        //    }
        //}
        //static async Task DownloadAsync3(string url, int n, CancellationToken cancellationToken)
        //{
        //    using (HttpClient client = new HttpClient())
        //    {
        //        for (int i = 0; i < n; i++)
        //        {
        //            var resp = await client.GetAsync(url, cancellationToken);
        //            string html = await resp.Content.ReadAsStringAsync();
        //            Console.WriteLine($"{DateTime.Now}:{html}");
        //        }
        //    }
        //}

        // WhenAll
        //static async Task Main(string[] args)
        //{
        //    Task<string> t1 = File.ReadAllTextAsync(@"D:\MyNote\DotNetCore\code\1.txt");
        //    Task<string> t2 = File.ReadAllTextAsync(@"D:\MyNote\DotNetCore\code\2.txt");
        //    Task<string> t3 = File.ReadAllTextAsync(@"D:\MyNote\DotNetCore\code\test.txt");
        //    string[] strs = await Task.WhenAll(t1, t2, t3);
        //    string s1 = strs[0];
        //    string s2 = strs[1];
        //    string s3 = strs[2];
        //    Console.WriteLine(s1);
        //    Console.WriteLine(s2);
        //    Console.WriteLine(s3);
        //}
        //static async Task Main(string[] args)
        //{
        //    string[] files = Directory.GetFiles("D:\\MyNote\\DotNetCore\\code");  // 拿到文件夹下的所有文件名
        //    Task<int>[] count = new Task<int>[files.Length];  // 创建一个用来保存每一个文件字符数量的数组
        //    for (int i = 0; i < files.Length; i++)
        //    {
        //        string filename = files[i];
        //        Task<int> t = GetCharCount(filename);
        //        count[i] = t;
        //    }
        //    int[] counts = await Task.WhenAll(count);  // 将每个文件字符数放在一个数组里面
        //    int sum = counts.Sum();  // 计算数组的和
        //    Console.WriteLine(sum);
        //}
        //static async Task<int> GetCharCount(string filename)
        //{
        //    string s = await File.ReadAllTextAsync(filename);
        //    return s.Length;
        //}

        // LINQ
        // 委托
        //delegate void D1();
        //delegate int D2(int a, int b);
        //static void Main(string[] args)
        //{
        //    D1 d = F1;
        //    d();  // 我是方法F1
        //    d = F2;
        //    d();  // 我是方法F2

        //    D2 d2 = Add;
        //    Console.WriteLine(d2(10, 20));  // 30

        //    Action a = F1;
        //    a();

        //    Func<int, int, int> f = Add;
        //    Console.WriteLine(f(12, 2));
        //}
        //static void F1()
        //{
        //    Console.WriteLine("我是方法F1");
        //}
        //static void F2()
        //{
        //    Console.WriteLine("我是方法F2");
        //}
        //static int Add(int i, int j)
        //{
        //    return i + j;
        //}

        // 委托指向匿名方法
        //static void Main(string[] args)
        //{
        //    Action f1 = delegate ()
        //    {
        //        Console.WriteLine("Hello World"); 
        //    };
        //    f1();
        //    Action<string, int> f2 = delegate (string name, int age)
        //    {
        //        Console.WriteLine($"name={name}, age={age}");
        //    };
        //    f2("zsm",20);
        //    Func<int, int, int> f3 = delegate (int a, int b)
        //    {
        //        return a + b;
        //    };
        //    Console.WriteLine(f3(10, 10));
        // lambda
        //    Func<int, int, int> f4 = (a, b) =>
        //    {
        //        return a + b;
        //    };
        //    Console.WriteLine(f4(100,20));

        //    Action<int,int> f5 = (a, b) => Console.WriteLine($"a={a},b={b}");
        //    f5(30, 29);
        //    Func<int, int, int> f6 = (a, b) => a + b;
        //    Console.WriteLine(f6(23, 45));

        //    Action<int> f7 = a => Console.WriteLine(a);
        //    f7(100);
        //    Func<int, int> f8 = a => a + 10;
        //    Console.WriteLine(f8(100));
        //}

        // LINQ
        //static void Main(string[] args)
        //{
        //    int[] arr = { 12, 2, 4, 54, 3, 4, 23, 54, 54, 677, 98, 6, 45, 0, 0 };
        //    // IEnumerable<int> res = arr.Where(a => a > 10);
        //    // IEnumerable<int> res = MyWhere2(arr, a => a > 10);
        //    var res = MyWhere2(arr, a => a > 10);
        //    foreach (int i in res)
        //    {
        //        Console.WriteLine(i);
        //    }
        //}
        //static IEnumerable<int> MyWhere(IEnumerable<int> items, Func<int, bool> f)
        //{
        //    List<int> res = new List<int>();
        //    foreach(int i in items)
        //    {
        //        if (f(i) == true)
        //        {
        //            res.Add(i);
        //        }
        //    }
        //    return res;
        //}
        //static IEnumerable<int> MyWhere2(IEnumerable<int> items, Func<int, bool> f)
        //{
        //    foreach (int i in items)
        //    {
        //        if (f(i) == true)
        //        {
        //            yield return i;
        //        }
        //    }
        //}

        // LINQ 的常用方法
        //class Employee
        //{
        //    public long Id { get; set; }
        //    public string? Name { get; set; }
        //    public int Age { get; set; }
        //    public bool Gender { get; set; }
        //    public int Salary { get; set; }
        //    public override string ToString()
        //    {
        //        return $"id = {Id}, name = {Name}, age = {Age}, gender={Gender}, salary = {Salary}";
        //    }
        //}
        //static void Main(string[] args)
        //{
        //    List<Employee> list = new List<Employee>();
        //    list.Add(new Employee { Id = 1, Name = "Mary", Age = 19, Gender = false, Salary = 2147 });
        //    list.Add(new Employee { Id = 2, Name = "Jack", Age = 32, Gender = true, Salary = 1000 });
        //    list.Add(new Employee { Id = 3, Name = "Bob", Age = 21, Gender = true, Salary = 4521 });
        //    list.Add(new Employee { Id = 4, Name = "Tom", Age = 18, Gender = true, Salary = 9000 });
        //    list.Add(new Employee { Id = 5, Name = "Jerry", Age = 34, Gender = true, Salary = 1201 });
        //    list.Add(new Employee { Id = 6, Name = "Lucy", Age = 25, Gender = false, Salary = 3587 });
        //    list.Add(new Employee { Id = 7, Name = "Rose", Age = 32, Gender = false, Salary = 5470 });
        //    list.Add(new Employee { Id = 8, Name = "Jim", Age = 19, Gender = true, Salary = 8740 });

        //    //IEnumerable<Employee> items = list.Where(e => e.Age > 20);
        //    //foreach(Employee e in items)
        //    //{
        //    //    Console.WriteLine(e);
        //    //}

        //    //Console.WriteLine(list.Count());
        //    //Console.WriteLine(list.Count(e => e.Age > 30));
        //    //Console.WriteLine(list.Count(e => e.Age > 30 && e.Salary > 2000));

        //    //Console.WriteLine(list.Any(e => e.Age < 18));
        //    //Console.WriteLine(list.Any(e => e.Salary > 2000));

        //    // list.Single();  // Unhandled exception. System.InvalidOperationException: Sequence contains more than one element
        //    // Employee e =  list.Where(e => e.Name == "Jack").Single();
        //    // Console.WriteLine(e);  // id = 2, name = Jack, age = 32, gender=True, salary = 1000
        //    //Employee e1 = list.Where(e => e.Name == "ZSM").Single();
        //    //Console.WriteLine(e1);  // Unhandled exception. System.InvalidOperationException: Sequence contains no elements
        //    // Employee e1 = list.Single(e => e.Name == "Jack");
        //    // Console.WriteLine(e);

        //    //Employee e = list.SingleOrDefault(e => e.Name == "ZSM");
        //    //Console.WriteLine(e == null);  // 
        //    //Employee e1 = list.SingleOrDefault(e => e.Name == "Jim");
        //    //Console.WriteLine(e1);  // id = 8, name = Jim, age = 19, gender=True, salary = 8740

        //    //int[] nums = new int[] { 1, 2, 43, 45, 76, 8, 6, 4, 9 };
        //    //int i = nums.SingleOrDefault(a => a > 100);
        //    //Console.WriteLine(i);  // 0
        //    //int j = nums.SingleOrDefault(a => a > 45);
        //    //Console.WriteLine(j);  // 76
        //    // int k = nums.SingleOrDefault(a => a > 10);
        //    // Unhandled exception. System.InvalidOperationException: Sequence contains more than one matching element

        //    //Employee e = list.First(e => e.Age > 30);
        //    //Console.WriteLine(e);  // id = 2, name = Jack, age = 32, gender = True, salary = 1000
        //    //// Employee e1 = list.First(e => e.Age > 200);
        //    //// Unhandled exception. System.InvalidOperationException: Sequence contains no matching element
        //    //Employee e1 = list.FirstOrDefault(e => e.Age > 200);
        //    //Console.WriteLine(e1 == null);  // True

        //    //IEnumerable<Employee> items = list.OrderBy(e => e.Age);
        //    //foreach(Employee e in items)
        //    //{
        //    //    Console.WriteLine(e); 
        //    //}

        //    //IEnumerable<Employee> items = list.OrderByDescending(e => e.Age);
        //    //foreach (Employee e in items)
        //    //{
        //    //    Console.WriteLine(e);
        //    //}

        //    //int[] nums = new int[] { 1, 2, 43, 45, 76, 8, 6, 4, 9 };
        //    //Random rand = new Random();
        //    //var items = nums.OrderByDescending(e => rand.Next());
        //    //foreach (int i in items)
        //    //{
        //    //    Console.WriteLine(i);
        //    //}

        //    //IEnumerable<Employee> items = list.OrderBy(e => e.Name[e.Name.Length - 1]);
        //    //foreach (var e in items)
        //    //{
        //    //    Console.WriteLine(e);
        //    //}

        //    //IEnumerable<Employee> items = list.OrderBy(e => e.Age).ThenBy(e => e.Id);
        //    //foreach (var e in items)
        //    //{
        //    //    Console.WriteLine(e);
        //    //}

        //    //IEnumerable<Employee> items = list.Skip(20);//.Take(3);
        //    //foreach (var e in items)
        //    //{
        //    //    Console.WriteLine(e);
        //    //}

        //    //IEnumerable<IGrouping<int, Employee>> items = list.GroupBy(e => e.Age);
        //    //foreach(IGrouping<int, Employee> g in items)
        //    //{
        //    //    Console.WriteLine(g.Key);
        //    //    foreach(Employee e in g)
        //    //    {
        //    //        Console.WriteLine(e);
        //    //    }
        //    //    Console.WriteLine("===========================");
        //    //}

        //    //var items = list.GroupBy(e => e.Age);
        //    //foreach (var g in items)
        //    //{
        //    //    Console.WriteLine(g.Key);
        //    //    foreach (var e in g)
        //    //    {
        //    //        Console.WriteLine(e);
        //    //    }
        //    //    Console.WriteLine("===========================");
        //    //}

        //    //IEnumerable<string> ages = list.Select(e => e.Age + "," + e.Name);
        //    //foreach(var i in ages)
        //    //{
        //    //    Console.WriteLine(i);
        //    //}

        //    //var obj1 = new { Name = "zsm", Age = 19, Tel = "15760656503" };
        //    //Console.WriteLine($"{obj1.Name},{obj1.Age},{obj1.Tel}");  // zsm,19,15760656503

        //    //var items = list.Select(e => new { Name = e.Name, Age = e.Age, Gender = e.Gender ? "男" : "女" });
        //    //foreach(var i in items)
        //    //{
        //    //    Console.WriteLine(i.Name + " " + i.Age + " " + i.Gender);
        //    //}

        //    //IEnumerable<Employee> items = list.Where(e => e.Age > 19);
        //    //List<Employee> list2 = items.ToList();
        //    //Employee[] array2 = items.ToArray();

        //    //var items = list.Where(e => e.Id > 2)
        //    //    .GroupBy(e => e.Age)
        //    //    .OrderBy(e => e.Key)
        //    //    .Take(3)
        //    //    .Select(e => new {NL = e.Key, RS = e.Count(), PJ = e.Average(e => e.Salary)});
        //    //foreach(var i in items)
        //    //{
        //    //    Console.WriteLine(i);
        //    //}

        //    //var items = list.Where(e => e.Salary > 3000)
        //    //    .OrderBy(e => e.Age)
        //    //    .Select(e => new { e.Age, e.Name, Gender = e.Gender ? "男" : "女" });
        //    //foreach(var i in items)
        //    //{
        //    //    Console.WriteLine(i);
        //    //}

        //    //var items = from e in list
        //    //            where e.Salary > 3000
        //    //            select new { e.Age, e.Name, Gender = e.Gender ? "男" : "女"  };
        //    //foreach (var i in items)
        //    //{
        //    //    Console.WriteLine(i);
        //    //}

        //    // 性能与面试
        //    //string s = "61,90,100,18,22,38,66,80,93,55,50,89";
        //    //string[] ss = s.Split(",");
        //    //IEnumerable<int> nums = ss.Select(e => Convert.ToInt32(e));
        //    //double ave = nums.Average();
        //    //Console.WriteLine(ave);
        //    //double ave = s.Split(',').Select(e => Convert.ToInt32(e)).Average();
        //    //Console.WriteLine(ave);


        //    //string s = "HelloWorld, HHHaaa, java C# is nb.";
        //    //var items = s.Where(e => char.IsLetter(e))
        //    //    .Select(e => char.ToLower(e))
        //    //    .GroupBy(e => e)
        //    //    .Select(e => new { e.Key, Count = e.Count() })
        //    //    .OrderByDescending(e => e.Count)
        //    //    .Where(e => e.Count > 2);
                 
        //    //foreach (var i in items)
        //    //{
        //    //    Console.WriteLine(i);
        //    //}
        //}

        // 依赖注入
        //public interface ITestService
        //{
        //    public string Name { get; set; }
        //    public void SayHi();
        //}
        //public class TestServiceImpl : ITestService
        //{
        //    public string Name { get; set; }
        //    public void SayHi()
        //    {
        //        Console.WriteLine($"Hi, I am {Name}");
        //    }
        //}
        //static void Main(string[] args)
        //{
        //    //ITestService it = new TestServiceImpl();
        //    //it.Name = "Tom";
        //    //it.SayHi();
        //    ServiceCollection service = new ServiceCollection();
        //    // service.AddTransient<TestServiceImpl>();
        //    // service.AddSingleton<TestServiceImpl>();
        //    service.AddScoped<TestServiceImpl>();
        //    using (ServiceProvider sp = service.BuildServiceProvider())  // ServiceProvider == 服务定位器
        //    {
        //        //TestServiceImpl t = sp.GetService<TestServiceImpl>();
        //        //t.Name = "Tom";
        //        //t.SayHi();

        //        //TestServiceImpl t1 = sp.GetService<TestServiceImpl>();
        //        //t1.Name = "Bob";
        //        //t1.SayHi();

        //        //t.SayHi();
        //        //Console.WriteLine(object.ReferenceEquals(t, t1));
        //        using (IServiceScope scope1 = sp.CreateScope())
        //        {
        //            // 在 Scope 中获取相关的对象，用 scope1.ServiceProvider 而不是 sp
        //            TestServiceImpl t = scope1.ServiceProvider.GetService<TestServiceImpl>();
        //            TestServiceImpl t1 = scope1.ServiceProvider.GetService<TestServiceImpl>();
        //            Console.WriteLine(object.ReferenceEquals(t, t1));
        //        }
        //    }
        //}

        // DI 会传染
        //static void Main(string[] args)
        //{
        //    ServiceCollection services = new ServiceCollection();
        //    services.AddScoped<Controller>();
        //    services.AddScoped<ILog, LogImpl>();
        //    services.AddScoped<IStorage, StorageImpl>();
        //    services.AddScoped<IConfig, ConfigImpl>();

        //    using (var sp = services.BuildServiceProvider())
        //    {
        //        var c = sp.GetRequiredService<Controller>();
        //        c.Test();
        //    }
        //}
        //class Controller
        //{
        //    private readonly ILog log;
        //    private readonly IStorage storage;
        //    public Controller(ILog log, IStorage storage)
        //    {
        //        this.log = log;
        //        this.storage = storage;
        //    }
        //    public void Test()
        //    {
        //        log.Log("开始上传");
        //        storage.Save("helloWorld", "1.txt");
        //        log.Log("上传完毕");
        //    }
        //}
        //interface ILog
        //{
        //    public void Log(string msg);
        //}
        //class LogImpl : ILog
        //{
            
        //    void ILog.Log(string msg)
        //    {
        //        Console.WriteLine($"日志：{msg}");

        //    }
        //}
        //interface IConfig
        //{
        //    public string GetValue(string name);
        //}
        //class ConfigImpl : IConfig
        //{
        //    public string GetValue(string name)
        //    {
        //        return "hello";
        //    }
        //}
        //interface IStorage
        //{
        //    public void Save(string content, string name);
        //}
        //class StorageImpl : IStorage
        //{
        //    private readonly IConfig config;
        //    public StorageImpl(IConfig config)
        //    {
        //        this.config = config;
        //    }
        //    public void Save(string content, string name)
        //    {
        //        string server = config.GetValue("server");
        //        Console.WriteLine($"向服务器{server}的文件名为{name}上传{content}");
        //    }
        //}

        // 配置系统
        //static void Main(string[] args)
        //{
        //    ConfigurationBuilder configBuilder = new ConfigurationBuilder();
        //    configBuilder.AddJsonFile("config.json", optional: true, reloadOnChange: true);
        //    IConfigurationRoot configRoot = configBuilder.Build();
        //    //string name = configRoot["name"];
        //    //string proxyAddress = configRoot.GetSection("proxy:address").Value;
        //    Proxy p = configRoot.GetSection("proxy").Get<Proxy>();
        //    Console.WriteLine(p.Address);
        //    Console.WriteLine(p.Port);
        //}
        //class Proxy
        //{
        //    public string Address { get; set; }
        //    public int Port { get; set; }
        //}


    }

} 