package stack;

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
