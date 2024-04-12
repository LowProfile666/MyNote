DispatcherServlet:

	mappedHandler.applyPostHandle(processedRequest, response, mv);

HandlerExecutionChain:
	
	void applyPostHandle(HttpServletRequest request, HttpServletResponse response, @Nullable ModelAndView mv)
			throws Exception {

		for (int i = this.interceptorList.size() - 1; i >= 0; i--) {
			HandlerInterceptor interceptor = this.interceptorList.get(i);
			interceptor.postHandle(request, response, this.handler, mv);
		}
	}

通过源码解决，可以很轻松的看到，从List集合中逆序(i--)逐一取出拦截器对象，并且调用拦截器的 postHandle方法。