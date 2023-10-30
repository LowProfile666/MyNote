package com.bjpowernode.javaweb.servlet;

import jakarta.servlet.*;
import jakarta.servlet.http.*;
import java.io.*;
import java.util.*;

/*
username=zhangsan&userpwd=123&interest=s&interest=d
Map<String,String[]>
key				value
---------------------------
"username"		{"zhangsan"}
"userpwd"		{"123"}
"interest"		{"s", "d"}

总结一下：request接口中四个非常重要的方法。
	Map<String,String[]> parameterMap = request.getParameterMap();
	Enumeration<String> names = request.getParameterNames();
	String[] values = request.getParameterValues("name");
	String value = request.getParameter("name");


*/
public class RequestTestServlet extends HttpServlet{

	public void doPost(HttpServletRequest request, HttpServletResponse response)
		throws IOException,ServletException{
		// 面向接口编程:HttpServletRequest接口。
		// 获取前端提交的数据
		// 前端会提交什么数据呢？
		// username=zhangsan&userpwd=123&interest=s&interest=d
		// 以上的数据会被小猫咪封装到request对象中。

		// 获取参数Map集合
		Map<String,String[]> parameterMap = request.getParameterMap();
		// 遍历Map集合(获取Map集合中所有的key，遍历)
		Set<String> keys = parameterMap.keySet();
		Iterator<String> it = keys.iterator();
		while(it.hasNext()){
			String key = it.next();
			//System.out.println(key);
			// 通过key获取value
			String[] values = parameterMap.get(key);
			/*
				username=[Ljava.lang.String;@7cce40b4
				userpwd=[Ljava.lang.String;@7453f0b9
				interest=[Ljava.lang.String;@4063ebb5
			*/
			//System.out.println(key + "=" + values);

			// 遍历一维数组
			System.out.print(key + "=");

			for(String value : values){
				System.out.print(value + ",");
			}
			// 换行
			System.out.println();
		}

		// 直接通过getParameterNames()这个方法，可以直接获取这个Map集合的所有key
		Enumeration<String> names = request.getParameterNames();
		while(names.hasMoreElements()){
			String name = names.nextElement();
			System.out.println(name);
		}

		// 直接通过name获取value这个一维数组。
		String[] usernames = request.getParameterValues("username");
		String[] userpwds = request.getParameterValues("userpwd");
		String[] interests = request.getParameterValues("interest");

		// 遍历一维数组
		for(String username : usernames){
			System.out.println(username);
		}

		for(String userpwd : userpwds){
			System.out.println(userpwd);
		}

		for(String interest : interests){
			System.out.println(interest);
		}

		// 通过name获取value这个一维数组的第一个元素
		// 这个方法使用最多，因为这个一维数组中一般只有一个元素。
		String username = request.getParameter("username");
		String userpwd = request.getParameter("userpwd");
		//String interest = request.getParameter("interest");

		// 既然是checkbox，调用方法：request.getParameterValues("interest")
		String[] interests2 = request.getParameterValues("interest");

		// 获取的都是一维数组当中的第一个元素。
		System.out.println(username);
		System.out.println(userpwd);
		//System.out.println(interest);

		for(String interest : interests2){
			System.out.println(interest);
		}


	}
}