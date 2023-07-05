using System;
using System.Collections.Generic;
using System.Text;

namespace ConfigServices
{
    public interface IConfigServices
    {
        /**
         * 读取名字为 name 的配置项的值
         */
        public string GetValue(string name);
    }
}
