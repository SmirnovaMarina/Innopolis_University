/**
 * Class for nodes of a doubly linked list
 * @author Smirnova Marina
 *
 */

public class Node {

    /** content of a node*/
    private String word;
    private int frequency;

    /** next is the next node
     * prev is the previous node*/
    private Node next;
    private Node prev;

    Node(String string, Node next, Node prev){
        this.next = next;
        this.prev = prev;
        word = string;
    }


    String getWord(){
        return word;
    }

    int getFrequency(){
        return frequency;
    }

    Node getNext(){
        return next;
    }

    Node getPrev(){
        return prev;
    }

    void setWord(String string){
        word = string;
    }

    void setFrequency(int num){
        frequency = num;
    }

    void setNext(Node next){
        this.next = next;
    }

    void setPrev(Node prev){
        this.prev = prev;
    }

}
