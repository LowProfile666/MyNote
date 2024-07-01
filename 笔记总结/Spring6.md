# 需要的依赖

+ spring-context

# 注解式开发

## bean的注解

控制器类上使用：@Controller

service类上使用：@Service

dao类上使用：@Repository

@Controller、@Service、@Repository这三个注解都是@Component注解的别名。

他们都是只有一个value属性。value属性用来指定bean的id，也就是bean的名字。

```java
@Component("vipBean")
public class Vip {
}
```

如果不指定value的值，spring会自动默认名字是类名首字母小写。

```java
@Component
public class BankDao {
}
```

这个BankDao的bean的名字为：bankDao。

## 包扫描

需要在spring.xml文件中指定spring要扫描的包：

```xml
<context:component-scan base-package="com.zsm.spring6.bean"/>
```

## 注入的注解

给Bean属性赋值需要用到这些注解：

- @Value
- @Autowired
- @Qualifier
- @Resource

### @Value

可以使用在属性上

```java
@Component
public class User {
    @Value(value = "zhangsan")
    private String name;
    @Value("20")
    private int age;
}
```

可以使用在set方法上

```java
@Component
public class User {
    private String name;
    private int age;

    @Value("李四")
    public void setName(String name) {
        this.name = name;
    }

    @Value("30")
    public void setAge(int age) {
        this.age = age;
    }
}
```

可以使用在构造方法的参数上

```java
@Component
public class User {
    private String name;
    private int age;

    public User(@Value("隔壁老王") String name, @Value("33") int age) {
        this.name = name;
        this.age = age;
    }
}
```

### @Autowired

用来注入非简单类型。单独使用该注解，默认是根据类型装配。

使用在属性上：

```java
@Service // 纳入bean管理
public class UserService {
    // @Autowired注解使用的时候，不需要指定任何属性，直接使用这个注解即可
    // 这个注解的作用是根据类型byType进行自动装配
    @Autowired // 在属性上注入
    private UserDao userDao;
    
    // 没有提供构造方法和setter方法。

    public void save(){
        userDao.insert();
    }
}
```

使用在set方法上：

```java
@Service
public class UserService {
    private UserDao userDao;

    @Autowired
    public void setUserDao(UserDao userDao) {
        this.userDao = userDao;
    }

    public void save(){
        userDao.insert();
    }
}
```

使用在构造方法的参数上：

```java
@Service
public class UserService {
    private UserDao userDao;

    public UserService(@Autowired UserDao userDao) {
        this.userDao = userDao;
    }

    public void save(){
        userDao.insert();
    }
}
```

@Autowired还可以省略不写，只有当：构造方法只有一个，且构造方法上的参数和属性能够对应的时候

```java
@Service
public class UserService {
    private UserDao userDao;

    public UserService(UserDao userDao) {
        this.userDao = userDao;
    }

    public void save(){
        userDao.insert();
    }
}
```

### @Qualifier

当一个接口有两个不同的实现类时，就不能使用通过类型自动装配了，就需要通过名字来自动装配。

@Autowired注解和@Qualifier注解联合起来才可以根据名称进行装配，在@Qualifier注解中指定Bean名称。

```java
@Service
public class UserService {
    private UserDao userDao;

    @Autowired
    @Qualifier("userDaoForOracle") // 这个是bean的名字。
    public void setUserDao(UserDao userDao) {
        this.userDao = userDao;
    }

    public void save(){
        userDao.insert();
    }
}
```

### @Resource

该注解也是用来注入非简单类型的。这是标准注解。

@Resource注解是JDK包中的，@Autowired注解是Spring包中的。

@Resource注解默认根据名称装配（byName），未指定name时，使用属性名作为name。通过name找不到的话会自动启动通过类型装配（byType）。

该注解能用在属性上：

```java
@Service
public class UserService {
    // @Resource(name = "xyz")
    @Resource  // 这个name默认是userDao
    private UserDao userDao;

    public void save(){
        userDao.insert();
    }
}
```

用在set方法上：set方法的方法名去掉set后，首字母小写就是name

```java
@Service
public class UserService {
    private UserDao userDao;

    // @Resource(name = "userDaoForMySQL")
    @Resource  // userDao就是name
    public void setUserDao(UserDao userDao) {
        this.userDao = userDao;
    }

    public void save(){
        userDao.insert();
    }
}
```

