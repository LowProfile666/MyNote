package com.zsm.servlet;

import jakarta.servlet.Servlet;
import jakarta.servlet.ServletException;
import jakarta.servlet.ServletRequest;
import jakarta.servlet.ServletResponse;
import jakarta.servlet.ServletConfig;
import java.io.IOException;
import java.io.PrintWriter;


public class HelloServlet implements Servlet{

	// 5个方法
	public void init(ServletConfig config) throws ServletException{
	
	}

	public void service(ServletRequest request,ServletResponse response)
		throws ServletException , IOException{

		// 向控制台打印输出
		System.out.println("My First Servlet, Hello Servlet");

		// 设置响应的内容类型是普通文本或html代码
		// 需要在获取流对象之前设置，有效。
		// 如果中文乱码，可以在后面加上一句："text/html;charset=UTF-8"
		response.setContentType("text/html");

		// 怎么将一个信息直接输出到浏览器上？
		// 需要使用ServletResponse接口：response
		// response表示响应：从服务器向浏览器发送数据叫做响应。
		PrintWriter out = response.getWriter();
		
		// 设置响应的内容类型时不要在获取流之后设置。
		//response.setContentType("text/html");

		out.print("Hello Servlet, You are my first servlet!");

		// 浏览器是能够识别html代码的，那我们是不是应该输出一段HTML代码呢？
		out.print("<h1>hello servlet，你好Servlet</h1>");

		// 这是一个输出流，负责输出字符串到浏览器
		// 这个输出流不需要我们刷新，也不需要我们关闭，这些都由Tomcat来维护。
		/*
		out.flush();
		out.close();
		*/
	}

	public void destroy(){
	
	}

	public String getServletInfo(){
		return "";
	}

	public ServletConfig getServletConfig(){
		return null;
	}
}