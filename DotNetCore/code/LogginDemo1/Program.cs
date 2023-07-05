using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using NLog.Extensions.Logging;
using Serilog;
using Serilog.Formatting.Json;

namespace LogginDemo1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            ServiceCollection service = new ServiceCollection();
            service.AddLogging(logBuilder =>
            {
                //logBuilder.AddConsole();
                //logBuilder.AddNLog();
                //logBuilder.SetMinimumLevel(LogLevel.Trace);  // 设置最低级别
                Log.Logger = new LoggerConfiguration()
                .MinimumLevel.Debug()
                .Enrich.FromLogContext()
                .WriteTo.Console(new JsonFormatter())
                .CreateLogger();
                logBuilder.AddSerilog();     
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