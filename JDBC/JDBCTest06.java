package com.zsm.jdbc;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;


/**
 * Author : Mao
 * Time :  2023/10/13
 */
/*
实现功能：
    模拟用户登录的功能
    描述：程序运行的时候，提供一个输入的入口，可以让用户输入用户名和密码
        用户输入后，提交信息，Java程序收集到用户信息，连接数据库验证信息是否合法，
        合法：显示成功
        非法：显示失败
    准备：
        在实际开发中，表的设计会使用专业的建模工具，PowerDesigner

    当前程序存在问题：
        用户名：123
        密码：123' or '1'='1
        这种现象被称为SQL注入（安全隐患）
    导致SQL注入的原因：
        用户输入的信息中含有sql语句的关键字，并且这些关键字参与sql语句的编译过程
        导致sql语句的愿意被扭曲，进而达到sql注入
 */
public class JDBCTest06 {
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
        Statement stmt = null;
        ResultSet res = null;
        try {
            // 1.注册驱动
            Class.forName("com.mysql.cj.jdbc.Driver");
            // 2.获取连接
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/dljdtest", "root", "2002");
            // 3.创建sql对象
            stmt = conn.createStatement();
            // 4.执行sql语句
            String sql = "select * from t_user where loginName = '" + username + "' and loginPwd = '" + password + "'";
            // 以上正好完成了sql语句的拼接，，正好将用户提供的非法信息编译进去，导致了原sql语句的含义被扭曲了
            res = stmt.executeQuery(sql);
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
