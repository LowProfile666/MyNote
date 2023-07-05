package LinkedList;
/*
根据带有头部的单链表，实现商品增删改查，并且也可以针对商品已编号进行排序，完成排行榜。
 */
public class LinkedListObj {
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
    // 获取长度
    public int length(){
        if (head.next == null)
            return 0;
        GoodsNode temp = head.next;
        int length = 0;
        while (temp != null) {
            length++;
            temp = temp.next;
        }
        return length;
    }

}
