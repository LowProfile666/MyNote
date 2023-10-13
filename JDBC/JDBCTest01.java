/*
	JDBC编程六步
*/
import java.sql.Driver;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Connection;
import java.sql.Statement;

public class JDBCTest01 {
	public static void main(String[] args) {
		Connection conn = null;
		Statement stmt = null;
		try{
			// 1 注册驱动
			// java.sql.Driver driver = new com.mysql.jdbc.Driver();
			// Driver driver = new com.mysql.jdbc.Driver();  // mysql8.1.0已过时
			Driver driver = new com.mysql.cj.jdbc.Driver();
			DriverManager.registerDriver(driver);
			/*
			mysql8.1.0:
			使用Driver driver = new com.mysql.jdbc.Driver(); 会提示：
				Loading class `com.mysql.jdbc.Driver'. This is deprecated. The new driver class is `com.mysql.cj.jdbc.Driver'. 
				The driver is automatically registered via the SPI and manual loading of the driver class is generally unnecessary.
			*/

			// 2 获取连接

			String url = "jdbc:mysql://127.0.0.1:3306/dljdtest";  // url格式：jdbc:mysql://ip:port/database
			String username = "root";
			String password = "2002";
			conn = DriverManager.getConnection(url, username, password);
			/*
				url : 同一资源定位符（网络中某个资源的绝对路径）
				包括：协议、IP、Port、资源名

				jdbc:mysql://127.0.0.1:3306/dljdtest：
					jdbc:mysql：协议
					127.0.0.1：IP地址
					3306：MySQL数据库端口号
					dljdtest：具体的数据库实例名

				什么是通信协议？
					通信协议是通信之前就提前定好的数据传送格式。
					数据包具体怎么传数据，格式提前定好的。

			*/

			// 3 创建SQL操作对象(Statement专门执行sql语句的)
			stmt = conn.createStatement();

			// 4 执行SQL语句
			String sql = "insert into dept (deptno,dname,loc) values (51,'人部', '北京')";
			// 专门执行DML语句的（insert、update、delete）
			// 返回值是“影响数据库中的记录条数”
			int cnt = stmt.executeUpdate(sql);
			System.out.println(cnt == 1 ? "成功" : "失败");  // 成功

			System.out.println("数据库连接对象 = " + conn);  // 数据库连接对象 = com.mysql.cj.jdbc.ConnectionImpl@79079097

			// 5 处理查询结果集
		} catch(SQLException e) {
			e.printStackTrace();
		} finally {
			// 6 释放连接
			// 为了保证资源一定释放，在finally语句块中释放资源
			// 并且要遵循从小到大依次关闭
			// 分别对其 try catch
			try {
				if (stmt != null)	stmt.close();
			} catch(SQLException e) {
				e.printStackTrace();
			}
			try {
				if (conn != null)	conn.close();
			} catch(SQLException e) {
				e.printStackTrace();
			}
		}
	}
}