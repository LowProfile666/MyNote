package com.bjpowernode.javaweb.servlet;

import jakarta.servlet.*;
import jakarta.servlet.http.*;
import java.io.*;
import java.util.*;

public class AServlet extends HttpServlet{

	public void doGet(HttpServletRequest request, HttpServletResponse response)
		throws IOException,ServletException{

		// 获取系统当前时间
		Date nowTime = new Date();

		// 向request域当中绑定数据。
		request.setAttribute("sysTime", nowTime);

		// 从request域当中取出绑定的数据。
		//Object obj = request.getAttribute("sysTime");

		// 输出到浏览器
		/*
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		out.print("request域当中获取的系统当前时间 = " + obj);
		*/

		// 通过AServlet能不能跳转到BServlet
		// 让AServlet和BServlet放到一次请求当中。
		// 可以的。使用Servlet当中请求转发机制。（下节课再说。）
	}
}