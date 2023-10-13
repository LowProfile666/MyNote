package com.zsm.jdbc;

import com.zsm.jdbc.util.DBUtil;

import java.sql.*;

/**
 * Author : Mao
 * Time :  2023/10/13
 * 这个程序负责修改锁住的记录
 */
public class JDBCTest14 {
    public static void main(String[] args) {
        Connection conn = null;
        PreparedStatement ps = null;

        try {
            conn = DBUtil.getConnection();
            // 开启事务
            conn.setAutoCommit(false);

            String sql = "update emp set sal = sal * 1.1 where job = ?";
            ps = conn.prepareStatement(sql);
            ps.setString(1,"MAnager");
            int cnt = ps.executeUpdate();
            System.out.println(cnt);
            // 提交事务（事务结束）
            conn.commit();
        } catch (Exception e) {
            // 回顾事务（结束事务）
            if (conn != null) {
                try {
                    conn.rollback();
                } catch (SQLException ex) {
                    throw new RuntimeException(ex);
                }
            }
            throw new RuntimeException(e);
        } finally {
            DBUtil.close(conn, ps, null);
        }
    }
}
