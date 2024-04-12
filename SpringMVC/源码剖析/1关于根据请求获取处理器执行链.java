分析这一行代码：
HandlerExecutionChain mappedHandler = getHandler(request);

1. HandlerExecutionChain：处理器执行链对象

2. HandlerExecutionChain中的属性：
	public class HandlerExecutionChain{
		// 底层对应的是一个HandlerMethod对象
		// 处理器方法对象
		Object handler = new HandlerMethod(.....);
		// 该请求对应的所有的拦截器按照顺序放到了ArrayList集合中
		// 所有的拦截器对象也都是在服务器启动的时候都创建好。
		List<HandlerInterceptor> interceptorList;
	}

3. HandlerMethod 是什么？
	
	HandlerMethod是最核心的要执行的目标，翻译为：处理器方法。
	注意：HandlerMethod 是在web服务器启动时初始化spring容器的时候，就创建好了。
	这个类当中比较重要的属性包括：beanName和Method
	例如，以下代码：
		@Controller("userController")
		public class UserController{
			@RequestMapping("/login")
			public String login(User user){
				return ....
			}
		}
	那么以上代码对应了一个HandlerMethod对象：
		public class HandlerMethod{
			private String beanName = "userController";
			private Method loginMethod;
		}

4. getHandler(request);
	这个方法还是在DispatcherServlet类中。
	protected HandlerExecutionChain getHandler(HttpServletRequest request) throws Exception {
		if (this.handlerMappings != null) {
			for (HandlerMapping mapping : this.handlerMappings) {
				// 通过合适的 HandlerMapping才能获取到 HandlerExecutionChain对象。
				// 如果你处理器方法使用了 @RequestMapping注解，那么以下代码中的mapping是：RequestMappingHandlerMapping对象。
				HandlerExecutionChain handler = mapping.getHandler(request);
				if (handler != null) {
					return handler;
				}
			}
		}
		return null;
	}

	重点：
		我们处理请求的第一步代码是：HandlerExecutionChain mappedHandler = getHandler(request);
		其本质上是调用了：HandlerExecutionChain handler = mapping.getHandler(request);

	mapping变量就是 HandlerMapping。
	HandlerMapping是一个接口：
		翻译为处理器映射器，专门负责映射的。就是本质上根据请求路径去映射处理器方法的。
		HandlerMapping接口下有很多实现类：
			例如其中一个比较有名的，常用的：RequestMappingHandlerMapping
			这个 RequestMappingHandlerMapping 叫做：@RequestMapping注解专用的处理器映射器对象。

			当然，如果你没有使用 @RequestMapping注解，也可以写xml配置文件来进行映射，那个时候对应的就是其他的HandlerMapping接口的实现类了。
	
	HandlerMapping 对象也是在服务器启动阶段创建的，所有的HandlerMapping对象都是在服务器启动阶段创建，并且存放到集合中。
	public class DispatcherServlet{
		List<HandlerMapping> handlerMappings;
	}

5. RequestMappingHandlerMapping中的 getHandler(request);
	HandlerExecutionChain handler = mapping.getHandler(request);
	
	mapping.getHandler(request);这个方法底层一定是获取了 HandlerMethod 对象，将其赋值给 HandlerExecutionChain的handler属性

	public class RequestMappingHandlerMapping extends AbstractHandlerMethodMapping{
		protected void registerHandlerMethod(Object handler, Method method, RequestMappingInfo mapping) {
			super.registerHandlerMethod(handler, method, mapping);
			updateConsumesCondition(mapping, method);
		}
	}

	public class AbstractHandlerMethodMapping{
		protected void registerHandlerMethod(Object handler, Method method, T mapping) {
			this.mappingRegistry.register(mapping, handler, method);
		}

		public void register(T mapping, Object handler, Method method) {
			HandlerMethod handlerMethod = createHandlerMethod(handler, method);
		}

		protected HandlerMethod createHandlerMethod(Object handler, Method method) {
			if (handler instanceof String beanName) {
				return new HandlerMethod(beanName,
						obtainApplicationContext().getAutowireCapableBeanFactory(),
						obtainApplicationContext(),
						method);
			}
			return new HandlerMethod(handler, method);
		}
	}
	

这一步牵连到的类有哪些：
	HandlerExecutionChain
	HandlerMethod
	HandlerInterceptor
	HandlerMapping
		RequestMappingHandlerMapping（是HandlerMaping接口的实现）