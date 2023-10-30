package com.bjpowernode.javaweb.servlet;

import jakarta.servlet.*;
import jakarta.servlet.http.*;
import java.io.*;
import java.util.*;

public class BServlet extends HttpServlet{

	public void doGet(HttpServletRequest request, HttpServletResponse response)
		throws IOException,ServletException{

		// 从request域当中取出绑定的数据。
		Object obj = request.getAttribute("sysTime");

		// 输出到浏览器
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		out.print("request域当中获取的系统当前时间 = " + obj);
	}
}