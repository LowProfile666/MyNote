/*
	JDBC编程六步
*/
import java.sql.Driver;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Connection;
import java.sql.Statement;

public class JDBCTest02 {
	public static void main(String[] args) {
		Connection conn = null;
		Statement stmt = null;
		try{
			// 1 注册驱动
			DriverManager.registerDriver(new com.mysql.cj.jdbc.Driver());
			
			// 2 获取连接
			conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/dljdtest", "root", "2002");
			
			// 3 创建SQL操作对象(Statement专门执行sql语句的)
			stmt = conn.createStatement();

			// 4 执行SQL语句
			// JDBC中的sql语句不需要写分号
			// String sql = "delete from dept where deptno = 40";
			String sql = "update dept set dname = 'xsb', loc = 'tj' where deptno = 20";
			int cnt = stmt.executeUpdate(sql);
			System.out.println(cnt == 1 ? "成功" : "失败");  // 成功

			// 5 处理查询结果集
		} catch(SQLException e) {
			e.printStackTrace();
		} finally {
			if (conn != null) try {
				conn.close();
			} catch(SQLException e) {
				e.printStackTrace();
			}
			if (stmt != null) try {
				stmt.close();
			} catch(SQLException e) {
				e.printStackTrace();
			}
		}
	}
}