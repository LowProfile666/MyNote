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