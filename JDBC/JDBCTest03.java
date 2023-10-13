/*
	注册驱动的另一种方式
*/

/*
	JDBC编程六步
*/
import java.sql.*;


public class JDBCTest03 {
	public static void main(String[] args) {
		Connection conn = null;
		Statement stmt = null;
		try{
			// 1 注册驱动
			// 这是注册驱动的第一种方式
			// DriverManager.registerDriver(new com.mysql.cj.jdbc.Driver());
			// 第二种方式，常用，因为参数是一个字符串，字符串可以写到xxx.properties文件中
			// 以下方法不需要接受返回值，因为我们只想用它的类加载动作
			/* 
				因为 com.mysql.cj.jdbc.Driver 这个类里有一个静态代码块：
				 static {
			        try { DriverManager.registerDriver(new Driver()); } 
			        catch(SQLException E) { throw new RuntimeException("Can't register driver!"); }
				 }
				 这和我们第一种方式的操作一样，而Class.forName()会导致后面的参数类加载，但是会抛ClassNotFoundException异常
			*/
			Class.forName("com.mysql.cj.jdbc.Driver");
			// 2 获取连接
			conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/dljdtest", "root", "2002");
			
			
		} catch(SQLException e) {
			e.printStackTrace();
		} catch(ClassNotFoundException e) {
			e.printStackTrace();
		}
	}
}