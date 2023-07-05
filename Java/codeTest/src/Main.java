package test;
// import java.util.Scanner;

//public class Main{
//    static int ans = 0;
//    public static void main(String[] args) {
//        ans = 0;
//        Scanner sc = new Scanner(System.in);
//        int n = sc.nextInt();
//        int[] q = new int[n];
//        for (int i = 0; i < n; i++)
//            q[i] = sc.nextInt();
//        mergeSort(q, 0, n-1);
//        System.out.println(ans);
//        for (int i = 0; i < n; i++)
//            System.out.print(q[i] + " ");
//    }
//    public static void mergeSort(int[] q, int l, int r) {
//        if (l >= r)
//            return;
//        int m = l + (r-l>>1);
//        mergeSort(q, l, m);
//        mergeSort(q, m+1, r);
//        int i = l, j = m+1;
//        int[] temp = new int[r-l+1];
//        int top = 0;
//        while (i <= m && j <= r) {
//            if (q[i] <= q[j])
//                temp[top++] = q[i++];
//            else {
//                temp[top++] = q[j++];
//                ans += m-l+1;
//            }
//        }
//        while (i <= m)  temp[top++] = q[i++];
//        while (j <= r)  temp[top++] = q[j++];
//        for (i = l, j = 0; i <= r; i++, j++) {
//            q[i] = temp[j];
//        }
//    }
//}

//public class Main {
//    public static void main(String[] args) {
//        checkIpv6("2001:0db8:85a3:0:0:8A2E:0370:7334:");
//    }
//    public static boolean checkIpv4(String s) {
//        if (s.contains(":"))
//            return false;
//        String[] ss = s.split("\\.");
//        System.out.println(ss.length);
//        for (String str : ss) {
//            System.out.println(str);
//        }
//        if (ss.length != 4)
//            return false;
//
//        for (String str : ss) {
//            if (str.charAt(0) == '0')
//                return false;
//            System.out.println(Integer.parseInt(str));
//            if (Integer.parseInt(str) > 255)
//                return false;
//        }
//        return true;
//    }
//    public static boolean checkIpv6(String s) {
//        if (s.contains(".")))
//            return false;
//        String[] ss = s.split(":");
//        for (String str : ss)
//            System.out.print("*" + str + "*");
//        if (ss.length != 8)
//            return false;
//        for (String str : ss) {
//            if (str.length() > 4 || str.length() == 0)
//                return false;
//        }
//        return true;
//    }
//}

//public class Main{
//    public static void main(String[] args) {
//        ListNode l1 = new ListNode(1);
//        ListNode l2 = new ListNode(2);
//        ListNode l3 = new ListNode(3);
//        ListNode l4 = new ListNode(4);
//        ListNode l5 = new ListNode(5);
//        l1.next = l2;
//        l2.next = l3;
//        l3.next = l4;
//        l4.next = l5;
//        l5.next = null;
//        reverseList(l1);
//    }
//    public static ListNode reverseList(ListNode head) {
//        if (head == null || head.next == null)
//            return head;
//        ListNode res = new ListNode(-1, null);
//        reverse(head, res);
//        return res;
//    }
//    public static ListNode reverse(ListNode head, ListNode outHead) {
//        if (head.next == null) {
//            outHead = head;
//            return head;
//        }
//        ListNode res = reverse(head.next, outHead);
//        res.next = head;
//        head.next = null;
//        return head;
//    }
//}
//
//class ListNode {
//     int val;
//    ListNode next;
//    ListNode() {}
//    ListNode(int val) { this.val = val; }
//    ListNode(int val, ListNode next) { this.val = val; this.next = next; }
//}

//import java.util.*;
//public class Main{
//    public static void main(String[] args) {
//        TreeNode t4 = new TreeNode(5);
//        TreeNode t3 = new TreeNode(3);
//        TreeNode t2 = new TreeNode(2, null, t4);
//        TreeNode t1 = new TreeNode(1, t2, t3);
//        Solution s = new Solution();
//        s.binaryTreePaths(t1);
//    }
//}
//
//
//class TreeNode {
//     int val;
//     TreeNode left;
//     TreeNode right;
//     TreeNode() {}
//     TreeNode(int val) { this.val = val; }
//     TreeNode(int val, TreeNode left, TreeNode right) {
//         this.val = val;
//         this.left = left;
//         this.right = right;
//     }
// }
//class Solution {
//    List<String> ans;
//    public List<String> binaryTreePaths(TreeNode root) {
//        ans = new ArrayList<>();
//        StringBuffer sb = new StringBuffer();
//        preOrder(sb, root);
//        return ans;
//    }
//    public void preOrder(StringBuffer path, TreeNode root) {
//        if (root == null)
//            return;
//        if (root.left == null && root.right == null) {
//            path.append(""+root.val);
//            ans.add(path.toString());
//            return;
//        }
//        path.append(root.val + "->");
//        preOrder(path, root.left);
//        preOrder(path, root.right);
//    }
//}
//
//

public class Main{
    public static void main(String[] args){
        int a = 1, b = 2;
        a ^= b ^= a ^= b;
        // a ^= b;
        // b ^= a;
        // a ^= b;
        System.out.println(a);
        System.out.println(b);
    }
}