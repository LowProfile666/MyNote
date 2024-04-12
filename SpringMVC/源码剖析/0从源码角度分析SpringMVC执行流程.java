// 前端控制器，SpringMVC最核心的类
public class DispatcherServlet extends FrameworkServlet {
	// 前端控制器最核心的方法，这个方法是负责处理请求的，一次请求，调用一次 doDispatch 方法。
	protected void doDispatch(HttpServletRequest request, HttpServletResponse response) throws Exception {
		// 通过请求获取处理器
		// 请求：http://localhost:8080/springmvc/hello （有URI）
		// 根据请求路径来获取对应的要执行的处理器
		// 实际上返回的是一个处理器执行链对象
		// 这个执行链(链条)把谁串起来了呢？把这一次请求要执行的所有拦截器和处理器串起来了。
		// HandlerExecutionChain是一次请求对应一个对象
		HandlerExecutionChain mappedHandler = getHandler(request);
		
		// 根据处理器获取处理器适配器对象
		HandlerAdapter ha = getHandlerAdapter(mappedHandler.getHandler()); // Handler就是我们写的Controller

		// 执行该请求对应的所有拦截器中的 preHandle 方法
		if (!mappedHandler.applyPreHandle(processedRequest, response)) {
			return;
		}

		// 调用处理器方法，返回ModelAndView对象
		// 在这里进行的数据绑定，实际上调用处理器方法之前要给处理器方法传参
		// 需要传参的话，这个参数实际上是要经过一个复杂的数据绑定过程（将前端提交的表单数据转换成POJO对象）
		mv = ha.handle(processedRequest, response, mappedHandler.getHandler());

		// 执行该请求对应的所有拦截器中的 postHandle 方法
		mappedHandler.applyPostHandle(processedRequest, response, mv);

		// 处理分发结果（本质上就是响应结果到浏览器）
		processDispatchResult(processedRequest, response, mappedHandler, mv, dispatchException);
	}

	private void processDispatchResult(HttpServletRequest request, HttpServletResponse response,
			@Nullable HandlerExecutionChain mappedHandler, @Nullable ModelAndView mv,
			@Nullable Exception exception) throws Exception {
		// 渲染
		render(mv, request, response);
		// 执行该请求所对应的所有拦截器的afterCompletion方法
		mappedHandler.triggerAfterCompletion(request, response, null);
	}

	protected void render(ModelAndView mv, HttpServletRequest request, HttpServletResponse response) throws Exception {
		// 通过视图解析器进行解析，返回视图View对象
		View view = resolveViewName(viewName, mv.getModelInternal(), locale, request);
		// 调用视图对象的渲染方法（完成响应）
		view.render(mv.getModelInternal(), request, response);
	}

	protected View resolveViewName(String viewName, @Nullable Map<String, Object> model,
			Locale locale, HttpServletRequest request) throws Exception {
		// 视图解析器
		ViewResolver viewResolver;
		// 通过视图解析器解析返回视图对象View
		View view = viewResolver.resolveViewName(viewName, locale);
	}
}


// 视图解析器接口
public interface ViewResolver {
	View resolveViewName(String viewName, Locale locale) throws Exception;
}

// 视图解析器接口实现类也很多：ThymeleafViewResolver、InternalResourceViewResolver

// 视图接口
public interface View{
	void render(@Nullable Map<String, ?> model, HttpServletRequest request, HttpServletResponse response)
			throws Exception;
}

// 每一个接口肯定是有接口下的实现类，例如View接口的实现类：ThymeleafView、InternalResourceView....



