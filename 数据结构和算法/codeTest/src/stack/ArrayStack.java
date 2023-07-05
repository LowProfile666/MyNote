package stack;

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
        s = new int[maxSize];
    }
    /**
     * 判断栈是否为空
     */
    public boolean isEmpty(){
        return this.top == 0;
    }

    /**
     * 判断栈是否已满
     */
    public boolean isFull(){
        return this.top == this.maxSize - 1;
    }
    /**
     * 压栈
     */
    public void push(int val){
        if(this.isFull()){
            throw new RuntimeException("栈以满！");
        }
        this.s[this.top++] = val;
    }
    /**
     * 出栈
     */
    public int pop(){
        if(this.isEmpty()){
            throw new RuntimeException("栈为空！");
        }
        return this.s[--this.top];
    }
    public void list(){
        if(isEmpty()){
            throw new RuntimeException("空栈！");
        }
        for (int i = 0; i < top; i++) {
            System.out.println(s[i]);
        }
    }
    public int length(){
        return top;
    }
    public int peek(){
        if(isEmpty()){
            throw new RuntimeException("空栈！");
        }
        return this.s[this.top-1];
    }
}
