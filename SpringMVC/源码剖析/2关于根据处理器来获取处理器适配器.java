分析：
HandlerAdapter ha = getHandlerAdapter(mappedHandler.getHandler());

1. 底层使用了适配器模式。

2. 每一个处理器(我们自己写的Controller)，都有自己适合的处理器适配器。

3. 在SpringMVC当中处理器适配器也有很多种，其中一个比较有名的，常用的处理器适配器是：RequestMappingHandlerAdapter
这个处理器适配器是专门处理 “处理器方法”上有 @RequestMapping 注解的。

4. mappedHandler.getHandler() 获取的是 HandlerMethod 对象

5. HandlerAdapter也是一个接口：
	其中有一个常用的实现类：RequestMappingHandlerAdapter

6. 在服务器启动阶段，所有的 HandlerAdapter接口的实现类都会创建出来。在服务器启动阶段！！！！！！
	List<HandlerAdapter> handlerAdapters;

7. HandlerAdapter接口非常重要，通过这个接口来调用最终的 HandlerMethod。

8. HandlerAdapter是适配器，是对 HandlerMethod 进行的适配。

9. 在DispatcherServlet类中，如下代码：
	protected HandlerAdapter getHandlerAdapter(Object handler) throws ServletException {
		if (this.handlerAdapters != null) {
			for (HandlerAdapter adapter : this.handlerAdapters) {
				if (adapter.supports(handler)) {
					return adapter;
				}
			}
		}
	}