// 将连接数据库的所有信息配置到配置文件中
/*
	实际开发中不建议把连接数据库的信息写死到Java程序中
*/
import java.sql.*;
import java.util.*;

public class JDBCTest04 {
	public static void main(String[] args) {
		// 使用资源绑定器绑定配置文件
		ResourceBundle bundle = ResourceBundle.getBundle("jdbc");
		String driver = bundle.getString("driver");
		String url = bundle.getString("url");
		String username = bundle.getString("username");
		String password = bundle.getString("password");

		Connection conn = null;
		Statement stmt = null;
		try{
			// 1 注册驱动
			Class.forName(driver);
			
			// 2 获取连接
			conn = DriverManager.getConnection(url, username, password);
			
			// 3 创建SQL操作对象(Statement专门执行sql语句的)
			stmt = conn.createStatement();

			// 4 执行SQL语句
			String sql = "update dept set dname = 'xsb', loc = 'tj' where deptno = 20";
			int cnt = stmt.executeUpdate(sql);
			System.out.println(cnt == 1 ? "成功" : "失败");  // 成功

			// 5 处理查询结果集
		} catch(Exception e) {
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