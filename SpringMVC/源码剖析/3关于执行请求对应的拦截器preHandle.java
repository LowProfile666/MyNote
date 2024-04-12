关于执行请求对应的拦截器的preHandle方法

DispatcherServlet:
if (!mappedHandler.applyPreHandle(processedRequest, response)) {
	return;
}


HandlerExecutionChain：
boolean applyPreHandle(HttpServletRequest request, HttpServletResponse response) throws Exception {
	for (int i = 0; i < this.interceptorList.size(); i++) {
		HandlerInterceptor interceptor = this.interceptorList.get(i);
		if (!interceptor.preHandle(request, response, this.handler)) {
			triggerAfterCompletion(request, response, null);
			return false;
		}
		this.interceptorIndex = i;
	}
	return true;
}

遍历List集合，从List集合中取出每一个 HandlerInterceptor对象，调用 preHandle，i++，可见是顺序调用。