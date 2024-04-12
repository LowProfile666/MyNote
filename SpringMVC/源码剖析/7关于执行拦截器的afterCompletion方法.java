DispatcherServlet:

	private void processDispatchResult(HttpServletRequest request, HttpServletResponse response,
			@Nullable HandlerExecutionChain mappedHandler, @Nullable ModelAndView mv,
			@Nullable Exception exception) throws Exception {
		// 渲染
		render(mv, request, response);
		// 执行该请求所对应的所有拦截器的afterCompletion方法
		mappedHandler.triggerAfterCompletion(request, response, null);
	}

HandlerExecutionChain:
	
	void triggerAfterCompletion(HttpServletRequest request, HttpServletResponse response, @Nullable Exception ex) {
		for (int i = this.interceptorIndex; i >= 0; i--) {
			HandlerInterceptor interceptor = this.interceptorList.get(i);
			try {
				interceptor.afterCompletion(request, response, this.handler, ex);
			}
			catch (Throwable ex2) {
				logger.error("HandlerInterceptor.afterCompletion threw exception", ex2);
			}
		}
	}

	通过源码可以看出，也是通过逆序(i--)的方式进行拦截器的调用，调用拦截器的afterCompletion方法。