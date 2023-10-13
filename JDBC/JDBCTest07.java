package com.zsm.jdbc;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

/**
 * Author : Mao
 * Time :  2023/10/13
 * 解决SQL注入问题
 *      只要用户提供的信息不参与sql语句的编译过程，问题就解决了
 *      要想用户信息不参与sql语句的编译，那么必须使用java.sql.PreparedStatement
 *      PreparedStatement接口继承了java.sql.Statement
 *      PreparedStatement是属于预编译的数据库操作对象
 *      PreparedStatement的原理是：预先对SQL语句的框架进行编译，然后再给SQL语句进行传值
 * 对比一下：Statement 和 PreparedStatement
 *      Statement存在sql注入问题，PreparedStatement解决了sql注入问题
 *      Statement是编译一次执行一次，PreparedStatement是编译一次，执行N次，效率更高
 *      PreparedStatement会在编译阶段做类型的安全检查
 * 综上：PreparedStatement使用较多，只有极少的情况下采用Statement
 * 什么情况下用Statement？
 *      业务方面要求必须支持SQL注入的时候。
 */
public class JDBCTest07 {
    public static void main(String[] args) {
        // 初始化一个界面
        Map<String, String> userLoginInfo = initUI();
        // 验证用户名和密码
        boolean loginSuccess = login(userLoginInfo);
        // 最后输出结果
        System.out.println(loginSuccess ? "成功" : "失败");
    }

    /**
     * 用户登录
     * @param userLoginInfo 用户登录信息
     * @return true表示成功，false表示失败
     */
    private static boolean login(Map<String, String> userLoginInfo) {
        String username = userLoginInfo.get("username");
        String password = userLoginInfo.get("password");
        // JDBC
        Connection conn = null;
        PreparedStatement ps = null;  // 这里使用PreparedStatement，预编译的数据库对象
        ResultSet res = null;
        try {
            // 1.注册驱动
            Class.forName("com.mysql.cj.jdbc.Driver");
            // 2.获取连接
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/dljdtest", "root", "2002");
            // 3.创建预编译的sql对象
            // SQL语句的框架，其中一个？表示一个占位符，一个？将来表示一个值，注意：占位符不能用单引号括起来
            String sql = "select * from t_user where loginName = ? and loginPwd = ?";
            // 程序执行到此处，会发送sql语句框子给DBMS，然后DBMS进行sql语句的预先编译
            ps = conn.prepareStatement(sql);
            // 在这里给占位符赋值（第一个？下标是 1，第二个？下标是 2，JDBC中的所有下标从1开始）
            ps.setString(1,username);
            ps.setString(2,password);
            // 4.执行sql语句
            res = ps.executeQuery();
            // 5.处理查询结果集
            if (res.next())   return true;
        } catch (Exception e) {
            throw new RuntimeException(e);
        } finally {
            if (res != null) {
                try {
                    res.close();
                } catch (SQLException e) {
                    throw new RuntimeException(e);
                }
            }
            if (ps != null) {
                try {
                    ps.close();
                } catch (SQLException e) {
                    throw new RuntimeException(e);
                }
            }
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException e) {
                    throw new RuntimeException(e);
                }
            }
        }
        return false;
    }

    /**
     * 初始化用户界面
     * @return 用户输入的用户名和密码
     */
    private static Map<String, String> initUI() {
        Scanner sc = new Scanner(System.in);
        System.out.println("用户名：");
        String username = sc.nextLine();
        System.out.println("密码：");
        String password = sc.nextLine();
        Map<String, String> res = new HashMap<>();
        res.put("username", username);
        res.put("password", password);
        return res;
    }
}
