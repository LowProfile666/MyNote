package queue;

public class ArrayQueue {
    private int[] queue;
    private int maxSize;
    private int front;
    private int rear;

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
