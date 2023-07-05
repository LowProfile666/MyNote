using System;
using System.Collections.Generic;
using System.Text;

namespace ConfigServices
{
    /**
     * 环境变量配置
     */
    public class EnvVarConfigServices : IConfigServices
    {
        public string GetValue(string name)
        {
            return Environment.GetEnvironmentVariable(name);
        }
    }
}
