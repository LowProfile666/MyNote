// import java.util.Scanner;

// public class Main{
//     public static void main(String[] args) {
//         Scanner sc = new Scanner(System.in);
//         int a = sc.nextInt();
//         int b = sc.nextInt();
//         System.out.println(gcd(a,b));
//     }
//     public static int gcd(int a, int b) {
//         return b == 0 ? a : gcd(b, a%b);
//     }
//     public static int lcm(int a, int b) {
//         return (a*b) / gcd(a, b);
//     }
//     // public static int lcm(int a, int b) {
//     //     int[] arr1 = new int[a+1];
//     //     int[] arr2 = new int[b+1];
//     //     int ret = 1;
//     //     decomposedPrimeFactor(arr1, a);
//     //     decomposedPrimeFactor(arr2, b);
//     //     int minLen = arr1.length > arr2.length ? arr2.length : arr1.length;
//     //     for (int i = 0; i < minLen; i++) {
//     //         int max = arr1[i] > arr2[i] ? arr1[i] : arr2[i];
//     //         while (max != 0) {
//     //             ret *= i;
//     //             max--;
//     //         }
//     //     }
//     //     if (minLen == arr1.length) {
//     //         for (int i = minLen; i < arr2.length; i++) {
//     //             while (arr2[i] != 0) {
//     //                 ret *= i;
//     //                 arr2[i]--;
//     //             }
//     //         }
//     //     }
//     //     else {
//     //         for (int i = minLen; i < arr1.length; i++) {
//     //             while (arr1[i] != 0) {
//     //                 ret *= i;
//     //                 arr1[i]--;
//     //             }
//     //         }
//     //     }
//     //     return ret;
//     // }
//     // public static int gcd(int a, int b) {
//     //     int[] arr1 = new int[a+1];  // ??0??
//     //     int[] arr2 = new int[b+1];  // ??1??
//     //     int ans = 1;
//     //     decomposedPrimeFactor(arr1, a);
//     //     decomposedPrimeFactor(arr2, b);
//     //     int minLen = arr1.length > arr2.length ? arr2.length : arr1.length;
//     //     for (int i = 2; i < minLen; i++) {
//     //         int min = arr1[i] > arr2[i] ? arr2[i] : arr1[i];
//     //         while (min != 0) {
//     //             ans *= i;
//     //             min--;
//     //         }
//     //     }
//     //     return ans;
//     // }
//     // public static void decomposedPrimeFactor(int[] primeFactors, int num) {
//     //     for (int i = 2; i <= num; i++) {
//     //         while (num != 0 && num % i == 0) {
//     //             num /= i;
//     //             primeFactors[i]++;
//     //         }
//     //     }
//     // }
// }

// import java.util.Scanner;

// public class Main{
//     public static void main(String[] args) {
//         Scanner sc = new Scanner(System.in);
//         int a = sc.nextInt();
//         int b = sc.nextInt();
//         int l = sc.nextInt();
//         int ansa = 100, ansb = 1;
//         for (int i = 1; i <= l; i++) {
//             for (int j = 1; j <= l; j++) {
//                 if (gcd(i,j) == 1) {
//                     if (i*b >= j*a) {
//                         if (i*ansb < j*ansa) {
//                             ansa = i;
//                             ansb = j;
//                         }
//                     }   
//                 }
//             }
//         }
//         System.out.println(ansa + " " + ansb);
//     }
//     public static int gcd(int a, int b) {
//         return b == 0 ? a : gcd(b, a%b);
//     }
// }

// public class Main{
//     public static void main(String[] args) {
//         for (int i = 1; i <= 3; i++) {
//             for (int j = 3-i; j > 0; j--)
//                 System.out.print(" ");
//             for (int j = 2*i-1; j > 0; j--)
//                 System.out.print("*");
//             System.out.println();
//         }
//         for (int i = 2; i >= 1; i--) {
//             for (int j = 0; j < 3-i; j++)
//                 System.out.print(" ");
//             for (int j = 0; j < 2*i-1; j++)
//                 System.out.print("*");
//             System.out.println();
//         }
//     }
// }

// import java.util.*;

// public class Main{
//     public static void main(String[] args){
//         Scanner sc = new Scanner(System.in);
//         int n = sc.nextInt();
//         List<List<Integer>> res = new ArrayList<>();
//         List<Integer> num = new ArrayList<>();
//         while (n-- != 0) {
//             List<Integer> list = new ArrayList<>();
//             int x = sc.nextInt();
//             int k = sc.nextInt();
//             if (x % k != 0) {
//                 num.add(1);
//                 list.add(x);
//                 res.add(list);
//                 continue;
//             }
//             int ans = 0;
            
//             for (int i = x; i > 1 && x > 0; i--) {
//                 if (i % k != 0) {
//                     ans++;
//                     list.add(i);
//                     if ((x-i) % k != 0) {
//                         list.add(x-i);
//                         ans++;
//                         x -= (x-i);
//                     }
//                     x -= i;
//                 }
//             }
//             num.add(ans);
//             res.add(list);
//         }
//         for (int i = 0; i < num.size(); i++) {
//             System.out.println(num.get(i));
//             for (int j = 0; j < res.get(i).size(); j++)
//                 System.out.print(res.get(i).get(j) + " ");
//             System.out.println();
//         }
//     }
// }

// import java.util.Scanner;
 
// public class Main{
//     public static void main(String[] args){
//         Scanner sc = new Scanner(System.in);
//         int n = sc.nextInt();
//         while (n-- != 0) {
//             int ans = 1, temp = 1;
//             int len = sc.nextInt();
//             String str = sc.next();
//             char[] s = str.toCharArray();
//             for (int i = 1; i < s.length; i++) {
//                 if (s[i] == s[i-1])
//                     temp++;
//                 else {
//                     ans = ans > temp ? ans : temp;
//                     temp = 1;
//                 }
//             }
//             ans = ans > temp ? ans : temp;
//             System.out.println(ans+1);
//         }
//     }
// }

// import java.util.Scanner;

// public class Main{
//     public static void main(String[] args) {
//         Scanner sc = new Scanner(System.in);
//         int T = sc.nextInt();
//         while (T-- != 0) {
//             int n = sc.nextInt();
//             int k = sc.nextInt();
//             int[] res = {-1, -1};
//             boolean ok = false;
//             for (int x = 0; x <= n; x++) {
//                 for (int y = 1; y <= n; y++) {
//                     if (x + y == k) {
//                         if ((n & x) % y == k) {
//                             res[0] = x;
//                             res[1] = y;
//                             ok = true;
//                             break;
//                         }
//                     }
//                 }
//                 if (ok)
//                     break;
//             }
//             if (ok)
//                 System.out.println(res[0] + " " + res[1]);
//             else
//                 System.out.println(res[0]);
//         }
//     }
// }

// public class Main{
//     public static void main(String[] args) {
//         System.out.println(toDecimal(134, 16));
//     }
//     public static int toDecimal(int num, int x) {
//         int res = 0;
//         int t = 1;
//         while (num != 0) {
//             res += num % x * t;
//             num /= x;
//             t *= x;
//         }
//         return res;
//     }
// }

// public class Main{
//     public static void main(String[] args) {
//         String s1 = "abcdef";
//         String s2 = "abcd";
//         System.out.println(s1.compareTo(s2));
//     }
// }

// public class Main{
//     public static void main(String[] args) {
//         double d = (22.99-16.00) / (11-8);
//         double a1 = 16.00 - 8*d;
//         for (int i = 1; i <= 36; i++) {
//             System.out.printf("%.2f ", a1+i*d);
//         }
//     }
// }
// public class Main{
//     public static void main(String[] args) {
//         int[] cnt = new int[26];
//         String s = "abcdefgj";
//         for (int i = 0; i < s.length(); i++) {
//             cnt[s.charAt(i)-'a']++;
//         }
//         for (int i = 0; i < 26; i++) {
//             System.out.println((char)('a'+i) + " " + cnt[i]);
//         }
//     }
// }

// import java.util.*;
// public class Main{
//     public static void main(String[] args) {
//         // String s = "abcdef";
//         // s = reverse(s.toCharArray());
//         // System.out.println(s);
//         // StringBuilder sb1 = new StringBuilder("abcdef");
//         // System.out.println(sb1.reverse().toString());
//         // StringBuffer sb2 = new StringBuffer("abcdef");
//         // System.out.println(sb2.reverse().toString());
//         // System.out.println(-2147483648 % 10);

//         reverseWords("  hello world!  ");

//     }
//     public static String reverseWords(String s) {
//         if (s.equals(""))
//             return s;
//         String[] ss = s.split(" ");
//         StringBuffer sb = new StringBuffer();
//         for (int i = ss.length-1; i >= 0; i--) {
//             System.out.println("*" + ss[i] + "*");
//             if (!ss[i].equals("")) {
//                 if (i != ss.length-1)
//                     sb.append(" ");
//                 sb.append(ss[i]);
//             }
//         }
//         System.out.println(sb);
//         return sb.toString();
//     }
//     public static String reverse(char[] s) {
//         int l = 0, r = s.length-1;
//         while (l < r) {
//             char t = s[l];
//             s[l] = s[r];
//             s[r] = t;
//             l++;
//             r--;
//         }
//         return String.valueOf(s);
//     }
// }

// import java.util.*;
// public class Main{
//     public static void main(String[] args) {
//         Scanner sc = new Scanner(System.in);
//         String num1 = sc.next();
//         String num2 = sc.next();
//         char[] s1 = num1.toCharArray();
//         char[] s2 = num2.toCharArray();
//         reverse(s1, 0, s1.length-1);
//         reverse(s2, 0, s2.length-1);

//         System.out.println(getResult(sub(s1, s2)));
//     }
//     public static char[] mul(char[] s1, char[] s2) {
//         int len = s1.length + s2.length;
//         int[] num = new int[len+1]; 
//         for (int i = 0; i < s1.length; i++) {
//             for (int j = 0; j < s2.length; j++) {
//                 num[i+j] += (char)((s1[i]-'0') * (s2[j]-'0'));
//             }
//         }
//         for (int i = 0; i < num.length-1; i++) {
//             num[i+1] += num[i] / 10;
//             num[i] %= 10;
//         }
//         char[] res = new char[num.length];
//         for (int i = 0; i < res.length; i++)
//             res[i] = '0';
//         for (int i = 0; i < res.length; i++) {
//             res[i] = (char)(num[i]+'0');
//         }
//         return res;
//     }
//     public static char[] sub(char[] s1, char[] s2) {
//         int len = s1.length > s2.length ? s1.length : s2.length;
//         char[] res = new char[len+1]; 
//         for (int i = 0; i < res.length; i++)
//             res[i] = '0';
//         int n1 = 0, n2 = 0, cap = 0;
//         for (int i = 0; i < len; i++) {
//             n1 = i < s1.length ? s1[i]-'0' : 0;
//             n2 = i < s2.length ? s2[i]-'0' : 0;
//             if (n1 < n2) {
//                 res[i] = (char)(n1+10-n2-cap+'0');
//                 cap = 1;
//             } else {
//                 res[i] = (char)(n1-n2-cap+'0');
//                 cap = 0;
//             }
//         }
//         if (cap == 1) {
//             res =  sub(s2, s1);
//             res[len] = '-';
//         }
//         return res;
//     }
//     public static char[] add(char[] s1, char[] s2) {
//         int len = s1.length > s2.length ? s1.length : s2.length;
//         char[] res = new char[len+1];
//         int n1 = 0, n2 = 0, cap = 0, cur = 0;
//         for (int i = 0; i <= len; i++) {
//             n1 = i < s1.length ? s1[i]-'0' : 0;
//             n2 = i < s2.length ? s2[i]-'0' : 0;
//             cur = n1+n2+cap;
//             cap = cur / 10;
//             res[i] = (char)(cur % 10 + '0');
//         }
//         return res;
//     }
//     public static void reverse(char[] s, int l, int r) {
//         while (l < r) {
//             char t = s[l];
//             s[l] = s[r];
//             s[r] = t;
//             l++;
//             r--;
//         }
//     }
//     public static String getResult(char[] s) {
//         int i = 0, top = 0;
//         boolean ok = false;
//         for (i = s.length-1; i >= 0; i--) {
//             if (s[i] == '-') {
//                 ok = true;
//             }
//             else if (s[i] != '0')
//                 break;
//         }
//         if (i <= 0)
//             return "0";
//         char[] res;
//         if (ok) {
//             res = new char[i+2];
//             res[top++] = '-';
//         }
//         else
//             res = new char[i+1];
//         for ( ; i >= 0; i--) {
//             res[top++] = s[i];
//         }
//         return String.valueOf(res);
//     }
// }



// public class Main{
//     public static void main(String[] args) {
//         char c = 'a';
//         int i = c;
//         System.out.println(i);

//         int j = 'a' + 'b';
//         System.out.println(j);

//         int k = 'a' - 4;
//         System.out.println(k);

//         i = 4 + '0';
//         System.out.println(i);

//         char c2 = 3 + '0';
//         System.out.println(c2);

//         i = '9' - '0';
//         System.out.println(i);

//         i = '9';
//         System.out.println(i);

//         c = 65 + 3;
//         System.out.println(c);

//     }
// }


//import java.util.*;
//
//public class Main{
//    public static void main(String[] args) {
//        Scanner sc = new Scanner(System.in);
//        int t = sc.nextInt();
//        while (t-- != 0) {
//            int n = sc.nextInt();
//            int k = sc.nextInt();
//            int q = sc.nextInt();
//            int cnt = 0, top = 0;
//            int[] cnts = new int[n];
//            for (int i = 0; i < n; i++) {
//                int a  = sc.nextInt();
//                if (a <= q)
//                    cnt++;
//                else if (cnt != 0) {
//                    cnts[top++] = cnt;
//                    cnt = 0;
//                }
//            }
//            if (top < n && cnt != 0)
//                cnts[top++] = cnt;
//            int res = 0;
//            for (int i = 0; i < top; i++) {
//                if (cnts[i] < k)
//                    continue;
//                res += sum(cnts[i], k);
//            }
//            System.out.println(res);
//        }
//    }
//    public static int sum(int cnt, int k) {
//        if (cnt == k)
//            return 1;
//        int res = 0;
//        if (k == 1)
//            res += cnt;
//        for (int i = 1; i <= cnt; i++) {
//            int j = k+i-1;
//            res += cnt-j;
//            // for (int j = i+1; j <= cnt; j++) {
//            //     if (j-i+1 >= k)
//            //         res++;
//            // }
//        }
//        return res;
//    }
//}



// import java.util.*;

// public class Main {
//     public static void main(String[] args) {
//         Scanner sc = new Scanner(System.in);
//         int n = sc.nextInt();
//         int x = sc.nextInt(); 
//         int y = sc.nextInt();
//         int a = sc.nextInt();
//         int b = sc.nextInt();
//         long res = 0, max = 0;
//         int cnt1 = 0, cnt2 = 0;
//         int S = 0, s = 0, M = 0, m = 0;
//         for (int i = 0; i < n; ++i) {
//             max = res > max ? res : max;
//             S = sc.nextInt();
//             s = sc.nextInt();
//             M = sc.nextInt();
//             m = M - S*x - s*y;
//             if (m == 0) {
//                 cnt2 = 0;
//                 if (++cnt1 >= b && res != 0) {
//                     res >>= 1;
//                 }
//                 continue;
//             }
//             cnt1 = 0;
//             res += m;
//             if (m > M-m) {
//                 res += 0.5 * m;
//                 if (0.5*m % 1 != 0)
//                     ++res;
//             }
//             if (++cnt2 >= a)
//                 res <<= 1;
//         }
//         max = res > max ? res : max;
//         System.out.println(max + " " + res);
//     }
// }


// import java.util.*;
// public class Main{
//     public static void main(String[] args) {
//         List list = new ArrayList();
//         list.add(3);
//         list.add(2);
//         list.add(6);
//         list.add(4);
//         list.add(9);
//         list.add(8);
//         list.add(7);
//         list.add(5);
//         Collections.sort(list);  
//         for (int i = 0; i < list.size(); i++)
//             System.out.print(list.get(i));  // 23456789
//     }
// }

// import java.util.*;
// public class Main{
//     public static void main(String[] args) {
//         Scanner sc = new Scanner(System.in);
//         int n = sc.nextInt();
//         int[] arr = new int[n];
//         for (int i = 0; i < n; i++)
//             arr[i] = sc.nextInt();
//         int m = sc.nextInt();
//         int a = 0, l = 0, r = 0, x = 0;
//         while (m-- != 0) {
//             a = sc.nextInt();
//             l = sc.nextInt();
//             r = sc.nextInt();
//             if (a == 1) {
//                 System.out.println(sum(arr, l-1, (r>=n?n-1:r-1)));
//             } else {
//                 x = sc.nextInt();
//                 for (int i = l-1; i < r; i++) {
//                     arr[i] ^= x;
//                 }
//             }
//         }
//     }
//     public static int sum(int[] a, int l, int r) {
//         int res = 0;
//         while (l <= r) {
//             res += a[l];
//             l++;
//         }
//         return res;
//     }
// }

//import java.util.*;
/*
    ԭʼ??ݣ?1 2 6 3 4 7 5

    ????β??????ݣ?2 6 3 4 7 5
    ??????????
        ??ǰ?????2
        ??ǰ????б??1
        2 > 1 : 2 ??? 1 ֮??

    ?ڶ??β??????ݣ?6 3 4 7 5
    ?ڶ????????
        ??ǰ?????6
        ??ǰ????б??1 2
        6 > 2 : 6 ??? 2 ֮??

    ????β??????ݣ?3 4 7 5
    ??????????
        ??ǰ?????3
        ??ǰ????б??1 2 6
        3 < 6 :
        3 > 2 : 3 ??? 2 ֮??

    ??Ĵβ??????ݣ?4 7 5
    ??Ĵ??????
        ??ǰ?????4
        ??ǰ????б??1 2 3 6
        4 < 6 : 
        4 > 3 : 4 ??? 3 ֮??

    ??????????ݣ?7 5
    ???ѭ????
        ??ǰ?????7
        ??ǰ????б??1 2 3 4 6
        7 > 6 : 7 ??? 6 ֮??

    ????β??????ݣ?5
    ??????????
        ??ǰ?????5
        ??ǰ????б??1 2 3 4 6 7
        5 < 7 :
        5 < 6 :
        5 > 4 : 5 ??? 4 ֮??

    ??ˣ?????????Ϊ??1 2 3 4 5 6 7

*/

// public class Main{
//     public static void main(String[] args){
//         int[] nums = {1, 2, 6, 3, 4, 7, 5};
//         for (int i = 0; i < nums.length; i++) {
//             int cur = nums[i];
//             int j = i - 1;
//             while (j >= 0 && nums[j] > cur) {
//                 nums[j+1] = nums[j];
//                 j--;
//             }
//             nums[j+1] = cur;
//         }
//         System.out.println(Arrays.toString(nums));
//     }
// }

// import java.util.*;

// public class Main{
//     public static void main(String[] args){
//         Scanner sc = new Scanner(System.in);
//         int t = sc.nextInt();
//         while (t-- != 0) {
//             int n = sc.nextInt();
//             int[] cnt = new int[201];
//             for (int i = 0; i < n; i++) 
//                 ++cnt[sc.nextInt()];
//             boolean ok = true;
//             for (int i = 0; i < 200; i++) {
//                 if (cnt[i] < cnt[i+1]) {
//                     ok = false;
//                     break;
//                 }
//             }
//             if (ok)
//                 System.out.println("YES");
//             else
//                 System.out.println("NO");
//         }
//     }
// }


// import java.util.*;
// public class Main{
//     public static void main(String[] args){
//         Scanner sc = new Scanner(System.in);
//         int t = sc.nextInt();
//         while (t-- != 0) {
//             int n = sc.nextInt();
//             int[] a = new int[n];
//             for (int i = 0; i < n; i++)
//                 a[i] = sc.nextInt();
//             Arrays.sort(a);
//             int res = 0;
//             for (int i = 0, j = a.length-1; i < j; i++, j--) {
//                 res += a[j] - a[i];
//             }
//             System.out.println(res);
//         }
//     }
// }

// import java.util.*;
// public class Main{
//     public static void main(String[] args){
//         Scanner sc = new Scanner(System.in);
//         int t = sc.nextInt();
//         while (t-- != 0) {
//             int n = sc.nextInt();
//             int[] a = new int[n];
//             long res = 0;
//             for (int i = 0; i < n; i++) {
//                 a[i] = sc.nextInt();
//                 res += a[i] > 0 ? a[i] : -a[i];
//             }
//             int cnt = 0;
//             for (int i = 0; i < a.length; i++) {
//                 if (a[i] < 0) {
//                     cnt++;
//                     while (i < a.length && a[i] <= 0)
//                         i++;
//                 }
//             }
//             System.out.println(res +" " + cnt);
//         }
//     }
// }

// import java.util.*;
// public class Main{
//     public static void main(String[] args){
//         Scanner sc = new Scanner(System.in);
//         int t = sc.nextInt();
//         while (t-- != 0) {
//             long n = sc.nextLong();
//             long res = n;
//             while (n != 0) {
//                 res += n / 2;
//                 n /= 2;
//             }
//             System.out.println(res);
//         }
//     }
// }


// import java.util.*;
// public class Main{
//     public static void main(String[] args){
//         Scanner sc = new Scanner(System.in);
//         int t = sc.nextInt();
//         while (t-- != 0) {
//             int n = sc.nextInt();
//             int[][] grid = new int[n+1][n+1];
//             for (int i = 0; i < n-1; i++) {
//                 int x = sc.nextInt();
//                 int y = sc.nextInt();
//                 grid[x][y] = 1;
//                 grid[y][x] = 1;
//             }
            
//             List<Integer> nodes = new ArrayList<>();
//             for (int i = 1; i < n+1; i++) {
//                 boolean ok = true;
//                 int j = i+1;
//                 for ( ; j < n+1; j++) {
//                     if (grid[i][j] != 0) {
//                         ok = false;
//                         break;
//                     }
//                 }
//                 if (ok)
//                     nodes.add(i);
//             }
//             int q = sc.nextInt();
//             while (q-- != 0) {
//                 int a = sc.nextInt();
//                 int b = sc.nextInt();
//                 int anum = 0, bnum = 0;
//                 for (int i = nodes.size()-1; i >= 0; i--) {
//                     if (isConnect(grid, a, nodes.get(i))) {
//                         anum++;
//                     }
//                     if (isConnect(grid, b, nodes.get(i))) {
//                         bnum++;
//                     }
//                 }
//                 System.out.println((long)anum * bnum);
//             }
//         }
//     }
//     public static boolean isConnect(int[][] grid, int a, int key) {
//         if (a == key)
//             return true;
//         if (grid[a][key] == 1)
//             return true;
//         for (int i = a+1; i < grid.length; i++) {
//             if (grid[a][i] == 1) {
//                 return isConnect(grid, i, key);
//             }
//         }
//         return false;
//     }
// }


// import java.util.*;

// public class Main{
//     public static void main(String[] args) {
//         Scanner sc = new Scanner(System.in);
//         char[] a = "3284925390".toCharArray();
//         int b = 19;
        
//         List<Integer> A = new ArrayList<>();
//         for (int i = a.length-1; i >= 0; i--) {
//             A.add(a[i]-'0');
//         }
        
//         List<Integer> C = mul(A, b);
        
//         for (int i = C.size()-1; i >= 0 ; i--) {
//             System.out.print(C.get(i));
//         }    
//     }
//     public static List<Integer> mul(List<Integer> a, int b) {
//         List<Integer> c = new ArrayList<>();
//         int t = 0;
//         for (int i = 0; i < a.size(); i++) {
//             t += a.get(i) * b;
//             c.add(t % 10);
//             t /= 10;
//         }
//         for (int i = c.size()-1; i > 0; i--){
//             if (c.get(i) != 0)
//                 break;
//             c.remove(i);
//             System.out.println(c.size());
//         }
//         return c;
//     }
// } 

// import java.util.*;
// public class Main{
//     public static void main(String[] args) {
//         int[] arr = {1, 3, 5, 2, 7, 9, 6, 8, 4, 0};
//         countingSort(arr);
//         System.out.println(Arrays.toString(arr));
//     }
//     // 假设 0 <= arr[i] <= 100
//     public static void countingSort(int[] arr) {
//         int[] cnt = new int[101];
//         for (int a : arr) {
//             ++cnt[a];
//         }
//         int top = 0;
//         for (int i = 0; i < cnt.length; i++) {
//             while (cnt[i] != 0) {
//                 arr[top++] = i;
//                 cnt[i]--;
//             }
//         }
//     }
//     // public static void shellSort(int[] arr) {
//     //     for (int d = arr.length / 2; d >= 1; d /= 2) {
//     //         for (int i = d; i < arr.length; i++) {
//     //             int cur = arr[i];
//     //             int j = i - d;
//     //             while (j >= 0 && arr[j] > cur) {
//     //                arr[j+d] = arr[j];
//     //                j -= d; 
//     //             }
//     //             arr[j+d] = cur;
//     //         }
//     //     }
//     // }
// }

// 
// import java.util.*;
// public class Main{
//     static int count, resx, resy;
//     static List<int[]> list;
//     public static void main(String[] args){
//         list = new ArrayList<>();
//         Scanner sc = new Scanner(System.in);
//         int n = sc.nextInt();
//         int m = sc.nextInt();
//         count = n * m;
//         int k = sc.nextInt();
//         int[][] mat = new int[n+1][m+1];
//         for (int i = 0; i < k; i++) {
//             int x = sc.nextInt();
//             int y = sc.nextInt();
//             mat[x][y] = 1;
//             list.add(new int[]{x, y});
//         }
//         count -= k;
//         resx = 1; resy = 1;
//         for (int i = 0; i < list.size(); i++) {
//             int x = list.get(i)[0];
//             int y = list.get(i)[1];
//             System.out.println(x + " " + y + " " + count);
//             dfs(mat, n+1, m+1, x, y);
//             if (count < 1)
//                 break;
//         }
//         System.out.println(resx + " " + resy);
//     }
//     public static void dfs(int[][] mat, int n, int m, int x, int y) {
//         if (x-1 >= 1 && mat[x-1][y] != 1) {
//             if (--count == 0) {
//                 resx = x-1;
//                 resy = y;
//             }
//             list.add(new int[]{x-1, y});
//             mat[x-1][y] = 1;
//         }
            
//         if (x+1 < n && mat[x+1][y] != 1) {
//             if (--count == 0) {
//                 resx = x+1;
//                 resy = y;
//             }
//             list.add(new int[]{x+1, y});
//             mat[x+1][y] = 1;
//         }
            
//         if (y-1 >= 1 && mat[x][y-1] != 1) {
//             if (--count == 0) {
//                 resx = x;
//                 resy = y-1;
//             }
//             list.add(new int[]{x, y-1});
//             mat[x][y-1] = 1;
//         }
            
//         if (y+1 < m && mat[x][y+1] != 1) {
//            if (--count == 0) {
//                 resx = x;
//                 resy = y+1;
//             }
//             list.add(new int[]{x, y+1});
//             mat[x][y+1] = 1;
//         }
            
//     }
// }


// import java.util.*;
// public class Main{
//     public static void main(String[] args){
//         Scanner sc = new Scanner(System.in);
//         int n = sc.nextInt();
//         int v = sc.nextInt();
//         int[] a = new int[n];
//         for (int i = 0; i < n; i++) a[i] = sc.nextInt();
//         int[] b = new int[n];
//         for (int i = 0; i < n; i++) b[i] = sc.nextInt();
//         int amin = 100;
//         double bmin = 100;
//         for (int i = 0; i < n; i++) {
//             amin = amin < a[i] ? amin : a[i];
//         }
//         for (int i = 0; i < n; i++) {
//             if (a[i] == amin) 
//                 bmin = bmin < b[i] ? bmin : b[i];
//         }
//         double res = 0;
//         for (int i = 0; i < n; i++) {
//             double cur = (double)(bmin * a[i]) / amin;
//             System.out.print(amin + " " + bmin + " " + a[i] + " " + b[i] + " " + (double)(bmin * a[i]) / amin + " ");
//             if (cur > b[i])
//                 cur = b[i];
//             System.out.println(cur);
//             res += cur;
//             if (res >= v) {
//                 res = v;
//                 break;
//             }
//         }
//         System.out.printf("%.1f", res);
//     }
// }


// public class Main{
//     public static void main(String[] args) {
//         // int i = 0, j = 1;
//         // int c = (i=1, j+1);
//         // System.out.println(i + " " + j + " " + c);
//         int i = 0, j = 0;
// i = (j = 1, j + 1);
// System.out.println(i); // 输出 2
// System.out.println(j); // 输出 1
//     }
// }

// import java.util.Arrays;
// public class Main{
//     public static void main(String[] args) {
//         int t = 10 >>> 2;
//         // int[] arr = {1, 3, 5, 2, 7, 9, 6, 8, 4, 0};
//         int[] arr = {23, 4, 54, 76, 345, 64, 244, 67, 77, 55, 34, 1, 3, 5, 2, 7, 14, 6, 54, 4, 0};
//         radixSort(arr, 8);
//         System.out.println("排序后：" + Arrays.toString(arr));
//     }
//     public static void radixSort(int[] arr, int maxSize) {
//         int[][] cnt = new int[10][arr.length];
//         int[] tops = new int[10];
//         int curSize = 1;
//         int power = 1;
//         while (curSize <= maxSize) {
//             for (int i = 0; i < arr.length; i++) {
//                 int r = arr[i] / power % 10;
//                 cnt[r][tops[r]++] = arr[i];
//             }
//             int top = 0;
//             for (int i = 0; i < 10; i++) {
//                 for (int j = 0; j < tops[i]; j++) {
//                     arr[top++] = cnt[i][j];
//                 }
//                 tops[i] = 0;
//             }
//             curSize++;
//             power *= 10;
//         }
//     }
// }


// public class Main{
//     public static void main(String[] args){
// //         int a = 4, b = 2;
// //         // a ^= b ^= a ^= b;
// //         a *= b += a -= 2;
// // //         a ^= b;
// // // b ^= a;
// // // a ^= b;
//         int a = 0b1010;           // (1)
//         int b = 0b0110; 
//         System.out.println(a);
//         System.out.println(b);
//     }
// }

// import java.util.*;
// public class Main{
//     public static void main(String[] args){
//         Scanner sc = new Scanner(System.in);
//         int T = sc.nextInt();
//         int num = 1;
//         while (T-- != 0) {
//             char[] s = sc.next().toCharArray();
//             char[] t = sc.next().toCharArray();
//             int[] cnt = new int[26];
//             for (char c : t) 
//                 ++cnt[c-'a'];
//             int res = 0;
//             for (char c : s) {
//                 int min = 0;
//                 char temp = c;
//                 System.out.println(temp);
//                 while (cnt[(temp-'a') % 26] == 0) {
//                     temp--;
//                 }
//                 min = c - temp;
//                 temp = c;
//                 while (cnt[(temp-'a') % 26] == 0) {
//                     temp++;
//                 }
//                 min = Math.min(min, temp-c);
//                 res += min;
//             }
//             System.out.println("Case #" + num + ": " + res);
//             num++;
//         }
//     }
// }

import java.util.*;
import java.io.*;

public class Main{
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int t = in.read()-'0';
        // System.out.println(t);
        for (int cases = 1; cases <= t; cases++) {
            String s = in.readLine();
            char[] ss = s.toCharArray();
            int[] k_idx = new int[ss.length];
            int[] s_idx = new int[ss.length];
            int top1 = 0, top2 = 0;
            for (int i = 0; i < ss.length-4; i++) {
                int j = i + 4;
                if (s.substring(i, j).equals("KICK"))
                    k_idx[top1] = i;
                else if (j+1 <= ss.length && s.substring(i, j+1).equals("START"))
                    s_idx[top2] = i;
            }
            int res = 0;
            for (int k : k_idx) {
                for (int i : s_idx) {
                    if (i > k)
                        res++;
                }
            }
            System.out.println("Case #" + cases + ": " + res);
        }
    }
}