package com.zsm.jdbc;

import com.zsm.jdbc.util.DBUtil;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 * Author : Mao
 * Time :  2023/10/13
 * 测试DBUtil工具类
 * 实现模糊查询
 */
public class JDBCTest12 {
    public static void main(String[] args) {
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try {
            // 获取连接
            conn = DBUtil.getConnection();
            // 获取预编译的数据库操作对象
//            String sql = "select ename from emp where ename like '_?%'";  // ? 两边不能有 '
//            ps = conn.prepareStatement(sql);
//            ps.setString(1, "A");

            String sql = "select ename from emp where ename like ?";
            ps = conn.prepareStatement(sql);
            ps.setString(1, "_A%");
            rs = ps.executeQuery();
            while (rs.next())
                System.out.println(rs.getString("ename"));

        } catch (Exception e) {
            throw new RuntimeException(e);
        } finally {
            DBUtil.close(conn, ps, rs);
        }

    }
}
