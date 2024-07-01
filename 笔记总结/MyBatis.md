# 使用

## 1 引入依赖

1、在pom.xml文件中引入mybatis的依赖和mysql的依赖：

```xml
<!--mybatis核心依赖-->
<dependency>
  <groupId>org.mybatis</groupId>
  <artifactId>mybatis</artifactId>
  <version>3.5.10</version>
</dependency>
<!--mysql驱动依赖-->
<dependency>
  <groupId>mysql</groupId>
  <artifactId>mysql-connector-java</artifactId>
  <version>8.0.30</version>
</dependency>
```

## 2 创建配置文件

2、在resources目录下创建mybatis的配置文件mybatis-config.xml：

+ 放到resources目录下的文件相当于放到了类的根目录下。

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration
        PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
    <environments default="development">
        <environment id="development">
            <transactionManager type="JDBC"/>
            <dataSource type="POOLED">
                <property name="driver" value="com.mysql.cj.jdbc.Driver"/>
                <property name="url" value="jdbc:mysql://localhost:3306/powernode"/>
                <property name="username" value="root"/>
                <property name="password" value="root"/>
            </dataSource>
        </environment>
    </environments>
    <mappers>
        <!--sql映射文件创建好之后，需要将该文件路径配置到这里-->
        <mapper resource=""/>
    </mappers>
</configuration>
```

+ 注意1：mybatis核心配置文件的文件名不一定是mybatis-config.xml，可以是其它名字。
+ 注意2：mybatis核心配置文件存放的位置也可以随意。

3、在resources目录下创建mapper的配置文件，比如CarMapper.xml：

+ 在这个配置文件中编写SQL语句

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<!--namespace先随意写一个-->
<mapper namespace="car">
    <!--insert sql：保存一个汽车信息-->
    <insert id="insertCar">
        insert into t_car
            (id,car_num,brand,guide_price,produce_time,car_type) 
        values
            (null,'102','丰田mirai',40.30,'2014-10-05','氢能源')
    </insert>
</mapper>
```

+ 注意1：sql语句最后结尾可以不写“;”

+ 注意2：CarMapper.xml文件的名字不是固定的。可以使用其它名字。

+ 注意3：CarMapper.xml文件的位置也是随意的。

4、将创建的mapper配置文件配置到mybatis核心配置文件中：

```xml
<mappers>
    <!--sql映射文件创建好之后，需要将该文件路径配置到这里-->
    <mapper resource="CarMapper.xml"/>
</mappers>
```

+ 使用resource属性，这种方式是从类路径当中加载资源

## 3 编写代码

5、编写代码

mybatis中执行sql语句的对象是SqlSession对象，SqlSession对象通过SqlSessionFactory对象来获得，SqlSessionFactory对象通过SqlSessionFactoryBuilder对象的build方法创建。

所以获取一个执行sql语句的SqlSession对象：

```java
// 1. 创建SqlSessionFactoryBuilder对象
SqlSessionFactoryBuilder sqlSessionFactoryBuilder = new SqlSessionFactoryBuilder();
// 2. 创建SqlSessionFactory对象
InputStream is = Thread.currentThread().getContextClassLoader().getResourceAsStream("mybatis-config.xml");
SqlSessionFactory sqlSessionFactory = sqlSessionFactoryBuilder.build(is);
// 3. 创建SqlSession对象
SqlSession sqlSession = sqlSessionFactory.openSession();
```

+ 在创建SqlSessionFactory对象时，需要一个输入流，这个输入流指向mybatis的核心配置文件mybatis-config.xml

+ 而mybatis核心配置文件的名字就是在这里使用，所以可以随意命名；位置也是可以随意，只要这个输入流能找到。

+ mabatis有一个Resources类，提供了一个方法，从类路径当中获取资源：

  ```java
  InputStream is = Resources.getResourceAsStream("mybatis-config.xml");
  ```

通过这个SqlSession对象执行sql语句：

```java
sqlSession.insert("insertCar");
sqlSession.commit();
sqlSession.close();
```

+ 执行了一句插入语句， 这个"insertCar"必须是sql语句的id，这个sql语句是写在CarMapper.xml中的
+ mybatis默认采用的事务管理器是JDBC，默认是不提交的，需要手动提交。

# 事务

 mbatis中的事务是需要自己手动提交的：

```java
sqlSession.commit();
```

在 mybatis 中，提供了两种事务管理机制：

第一种：JDBC事务管理器：

mybatis 框架自己管理事务，自己采用原生的 JDBC 代码去管理事务：

+ `conn.setAutoCommit(false)`，开启事务
+ `conn.commit()`：提交事务

第二种：MANAGED事务管理器：

mybatis 不再负责事务的管理了，事务管理交给其他容器来负责，例如：Spring。

在 mybatis-config.xml 文件中，可以通过以下的配置来进行 mybatis 的事务管理：

```xml
<transactionManager type="JDBC"/>
```

+ type 属性的值有两个（不区分大小写）：
  + JDBC（jdbc）
  + MANAGED（managed）

# 使用JUnit

JUnit是专门做单元测试的组件。

1、引入依赖：

```xml
<!-- junit依赖 -->
<dependency>
    <groupId>junit</groupId>
    <artifactId>junit</artifactId>
    <version>4.13.2</version>
    <scope>test</scope>
</dependency>
```

2、编写单元测试类【测试用例】：

```java
// 测试用例
public class CarMapperTest{
    // 测试方法
    @Test
    public void testInsert(){}
    @Test
    public void testUpdate(){}
}
```

+ 测试用例中每一个测试方法上使用`@Test`注解进行标注。	

测试用例的名字以及每个测试方法的定义都是有规范的：

- 测试用例的名字：`XxxTest`

- 测试方法声明格式：`public void test业务方法名(){}`

注意：测试方法没有参数列表，没有返回值。

# 使用logback

logback是一个日志框架。

1、引入依赖：

```xml
<dependency>
  <groupId>ch.qos.logback</groupId>
  <artifactId>logback-classic</artifactId>
  <version>1.2.11</version>
  <scope>test</scope>
</dependency>
```

2、创建logback配置文件：

+ 文件名必须叫做`logback.xml`或`logback-test.xml`，必须放到类路径当中

```xml
<?xml version="1.0" encoding="UTF-8"?>

<configuration debug="false">
    <!-- 控制台输出 -->
    <appender name="STDOUT" class="ch.qos.logback.core.ConsoleAppender">
        <encoder class="ch.qos.logback.classic.encoder.PatternLayoutEncoder">
            <!--格式化输出：%d表示日期，%thread表示线程名，%-5level：级别从左显示5个字符宽度%msg：日志消息，%n是换行符-->
            <pattern>%d{yyyy-MM-dd HH:mm:ss.SSS} [%thread] %-5level %logger{50} - %msg%n</pattern>
        </encoder>
    </appender>
    <!-- 按照每天生成日志文件 -->
    <appender name="FILE" class="ch.qos.logback.core.rolling.RollingFileAppender">
        <rollingPolicy class="ch.qos.logback.core.rolling.TimeBasedRollingPolicy">
            <!--日志文件输出的文件名-->
            <FileNamePattern>${LOG_HOME}/TestWeb.log.%d{yyyy-MM-dd}.log</FileNamePattern>
            <!--日志文件保留天数-->
            <MaxHistory>30</MaxHistory>
        </rollingPolicy>
        <encoder class="ch.qos.logback.classic.encoder.PatternLayoutEncoder">
            <!--格式化输出：%d表示日期，%thread表示线程名，%-5level：级别从左显示5个字符宽度%msg：日志消息，%n是换行符-->
            <pattern>%d{yyyy-MM-dd HH:mm:ss.SSS} [%thread] %-5level %logger{50} - %msg%n</pattern>
        </encoder>
        <!--日志文件最大的大小-->
        <triggeringPolicy class="ch.qos.logback.core.rolling.SizeBasedTriggeringPolicy">
            <MaxFileSize>100MB</MaxFileSize>
        </triggeringPolicy>
    </appender>

    <!--mybatis log configure-->
    <logger name="com.apache.ibatis" level="TRACE"/>
    <logger name="java.sql.Connection" level="DEBUG"/>
    <logger name="java.sql.Statement" level="DEBUG"/>
    <logger name="java.sql.PreparedStatement" level="DEBUG"/>

    <!-- 日志输出级别,logback日志级别包括五个：TRACE < DEBUG < INFO < WARN < ERROR -->
    <root level="DEBUG">
        <appender-ref ref="STDOUT"/>
        <appender-ref ref="FILE"/>
    </root>

</configuration>
```

# 给sql语句传值

## 使用map

将数据放到一个Map集合中，在sql语句中来使用这个Map集合传值。

Java测试程序：

```java
public class CarMapperTest {
    @Test
    public void testInsertCar(){
        // 准备数据
        Map<String, Object> map = new HashMap<>();
        map.put("carNum", "103");
        map.put("brand", "奔驰E300L");
        map.put("guidePrice", 50.3);
        map.put("produceTime", "2020-10-01");
        map.put("carType", "燃油车");
        // 获取SqlSession对象
        SqlSession sqlSession = SqlSessionUtil.openSession();
        // 执行SQL语句（使用map集合给sql语句传递数据）
        int count = sqlSession.insert("insertCar", map);
        System.out.println("插入了几条记录：" + count);
    }
}
```

sql语句：

```java
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">

<!--namespace先随便写-->
<mapper namespace="car">
    <insert id="insertCar">
        insert into t_car(car_num,brand,guide_price,produce_time,car_type) values(#{carNum},#{brand},#{guidePrice},#{produceTime},#{carType})
    </insert>
</mapper>
```

#{} 的里面必须填写map集合的key，不能随便写。

## 使用pojo

使用pojo传值时，本质上是调用的pojo的get方法，sql语句中的#{}中必须写get方法的方法名去掉get之后将剩下的单词首字母变小写，例如：getAge对应的是#{age}。

Java程序：

```java
@Test
public void testInsertCarByPOJO(){
    // 创建POJO，封装数据
    Car car = new Car();
    car.setCarNum("103");
    car.setBrand("奔驰C200");
    car.setGuidePrice(33.23);
    car.setProduceTime("2020-10-11");
    car.setCarType("燃油车");
    // 获取SqlSession对象
    SqlSession sqlSession = SqlSessionUtil.openSession();
    // 执行SQL，传数据
    int count = sqlSession.insert("insertCarByPOJO", car);
    System.out.println("插入了几条记录" + count);
}
```

sql语句：

```xml
<insert id="insertCarByPOJO">
  <!--#{} 里写的是POJO的get方法去掉get之后的单词首字母小写-->
  insert into t_car(car_num,brand,guide_price,produce_time,car_type) values(#{carNum},#{brand},#{guidePrice},#{produceTime},#{carType})
</insert>
```

如果没有对应的get方法，会报错。

## 只有一个占位符

当sql语句中只有一个#{}时，#{}里面的内容可以随便写。

# 处理查询结果集

## 查询返回一个Java对象

对于一个查询语句来说，需要指定它的“结果类型”或者“结果映射”。

所以想让mybatis查询之后返回一个Java对象的话，至少要告诉mybatis返回一个什么类型的Java对象，可以在<select>标签中添加resultType属性，用来指定查询要转换的类型：

```xml
<select id="selectCarById" resultType="com.powernode.mybatis.pojo.Car">
  select * from t_car where id = #{id}
</select>
```

同时，查询出来的结果集的**列名**必须和Java对象的**属性名**一致，否则对应的属性不会被赋值。

+ 可以在sql语句中使用as来取别名

  ```xml
  <select id="selectCarById" resultType="com.powernode.mybatis.pojo.Car">
  select 
      id, car_num as carNum, 
      brand, 
      guide_price as guidePrice, 
      produce_time as produceTime, 
      car_type as carType 
  from 
      t_car 
  where 
      id = #{id}
  </select>
  ```

## 查询返回一个List集合

还是要用resultType属性来指定List集合中的数据类型，而不是指定List类型。

```xml
<select id="selectCarAll" resultType="com.powernode.mybatis.pojo.Car">
select 
    id, car_num as carNum, 
    brand, 
    guide_price as guidePrice, 
    produce_time as produceTime, 
    car_type as carType 
from 
    t_car 
</select>
```

# SqlMapper的namespace

在SQL Mapper配置文件中<mapper>标签的namespace属性可以翻译为命名空间，这个命名空间主要是为了防止sqlId冲突的。

如果有两个mapper配置文件，其中的有sql语句的id一样，那么就需要通过namespace来区分，否则会报错。

比如有一个CarMapper2.xml配置文件，他的命名空间是car2：

```xml
<mapper namespace="car2">
    <select id="selectCarAll" resultType="com.powernode.mybatis.pojo.Car">
    select 
        id, car_num as carNum, 
        brand, 
        guide_price as guidePrice, 
        produce_time as produceTime, 
        car_type as carType 
    from 
        t_car 
    </select>
</mapper>
```

那么在Java程序中使用car2的selectAll语句：

```java
List<Object> cars = sqlSession.selectList("car2.selectCarAll");
```

# #{}和${}

\#{}：先编译sql语句，再给占位符传值，底层是PreparedStatement实现。可以防止sql注入，比较常用。

${}：先进行sql语句拼接，然后再编译sql语句，底层是Statement实现。存在sql注入现象。只有在需要进行sql语句关键字拼接的情况下才会用到。

# 不写mapper实现类

mybatis可以自己实现mapper接口的实现类，但是需要注意，mapper.xml文件中的namespace必须是和mapper接口名一致，id必须和接口中的方法名一致。

# 别名

mapper.xml文件中的resultType属性用来指定查询结果集的封装类型，可以起别名。

第一种方式：

```xml
<typeAliases>
  <typeAlias type="com.powernode.mybatis.pojo.Car" alias="Car"/>
</typeAliases>
```

- type属性：指定给哪个类起别名
- alias属性：别名。
  -  alias属性不是必须的，如果缺省的话，type属性指定的类型名的简类名作为别名。
  -  alias是大小写不敏感的。也就是说假设alias="Car"，再用的时候，可以CAR，也可以car，也可以Car，都行。

第二种方式：

```xml
<typeAliases>
  <package name="com.powernode.mybatis.pojo"/>
</typeAliases>
```

只需要指定包名，该包下的所有类都自动起别名，别名就是简类名。并且别名不区分大小写。

# 结果映射

查询结果的列名和java对象的属性名对应不上怎么办？

- 第一种方式：as 给列起别名
- 第二种方式：使用resultMap进行结果映射
- 第三种方式：是否开启驼峰命名自动映射（配置settings）

使用resultMap进行结果映射：

```xml
<resultMap id="carResultMap" type="car">
  <!--对象的唯一标识，官方解释是：为了提高mybatis的性能。建议写上。-->
  <id property="id" column="id"/>
  <result property="carNum" column="car_num"/>
  <!--当属性名和数据库列名一致时，可以省略。但建议都写上。-->
  <!--javaType用来指定属性类型。jdbcType用来指定列类型。一般可以省略。-->
  <result property="brand" column="brand" javaType="string" jdbcType="VARCHAR"/>
  <result property="guidePrice" column="guide_price"/>
  <result property="produceTime" column="produce_time"/>
  <result property="carType" column="car_type"/>
</resultMap>

<!--resultMap属性的值必须和resultMap标签中id属性值一致，用来指定使用哪个结果集 。-->
<select id="selectAllByResultMap" resultMap="carResultMap">
  select * from t_car
</select>
```

驼峰命名自动映射：

```xml
<!--放在properties标签后面-->
<settings>
  <setting name="mapUnderscoreToCamelCase" value="true"/>
</settings>
```

使用这种方式的前提是：属性名遵循Java的命名规范，数据库表的列名遵循SQL的命名规范。

+ Java命名规范：首字母小写，后面每个单词首字母大写，遵循驼峰命名方式。
+ SQL命名规范：全部小写，单词之间采用下划线分割。
