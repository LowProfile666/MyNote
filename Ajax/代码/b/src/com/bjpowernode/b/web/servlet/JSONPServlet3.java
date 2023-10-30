package com.bjpowernode.b.web.servlet;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

@WebServlet("/jsonp3")
public class JSONPServlet3 extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        // 获取函数名
        //String callback = request.getParameter("callback");
        String callback = request.getParameter("fun");

        // 响应一段js代码，调用函数
        response.getWriter().print(callback + "({\"username\":\"lisi\"})");
    }
}
