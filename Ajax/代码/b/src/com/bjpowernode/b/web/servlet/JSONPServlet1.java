package com.bjpowernode.b.web.servlet;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/jsonp1")
public class JSONPServlet1 extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        // 在后台输出
        //System.out.println("jsonp方式完成跨域访问");

        // 向前端响应一段js代码呢？
        PrintWriter out = response.getWriter();
        //out.print("alert(123)"); // 这是响应一段js代码，只不过这个alert函数是JS内置的函数，可以直接用。
        // 注意：不要误以为是后端java代码调用了sayHello()函数，实际上后端只负责响应一个字符串回去。
        // 真正的调用者，还是浏览器，浏览器接收到这个字符串之后，会自动将这个字符串当做一段js代码解释执行。
        //out.print("sayHello()"); // 这也是响应一段JS代码。只不过这个sayHello函数是程序员自定义的。

        //响应一段js代码，然后传一个json数据给前端
        //out.print("sayHello({\"name\" : \"jackson\"})");

        // 动态获取函数名
        String fun = request.getParameter("fun");
        //out.print(fun + "({\"name\" : \"jackson\"})");
        out.print(fun + "()");

    }
}
