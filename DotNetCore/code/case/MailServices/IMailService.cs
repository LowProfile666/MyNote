using System;
using System.Collections.Generic;
using System.Text;

namespace MailServices
{
    public interface IMailService
    {
        /**
         * title : 邮件标题
         * to : 发给谁
         * body : 邮件内容
         */
        public void Send(string title, string to, string body);
    }
}
