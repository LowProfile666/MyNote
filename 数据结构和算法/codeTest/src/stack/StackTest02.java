package stack;


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
        String s = "4+5+4-8*2/2+2*10";
        System.out.println(s + "=" + calculate(s));
    }
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
                        int res = calculator(numberStack.pop(), numberStack.pop(), symbolStack.pop());
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
    public static int priority(int c){
        if(c == '/' || c == '*')
            return 1;
        return 0;
    }

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
