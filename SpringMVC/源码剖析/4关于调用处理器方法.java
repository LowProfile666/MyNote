关于调用处理器方法：
	mv = ha.handle(processedRequest, response, mappedHandler.getHandler());

	ha 是处理器适配器

	mv 是ModelAndView对象

	这个方法是最核心的，调用请求路径对应的HandlerMethod。（调用处理器方法。）


ha是HandlerAdapter，如果是 @RequestMapping 注解对应的，那么就是 RequestMappingHandlerAdapter：

RequestMappingHandlerAdapter：
	protected ModelAndView handleInternal(HttpServletRequest request,
				HttpServletResponse response, HandlerMethod handlerMethod) throws Exception {
		mav = invokeHandlerMethod(request, response, handlerMethod);
	}
	protected ModelAndView invokeHandlerMethod(HttpServletRequest request,
			HttpServletResponse response, HandlerMethod handlerMethod) throws Exception {
		// 获取一个数据绑定工厂
		WebDataBinderFactory binderFactory = getDataBinderFactory(handlerMethod);
		// 获取一个可调用的处理器方法
		ServletInvocableHandlerMethod invocableMethod = createInvocableHandlerMethod(handlerMethod);
		// 给可调用的方法绑定数据
		invocableMethod.setDataBinderFactory(binderFactory);
		// 给可调用的方法设置参数
		invocableMethod.setParameterNameDiscoverer(this.parameterNameDiscoverer);
		// 可调用的方法执行了。
		invocableMethod.invokeAndHandle(webRequest, mavContainer);
	}

在HandlerAdapter中做的核心事情：
	将前端提交的form数据通过 HttpMessageConverter 将其转换成 POJO对象。（数据转换）
	并将数据绑定到 HandlerMethod 对象上。
	调用HandlerMethod。
	返回 ModelAndView

