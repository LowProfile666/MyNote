public class DispatcherServlet extends FrameworkServlet {

	// 前端控制器的核心方法，处理请求，返回视图，渲染视图，都是在这个方法中完成的。
	protected void doDispatch(HttpServletRequest request, HttpServletResponse response) throws Exception {

		
		// 根据请求路径调用映射的处理器方法，处理器方法执行结束之后，返回逻辑视图名称
		// 返回逻辑视图名称之后，DispatcherServlet会将 逻辑视图名称ViewName + Model，将其封装为ModelAndView对象。
		mv = ha.handle(processedRequest, response, mappedHandler.getHandler());

		// 这行代码的作用是处理视图
		processDispatchResult(processedRequest, response, mappedHandler, mv, dispatchException);
	}

	private void processDispatchResult(HttpServletRequest request, HttpServletResponse response,
			@Nullable HandlerExecutionChain mappedHandler, @Nullable ModelAndView mv,
			@Nullable Exception exception) throws Exception {
		// 渲染页面（将模板字符串转换成html代码响应到浏览器）
		render(mv, request, response);
	}

	protected void render(ModelAndView mv, HttpServletRequest request, HttpServletResponse response) throws Exception {
		// 这个方法的作用是将 逻辑视图名称 转换成 物理视图名称 ，并且最终返回视图对象View
		View view = resolveViewName(viewName, mv.getModelInternal(), locale, request);

		// 真正的将模板字符串转换成HTML代码，并且将HTML代码响应给浏览器。（真正的渲染。）
		view.render(mv.getModelInternal(), request, response);
	}

	protected View resolveViewName(String viewName, @Nullable Map<String, Object> model,
			Locale locale, HttpServletRequest request) throws Exception {
		// 其实这一行代码才是真正起作用的：将 逻辑视图名称 转换成 物理视图名称 ，并且最终返回视图对象View
		ViewResolver viewResolver;  // 底层会创建一个ThymeleafViewResolver
		// 如果使用的是Thymeleaf，那么返回的视图对象：ThymeleafView对象。
		View view = viewResolver.resolveViewName(viewName, locale); 
		return view;
	}

}


// 这是一个接口（负责视图解析的）
public interface ViewResolver { // 如果使用Thymeleaf，那么该接口的实现类就是：ThymeleafViewResolver
	// 这个方法就是将:逻辑视图名称 转换成 物理视图名称 ，并且最终返回视图对象View
	View resolveViewName(String viewName, Locale locale) throws Exception;
}

// 这是一个接口（负责将 模板字符串 转换成HTML代码，响应给浏览器）
public interface View {
	void render(@Nullable Map<String, ?> model, HttpServletRequest request, HttpServletResponse response)
			throws Exception;
}

/*
	核心类：DispatcherServlet
	核心接口1：ViewResolver（如果你使用的是Thymeleaf，那么底层会创建ThymeleafViewResolver对象）
	核心接口2：View（如果你使用的是Thymeleaf，那么底层会创建ThymeleafView对象）

	结论：如果你自己想实现属于自己的视图。你至少需要编写两个类，
		一个类实现ViewResolver接口，实现其中的resolveViewName方法。
		另一个类实现View接口，实现其中的render方法。
*/