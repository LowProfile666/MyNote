package com.zsm.servlet;

import javax.servlet.Servlet;

// 充当的角色发生了改变:webapp开发者
// 只要是我们webapp开发者写的XXXServlet都要实现Servlet接口
public class BankServlet implements Servlet{
	public void service(){
		System.out.println("BankServlet's service...");
	}
}