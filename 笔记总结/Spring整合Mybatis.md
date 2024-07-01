主要问题就是将Mybatis中需要用到的一些对象交给Spring来管理。

首先是要引入spring和mybatis需要的依赖：

+ Spring需要的依赖：spring-context
+ Mybatis需要的依赖：mybatis、mysql-connector-java、druid
+ spring和mybatis集成依赖：mybatis-spring、spring-jdbc
+ 测试依赖：junit
+ 日志依赖：logback-classic

Mybatis中操作数据库的对象是SqlSession对象，所以要用Spring来管理SqlSession对象。在Mybatis中，SqlSession这个对象由SalSessionFactory对象创建，而SqlSessionFactory这个对象又是由SqlSessionFactoryBuilder对象创建。

Mybatis中获取SqlSession对象是这样的：

```java
SqlSessionFactoryBuilder sqlSessionFactoryBuilder = new SqlSessionFactoryBuilder();
SqlSessionFactory sqlSessionFactory = sqlSessionFactoryBuilder.build(Resources.getResourceAsStream("mybatis-config.xml"));
SqlSession sqlSession = sqlSessionFactory.openSession(true);
```

Mybatis中SqlSession对象操作的是SqlMapper文件，需要先获取Mapper对象，也就是dao对象，这个dao对象的类不需要自己写，只需要实现接口，然后通过SqlSession对象来创建对应的dao对象：

```java
UserMapper mapper = sqlSession.getMapper(UserMapper.class);
```

用Spring来整合Mybatis，mybatis的配置文件就可有可无了，大部分配置都被spring的配置文件代替了，之前的mybatis可能有这些配置：

```xml
<configuration>
    <!--引入外部属性文件-->
    <properties resource="jdbc.properties" />
    <!--起别名-->
    <typeAliases>
        <package name="com.zsm.bean"/>
    </typeAliases>
    <!--配置环境-->
    <environments default="dev">
        <environment id="dev">
            <!--事务管理器-->
            <transactionManager type="JDBC" />
            <!--数据源-->
            <dataSource type="POOLED">
                <property name="driver" value="${jdbc.driver}"/>
                <property name="url" value="${jdbc.url}"/>
                <property name="username" value="${jdbc.username}"/>
                <property name="password" value="${jdbc.password}"/>
            </dataSource>
        </environment>
    </environments>

    <!--注册mapper-->
    <mappers>
        <package name="com.zsm.mapper"/>
    </mappers>
</configuration>
```

在Spring中，可以通过SqlSessionFactoryBean来创建SqlSessionFactory对象，这个SqlSessionFactoryBean类在mybatis-spring依赖中。

在spring配置文件中，需要定义mybatis中的数据源、SqlSessionFactoryBean（用来创建SqlSession对象）、mapper扫描器：

```xml
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd http://www.springframework.org/schema/context https://www.springframework.org/schema/context/spring-context.xsd">

    <!--包扫描-->
    <context:component-scan base-package="com.zsm" />
    <!--引入外部属性文件，注意路径-->
    <context:property-placeholder location="classpath:jdbc.properties" />
    <!--数据源-->
    <bean id="dataSource" class="com.alibaba.druid.pool.DruidDataSource">
        <property name="driverClassName" value="${jdbc.driver}"/>
        <property name="url" value="${jdbc.url}"/>
        <property name="username" value="${jdbc.username}"/>
        <property name="password" value="${jdbc.password}"/>
    </bean>
    <!--SqlSessionFactoryBean-->
    <bean class="org.mybatis.spring.SqlSessionFactoryBean" >
        <!--起别名-->
        <property name="typeAliasesPackage" value="com.zsm.bean" />
        <!--注册数据源-->
        <property name="dataSource" ref="dataSource" />
    </bean>
    <!--包扫描器-->
    <bean class="org.mybatis.spring.mapper.MapperScannerConfigurer">
        <property name="basePackage" value="com.zsm.mapper" />
    </bean>
</beans>
```

这样就可以不需要mybatis-config配置文件了。

![image-20240627094052726](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406270940819.png)

测试程序：

```java
@Test
public void testGetUser() {
    ApplicationContext applicationContext = new ClassPathXmlApplicationContext("spring.xml");
    UserService userService = applicationContext.getBean("userService", UserService.class);
    User zsm = userService.getUser("zsm");
    System.out.println(zsm);
}
```

