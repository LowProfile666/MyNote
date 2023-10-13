/*
	处理查询集
*/

import java.sql.*;
import java.util.*;

public class JDBCTest05 {
	public static void main(String[] args) {
		// 使用资源绑定器绑定配置文件
		ResourceBundle bundle = ResourceBundle.getBundle("jdbc");
		String driver = bundle.getString("driver");
		String url = bundle.getString("url");
		String username = bundle.getString("username");
		String password = bundle.getString("password");

		Connection conn = null;
		Statement stmt = null;
		ResultSet rs = null;  // 结果集
		try{
			// 1 注册驱动
			Class.forName(driver);
			
			// 2 获取连接
			conn = DriverManager.getConnection(url, username, password);
			
			// 3 创建SQL操作对象(Statement专门执行sql语句的)
			stmt = conn.createStatement();

			// 4 执行SQL语句
			/*
			 * int executeUpdate（inset/update/delete）
			 * ResultSet executeQuery（select）
			 */
			String sql = "select empno a, ename, sal from emp";
			// 专门执行DQL语句的方法
			rs = stmt.executeQuery(sql);

			// 5 处理查询结果集
			// rs.next() 返回为true，表示光标指向的当前行有数据
			// getString()：不管数据库中的数据类型是什么，都以String的形式取出
			// JDBC中所有下标从1开始，不是从0开始
			while (rs.next()) {
				// getString可以使用列号来取值
				// String empno = rs.getString(1);
				// String ename = rs.getString(2);
				// String sal = rs.getString(3);

				// getString还可以使用列名来取值（推荐）
				// String empno = rs.getString("empno");
				// String ename = rs.getString("ename");
				// String sal = rs.getString("sal");

				// getString其实是使用的查询结果（可能会重命名）的列名来取值
				// String empno = rs.getString("a");
				// String ename = rs.getString("ename");
				// String sal = rs.getString("sal");

				// 除了可以以String类型取出之外，还可以以特定类型取出
				int empno = rs.getInt("a");
				String ename = rs.getString("ename");
				double sal = rs.getDouble("sal");

				System.out.println(empno + " " + ename + " " + sal);
			}
		} catch(Exception e) {
			e.printStackTrace();
		} finally {
			if (rs != null) try {
				rs.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
			if (conn != null) try {
				conn.close();
			} catch(SQLException e) {
				e.printStackTrace();
			}
			if (stmt != null) try {
				stmt.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}
}