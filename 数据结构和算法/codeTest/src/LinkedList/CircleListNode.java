package LinkedList;

public class CircleListNode {
    private int id;
    private CircleListNode next;
    public CircleListNode(int id) {
        this.id = id;
    }
    public int getId() {
        return id;
    }
    public void setId(int id) {
        this.id = id;
    }
    public CircleListNode getNext() {
        return next;
    }
    public void setNext(CircleListNode next) {
        this.next = next;
    }

    @Override
    public String toString() {
        return "CircleListNode{" +
                "id=" + id +
                '}';
    }
}
