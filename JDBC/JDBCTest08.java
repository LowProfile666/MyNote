package com.zsm.jdbc;

import java.sql.*;
import java.util.Scanner;

/**
 * Author : Mao
 * Time :  2023/10/13
 */
public class JDBCTest08 {
    public static void main(String[] args) {
        // 用户输入desc表示降序，asc表示升序
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入：");
        String key = sc.nextLine();

        /*
        // JDBC
        // Exception in thread "main" java.lang.RuntimeException: java.sql.SQLSyntaxErrorException: You have an error in your SQL syntax;
        // check the manual that corresponds to your MySQL server version for the right syntax to use near ''desc'' at line 1
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet res = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/dljdtest", "root", "2002");
            String sql = "select ename from emp orderby ?";
            ps = conn.prepareStatement(sql);
            ps.setString(1, key);
            res = ps.executeQuery();
            while (res.next())
                System.out.println(res.getString("ename"));
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
        */
        Connection conn = null;
        Statement stmt = null;
        ResultSet res = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/dljdtest", "root", "2002");
            stmt = conn.createStatement();
            String sql = "select ename from emp order by ename " + key;
            res = stmt.executeQuery(sql);
            while (res.next())
                System.out.println(res.getString("ename"));
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
    }
}
