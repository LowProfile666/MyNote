# Java基础

## List 集合排序

### 1 通过 Collections

Collections 类中有两个对 List 集合排序的方法：

![image-20230824161245278](https://gitee.com/LowProfile666/image-bed/raw/master/img/202308241612650.png)

+ 第一种排序方法，针对 List 集合里面的元素都实现了 Comparable 接口，如果 List 集合里的元素是对象的话，可以通过重写对象的 compareTo 方法来自定义排序规则。

```java
Collections.sort(list);
```

+ 第二种排序方法，需要自己实现一个 Comparator 类，在里面重写 compare 方法，定义自己的排序规则。

这是匿名内部类的方式：

```java
Collections.sort(list, new Comparator<>(){
    public int compare(){
   		// 自定义规则     
    }
});
```



### 2 通过 List

List 接口中有一个 sort 方法：

![image-20230824162305035](https://gitee.com/LowProfile666/image-bed/raw/master/img/202308241623070.png)

也是需要自己实现一个 Comparator 类，在其中重写 compare 方法。

```java
list.sort(new Comparator<>(){
    public int compare(){
        // 自定义规则
    }
});
```

## 两个数组比较

数组相等的条件不仅要求数组元素的个数必须相等，而且要求对应位置的元素也相等。Arrays 类提供了 equals() 方法比较整个数组。

![image-20230826195036501](https://gitee.com/LowProfile666/image-bed/raw/master/img/202308261950571.png)

`equals(int[] a, int[] b)`：可以直接比较两个数组是否一样。

`equals(int[]a, int aFromIndex, int aToIndex, int[] b, int bFromIndex, int bToIndex)`：比较两个数组指定范围的部分是否一样。

equals 方法中带有参数 Comparator 的即代表可以自定义比较器，自定义比较规则。

## fill 初始化数组

Arrays 类中有一个 fill 静态方法，作用是以特定值填充数组。

![image-20230826195407289](https://gitee.com/LowProfile666/image-bed/raw/master/img/202308261954355.png)

但是 **Arrays.fill() 并不能提高赋值的效率，在函数的内部也是用for循环的方式 实现的。**

## 数组转集合

数组只能转换为List集合。

总结：

+ 使用 `asList()` 方法转为 list 集合
+ 转成的 list 集合大小不能改变（不能插入和删除元素）
+ 转成的 list 集合中的元素可以修改
  + 原数组的值也会被修改
  + 原数组的值被修改时，list 集合中的值也会被修改

数组转换为集合使用的是数组的工具类Arrays的静态方法`asList`。这个方法返回一个固定长度大小的列表。

![image-20231007191528851](https://gitee.com/LowProfile666/image-bed/raw/master/img/202310071915476.png)

```java
public class Main {
    public static void main(String[] args) {
        Integer[] a = {1, 23, 4, 6, 54, 78};
        String[] s = {"1", "ds"};
        List<Integer> listA = Arrays.asList(a);
        List<String> listS = Arrays.asList(s);
        System.out.println(listA);  // [1, 23, 4, 6, 54, 78]
        System.out.println(listS);  // [1, ds]
    }
}
```

既然是固定长度大小，那么再往list中添加元素就不行了：

```java
public class Main {
    public static void main(String[] args) {
        String[] s = {"1", "ds"};
        List<String> listS = Arrays.asList(s);
        System.out.println(listS);
        listS.add("2");  // java.lang.UnsupportedOperationException
    }
}
```

但是可以改变列表中的值，同时原数组的值也会被改变：

```java
public class Main {
    public static void main(String[] args) {
        String[] s = {"1", "ds"};
        List<String> listS = Arrays.asList(s);
        listS.set(1, "2"); 
        System.out.println(listS);  // [1, 2]
        System.out.println(Arrays.toString(s));  // [1, 2]
    }
}
```

改变原数组中的值的时候，列表的值也会被改变：

```java
public class Main {
    public static void main(String[] args) {
        String[] s = {"1", "ds"};
        List<String> listS = Arrays.asList(s);
        s[0] = "22";
        System.out.println(listS);  // [22, ds]
        System.out.println(Arrays.toString(s));  // [22, ds]
    }
}
```

要想往集合里面添加元素，可以用一个新的空集合来实现，这样也不会修改原数组。

可以根据原列表来创建新列表：

```java
public class Main {
    public static void main(String[] args) {
        String[] s = {"1", "ds"};
        List<String> listS = Arrays.asList(s);
        List<String> list2 = new ArrayList<>(listS);

        list2.add("hhhh");
        System.out.println(listS);  // [1, ds]
        System.out.println(list2);  // [1, ds, hhh]
        System.out.println(Arrays.toString(s));  // [1, ds]
    }
}
```

可以使用`addAll()`方法：

```java
public class Main {
    public static void main(String[] args) {
        String[] s = {"1", "ds"};
        List<String> listS = Arrays.asList(s);
        List<String> list2 = new ArrayList<>();
        list2.addAll(listS);
        
        list2.add("hhhh");
        System.out.println(listS);  // [1, ds]
        System.out.println(list2);  // [1, ds, hhh]
        System.out.println(Arrays.toString(s));  // [1, ds]
    }
}
```



## 集合转数组

使用 `toArray()` 方法。

![image-20231007193216654](https://gitee.com/LowProfile666/image-bed/raw/master/img/202310071932693.png)

使用无参 `toArray()` 方法时，返回的是 `Object[]` ：

```java
public class Main {
    public static void main(String[] args) {
        Set<String> set = new HashSet<>();
        set.add("hl");
        set.add("wd");
        Object[] s = set.toArray();
        // 不能这样写
        // String[] s = set.toArray();
        System.out.println(Arrays.toString(s));  // [hl, wd]
    }
}
```

使用有参 `toArray()` 方法时，参数传入一个目标类型的数组，需要定义维度大小：

```java
public class Main {
    public static void main(String[] args) {
        Set<String> set = new HashSet<>();
        set.add("hl");
        set.add("wd");
        String[] s = set.toArray(new String[2]);
        System.out.println(Arrays.toString(s));  // [hl, wd]
    }
}
```

`set.toArray(new String[2])` 中的数组的维度大小 n 必须要写，有两种情况：

+ 小于等于集合中元素的个数：生成的数组的长度就为集合中元素的个数
+ 大于集合中元素的个数：生成的数组的长度为 n，多出来的位置初始为null



## 求两个数的最大值

公式：$max=\frac{a+b+abs(a-b)}{2}$ 。

理解：`abs(a-b)` 是两个数的差值，假如 b 大于 a，那么 a+b+abs(a-b) 就等于 2b，再除以 2，就是最大值，如图：

![image-20230829105633443](https://gitee.com/LowProfile666/image-bed/raw/master/img/202308291056496.png)





## 关于1的左移得到整型的最大值

int 的最大值为 $$2^{31}-1$$，可以通过 $$(1 << 31) - 1$$ 或 `Integer.MAX_VALUE` 得到

```java
jshell> (1 << 31) - 1
$1 ==> 2147483647
```

但注意：$$1<<31$$ 是 int 的最小值：

```java
jshell> 1 << 31
$2 ==> -2147483648
```

long 的最大值为 $$2^{63}-1$$ ，可以通过 $$(1L<<63)-1$$ 或 `Long.MAX_VALUE`得到：

```java
jshell> (1L << 63) - 1
$3 ==> 9223372036854775807
```

但注意：$$1L<<63$$ 是 long 的最小值：

```
jshell> 1L << 63
$4 ==> -9223372036854775808
```



## 匿名内部类访问局部变量的问题

在写安卓的过程中，碰到一个问题：

```java
protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    EdgeToEdge.enable(this);
    setContentView(R.layout.activity_detail);
    Intent intent = getIntent();
    Bundle bundle = intent.getBundleExtra("mapBundle");
    String number = bundle.getString("number");
    String name = bundle.getString("name");
    String clazz = bundle.getString("class");
    int photo = bundle.getInt("photo");

    ImageView photoIV = findViewById(R.id.detail_photo_iv);
    EditText numberEt = findViewById(R.id.detail_number_et);
    EditText classEt = findViewById(R.id.detail_class_et);
    EditText nameET = findViewById(R.id.detail_name_et);
    Button editBtn = findViewById(R.id.detail_edit_btn);
    Button deleteBtn = findViewById(R.id.detail_delete_btn);

    photoIV.setImageResource(photo);
    numberEt.setText(number);
    classEt.setText(clazz);
    nameET.setText(name);
    numberEt.setEnabled(false);

    StudentDao dao = new StudentDao(new DBHelper(this));

    editBtn.setOnClickListener(new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            name = nameET.getText().toString();
            clazz = classEt.getText().toString();
            dao.edit(number, name, clazz);
            Toast.makeText(DetailActivity.this, "修改成功！", Toast.LENGTH_SHORT).show();
            finish();
        }
    });
}
```

以上代码这一部分会编译报错：

```java
name = nameET.getText().toString();
clazz = classEt.getText().toString();
```

**因为这两个变量不是在匿名内部类中定义的，是外面的局部变量，只能被访问，不能被修改，所以重新赋值会报错。**

如果外面的局部变量在声明之后又被修改过了，那么在匿名内部类中连访问都不行了：

```java
int i = 10;
i = 20;

editBtn.setOnClickListener(new View.OnClickListener() {
    @Override
    public void onClick(View v) {
        Log.i("hhhhhh", i + "");
        String name = nameET.getText().toString();
        String clazz = classEt.getText().toString();
        dao.edit(number, name, clazz);
        Toast.makeText(DetailActivity.this, "修改成功！", Toast.LENGTH_SHORT).show();
        finish();
    }
});
```





# Spring

## 定时任务

比如：

```java
@EnableScheduling //开启定时任务的支持
@Component
public class DataCacheTask {
    @Scheduled(cron = "0 /3 * * * *", timeUnit = TimeUnit.MICROSECONDS)
    public void task() {
        System.out.println("这里面就写具体要执行的业务逻辑代码......" + new Date());
    }
}
```

1. **`@EnableScheduling`**:
   - 这是一个注解，用于启用Spring的定时任务调度功能。通常放在配置类上，告诉Spring要扫描并执行定时任务。
2. **`@Component`**:
   - 这是一个Spring的注解，表示这个类是一个Spring组件。Spring会自动检测并将其注册为Spring应用程序上下文中的一个Bean，允许依赖注入。
3. **`@Scheduled`**:
   - 这是用于定义定时任务的注解。可以设置触发任务的时间和频率。
   - `cron = "0 /3 * * * *"`: 这是一个cron表达式，用于指定任务的执行时间，意思是每3分钟执行一次。
   - `timeUnit = TimeUnit.MICROSECONDS`：这个参数在`@Scheduled`注解中其实是无效的，因为`@Scheduled`的cron表达式已经决定了时间单位。

### Scheduled注解

`@Scheduled`注解是Spring框架中用于定义定时任务的方法。它可以用来在特定时间或间隔时间内自动触发一个方法的执行。`@Scheduled`注解提供了多种配置方式，可以通过不同的参数来定义任务的调度策略。

常用参数

1. **cron**:

   - 使用Cron表达式来定义任务的执行时间。

   - 例如：`"0 0/5 * * * ?" `表示每5分钟执行一次。

   - 示例：

     ```java
     @Scheduled(cron = "0 0/5 * * * ?")
     public void cronTask() {
         System.out.println("每5分钟执行一次");
     }
     ```

2. **fixedRate**:

   - 按固定的频率执行任务，以毫秒为单位。

   - 任务之间的间隔时间是固定的，不考虑任务的执行时间。

   - 示例：

     ```java
     @Scheduled(fixedRate = 5000)
     public void fixedRateTask() {
         System.out.println("每5秒执行一次");
     }
     ```

3. **fixedDelay**:

   - 按固定的延迟执行任务，以毫秒为单位。

   - 当前任务执行完毕后，经过指定的延迟时间再执行下一次任务。

   - 示例：

     ```java
     @Scheduled(fixedDelay = 5000)
     public void fixedDelayTask() {
         System.out.println("每次任务执行完毕后等待5秒再执行下一次");
     }
     ```

4. **initialDelay**:

   - 首次执行任务的延迟时间，以毫秒为单位。

   - 常与`fixedRate`或`fixedDelay`结合使用。

   - 示例：

     ```java
     @Scheduled(fixedRate = 5000, initialDelay = 10000)
     public void initialDelayTask() {
         System.out.println("第一次等待10秒后执行，之后每5秒执行一次");
     }
     ```

5. **zone**:

   - 指定时区。默认是服务器的时区。

   - 示例：

     ```java
     @Scheduled(cron = "0 0 12 * * ?", zone = "America/New_York")
     public void zonedTask() {
         System.out.println("在纽约时间中午12点执行");
     }
     ```

### cron表达式

Cron表达式是一种用于调度任务的字符串格式，它定义了详尽的时间和日期规则。Cron表达式通常包含六个或七个字段，每个字段之间用空格分隔，定义任务在何时执行。以下是标准的六字段格式：

```
秒(0-59) 分(0-59) 小时(0-23) 日(1-31) 月(1-12) 星期(0-7，0和7都是星期天)
```

七字段的cron表达式就是多了一个年的字段，在最后面。

字段解释

1. **秒 (Seconds)**: 0-59
2. **分 (Minutes)**: 0-59
3. **小时 (Hours)**: 0-23
4. **日 (Day of month)**: 1-31
5. **月 (Month)**: 1-12 或者 JAN-DEC
6. **星期 (Day of week)**: 0-7 (0 和 7 都代表星期天) 或者 SUN-SAT

特殊字符

- **`*`**：匹配任意值。例如，`*`在“分钟”字段中表示每一分钟。
- **`,`**：枚举值。例如，“1,2,5”表示第1、2和5个时段。
- **`-`**：范围值。例如，“1-5”表示从第1到第5个时段。
- **`/`**：步长。例如，“0/15”表示从0开始，每15个单位。例如，“分钟”字段的“0/15”表示每小时的0、15、30和45分钟。
- **`?`**：只用于“日”和“星期”字段，表示不指定值。可用于避免冲突。
- **`L`**：表示“最后”的意思。可以用于“日”和“星期”字段。例如，“L”在“日”字段表示一个月的最后一天。
- **`W`**：表示工作日（周一到周五），只用于“日”字段。例如，“15W”表示最接近第15日的工作日。
- **`#`**：表示某月的第几个星期几。例如，“3#2”表示某月的第二个星期三。

示例

1. 每分钟

   ```
   * * * * *
   ```

2. 每天的每小时的第15分钟

   ```
   0 15 * * *
   ```

3. 每月的1日和15日的中午12点

   ```
   0 0 12 1,15 * *
   ```

4. 每周一至周五的上午10:15

   ```
   0 15 10 ? * MON-FRI
   ```

5. 每隔5分钟

   ```
   * 0/5 * * * *
   ```

6. 每月的最后一天的23:59

   ```
   59 59 23 L * ?
   ```

7. 每年的1月1日的0:00

   ```
   0 0 0 1 1 ?
   ```

实用工具：在写复杂的cron表达式时，您可以使用在线工具如[cronmaker](http://www.cronmaker.com/)来生成和验证您的表达式。

