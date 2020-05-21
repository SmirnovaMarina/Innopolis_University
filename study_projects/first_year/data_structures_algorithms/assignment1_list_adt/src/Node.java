/**
 * Class for nodes of a doubly linked list
 * @author Smirnova Marina
 *
 */
public class Node<E> {

    /** element is a content of a node*/
    private E element;

    /** next is the next node
     *  prev is the previous node*/
    private Node<E> next;
    private Node<E> prev;

    Node(E element, Node next, Node prev){
        this.element = element;
        this.next = next;
        this.prev = prev;
    }

    void setNext(Node<E> node){
        next = node;
    }

    void setPrev(Node<E> node){
        prev = node;
    }

    Node<E> getNext(){
        return next;
    }

    Node<E> getPrev(){
        return prev;
    }

    E getElement(){
        return element;
    }
}
