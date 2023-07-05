package LinkedList;

public class LinkedListTest01 {
    public static void main(String[] args) {
        LinkedListObj listObj = new LinkedListObj();
        GoodsNode node1 = new GoodsNode(1, "Nike Shoes", 1999.0);
        GoodsNode node2 = new GoodsNode(2, "Nike Clothes", 599.0);
        GoodsNode node3 = new GoodsNode(3, "Nike Hats", 199.0);
        GoodsNode node4 = new GoodsNode(4, "Lining Shoes", 299.0);

//        listObj.insert(node1);
//        listObj.insert(node2);
//        listObj.insert(node3);
//        listObj.insert(node4);

        listObj.insertOrder(node2);
        listObj.insertOrder(node4);
        listObj.insertOrder(node3);
        listObj.insertOrder(node1);

//        listObj.update(new GoodsNode(2, "Anta clothes", 299.09));
//        listObj.delete(3);
        System.out.println(listObj.length());
        listObj.list();
    }
}
