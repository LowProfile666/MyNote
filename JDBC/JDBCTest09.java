package com.zsm.jdbc;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

/**
 * Author : Mao
 * Time :  2023/10/13
 * PreparedStatement完成insert、delete、update
 */
public class JDBCTest09 {
    public static void main(String[] args) {
        Connection conn = null;
        PreparedStatement ps = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/dljdtest", "root", "2002");

//            String sql = "insert into dept (deptno, dname, loc) values (?,?,?)";
//            ps = conn.prepareStatement(sql);
//            ps.setInt(1,60);
//            ps.setString(2,"xsb");
//            ps.setString(3,"sh");
            String sql = "update dept  set dname = ?, loc = ?";
            ps = conn.prepareStatement(sql);
            ps.setString(1,"123465");
            ps.setString(2,"sdsds");

            int cnt = ps.executeUpdate();
            System.out.println(cnt);

        } catch (Exception e) {
            throw new RuntimeException(e);
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
