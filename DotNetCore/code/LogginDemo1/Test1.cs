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
