/**
 * Class that implements ADS list by doubly linked list
 * @author Smirnova Marina
 *
 */

public class List {

    /** header node is linked with the first element
     *  trailer is linked with the last element */
    private Node header;
    private Node trailer;

    /** current amount of elements in a list*/
    private int size = 0;

    /** Constructor creates a list with header and trailer connected with each other
     *  with no elements between them(means no elements in a list)*/
    List(){
        header = new Node(null, null, null);
        trailer = new Node(null, null, header);
        header.setNext(trailer);
    }

    void addFirst(String string){
        Node node = new Node(string, header.getNext(), header);
        header.getNext().setPrev(node);
        header.setNext(node);
        size += 1;

    }

    /**
     * Method to get current number of elements in a list
     * @return current amount of elements in a list
     */
    int getSize(){
        return size;
    }

    /**
     * Method to compare and add a new word at certain position
     * Organize a list of words in lexicographical order
     * @param string is an element to add
     */
    void compareAndInsert(String string){
        Node newNode = new Node(string, null, null);
        Node compareWith = header;
        int condition;
        int position = 0;

        do{
            position += 1;
            compareWith = compareWith.getNext();
            condition = string.compareTo(compareWith.getWord());

        } while(condition > 0 && position < size);

        if (position == size && condition>0){
            newNode.setNext(trailer);
            newNode.setPrev(compareWith);
            compareWith.setNext(newNode);
            trailer.setPrev(newNode);
        }
        else {
            newNode.setNext(compareWith);
            newNode.setPrev(compareWith.getPrev());
            compareWith.getPrev().setNext(newNode);
            compareWith.setPrev(newNode);
        }
        size += 1;
    }

    /**
     * Method to delete all elements of a list
     */
    void removeAll(){
        header.setNext(trailer);
        trailer.setPrev(header);
        size = 0;
    }

    /**
     * Method to print all elements of a list
     */
    void printList(){
        Node current = header.getNext();
        for (int i = 0; i<size; i++){
            System.out.print(current.getWord()+" ");
            current = current.getNext();
        }
    }
}
