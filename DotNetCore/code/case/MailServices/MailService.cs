using ConfigServices;
using LogServices;
using System;
using System.Collections.Generic;
using System.Text;

namespace MailServices
{
    public class MailService : IMailService
    {
        private readonly ILogProvider log;
        private readonly IConfigServices config;
        public MailService(ILogProvider log, IConfigServices config)
        {
            this.log = log;
            this.config = config;
        }
        public void Send(string title, string to, string body)
        {
            log.LogInfo("准备发送邮件了");
            string smtpServer = this.config.GetValue("smtpServer");
            string username = this.config.GetValue("username");
            string password = this.config.GetValue("password");
            Console.WriteLine($"邮件服务器地址:{smtpServer}, {username},{password}");
            Console.WriteLine($"发邮件{title}: {body} 给{to}");
            log.LogInfo("邮件发送完毕");
        }

    }
}
