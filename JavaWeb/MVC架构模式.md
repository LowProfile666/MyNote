# 三层架构

![三层架构2](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401111027403.png)

+ 表现层/Web层/表示层
+ 业务逻辑层
+ 持久化层

# MVC

Model、View、Controller

Model 实际上包含：

+ pojo/bean/domain
+ service
+ dao

MVC 对应 三层架构：

![MVC架构模式的理解](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401111028720.png)

# 什么是 DAO

Data Access Object，数据访问对象。

DAO 实际上是一种设计模式，属于 JavaEE 的设计模式之一。（不是 23 中设计模式）

# DAO 的作用

DAO 只负责数据的库表的 CRUD，没有任何的业务逻辑在里面。

没有任何业务逻辑，只负责表中数据增删改查的对象，叫 DAO 对象。

一般情况下，一张表会对应一个 DAO 对象。

在对应数据库表的实体类中，属性一般不建议设计为基本数据类型，建议使用包装类型，因为数据库中查出来的数据可能为 null，这样可以避免 null 带来的问题。

DAO 类中的方法起名一般是这些：

+ insert
+ deleteByXxx
+ update
+ selectByXxx
+ selectAll

# pojo、bean、domain

POJO：Plain Ordinary Java Object，简单的Java对象，实际就是普通 JavaBean 对象。

有的人也会把这种专门封装数据的对象，称为 bean 对象（JavaBean：咖啡豆）

有的人也会把这种专门封装数据的对象，称为 domain 对象，领域模型对象。

但这三个都是一个东西，只是程序员的习惯不同，叫法不同。

# service

service 翻译为：业务。xxxService 类是专门处理 xxx 业务的一个类。

业务类一般起名：XxxService、XxxBiz……

在该类中应该编写纯业务代码，只专注业务，不写别的，不和其他代码混合在一块。

service 类中方法起名，一定要体现出，要处理的是什么业务。一般是一个业务对应一个方法。

# 控制事务

一般是一个业务对应一个完整的事务。所以事务的控制应该放在 service 层里实现。

比如在转账的业务里，A 账户向 B 账户转 M 元，需要先将 A 账户的余额减少 M 元，再将 B 账户的余额增加 M 元，但是这两个步骤之间可能发生错误，导致第二步不会执行，这样的话，A 账户余额减少了，但是 B 账户的余额没有增加，这个时候就需要事务。

在第一步操作之前开启事务，在最后一步之后提交事务，如果步骤中间出现了错误，则回滚事务。

但是在项目中，业务处理在 service 层，数据库操作在 dao 层，在 service 层中开启事务的话需要数据库连接对象，但是这个数据库连接对象又和 dao 层操作数据库的对象不一样，这样在 service 层开启的事务就没有意义，不会有作用。

所以可以想到使用一个 map 集合，保存每个线程对应的数据库连接对象，这样在 service 类中可以拿到当前线程对应的数据库连接对象，service 调用 dao 层的方法时，dao 层的方法也可以拿到当前线程对应的数据库连接对象，service 和 dao 拿到的数据库连接对象是同一个，因为它们在同一个线程中。这样在 service 中开启的事务就有效了。

```java
import com.powernode.bank.exceptions.AppException;
import com.powernode.bank.exceptions.MoneyNotEnoughException;
import com.powernode.bank.utils.DBUtil;
import java.sql.Connection;
import java.sql.SQLException;

public class AccountService {
    // 为什么定义到这里？因为在每一个业务方法中都可以需要连接数据库。
    private AccountDao accountDao = new AccountDao();

    /**
     * 完成转账的业务逻辑
     * @param fromActno 转出账号
     * @param toActno 转入账号
     * @param money 转账金额
     */
    public void transfer(String fromActno, String toActno, double money) 
        	throws MoneyNotEnoughException, AppException {
        // service层控制事务
        try (Connection connection = DBUtil.getConnection()){
            System.out.println(connection);	
            // 开启事务(需要使用Connection对象)
            connection.setAutoCommit(false);

            // 查询余额是否充足
            Account fromAct = accountDao.selectByActno(fromActno);
            if (fromAct.getBalance() < money) {
                throw new MoneyNotEnoughException("对不起，余额不足");
            }
            // 程序到这里说明余额充足
            Account toAct = accountDao.selectByActno(toActno);
            // 修改余额（只是修改了内存中java对象的余额）
            fromAct.setBalance(fromAct.getBalance() - money);
            toAct.setBalance(toAct.getBalance() + money);
            // 更新数据库中的余额
            int count = accountDao.update(fromAct);

            // 模拟异常
            String s = null;
            s.toString();

            count += accountDao.update(toAct);
            if (count != 2) {
                throw new AppException("账户转账异常！！！");
            }

            // 提交事务
            connection.commit();
        } catch (SQLException e) {
            throw new AppException("账户转账异常！！！");
        }
    }
}
```



# ThreadLocal

自己模拟实现一个 ThreadLocal：

```java
package zhang.shi.mao;

import java.util.HashMap;
import java.util.Map;

/**
 * Author : ZSM
 * Time :  2024/01/11
 */
public class MyThreadLocal {
    /**
     * 所有需要和当前线程绑定的数据要放到这个容器当中
     */
    private Map<Thread, Object> map = new HashMap<>();

    /**
     * 向ThreadLocal当中绑定数据
     */
    public void set(Object obj) {
        map.put(Thread.currentThread(), obj);
    }

    /**
     * 从ThreadLocal中获取数据
     * @return
     */
    public Object get() {
        return map.get(Thread.currentThread());
    }

    /**
     * 从ThreadLocal中删除数据
     */
    public void remove() {
        map.remove(Thread.currentThread());
    }
}
```

在 java.lang 包下有内置的 ThreadLocal 类，直接使用即可。

```java
private static ThreadLocal<Connection> local = new ThreadLocal<>();
```

使用 ThreadLocal 写的 DBUtil：

```java
import java.sql.*;
import java.util.ResourceBundle;

public class DBUtil {
    private static ResourceBundle bundle = ResourceBundle.getBundle("resources/jdbc");
    private static String driver = bundle.getString("driver");
    private static String url = bundle.getString("url");
    private static String user = bundle.getString("user");
    private static String password = bundle.getString("password");

    // 不让创建对象，因为工具类中的方法都是静态的。不需要创建对象。
    // 为了防止创建对象，故将构造方法私有化。
    private DBUtil(){}

    // DBUtil类加载时注册驱动
    static {
        try {
            Class.forName(driver);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    // 这个对象实际上在服务器中只有一个。
    private static ThreadLocal<Connection> local = new ThreadLocal<>();

    /**
     * 这里没有使用数据库连接池，直接创建连接对象。
     * @return 连接对象
     * @throws SQLException
     */
    public static Connection getConnection() throws SQLException {
        Connection conn = local.get();
        if (conn == null) {
            conn = DriverManager.getConnection(url, user, password);
            local.set(conn);
        }
        return conn;
    }

    /**
     * 关闭资源
     * @param conn 连接对象
     * @param stmt 数据库操作对象
     * @param rs 结果集对象
     */
    public static void close(Connection conn, Statement stmt, ResultSet rs){
        if (rs != null) {
            try {
                rs.close();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
        if (stmt != null) {
            try {
                stmt.close();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
        if (conn != null) {
            try {
                conn.close();
                // 思考一下：为什么conn关闭之后，这里要从大Map中移除呢？
                // 根本原因是：Tomcat服务器是支持线程池的。也就是说一个人用过了t1线程，t1线程还有可能被其他用户使用。
                local.remove();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
```

# 分层

不同的功能要放在不同的包下。

![image-20240111113055328](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401111130387.png)

按三层架构：

+ 表示层/表现层/Web层：web（src下的web包）、\*.jsp（应用根目录下的jsp文件）
+ 业务逻辑层：service
+ 持久化层：dao

按 MVC 架构：

+ Model：dao、pojo、service
+ View：\*.jsp（应用根目录下的jsp文件）
+ Controller：web（src下的web包）

# 设计接口

层与层之间应该是采用接口的模式。

![image-20240111114054798](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401111140829.png)

每个接口要有实现类，实现类一般放在 impl 包下，命名为 接口名Impl 。





