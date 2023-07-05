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
