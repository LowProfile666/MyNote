package com.zsm.jdbc;

import com.zsm.jdbc.util.DBUtil;

import java.sql.*;

/**
 * Author : Mao
 * Time :  2023/10/13
 * 这个程序开启一个事务，这个事务专门进行查询，并且使用行级锁/悲观锁，锁住相关记录。
 */
public class JDBCTest13 {
    public static void main(String[] args) {
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;

        try {
            conn = DBUtil.getConnection();
            // 开启事务
            conn.setAutoCommit(false);

            String sql = "select ename, job, sal from emp where job = ? for update";
            ps = conn.prepareStatement(sql);
            ps.setString(1,"MAnager");
            rs = ps.executeQuery();
            while (rs.next())
                System.out.println(rs.getString("ename") + " " + rs.getString("job") + " " + rs.getString("sal"));

            // 提交事务（事务结束）
            conn.commit();  // 在这一行上打上断点，进行调试，然后运行JDBCTest14，JDBCTest14会一直等这边提交
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
            DBUtil.close(conn, ps, rs);
        }
    }
}
