# 一、数据结构和算法概述

算法是独立存在的一种解决问题的方法和思想。

数据结构是计算机存储、组织数据的方式。数据结构是指相互之间存在一种或多种特定关系的数据元素的集合。

==程序=数据结构+算法==

**线性结构**：是一个有序数据元素的集合，数据元素之间存在一对一的线性关系。

+ 顺序存储结构：顺序表，顺序表中存储元素是连续的。
+ 链式存储结构：链表，链表中的存储元素不一定是连续的。

**非线性结构**：二维数组、多维数组、树、图、广义表.... 

# 二、栈

栈是限制插入和删除只能在一个位置上进行的线性表。允许插入和删除的一端叫**栈顶（top）**，不允许插入和删除的另一端叫**栈底（bottom）**。

基本操作

+ PUSH：压栈、入栈（插入操作）。
+ POP：弹栈、出栈（删除操作）。

特点

+ 先进后出。

实现

+ 链表实现：动态栈
+ 数组实现：静态栈

用数组模拟实现：

```java
/*
用数组实现栈
 */
public class ArrayStack {
    private int maxSize;  // 栈的最大容量
    private int top = 0;  // 栈顶指针
    private int[] s;  // 栈

    public ArrayStack() {
        this(10);
    }
    public ArrayStack(int maxSize) {
        this.maxSize = maxSize;
        this.s = new int[maxSize];
    }

    // 判断栈空
    public boolean isEmpty(){
        return this.top == 0;
    }

	// 判断栈满
    public boolean isFull(){
        return this.top == this.maxSize - 1;
    }

    // 压栈
    public void push(int val){
        if(this.isFull()){
            throw new RuntimeException("栈以满！");
        }
        this.s[this.top++] = val;
    }

    // 出栈
    public int pop(){
        if(this.isEmpty()){
            throw new RuntimeException("栈为空！");
        }
        return this.s[--this.top];
    }
    
    // 打印栈
    public void list(){
        if(isEmpty()){
            throw new RuntimeException("空栈！");
        }
        for (int i = 0; i < top; i++) {
            System.out.println(s[i]);
        }
    }
    
    // 获取栈的长度
    public int length(){
        return top;
    }
}
```

应用1：通过以上数组模拟的栈来判断字符串是否是回文串。

思路：将字符串的每个字符压栈，然后弹栈，弹栈过程中与源字符串的每个字符串相比较。

```java
/*
利用ArrayStack类判断一个字符串是否是回文串
 */
public class StackTest {
    public static void main(String[] args) {
        System.out.println(isPalindrome("abcddcba"));
    }
    public static boolean isPalindrome(String str){
        char[] arr = str.toCharArray();
        // 初始化栈
        ArrayStack stack = new ArrayStack(10);
        // 元素压栈
        for (int i = 0; i < arr.length; i++) {
            stack.push(arr[i]);
        }
        // 出栈比较
        int len = stack.length();
        for (int i = 0; i < len; i++) {
            if(arr[i] != stack.pop())
                return false;
        }
        return true;
    }
}
```

应用2：用栈计算表达式。

```java
/*
用栈计算表达式的值
1、需要遍历字符串，获取每一个字符
2、判断当前字符是一个运算符还是数字
3、把数字存放在数字栈中，运算符存在运算符栈中
4、运算符栈：
    如果是一个空栈，那么直接将运算符入栈
    如果运算符栈中当前有其他运算符，则先判断运算符的优先级
        如果栈中原有的运算符的优先级小于等于当前要入栈的运算符，那么把原运算符弹栈并进行计算
        如果栈中原有的运算符的优先级大于当前要入栈的运算符，那么新的运算符直接入栈。
 */
public class StackTest02 {
    public static void main(String[] args) {
        String s = "44+2*10";
        System.out.println(s + "=" + calculate(s));
    }
    // 计算方法
    public static int calculate(String s){
        char[] arr = s.toCharArray();
        // 数字栈
        ArrayStack numberStack = new ArrayStack(10);
        // 符号栈
        ArrayStack symbolStack = new ArrayStack(10);
        // 将数字和运算符压栈
        int num = 0;  
        for (int i = 0; i < arr.length; i++) {
            if(arr[i] >= '0' && arr[i] <= '9')
                num = num * 10 + arr[i]-'0';
            else{
                // 先将之前的数字压栈
                numberStack.push(num);
                num = 0;
                // 判断运算符中是否有符号
                if(!symbolStack.isEmpty()){
                    
                    // 判断运算符的优先级
                    if(priority(arr[i]) <= priority(symbolStack.peek())){
                        // 先弹栈计算
                        int num1 = numberStack.pop();
                        int num2 = numberStack.pop();
                        int op = symbolStack.pop();
                        int res = calculator(num1, num2, op);
                        // 再入栈
                        numberStack.push(res);
                        symbolStack.push(arr[i]);
                    }else{
                        symbolStack.push(arr[i]);
                    }
                    
                }else {
                    symbolStack.push(arr[i]);
                }
            }
        }
        numberStack.push(num);
        while(!symbolStack.isEmpty()){
            int res = calculator(numberStack.pop(), numberStack.pop(), symbolStack.pop());
            numberStack.push(res);
        }
        return numberStack.peek();
    }
    // 计算优先级
    public static int priority(int c){
        if(c == '/' || c == '*')
            return 1;
        return 0;
    }
    // 数值计算
    public static int calculator(int num1, int num2, int operator){
        int res = 0;
        switch (operator){
            case '+': res = num1 + num2;break;
            case '-': res = num1 - num2;break;
            case '*': res = num1 * num2;break;
            case '/': res = num2 / num1;break;
        }
        return res;
    }
}
```

# 三、链表

链表（LinkedList）是一种物理存储单元上非连续、非顺序的存储结构。

特点：

+ 链表是以结点形式存储的，是链式存储
+ 链表分为带头结点链表和不带头结点链表，根据实际需求使用

## 单链表

单链表中每个结点包含 data 区域和 next 区域。

![image-20230510111249667](https://gitee.com/LowProfile666/image-bed/raw/master/img/%E5%8D%95%E5%90%91%E9%93%BE%E8%A1%A8%E7%A4%BA%E6%84%8F%E5%9B%BE.png)

应用：根据带有头部的单链表，实现商品增删改查，并且也可以针对商品已编号进行排序，完成排行榜。

链表的结点结构：

```java
package LinkedList;
/*
商品结点类
 */
public class GoodsNode {
    public int id;  // 编号
    public String name;  // 名字
    public double price;  // 价格
    public GoodsNode next;  // 指针域
    public GoodsNode() {
        this(0, "", 0.0);
        this.next = null;
    }
    public GoodsNode(int id, String name, double price) {
        this.id = id;
        this.name = name;
        this.price = price;
        this.next = null;
    }
    @Override
    public String toString() {
        return "GoodsNode{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", price=" + price +
                '}';
    }
}
```

链表的相关方法：

### 1、添加结点（尾插法）

```java
// 添加结点，尾插法
public void insert(GoodsNode goodsNode){
    GoodsNode temp = head;  		// head 是链表的头节点
    while (temp.next != null) {  	// 把链表循环到最末尾
        temp = temp.next;
    }
    temp.next = goodsNode;  		// 再在最末尾添加结点
}
```

### 2、按编号添加结点

+ 如果当前链表只有头节点，那么直接在头节点后面添加
+ 如果当前链表不止头节点，那么找到id值大于要插入的结点的id的结点
+ 如果已有此编号的结点，抛出异常

```java
// 按编号添加结点
public void insertOrder(GoodsNode goodsNode){
    GoodsNode temp = head;
    while (temp.next != null && temp.next.id < goodsNode.id) {  
        temp = temp.next;
    }
    if (temp.next == null) {  					// 最后一个结点或者是头结点
        temp.next = goodsNode;
    } else if (temp.next.id > goodsNode.id) {	// id值比要插入的结点id值大，
        goodsNode.next = temp.next;
        temp.next = goodsNode;
    } else {									// 编号相同的结点
        throw new RuntimeException("已存在结点！");
    }
}
```

### 3、修改结点

```java
 // 修改结点
public void update(GoodsNode goodsNode){
    if (head.next == null)								// 当前链表为空
        throw new RuntimeException("空链表！");
    GoodsNode temp = head;
    while (temp != null && temp.id != goodsNode.id) {	// 找到要修改的结点
        temp = temp.next;
    }
    if (temp == null)									
        System.out.println("未找到结点");
    else {												
        temp.name = goodsNode.name;
        temp.price = goodsNode.price;
    }
}
```

### 4、删除结点

```java
// 删除结点
public void delete(int id){
    if (head.next == null)
        throw new RuntimeException("空链表！");
    GoodsNode temp = head;
    while (temp != null && temp.next.id != id) {
        temp = temp.next;
    }
    if (temp == null)
        System.out.println("未找到结点");
    else {
        temp.next = temp.next.next;
    }
}
```

### 5、查看每一个结点

```java
 // 查看每一个结点
public void list(){
    if (head.next == null)
        throw new RuntimeException("空链表！");
    GoodsNode temp = head.next;
    while (temp != null) {
        System.out.println(temp);
        temp = temp.next;
    }
}
```

### 6、获取长度

不算头节点。

```java
public int length(){
    if (head.next == null)			// 不算头节点
        return 0;
    GoodsNode temp = head.next;
    int length = 0;
    while (temp != null) {
        length++;
        temp = temp.next;
    }
    return length;
}
```

### 7、完整代码

```java
package LinkedList;
/*
根据带有头部的单链表，实现商品增删改查，并且也可以针对商品已编号进行排序，完成排行榜。
 */
public class LinkedListObj {
    // 链表的头结点
    private GoodsNode head = new GoodsNode(); 

    // 添加结点，尾插法
    public void insert(GoodsNode goodsNode){
        GoodsNode temp = head;
        while (temp.next != null) {
            temp = temp.next;
        }
        temp.next = goodsNode;
    }
    // 按编号添加结点
    public void insertOrder(GoodsNode goodsNode){
        GoodsNode temp = head;
        boolean flg = false;
        while (temp.next != null && temp.next.id < goodsNode.id) {
            temp = temp.next;
        }
        if (temp.next == null) {
            temp.next = goodsNode;
        } else if (temp.next.id > goodsNode.id) {
            goodsNode.next = temp.next;
            temp.next = goodsNode;
        } else {
            throw new RuntimeException("已存在结点！");
        }
    }
    // 修改结点
    public void update(GoodsNode goodsNode){
        if (head.next == null)
            throw new RuntimeException("空链表！");
        GoodsNode temp = head;
        while (temp != null && temp.id != goodsNode.id) {
            temp = temp.next;
        }
        if (temp == null)
            System.out.println("未找到结点");
        else {
            temp.name = goodsNode.name;
            temp.price = goodsNode.price;
        }
    }
    // 删除结点
    public void delete(int id){
        if (head.next == null)
            throw new RuntimeException("空链表！");
        GoodsNode temp = head;
        while (temp != null && temp.next.id != id) {
            temp = temp.next;
        }
        if (temp == null)
            System.out.println("未找到结点");
        else {
            temp.next = temp.next.next;
        }
    }
    // 查看每一个结点
    public void list(){
        if (head.next == null)
            throw new RuntimeException("空链表！");
        GoodsNode temp = head.next;
        while (temp != null) {
            System.out.println(temp);
            temp = temp.next;
        }
    }
}
```

### 8、练习题目



## 双向链表

双向链表也叫双链表，它的每个数据结点中都有两个指针，分别指向直接后继和直接前驱。

应用：使用双向链表实现图书的增删改查。

链表的结点结构：

```java
package LinkedList;
/*
图书结点类
 */
public class BookNode {
    public int id;
    public String name;
    public double price;
    public BookNode next;
    public BookNode pre;
    public BookNode() {
        this(0, "", 0.0);
    }
    public BookNode(int id, String name, double price) {
        this.id = id;
        this.name = name;
        this.price = price;
    }
    @Override
    public String toString() {
        return "BookNode{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", price=" + price +
                '}';
    }
}
```

双向链表的相关方法：

大体和单向链表一样，只是多了一个指针域需要考虑。

### 1、添加结点（尾插法）

```java
// 插入结点（尾插法）
public void insert(BookNode bookNode){
    BookNode temp = head;
    while (temp.next != null) {
        temp = temp.next;
    }
    temp.next = bookNode;
    bookNode.pre = temp;
}
```

### 2、修改结点

```java
// 修改结点
public void update(BookNode bookNode){
    if (head.next == null)
        throw new RuntimeException("空链表！");
    BookNode temp = head;
    while (temp != null && temp.id != bookNode.id) {
        temp = temp.next;
    }
    if (temp == null)
        System.out.println("没有该节点！");
    else {
        temp.name = bookNode.name;
        temp.price = bookNode.price;
    }
}
```

### 3、删除结点

```java
// 删除结点
public void delete(int id){
    if (head.next == null)
        throw new RuntimeException("空链表！");
    BookNode temp = head.next;
    while (temp != null && temp.id != id) {
        temp = temp.next;
    }
    if (temp == null)
        System.out.println("没有该节点！");
    else {
        temp.pre.next = temp.next;
        if (temp.next != null)			// 考虑要删除的结点是不是尾结点
            temp.next.pre = temp.pre;	// 不是尾结点就修改pre
    }
}
```

### 4、查看每一个结点

```java
// 查询结点
public void list(){
    if (head.next == null)
        throw new RuntimeException("空链表！");
    BookNode temp = head.next;
    while (temp != null) {
        System.out.println(temp);
        temp = temp.next;
    }
}
```

### 5、完整代码

```java
package LinkedList;
/*
使用双向链表实现图书的增删改查。
 */
public class DouLinkedListObj {
    private BookNode head = new BookNode(0, "", 0.0);
    // 插入结点（尾插法）
    public void insert(BookNode bookNode){
        BookNode temp = head;
        while (temp.next != null) {
            temp = temp.next;
        }
        temp.next = bookNode;
        bookNode.pre = temp;
    }
    // 修改结点
    public void update(BookNode bookNode){
        if (head.next == null)
            throw new RuntimeException("空链表！");
        BookNode temp = head;
        while (temp != null && temp.id != bookNode.id) {
            temp = temp.next;
        }
        if (temp == null)
            System.out.println("没有该节点！");
        else {
            temp.name = bookNode.name;
            temp.price = bookNode.price;
        }
    }
    // 删除结点
    public void delete(int id){
        if (head.next == null)
            throw new RuntimeException("空链表！");
        BookNode temp = head.next;
        while (temp != null && temp.id != id) {
            temp = temp.next;
        }
        if (temp == null)
            System.out.println("没有该节点！");
        else {
            temp.pre.next = temp.next;
            if (temp.next != null)
                temp.next.pre = temp.pre;
        }
    }
    // 查询结点
    public void list(){
        if (head.next == null)
            throw new RuntimeException("空链表！");
        BookNode temp = head.next;
        while (temp != null) {
            System.out.println(temp);
            temp = temp.next;
        }
    }
}
```

### 6、练习题目



## 单向环型链表

### 1. 概念

### 2. 特点

### 3. 性质

### 4. 应用

约瑟夫环问题。

> 设编号为 $1,2……,n$ 的n个人围坐一圈，约定编号为 $k(1<=k<=n)$ 的人从 1 开始报数，数到 m 的那个人出列，他的下一位又从 1 开始报数，数到 m 的那个人又出列，他的下一位又从 1 开始报数，依次类推，直到所有人出列为止，由此产生一个出队编号的序列。

先定义环型链表的结点类：

```java
package LinkedList;
/*
环型链表结点类
*/
public class CircleListNode {
    private int id;
    private CircleListNode next;
    public CircleListNode(int id) {
        this.id = id;
    }
    public int getId() {
        return id;
    }
    public void setId(int id) {
        this.id = id;
    }
    public CircleListNode getNext() {
        return next;
    }
    public void setNext(CircleListNode next) {
        this.next = next;
    }
    @Override
    public String toString() {
        return "CircleListNode{" +
                "id=" + id +
                '}';
    }
}
```

#### 1）创建环型链表

```java
// 创建环型链表
public void init(int nums){				// 参数为环形链表的结点个数
    if (nums < 1) {
        System.out.println("数据错误");
        return;
    }
    CircleListNode last = null;			// 用来指环形链表的最后一个结点，方便每次插入结点
    for (int i = 1; i <= nums; i++) {
        CircleListNode node = new CircleListNode(i);
        if (i == 1) {					// 第一个结点
            first = node;				// first 是链表的属性，是第一个结点
            first.setNext(first);
        } else {
            last.setNext(node);
            node.setNext(first);
        }
        last = node;
    }
}
```

#### 2）查看环型链表

```java
// 查看环型链表
public void list(){
    if (first == null) {
        System.out.println("空链表！");
        return;
    }
    CircleListNode temp = first;
    while (true) {
        System.out.println(temp);
        temp = temp.getNext();
        if (temp == first)			// 当再一次循环到first时，表示一圈已经循环完了
            break;
    }
}
```

#### 3）约瑟夫问题

```java
/**
     * 约瑟夫问题
     * @param start 开始的结点
     * @param step  每次数几个
     * @param nums  结点总数
     */
public void YSF(int start, int step, int nums) {
    if (first == null) {
        System.out.println("空链表！");
        return;
    }
    if (start < 1 || start > nums || step < 1) {
        System.out.println("参数数据不正确！");
        return;
    }
    CircleListNode last = first;		// 用来指链表的最后一个结点
    // 先找到当前循环的末尾
    while (true) {
        if(last.getNext() == first)
            break;
        last = last.getNext();
    }
    // 再根据参数找到规定的起点位置和末尾位置
    for (int i = 1; i < start; i++) {		
        first = first.getNext();
        last = last.getNext();
    }
    // 双循环
    // 当环型链表只剩下一个结点时，退出外循环
    // 内循环用来模拟绕圈报数过程
    while (true) {
        for (int i = 1; i < step; i++) {
            first = first.getNext();
            last = last.getNext();
        }
        System.out.println(first.getId());  // 当前first所在结点是被出列的结点
        first = first.getNext();			// 然后first从下一个开始
        last.setNext(first);
        if (last == first)					// 仅剩一个结点时
            break;
    }
    System.out.println(last.getId());		// 这是最后一个结点出列
}
```

#### 4）完整代码

```java
package LinkedList;

public class CircleListObj {
    private CircleListNode first = new CircleListNode(-1);
    // 创建环型链表
    public void init(int nums){
        if (nums < 1) {
            System.out.println("数据错误");
            return;
        }
        CircleListNode last = null;
        for (int i = 1; i <= nums; i++) {
            CircleListNode node = new CircleListNode(i);
            if (i == 1) {
                first = node;
                first.setNext(first);
            } else {
                last.setNext(node);
                node.setNext(first);
            }
            last = node;
        }
    }
    // 查看环型链表
    public void list(){
        if (first == null) {
            System.out.println("空链表！");
            return;
        }
        CircleListNode temp = first;
        while (true) {
            System.out.println(temp);
            temp = temp.getNext();
            if (temp == first)
                break;
        }
    }
    /**
     * 约瑟夫问题
     * @param start 开始的结点
     * @param step  每次数几个
     * @param nums  结点总数
     */
    public void YSF(int start, int step, int nums) {
        if (first == null) {
            System.out.println("空链表！");
            return;
        }
        if (start < 1 || start > nums || step < 1) {
            System.out.println("参数数据不正确！");
            return;
        }
        CircleListNode last = first;
        // 先找到当前循环的末尾
        while (true) {
            if(last.getNext() == first)
                break;
            last = last.getNext();
        }
        // 再根据参数找到起点位置，和末尾位置
        for (int i = 1; i < start; i++) {
            first = first.getNext();
            last = last.getNext();
        }
        while (true) {
            for (int i = 1; i < step; i++) {
                first = first.getNext();
                last = last.getNext();
            }
            System.out.println(first.getId());
            first = first.getNext();
            last.setNext(first);
            if (last == first)
                break;
        }
        System.out.println(last.getId());
    }
}
```



### 5. 练习



# 四、稀疏数组

### 1. 概念



压缩条件：

+ 原数组中存在大量的无效数据，占据了大量的存储空间，真正有用的数据很少。
+ 压缩存储可以节省存储空间，避免资源地不必要浪费，在数据序列化到磁盘时，压缩存储可以提高IO效率。

处理方法：

+ 记录数组一共有几行几列，有多少个不同的值。
+ 把具有不同值元素的行列及值记录在一个小规模的数组中，从而缩小程序的规模。

### 2. 特点

### 3. 性质

### 4. 应用

使用稀疏数组来保留二维数组、把稀疏数组重新恢复为二维数组。

#### 1）准备条件

先新建一个有大量无效数据（等于0）的二维数组，然后给里面赋两个有效值。

```java
// 先有一个存在大量无效数据的二维数组
int[][] src = new int[11][11];
src[1][2] = 1;
src[2][3] = 2;
```

#### 2）创建压缩数组

先记录下原来二维数组中有效数值的个数，然后再创建数组。

```java
// 记录下二维数组中有效元素的个数
int cnt = 0;				// 记录有效值个数
for (int[] row : src) {
    for (int val : row) {
        if (val != 0)
            cnt++;
    }
}
// 创建压缩数组
int[][] sparseArr = new int[cnt+1][3];  // 行为有效值个数+1，每个有效值要占一行，加上第一行的信息
sparseArr[0][0] = src.length;			// 原数组的行数
sparseArr[0][1] = src[0].length;		// 原数组的列数
sparseArr[0][2] = cnt;					// 原数组的有效值个数
```

#### 4）压缩数组

```java
// 将数据进行压缩
int top = 1;		// 压缩数组从第2行开始存储，因为第1行存储了二维数组的信息。
for (int i = 0; i < src.length; i++) {
    for (int j = 0; j < src[i].length; j++) {
        if (src[i][j] != 0) {
            sparseArr[top][0] = i;
            sparseArr[top][1] = j;
            sparseArr[top][2] = src[i][j];
            top++;
        }
    }
}
```

#### 5）转回二维数组

```java
// 将压缩数组转为二维数组
int[][] newArray = new int[sparseArr[0][0]][sparseArr[0][1]];
for (int i = 1; i < sparseArr.length; i++) {
    newArray[sparseArr[i][0]][sparseArr[i][1]] = sparseArr[i][2];
}
```

#### 6）完整代码

```java
package array;

public class SparseArray {
    public static void main(String[] args) {
        // 先有一个存在大量无效数据的二维数组
        int[][] src = new int[11][11];
        src[1][2] = 1;
        src[2][3] = 2;
        // 打印二维数组
        myPrint(src);
        // 记录下二维数组中有效元素的个数
        int cnt = 0;
        for (int[] row : src) {
            for (int val : row) {
                if (val != 0)
                    cnt++;
            }
        }
        // 创建压缩数组
        int[][] sparseArr = new int[cnt+1][3];
        sparseArr[0][0] = src.length;
        sparseArr[0][1] = src[0].length;
        sparseArr[0][2] = cnt;
        // 将数据进行压缩
        int top = 1;
        for (int i = 0; i < src.length; i++) {
            for (int j = 0; j < src[i].length; j++) {
                if (src[i][j] != 0) {
                    sparseArr[top][0] = i;
                    sparseArr[top][1] = j;
                    sparseArr[top][2] = src[i][j];
                    top++;
                }
            }
        }
        // 打印压缩数组
       	myPrint(sparseArr);
        // 将压缩数组转为二维数组
        int[][] newArray = new int[sparseArr[0][0]][sparseArr[0][1]];
        for (int i = 1; i < sparseArr.length; i++) {
            newArray[sparseArr[i][0]][sparseArr[i][1]] = sparseArr[i][2];
        }
        // 打印二维数组
        myPrint(newArray);
    }
    public static void myPrint(int[][] arr) {
        for (int[] row : arr) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
    }
}
```

### 5. 练习

# 五、队列

## 1. 概念

队列是一种特殊的线性表，特殊之处在于它只允许在表的前端（front）进行删除操作，而在表的后端（rear）进行插入操作，和栈一样，队列是一种操作受限制的线性表。进行插入操作的端称为**队尾**，进行删除操作的端称为**队头**。

【队列示意图】

## 2. 特点

+ 先进先出
+ 队列是一个有序列表，可以用数组和链表来实现。

## 3. 性质

假溢出：队头和队尾指针都指向队列的末尾未开辟空间处，但此时队列内有存储元素的空间，却不能存储元素。

+ 比如，队列满之后，清空队列，但未归零队头队尾指针。

真溢出：队头和队尾指针都指向队列的末尾未开辟空间处，但此时队列内已经没有剩余空间存储元素。

+ 队列满之后。

## 4. 应用

使用数组实现队列。

### 1）判断队满

```java
// 判断队列是否满
public boolean isFull() {
    return rear == maxSize;  // maxSize是队列最大容量
}
```

### 2）判断队空

```java
// 判断队列是否为空
public boolean isEmpty() {
    return front == rear;
}
```

### 3）入队

```java
 // 入队
public void inQueue(int n) {
    if (isFull()) {
        System.out.println("队列已满");
        return;
    }
    queue[rear++] = n;
}
```

### 4）出队

```java
// 出队
public int deQueue() {
    if (isEmpty())
        throw new RuntimeException("队列为空");
    return queue[front++];
}
```

### 5）完整代码

```java
package queue;

public class ArrayQueue {
    private int[] queue;	// 队列
    private int maxSize;	// 队列最大容量
    private int front;		// 队头指针
    private int rear;		// 队尾指针
    public ArrayQueue() {
        this(10);
    }
    public ArrayQueue(int maxSize) {
        this.maxSize = maxSize;
        queue = new int[maxSize];
    }
    // 判断队列是否满
    public boolean isFull() {
        return rear == maxSize;
    }
    // 判断队列是否为空
    public boolean isEmpty() {
        return front == rear;
    }
    // 入队
    public void inQueue(int n) {
        if (isFull()) {
            System.out.println("队列已满");
            return;
        }
        queue[rear++] = n;
    }
    // 出队
    public int deQueue() {
        if (isEmpty())
            throw new RuntimeException("队列为空");
        return queue[front++];
    }
    // 查看队列元素
    public void printQueue() {
        if (isEmpty())
            throw new RuntimeException("队列为空");
        for (int i = front; i < rear; i++) {
            System.out.printf("queue[%d] : %d\n", i, queue[i]);
        }
    }
    public static void main(String[] args) {
        ArrayQueue q = new ArrayQueue(5);
        q.inQueue(1);
        q.inQueue(2);
        q.inQueue(3);
        q.inQueue(4);
        q.inQueue(5);
        q.inQueue(6);
        q.deQueue();
        q.printQueue();
    }
}
```

## 5. 练习

# 六、递归

## 1. 概念

**递归**就是方法自己调用自己，每次调用时传入的参数是不同的。

规则：

+ 执行一个方法时，就创建一个新的受保护的独立栈空间
+ 方法的局部变量是独立的，不会相互影响
+ 如果方法中使用的是引用类型变量，比如数组，则会共享引用型的数据
+ 递归必须向退出递归的条件接近，否则就是无限递归，会出现StackOverflowError
+ 一个方法执行完毕后，或者遇到return，就会返回数据，遵守谁调用就将结果返回给谁，同时当方法执行完毕或者返回时，该方法也就执行完毕

## 2. 特点

## 3. 性质

## 4. 应用

迷宫问题。一个8行7列的迷宫，四周都是墙（1），除墙以外的第三行的前两个格子也为墙（1），其余地方为空白处（0）。一个小球从左上角第一个格子处（1，1）出发，要走到左下角最后一个格子处（6，5）结束，输出小球的移动路线。

这个案例十分简单，主要是理解递归的执行方式。

```java
package recursion;

public class Maze {
    public static void main(String[] args) {
        // 迷宫地图
        int[][] map = new int[8][7];
        // 设置上下两端墙
        for (int i = 0; i < 7; i++) {
            map[0][i] = 1;
            map[7][i] = 1;
        }
        // 设置左右两端墙
        for (int i = 0; i < 7; i++) {
            map[i][0] = 1;
            map[i][6] = 1;
        }
        // 设置障碍墙
        map[3][1] = 1;
        map[3][2] = 1;
        // 打印迷宫地图
        System.out.println("原来的迷宫地图：");
        for (int[] row : map) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
        isRun(map, 1, 1);
        System.out.println("走过后的迷宫地图：");
        for (int[] row : map) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
    }
    /*
    用1表示墙，0表示路，2表示走过的路
     */
    public static boolean isRun(int[][] map, int i, int j) {
        if (map[6][5] == 2)     // 走到终点
            return true;
        else {
            if (map[i][j] == 0) {
                map[i][j] = 2;                      // 将走过的路标为2
                if (isRun(map, i+1, j))             // 往上
                    return true;
                else if (isRun(map, i+1, j))        // 往下
                    return true;
                else if (isRun(map, i, j-1))        // 往左
                    return true;
                else if (isRun(map, i, j+1))        // 往右
                    return true;
                else
                    return false;
            }else
                return false;
        }
    }
}
```

## 5. 练习

# 七、排序

## 1. 概念

**排序**也称之为排序算法（Sort Algorithm），是将一组数据以指定的顺序进行排列的过程。

分类：

+ 内部排序：将所有的数据都加载到内部存储器上进行排序。
+ 外部排序：数据量多、大，无法全部加载到内存中，需要借助外部存储（文档 ）进行排序。

算法分类图

![image-20230513100418838](https://gitee.com/LowProfile666/image-bed/raw/master/img/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95%E5%88%86%E7%B1%BB%E5%9B%BE.png)



## 2. 特点

## 3. 性质

|   排序算法   | 平均时间复杂度 | 最坏时间复杂度 | 空间复杂度 | 是否稳定 |
| :----------: | :------------: | :------------: | :--------: | :------: |
|   冒泡排序   |    $O(n^2)$    |    $O(n^2)$    |   $O(1)$   |    是    |
|   选择排序   |    $O(n^2)$    |    $O(n^2)$    |   $O(1)$   |   不是   |
| 直接插入排序 |    $O(n^2)$    |    $O(n^2)$    |   $O(1)$   |    是    |
|   归并排序   |   $O(nlogn)$   |   $O(nlogn)$   |   $O(n)$   |   是·    |
|   快速排序   |   $O(nlogn)$   |    $O(n^2)$    | $O(logn)$  |   不是   |
|    堆排序    |   $O(nlogn)$   |   $O(nlogn)$   |   $O(1)$   |   不是   |
|   希尔排序   |   $O(nlogn)$   |    $O(n^2)$    |   $O(1)$   |   不是   |
|   计数排序   |    $O(n+k)$    |    $O(n+k)$    |  $O(n+k)$  |    是    |
|   基数排序   |    $O(N*M)$    |    $O(N*M)$    |   $O(M)$   |    是    |

## 4. 应用

### 1）基数排序

**基数排序**（radix sort）属于“分配式排序”（distribution sort），又称“桶子法”（bucket sort），它是通过键值的部分，将要排序的元素分配至某些“桶”中，以达到排序的作用。基数排序法是属于稳定性的排序，其时间复杂度为 $O(nlog_rm)$ 。

**思想**：将所有的待比较数值统一设置为同样的数位长度，位数比较短的数前面补零，然后从最低位开始依次进行依次排序，这样从最低位排序一直到最高位排序完成以后，数列就变成一个有序序列。

以下代码只能排序三位数以内的数字，较为简单，主要是理解基数排序的原理：

```java
package sort;

import java.util.Arrays;

public class RadixSort {
    public static void main(String[] args) {
        int[] array = {23, 4, 54, 76, 345, 64, 244, 9, 78, 55, 34};
        System.out.println("排序前：" + Arrays.toString(array));
        radixSort(array);
        System.out.println("排序后：" + Arrays.toString(array));
    }
    public static void radixSort(int[] array) {
        int[][] bucket = new int[array.length][array.length];
        int[] aid = new int[array.length];
        // 比较个位数
        // 先按个位数放入桶内
        for (int i = 0; i < array.length; i++) {
            int j = array[i] % 10;
            bucket[j][aid[j]++] = array[i];
        }
        // 再取出来
        int idx = 0;
        for (int i = 0; i < aid.length; i++) {
            if (aid[i] != 0) {
                int j = 0;
                for ( ; j < aid[i]; j++)
                    array[idx++] = bucket[i][j];
                aid[i] = 0;
            }
        }
        System.out.println("array: " + Arrays.toString(array));  
        // array: [23, 4, 54, 64, 244, 34, 345, 55, 76, 78, 9]
        
        // 比较十位数
        // 先按十位放入桶内
        for (int i = 0; i < array.length; i++) {
            int j = array[i] / 10 % 10;
            bucket[j][aid[j]++] = array[i];
        }
        // 再取出来
        idx = 0;
        for (int i = 0; i < aid.length; i++) {
            if (aid[i] != 0) {
                int j = 0;
                for ( ; j < aid[i]; j++)
                    array[idx++] = bucket[i][j];
                aid[i] = 0;
            }
        }
        System.out.println("array: " + Arrays.toString(array));  
        // array: [4, 9, 23, 34, 244, 345, 54, 55, 64, 76, 78]
        
        // 比较百位
        // 先按百位放入桶内
        for (int i = 0; i < array.length; i++) {
            int j = array[i] / 100;
            bucket[j][aid[j]++] = array[i];
        }
        // 再取出来
        idx = 0;
        for (int i = 0; i < aid.length; i++) {
            if (aid[i] != 0) {
                for ( int j = 0; j < aid[i]; j++)
                    array[idx++] = bucket[i][j];
                aid[i] = 0;
            }
        }
        System.out.println("array: " + Arrays.toString(array));  
        // array: [4, 9, 23, 34, 54, 55, 64, 76, 78, 244, 345]
    }

}
```

### 2）冒泡排序

**思想：**通过对 待排序序列从前往后依次比较相邻元素值，若发现逆序则交换，使较大的元素从前往后逐步移向后面，就像水中气泡，从底冒起来。

代码

```java
package sort;

import java.util.Arrays;

public class BubblingSort {
    public static void main(String[] args) {
        int[] arr = {5, 4, 3, 6, 2, 1};
        for (int i = 0; i < arr.length-1; i++) {
            for (int j = 0; j < arr.length-i-1; j++) {
                if (arr[j] > arr[j+1]) {
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
        System.out.println(Arrays.toString(arr));
    }
}
```

### 3）快速排序

**快速排序**是冒泡排序的一种改进。通过一趟排序将要排序的数据分割成独立的两部分，其中一部分的所有数据都比另一部分所有的数据要小，然后再按此方法对这两部分数据分别进行快速排序，整个排序过程可以递归进行，以此达到整个数据变成有序序列。

代码，没太搞懂：

```java
package sort;

import java.util.Arrays;

public class QuickSort {
    public static void main(String[] args) {
        int[] arr = {2, 3, 6, 3, 8, 9, 5, 7, 1};
        sort(arr, 0, arr.length-1);
        System.out.println(Arrays.toString(arr));
    }
    public static void sort(int[] arr, int left, int right) {
        int l = left;
        int r = right;
        int m = (l+r) / 2;
        int pivot = arr[m];
        while (l < r) {
            while (arr[l] < pivot) {
                l++;
            }
            while (arr[r] > pivot) {
                r--;
            }
            if (l >= r)
                break;
            int temp = arr[l];
            arr[l] = arr[r];
            arr[r] = temp;
            if (arr[l] == pivot)
                r--;
            if (arr[r] == pivot)
                l++;
        }
        if (r == l) {
            l++;
            r--;
        }
        if (left < r)
            sort(arr, left, r);
        if (right > l)
            sort(arr, l, right);
    }
}
```

### 3）插入排序

**插入排序**属于内部排序，是对于排序的元素以插入的方式寻找该元素的适当位置，以达到排序的目的。

## 5. 练习

# 八、查询

## 1. 概念

## 2. 特点

## 3. 性质

## 4. 应用

## 5. 练习

# 九、哈希表

## 1. 概念

## 2. 特点

## 3. 性质

## 4. 应用

## 5. 练习

# 十、树

## 1. 概念

## 2. 特点

## 3. 性质

## 4. 应用

## 5. 练习

# 十一、树的应用

## 1. 概念

## 2. 特点

## 3. 性质

## 4. 应用

## 5. 练习

# 十二、多路查找树

## 1. 概念

## 2. 特点

## 3. 性质

## 4. 应用

## 5. 练习

# 十三、图

## 1. 概念

## 2. 特点

## 3. 性质

## 4. 应用

## 5. 练习

# 十四、常用算法



**学完以后，模板化，规范化，画图说明**

## 1. 概念

## 2. 特点

## 3. 性质

## 4. 应用

## 5. 练习

