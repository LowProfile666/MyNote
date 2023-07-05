package LinkedList;

public class LinkedListTest02 {
    public static void main(String[] args) {
        DouLinkedListObj listObj = new DouLinkedListObj();
        BookNode node1 = new BookNode(1, "HelloWorld", 30.0);
        BookNode node2 = new BookNode(2, "C语言程序设计", 40.0);
        BookNode node3 = new BookNode(3, "Java语言程序设计", 50.0);
        BookNode node4 = new BookNode(4, "数据库原理", 60.0);

        listObj.insert(node1);
        listObj.insert(node2);
        listObj.insert(node3);
        listObj.insert(node4);

        listObj.update(new BookNode(1, "算法导论", 40));
        listObj.delete(4);
        listObj.list();
    }
}
