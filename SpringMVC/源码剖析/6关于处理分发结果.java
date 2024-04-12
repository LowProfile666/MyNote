
public class DispatcherServlet{

	// 处理分发结果
	processDispatchResult(processedRequest, response, mappedHandler, mv, dispatchException);

	private void processDispatchResult(HttpServletRequest request, HttpServletResponse response,
			@Nullable HandlerExecutionChain mappedHandler, @Nullable ModelAndView mv,
			@Nullable Exception exception) throws Exception {
		// 渲染
		render(mv, request, response);
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