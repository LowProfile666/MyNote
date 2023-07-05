package LinkedList;
/*
商品结点类
 */
public class GoodsNode {
    public int id;
    public String name;
    public double price;
    public GoodsNode next;
    public GoodsNode() {
        this(0, "", 0.0);
        this.next = null;
    }
    public GoodsNode(int id, String name, double price) {
        this.id = id;
        this.name = name;
        this.price = price;
        this.next = null;
    }

    @Override
    public String toString() {
        return "GoodsNode{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", price=" + price +
                '}';
    }
}
