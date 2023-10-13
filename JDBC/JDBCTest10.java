package com.zsm.jdbc;

import javax.sound.midi.Soundbank;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

/**
 * Author : Mao
 * Time :  2023/10/13
 * JDBC的事务机制
 *      JDBC中的事务是自动提交的：只要执行任意一条DML语句，则自动提交一次，这是JDBC默认的
 *      重点三行代码
 *          conn.setAutoCommit(false);  // 关闭自动提交机制，开启事务
 *          conn.commit();  // 手动提交事务
 *          conn.rollback();  // 回滚事务
 */
public class JDBCTest10 {
    public static void main(String[] args) {
        Connection conn = null;
        PreparedStatement ps = null;

        try {
            // 1.注册驱动
            Class.forName("com.mysql.cj.jdbc.Driver");
            // 2.获取连接
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/dljdtest", "root", "2002");
            // 将自动提交机制改为手动提交
            conn.setAutoCommit(false);  // 开启事务

            // 3.获取数据库操作对象
            String sql = "update t_act set balance = ? where actno = ?";
            ps = conn.prepareStatement(sql);
            ps.setInt(2, 111);
            ps.setDouble(1, 10000);

            int cnt = ps.executeUpdate();

            ps.setInt(2, 222);
            ps.setDouble(1, 10000);
            cnt += ps.executeUpdate();

            System.out.println(cnt == 2 ? "成功" : "失败");

            // 程序能够走到这里说明以上程序没有异常，事务结束，手动提交
            conn.commit();

        } catch (Exception e) {
            // 回滚事务
            if (conn != null) {
                try {
                    conn.rollback();
                } catch (SQLException ex) {
                    throw new RuntimeException(ex);
                }
            }
            e.printStackTrace();
        } finally {
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

    }
}
