package com.bjpowernode.javaweb.servlet;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

@WebServlet("/proxy")
public class ProxyServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // 通过httpclient组件，发送HTTP GET请求，访问 TargetServlet
        HttpGet httpGet = new HttpGet("http://localhost:8081/b/target");
        httpGet.setHeader("Content-Type", "application/x-www-form-urlencoded");
        CloseableHttpClient httpClient = HttpClients.createDefault();
        HttpResponse resp = httpClient.execute(httpGet);
        HttpEntity entity = resp.getEntity();
        BufferedReader reader = new BufferedReader(new InputStreamReader(entity.getContent(), "UTF-8"));
        String line = null;
        StringBuffer responseSB = new StringBuffer();
        while ((line = reader.readLine()) != null) {
            responseSB.append(line);
        }
        reader.close();
        httpClient.close();
        // b站点响应回来的数据
        response.getWriter().print(responseSB);
    }
}
