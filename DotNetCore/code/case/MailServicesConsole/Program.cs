using ConfigServices;
using LogServices;
using MailServices;
using Microsoft.Extensions.DependencyInjection;
namespace MailServicesConsole
{
    public class Program
    {
        static void Main(string[] args)
        {
            ServiceCollection services = new ServiceCollection();
            // services.AddScoped(typeof(IConfigServices), s => new IniFileConfigService { FilePath = "mail.ini" });
            // services.AddScoped<ILogProvider, ConsoleLogProvider>();
            services.AddScoped<IConfigServices, EnvVarConfigServices>();
            services.AddScoped<IMailService, MailService>();
            using (var sp = services.BuildServiceProvider())
            {
                // 第一个根对象只能用 ServiceLocator
                var mailService = sp.GetRequiredService<IMailService>();
                mailService.Send("Hello", "trump@usa.gov", "东王你好");
            }
        }
    }
}