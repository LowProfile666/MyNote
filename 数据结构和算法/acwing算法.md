# 1. 基础算法

## 排序

### 快速排序

基于分治。

**步骤**：

+ 确定分界点：数组头、数组尾、数组中间、随机
+ 调整区间：保证分界点左边的数都小于等于分界点，分界点右边的数都大于等于分界点
+ 递归处理左右两端

**具体实现：**

在数组中选择一个数作为分界点（基准数），一般选择数组中间位置的数（位置随机都行），然后定义两个下标指针，分别指向数组的两端外，因为每次交换后两指针都应该往中间移动一步，并且可以准确的包含边界，所以这种写法配合 do while 循环更方便；

再遍历判断左指针指向的比分界点大或等的数，右指针指向的比分界点小或等的数，然后将左右两指针指向的数进行交换，就保证了小于等于分界点的数在左边，大于等于分界点的数在右边。

最后再递归左边部分数组，再递归右边部分数组。在递归左右部分时，它们的边界确定需要注意，不论是通过左指针还是右指针来确定边界，都是可以的，因为左指针和右指针限定的区域其实是对称的，但是对应的分界点不一样，需要考虑。

**代码模板**

C语言代码

```c
void quickSort(int q[], int l, int r) {
    if (l >= r)	return;
    int i = l-1, j = r+1, pivot = q[l+r>>1];
    while (i < j) {
        do ++i; while (q[i] < pivot);
        do --j; while (q[j] > pivot);
        if (i < j) {
            int t = q[i];
            q[i] = q[j];
            q[j] = t;
        }
    }
    quickSort(q, l, j);
    quickSort(q, j+1, r);
}
```

Java语言代码

```java
public void quickSort(int[] q, int l, int r) {
	if (l >= r)	return;
    int i = l-1, j = r+1, pivot = q[l+r>>1];  // （1）
    while (i < j) {
        do ++i; while (q[i] < pivot);
        do --j; while (q[j] > pivot);
        if (i < j) {
            int t = q[i];
            q[i] = q[j];
            q[j] = t;
        }
    }
    quickSort(q, l, j);						  // （2）
    quickSort(q, j+1, r);
}
```

（1）：定义左右指针，以及分界点，这里的分界点是数组中央的数

（2）：递归处理左部分，这里是用的右指针 j ，也可以用左指针 i ：`quickSort(q, l, i-1), quickSort(q, i, r)` ，但是需要注意边界问题：

+ 使用`quickSort(q, l, i-1), quickSort(q, i, r)` 这种写法时，注意分界点不能取到数组的最左边的数，分界点这里就应该改成这样：`pivot = q[l+r+1>>1]` ，这样保证取不到最左边的值（`q[l]`），否则的话会一直递归下去。
+ 同理，当使用 `quickSort(q, l, j), quickSort(q, j+1, r)` 时，也要注意分界点不能取到数组最右边的值（`q[r]`），所以分界点这样写就可以了：`pivot = q[l+r>>2]`。

以上边界问题，可以使用示例 `[1, 2]` 来模拟。

**题目练习**

| 序号 |                        题目链接                         |       备注       |
| :--: | :-----------------------------------------------------: | :--------------: |
|  1   | [快速排序](https://www.acwing.com/problem/content/787/) | 快速排序的模板题 |
|  2   | [第k个数](https://www.acwing.com/problem/content/788/)  |                  |

### 归并排序

基于分治。异于快速排序，快速排序是用一个数来将数组分为两部分，这个分界点随机；归并排序是用数组中间位置的数来分界，这个分界点是固定的。

**步骤：**

+ 确定分界点：数组中间位置
+ 递归排序左边和右边
+ 归并——合二为一

**具体实现：**

先确定出分界点，也就是数组的中间位置，然后直接进行递归左右两部分；再使用一个辅助数组，用来临时存储排好序的元素。

用双指针对两部分的元素进行比较，将较小的放入辅助数组，直到比较完其中一个部分，然后将另一个没有比较完的部分剩余的所有没比较的数都放入辅助数组，这时辅助数组里已经是排好序的一段序列了。这样其实就完成了归并。

再将辅助数组中的元素挨个赋值到原来的数组中。

**代码模板**

C语言代码

```c
void mergeSort(int q[], int l, int r) {
    if (l >= r)	return;
    int m = l + (r-l>>1);					// (1)
    mergeSort(q, l, m);						// (2)
    mergeSort(q, m+1, r);
    int temp[r-l+1];						// (3)
    int top = 0;
    int i = l, j = m+1;						// (4)
    while (i <= m && j <= r) {				// (5)
        if (q[i] < q[j])
            temp[top++] = q[i++];
        else
            temp[top++] = q[j++];
    }
    while (i <= m)	temp[top++] = q[i++];	// (6)
    while (j <= r)	temp[top++] = q[j++];
    for (i = l, j = 0; i <= r; i++, j++)	// (7)
        q[i] = temp[j];
}
```

Java语言代码

```java
public void mergeSort(int[] q, int l, int r) {
    if (l >= r)	return;
    int m = l + (r-l>>1);					// (1)
    mergeSort(q, l, m);						// (2)
    mergeSort(q, m+1, r);
    int temp = new int[r-l+1];				// (3)
    int top = 0;
    int i = l, j = m+1;						// (4)
    while (i <= m && j <= r) {				// (5)
        if (q[i] < q[j])
            temp[top++] = q[i++];
        else
            temp[top++] = q[j++];
    }
    while (i <= m)	temp[top++] = q[i++];	// (6)
    while (j <= r)	temp[top++] = q[j++];
    for (i = l, j = 0; i <= r; i++, j++) {  // (7)
        q[i] = temp[j];
    }	
}
```

（1）：确定数组的中间位置，就是分界点

（2）：递归左右两部分

（3）：创建一个辅助数组，用来存放当前 【l，r】区间的元素，并不是原数组全部的元素

（4）：定义两个指针，i 指针指向左边部分的元素，j 指针指向右边部分的元素

（5）：遍历左右两部分的元素，直到遍历完一部分为止

（6）：将没有遍历完的部分的元素全部放入辅助数组，完成归并

（7）：将排好序的数组放入原数组中

**题目练习**

| 序号 |                           题目链接                           |       备注       |
| :--: | :----------------------------------------------------------: | :--------------: |
|  1   | [归并排序](https://www.acwing.com/problem/content/description/789/) | 归并排序的模板题 |
|  2   | [逆序对的数量](https://www.acwing.com/problem/content/790/)  |     没做出来     |

 

## 二分

### 整数二分

有单调性一定可以二分，二分不一定需要单调性。

二分的本质是查找边界。

二分分为三种情况：

+ 查找某个特定值的下标
+ 查找满足性质（大于等于某个值）的起始下标
+ 查找满足性质（小于等于某个值）的终止下标

步骤：

+ 找中间值 q[mid] 。
+ 判断中间值是否满足性质
+ 更新边界

**第一种情况**

最基本的情况，在一个有序的列表中，查找一个指定值的下标。

以单调递增的序列为例，每次取一个中间值来与目标值进行比较，因为列表是有序的，所以如果中间值大于目标值的话，那说明目标值应该在中间值的左边部分，然后把搜索范围缩小；如果中间值小于目标值，那说明目标值应该在中间值的右边，然后把搜索范围缩小。

Java代码

```java
public int bianrySerach(int[] nums, int target) {
	int l = 0, r = nums.length-1;  // (0)
    while (l <= r) {  // (1)
		int m = l + r >> 1;
        if (nums[m] > target)
            r = m-1;
        else if (nums[m] < target)
            l = m+1;
        else
            return m;
    }
    return -1;
}
```

（0）：这里需要注意 r 的取值

+ r = nums.length-1：r 的位置是有效的，那么下面的（1）处应该是 l <= r，因为 r 的位置能取到。
+ r = nums.length ：r 的位置是无效的，那么下面的（1）处应该是 l < r ，因为 r 的位置取不到。

**后两种情况**

用图说明后两种情况：

![image-20230525093003566](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230525093003566.png)

1. 要二分出红色的右边界
   + 先算出一个中间值下标 mid = l + r +1 >> 1（注意：这里 +1 是为了防止下一步 l = mid 引起死循环。因为如果 l = r-1 时，mid 初始就为 l， 然后 l 更新就还是 l）
   + 判断 mid 是否满足这红色的性质
     + 如果满足：那么答案在 [mid, r] 之间，mid 可能会是答案，要更新 l = mid
     + 如果不满足：那么答案在 [l, mid-1] 之间，mid 不可能会是答案，要更新 r = mid - 1
2. 要二分出蓝色的边界
   + 先算出一个中间值下标 mid = l + r >> 1（因为这里不会导致以下操作产生死循环，所以不用 +1，这如果 +1 可能会让r=mid 产生死循环）
   + 判断 mid 是否满足这蓝色的性质
     + 如果满足：那么答案在 [l, mid] 之间，mid 可能会是答案，要更新 r = mid
     + 如果不满足：那么答案在 [mid+1, r] 之间，mid 不可能会是答案，要更新 l = mid + 1

对于这后面两种情况，有代码模板：

Java代码

```java
bool check(int x) {/* ... */} // 检查x是否满足某种性质

// 区间[l, r]被划分成[l, mid]和[mid + 1, r]时使用：
public int binarySerach1(int l, int r) {
    while (l < r) {
        int m = l + r >> 1;
        if (check(mid))  // (1)
            r = mid;
        else 
            l = mid + 1;
    }
    return l;
}

// 区间[l, r]被划分成[l, mid - 1]和[mid, r]时使用：
public int binarySerach2(int l, int r) {
    while (l < r) {
        int m = l + r + 1 >> 1;
        if (check(mid))
            l = mid;
        else 
            r = mid - 1;
    }
    return l;
}
```

（1）：check() 是用来判断 mid 是否满足性质的

**题目练习**

| 序号 | 题目链接                                                | 备注 |
| ---- | ------------------------------------------------------- | ---- |
| 1    | [数的范围](https://www.acwing.com/problem/content/791/) |      |

### 浮点数二分

没有整除，所以每次可以严格的缩小一半，不需要处理边界，每次保证答案在区间内，当区间的长度很小时（一般认为小于 1e-6），认为区间的两边界已经重合了。

Java 代码模板

```java
bool check(int x) {/* ... */} // 检查x是否满足某种性质

public double binarySerach3(double l, double e) {
    double eps = 1e-6;
    while (r - l > eps) {
        double m = l + (r-l) / 2;
        if (check(m))
            r = m;
        else
            l = m;
    }
    return l;
}
```

eps：假如结果保留 6 位，那么 eps 一般为 1e-8，结果保留 4 位，那么 eps 一般为 1e-6。

| 序号 | 题目链接                                                     | 备注 |
| ---- | ------------------------------------------------------------ | ---- |
| 1    | [数的三次方根](https://www.acwing.com/problem/content/description/792/) |      |

## 高精度

Java 中有大整数类，python 中的数字默认就是无限大。

一般有四种情况：

+ A + B：两个大整数相加
+ A - B：两个大整数相减
+ A $\times$ b：一个大整数乘上一个小整数
+ A $\div$ b：一个大整数除以一个小整数

一般 A 和 B 的位数是 10^6^ ，a 和 b 的大小值小于等于 10000。

### 大整数的存储

在这种情况下，基本的数据类型是不可能存储下这么大的数的，所以一般使用数组来进行存储。在存储的时候，是大整数的低位在前，高位在后。这样存储的话就方便进行进位的操作。

### 加法

用代码模拟竖式加法。

```
  A3 A2 A1 A0
+    B2 B1 B0
--------------
  C3 C2 C1 C0
```

将两个大整数的每一位对应相加，同时要加上当前位的进位：

+ $A_i+B_i+t \geqslant 10$：保留除以 10 的余数 $(A_i+B_i+t) \% 10$ ，向前进 1： $t=1$ 。
+ $A_i+B_i+t < 10$：保留当前和，$t=0$ 。

如果有数的最高位没有数，就当作 0 来计算。比如：1234 + 234 ==> 1234 + 0234

```
  1234
+ 0234
-------
  1468
```

Java代码模板

```java
// C = A + B, A >= 0, B >= 0
public int[] add(int[] a, int[] b) {
    if (b.length > a.length)  // (1)
        return add(b, a);
    int[] c = new int[a.length+1];
    int t = 0, top = 0;  // (2)
    for (int i = 0; i < a.length; i++) {
        t += a[i];  
        if (i < b.length)   t += b[i];  // (3)
        c[top++] = t % 10;
        t /= 10;
    }
    if (t != 0)  // (4)
        c[top] = 1;
    return c;
}
```

（1）：长度大的数组表示的数更大，保证 a 的长度是大于等于 b 的

（2）：t 是进位

（3）：因为是以 a 的长度来遍历的，所以需要判断 b 的长度，而不用判断 a。

（4）：最高位产生进位

| 题目链接                                                  | 备注 |
| --------------------------------------------------------- | ---- |
| [高精度加法](https://www.acwing.com/problem/content/793/) |      |

**题目描述**

> 给定两个正整数（不含前导 00），计算它们的和。
>
> #### 输入格式
>
> 共两行，每行包含一个整数。
>
> #### 输出格式
>
> 共一行，包含所求的和。
>
> #### 数据范围
>
> 1≤整数长度≤100000

**Java代码**

```java
import java.util.*;

public class Main{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        char[] a = sc.next().toCharArray();
        char[] b = sc.next().toCharArray();
        int[] A = new int[a.length];
        int[] B = new int[b.length];
        
        for (int i = a.length-1, j = 0; i >= 0; --i, ++j)
            A[j] = a[i]-'0';
            
        for (int i = b.length-1, j = 0; i >= 0; --i, ++j)
            B[j] = b[i]-'0';
            
        int[] C = add(A, B);
        
        int i = C.length-1;
        while (C[i] == 0)  --i;
        for ( ; i >= 0; --i)
            System.out.print(C[i]);
    }
    public static int[] add(int[] a, int[] b) {
        if (b.length > a.length)
            return add(b, a);
        int[] c = new int[a.length+1];
        int t = 0, top = 0;
        for (int i = 0; i < a.length; i++) {
            t += a[i];
            if (i < b.length)   t += b[i];
            c[top++] = t % 10;
            t /= 10;
        }
        if (t != 0)
            c[top] = t;
        return c;
    }
}
```

### 减法

用代码模拟竖式减法。

```
  A3 A2 A1 A0
-    B2 B1 B0
--------------
  C3 C2 C1 C0  
```

将两个大整数的每一位对应相减，同时要减去当前位的借位，假设借位 t ：

+ $A_i-B_i-t \geqslant 0$ ：保留当前值，$t=0$ 。
+ $A_i-B_i-t < 0$ ：需要向前借位 $t=1$ ，保留加 10 的值：$A_i+10-B_i-t$ 。

如果有数的最高位没有数，就当作 0 来计算。

为了方便计算并且贴近人们习惯，在运算减法之前先判断以下 A 和 B 的大小，保证 A 的是大于等于 B 的。

Java代码模板

```java
// C = A - B，满足A >= B, A >= 0, B >= 0
public int[] sub(int[] a, int[] b) {
    int[] c = new int[a.length+1];
    int top = 0;
    for (int i = 0, t = 0; i < a.length; i++) {  // (1)
        t = a[i] - t;
        if (i < b.length)   t -= b[i];
        c[top++] = (t+10) % 10;  // (2)
        if (t < 0) t = 1;  // (3)
        else t = 0;
    }
    return c;
}
```

（1）：t 是借位，同时用 t 表示当前位的差

（2）：当前位的差 t 有两种情况（大于等于 0 或小于 0）

+ $t \geqslant 0$ ：$(t+10)\%10=t\%10+10\%10$ 
+ $t< 0$ ：$(t+10)\%10$  

（3）：$t<0$ 说明需要借位

| 题目链接                                                  | 备注 |
| --------------------------------------------------------- | ---- |
| [高精度减法](https://www.acwing.com/problem/content/794/) |      |

**题目描述**

> 给定两个正整数（不含前导 00），计算它们的差，计算结果可能为负数。
>
> #### 输入格式
>
> 共两行，每行包含一个整数。
>
> #### 输出格式
>
> 共一行，包含所求的差。
>
> #### 数据范围
>
> 1≤整数长度≤10^5^

**Java代码**

```java
import java.util.*;

public class Main{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        char[] a = sc.next().toCharArray();
        char[] b = sc.next().toCharArray();
        int[] A = new int[a.length];
        int[] B = new int[b.length];

        for (int i = a.length-1, j = 0; i >= 0; --i, ++j)
            A[j] = a[i]-'0';

        for (int i = b.length-1, j = 0; i >= 0; --i, ++j)
            B[j] = b[i]-'0';

        int[] C;
        if (cmp(a, b)){
            C = sub(A, B);
        }
        else {
            C = sub(B, A);
            System.out.print("-");
        }
        int top = C.length-1;
        while (top > 0 && C[top] == 0)  --top;
        while (top >= 0)    System.out.print(C[top--]);
    }
    public static boolean cmp(char[] a, char[] b) {
        if (a.length != b.length)
            return a.length > b.length;
        for (int i = 0; i < a.length; i++)
            if (a[i] != b[i])
                return a[i] > b[i];
        return true;
    }
    public static int[] sub(int[] a, int[] b) {
        int[] c = new int[a.length+1];
        int top = 0;
        for (int i = 0, t = 0; i < a.length; i++) {
            t = a[i] - t;
            if (i < b.length)   t -= b[i];
            c[top++] = (t+10) % 10;
            if (t < 0) t = 1;
            else t = 0;
        }
        return c;
    }
}
```

### 乘法

用代码模拟乘法。

```
  A3 A2 A1 A0
x           b
--------------
  C3 C2 C1 C0  
```

但是这里的乘法和正常的竖式乘法有些不一样，在这里我们是用 A 的每一位值去乘以 b 整个数

+ 保留值：$(A_i \times b) \% 10$  
+ 进位值：$(A_i \times b) \div 10$   

Java代码模板

```java
// C = A * b
public int[] mul(int[] a, int b) {
    int[] c = new int[a.length+1];
    int t = 0, top = 0;
    for (int i = 0; i < a.length; i++) {
        t += a[i] * b;
        c[top++] = t % 10;
        t /= 10;
    }
    if (t != 0)
        c[top] = t;
    return c;
}
```

| 题目链接                                                     | 备注 |
| ------------------------------------------------------------ | ---- |
| [高精度乘法](https://www.acwing.com/problem/content/description/795/) |      |

**题目描述**

> 给定两个非负整数（不含前导 00） A 和 B，请你计算 A×B 的值。
>
> #### 输入格式
>
> 共两行，第一行包含整数 A，第二行包含整数 B。
>
> #### 输出格式
>
> 共一行，包含 A×B 的值。
>
> #### 数据范围
>
> 1≤A的长度≤100000
> 0≤B≤10000

**Java代码**

```java
import java.util.*;

public class Main{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        char[] a = sc.next().toCharArray();
        int b = sc.nextInt();
        
        List<Integer> A = new ArrayList<>();
        for (int i = a.length-1; i >= 0; i--) {
            A.add(a[i]-'0');
        }
        
        List<Integer> C = mul(A, b);
        for (int i = C.size()-1; i > 0; i--){
            if (C.get(i) != 0)
                break;
            C.remove(i);
        }
        for (int i = C.size()-1; i >= 0 ; i--) {
            System.out.print(C.get(i));
        }    
    }
    public static List<Integer> mul(List<Integer> a, int b) {
        List<Integer> c = new ArrayList<>();
        int t = 0;
        for (int i = 0; i < a.size(); i++) {
            t += a.get(i) * b;
            c.add(t % 10);
            t /= 10;
        }
        if (t != 0)
            c.add(t);
        return c;
    }
} 
```

### 除法

用代码模拟除法。

```
    C3 C2 C1 C0
  --------------
b | A3 A2 A1 A0         
  --------------
    r3 A2
    ------------
       r2 A1
       ---------
  		  r1 A0
  		  -----
  		     r0
```

除法和前面的有一点不一样，其他三个运算都是从低位开始的，但是除法是从高位开始计算的，所以理论上来讲存储大数据时应该从高位往低位存储，但是为了和其他运算统一，且一般都是四则运算混合运算，所以除法依旧使用从低位到高位的存储方法。

A 表示被除数，b 表示除数，C 表示商，r 表示余数。模拟除法可得：

+ $r=r*10+A_i$ 
+ $C_i=r\div b$ 
+ $r=r\%b$ 

Java代码模板

因为方便操作，除法就使用 List 集合来代替数组操作，其他三则运算都可以使用 List 集合来代替数组。

```java
// A / b = C ... r, A >= 0, b > 0
int r = 0;
public List<Integer> div(List<Integer> a, int b) {
    List<Integer> c = new ArrayList<>();
    r = 0;
    for (int i = a.size()-1; i >= 0; i--) {
        r = r * 10 + a.get(i);
        c.add(r/b);
        r %= b;
    }
    // （1）
    List<Integer> C = new ArrayList<>();
    for (int i = c.size()-1; i >= 0; i--) 
        C.add(c.get(i));
    // （2）
    for (int i = C.size()-1; i > 0; i--){
        if (C.get(i) != 0)
            break;
        C.remove(i);
    }
    return C;
}
```

（1）：将结果逆序

（2）：去除前导零

其实除法这里不需要进行逆序，因为计算时就是从高位开始计算的，保存的结果也是从高到低的，刚好就是正常的顺序，但是和存储一样，高精度运算一般都是四则混合运算，而其他运算后的结果是正常结果的逆序，所以为了方便操作，也将除法的结果进行逆序，这样返回后主函数里的输出操作就保持了一致。

如果不逆序的话可以这样写：

```java
// A / b = C ... r, A >= 0, b > 0
int r = 0;
public List<Integer> div(List<Integer> a, int b) {
    List<Integer> c = new ArrayList<>();
    r = 0;
    for (int i = a.size()-1; i >= 0; i--) {
        r = r * 10 + a.get(i);
        c.add(r/b);
        r %= b;
    }
    for (int i = 0; i < c.size()-1; ){  // (1)
        if (c.get(i) != 0)
            break;
        c.remove(i);
    }
    /*
    while (c.size() > 1 && c.get(0) == 0)
            c.remove(0);
	*/
    return c;
}
```

（1）：`remove(int index)` 方法会将被删除的位置右边的数据向左移，会改变 List 的长度，比如：

```
list : 0 3 6 4
index: 0 1 2 3
删除第一个数 0 后：
list : 3 6 4
index: 0 1 2
```

所以这里不用改变 i 的值。这一部分也可以换成注释中的写法：

```java
while (c.size() > 1 && c.get(0) == 0)
    c.remove(0);
```

| 题目链接                                                     | 备注 |
| ------------------------------------------------------------ | ---- |
| [高精度除法](https://www.acwing.com/problem/content/description/796/) |      |

**题目描述**

> 给定两个非负整数（不含前导 00） A，B，请你计算 A/B 的商和余数。
>
> #### 输入格式
>
> 共两行，第一行包含整数 A，第二行包含整数 B。
>
> #### 输出格式
>
> 共两行，第一行输出所求的商，第二行输出所求余数。
>
> #### 数据范围
>
> 1≤A的长度≤100000
> 1≤B≤10000
> B 一定不为 0

**Java代码**

```java
import java.util.*;

public class Main{
    static int r = 0;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        char[] a = sc.next().toCharArray();
        int b = sc.nextInt();
        
        List<Integer> A = new ArrayList<>();
        for (int i = a.length-1; i >= 0; i--) {
            A.add(a[i]-'0');
        }
        
        List<Integer> C = div(A, b);
        for (int i = 0; i < C.size() ; i++) {
            System.out.print(C.get(i));
        }
        System.out.println();
        System.out.println(r);
    }
    public static List<Integer> div(List<Integer> a, int b) {
        List<Integer> c = new ArrayList<>();
        r = 0;
        for (int i = a.size()-1; i >= 0; i--) {
            r = r * 10 + a.get(i);
            c.add(r/b);
            r %= b;
        }
        while (c.size() > 1 && c.get(0) == 0)
            c.remove(0);
        return c;
    }
} 
```



## 前缀和和差分

### 前缀和

#### 一维前缀和

有一个数组 A：{a1, a2, a3, ..., ai, ..., an}，前缀和就是：

$S_i=a_1+a_2+a_3+...+a_i$ 

作用：快速的求出原数组总一段数据的和

前缀和中的下标一般是从 1 开始，因为这样可以定义出一个 $S_0=0$ 来，这样会方便计算。

比如，计算区间 [l, r] 之间的元素和时，可以用 $S_r-S_{l-1}$ 的公式来计算：

+ $S_r=a_1+a_2+....+a_{l-1}+a_l+...+a_r$ 
+ $S_{l-1}=a_1+a_2+....+a_{l-1}$ 

计算区间 [1, r] 之间的元素和时，也可以使用 $S_r-S_{l-1}$ 该公式来计算，因为有个 $S_0=0$ 存在，所以可以少掉一些麻烦的边界问题。

Java代码模板

```java
// S[i] = a[1] + a[2] + ... a[i]
// a[l] + ... + a[r] = S[r] - S[l - 1]
// 构造前缀和数组：
int[] S = new int[n+1];
for (int i = 1; i <= n; i++) {
    S[i] = A[i] + S[i-1];
}
```

| 题目链接                                              | 备注 |
| ----------------------------------------------------- | ---- |
| [前缀和](https://www.acwing.com/problem/content/797/) |      |

**题目描述**

> 输入一个长度为 n 的整数序列。
>
> 接下来再输入 m 个询问，每个询问输入一对 l,r。
>
> 对于每个询问，输出原序列中从第 l 个数到第 r 个数的和。

**Java代码**

```java
import java.util.*;
public class Main{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        
        int[] nums = new int[n+1];
        nums[0] = 0;
        for (int i = 1; i <= n; i++) {
            nums[i] = sc.nextInt();
        }
        
        int[] sum = new int[n+1];
        for (int i = 1; i <= n; i++) {
            sum[i] = nums[i] + sum[i-1];
        }
        
        while (m-- != 0) {
            int l = sc.nextInt();
            int r = sc.nextInt();
            System.out.println(sum[r] - sum[l-1]);
        }
    }
}
```



#### 二维前缀和

作用：计算子矩阵的元素之和。

有一个二维数组，用 $S_{ij}$ 表示下标 (i, j) 到左上角 (0, 0) 的子矩阵的和，如图：

![image-20230623232720690](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230623232720690.png)

以 (x1, y1) 为左上角，(x2, y2) 为右下角的矩阵和如图：

![image-20230625183230201](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230625183230201.png)

那这一子矩阵的和就表示为：$S_{x2y2}-S_{x2(y1-1)}-S_{(x1-1)y2}+S_{(x1-1)(y1-1)}$ ，如图，

![image-20230625184138831](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230625184138831.png)

这里涉及到容斥原理，因为 $S_{(x1-1)(y1-1)} $ 被减去了两次，所以最后要加回来一次。

那么每个格子的前缀和 $S_{ij}$ 应该怎么求呢？

![image-20230625185001198](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230625185001198.png)

如图，$S_{ij}$ 应该由 $S_{i(j-1)}$ 加 $S_{(i-1)j}$ 且减去 $S_{(i-1)(j-1)}$ 值，再加上 (i, j) 本身的值，即：

$S_{ij}=S_{i(j-1)}+S_{(i-1)j}-S_{(i-1)(j-1)}+a_{ij}$ 

Java代码模板

```java
// S[i, j] = 第i行j列格子左上部分所有元素的和
// 以(x1, y1)为左上角，(x2, y2)为右下角的子矩阵的和为：
// 		S[x2, y2] - S[x1 - 1, y2] - S[x2, y1 - 1] + S[x1 - 1, y1 - 1]
// 构建前缀和数组：
int[][] s = new int[n+1][m+1];
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        s[i][j] = s[i][j-1] + s[i-1][j] - s[i-1][j-1] + mat[i][j];
    }
}
```

| 题目链接                                                     | 备注 |
| ------------------------------------------------------------ | ---- |
| [子矩阵的和](https://www.acwing.com/problem/content/description/798/) |      |

**题目描述**

> . 输入一个 n 行 m 列的整数矩阵，再输入 q 个询问，每个询问包含四个整数 x1,y1,x2,y2，表示一个子矩阵的左上角坐标和右下角坐标。
>
> 对于每个询问输出子矩阵中所有数的和。

**Java代码**

```java
import java.util.*;
public class Main{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        int q = sc.nextInt();
        int[][] mat = new int[n+1][m+1];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                mat[i][j] = sc.nextInt();
            }
        }
        int[][] s = new int[n+1][m+1];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                s[i][j] = s[i][j-1] + s[i-1][j] - s[i-1][j-1] + mat[i][j];
            }
        }
        while (q-- != 0) {
            int x1 = sc.nextInt();
            int y1 = sc.nextInt();
            int x2 = sc.nextInt();
            int y2 = sc.nextInt();
            System.out.println(s[x2][y2] - s[x2][y1-1] - s[x1-1][y2] + s[x1-1][y1-1]);
        }
    }
}
```

### 差分

是前缀和的逆运算。

有一个 A 数组：a1, a2, a3, ..., an。

构造一个 B 数组：b1, b2, b3, ...., bn。

使得 A 是 B 的前缀和，也就是： ai = b1 + b2 + b3 + .... + bi；此时 B 就称为 A 的差分。

#### 一维差分

有一个整数序列 A：{a1, a2, ……, an}，有一种操作是给定一个范围 [l, r] ，将 A 中范围 [l, r] 中的数都加上 c，有多次这样的操作。

构建一个 A 的差分数组 B：{b1, b2, ……, bn}，使得 ai = b1 + b2 + …… + bi，这样的话，要想使 A 中 [l, r] 的数都加上 c，就可以操作 B 中的两个数据，然后通过 B 来创建 A，而就不用遍历 A 中 [l, r] 的所有数据。

因为 A 是 B 的前缀和，所以只要将 bl 加上一个 c，那么 al 和其之后的所有数据都会加上一个 c，这是因为：

+ al = sum(b1, bl); 
+ a(l+1) = al + b(l+1)；
+ ……

而我们只需要在 [l, r] 的范围中加 c，所以在 bl+c 之后，还需要 b(r+1)-c，这样 a(r+1) 及其之后的所有数都会再减去一个 c。

![image-20230703201349001](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230703201349001.png)

Java代码模板

```java
// 给 A 中区间 [l, r] 中的每个数加上 c：B[l] += c, B[r + 1] -= c
public void insert(int[] b, int l, int r, int c) {
    b[l] += c;
    b[r+1] -= c;
}
```



| 题目链接                                                     | 备注 |
| ------------------------------------------------------------ | ---- |
| [差分](https://www.acwing.com/problem/content/description/799/) |      |

**题目描述**

> 输入一个长度为 n 的整数序列。
>
> 接下来输入 m 个操作，每个操作包含三个整数 l,r,c，表示将序列中 [l,r] 之间的每个数加上 c。
>
> 请你输出进行完所有操作后的序列。

**Java代码**

```java
import java.util.*;

public class Main{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        int[] a = new int[n+10];  // a 数组其实也可以不用
        int[] b = new int[n+10];  // 数组开大一点可以bi'mia
        for (int i = 1; i <= n; i++) {
            a[i] = sc.nextInt();
            insert(b, i, i, a[i]);  // 构建 b 数组时其实也是一种特殊情况的插入
        }
        while (m-- != 0) {
            int l = sc.nextInt();
            int r = sc.nextInt();
            int c = sc.nextInt();
            insert(b, l, r, c);
        }
        for (int i = 1; i <= n; i++)
            b[i] += b[i-1];
        for (int i = 1; i <= n; i++)
            System.out.print(b[i] + " ");
    }
    public static void insert(int[] b, int l, int r, int c) {
        b[l] += c;
        b[r+1] -= c;
    }
}
```



#### 二维差分

有一个矩阵 Anm，有一种操作是将 A 中左上角顶点为 (x1, y1) 、右下角顶点为 (x2, y2) 的子矩阵中的每一个数都加上一个 c，有多次这样的操作。

构建一个 A 的差分矩阵 Bnm，使得 Aij = Bij + B(i-1)j + Bi(j-1) - B(i-1)(j-1)，这样想要使 A 中 (x1,y1)(x2,y2) 子矩阵所有数都加上 c，就可以通过操作 B 中四个数据即可实现，而不用再遍历子矩阵中的所有数。

将 B(x1,y1) 加上一个 c 后，以 (x1,y1) 为左上顶点、(n,m) 为右下顶点的子矩阵中的所有数都会加上 c，而我们只需要 (x1,y1)(x2,y2) 的部分加 c，所以还要 B(x2+1,y1)-c、B(x1,y2+1)-c，而因为 (x2+1,y2+1) 减去了两次 c，所以还要 B(x2+1,y2+1)+c。![image-20230703204806450](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20230703204806450.png)

Java代码模板

```java
// 给以 (x1, y1) 为左上角，(x2, y2) 为右下角的子矩阵中的所有元素加上 c：
// B[x1, y1] += c, B[x2 + 1, y1] -= c, B[x1, y2 + 1] -= c, B[x2 + 1, y2 + 1] += c
public void insert(int[][] b, int x1, int y1, int x2, int y2, int c) {
    b[x1][y1] += c;
    b[x2+1][y1] -= c;
    b[x1][y2+1] -= c;
    b[x2+1][y2+1] += c;
}
```



| 题目链接                                                     | 备注 |
| ------------------------------------------------------------ | ---- |
| [差分矩阵](https://www.acwing.com/problem/content/description/800/) |      |

**题目描述**

> 输入一个 n 行 m 列的整数矩阵，再输入 q 个操作，每个操作包含五个整数 x1,y1,x2,y2,c，其中 (x1,y1) 和 (x2,y2) 表示一个子矩阵的左上角坐标和右下角坐标。
>
> 每个操作都要将选中的子矩阵中的每个元素的值加上 c。
>
> 请你将进行完所有操作后的矩阵输出。

**Java代码**

```java
import java.util.*;

public class Main{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        int q = sc.nextInt();
        int[][] a = new int[n+10][m+10];  // 数组的长度开大一点可以不用考虑边界情况
        int[][] b = new int[n+10][m+10];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                a[i][j] = sc.nextInt();
                insert(b, i, j, i, j, a[i][j]);
            }
        }
        while (q-- != 0) {
            int x1 = sc.nextInt();
            int y1 = sc.nextInt();
            int x2 = sc.nextInt();
            int y2 = sc.nextInt();
            int c = sc.nextInt();
            insert(b, x1, y1, x2, y2, c);
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                b[i][j] += b[i-1][j] + b[i][j-1] - b[i-1][j-1];
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                System.out.print(b[i][j] + " ");
            }
            System.out.println();
        }
    }
    public static void insert(int[][] b, int x1, int y1, int x2, int y2, int c) {
        b[x1][y1] += c;
        b[x2+1][y1] -= c;
        b[x1][y2+1] -= c;
        b[x2+1][y2+1] += c;
    }
}
```

