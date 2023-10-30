package com.bjpowernode.servlet;

import javax.servlet.Servlet;

// 充当的角色发生了改变:webapp开发者

public class UserListServlet implements Servlet{
	public void service(){
		System.out.println("UserListServlet's service...");
	}
}