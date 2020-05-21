/**
 * Class that implements ADS list by doubly linked list
 * @author Smirnova Marina
 *
 */
public class DoublyLinkedList<E> implements List<E> {

    /** header node is linked with the first element
     *  trailer is linked with the last element */
    private Node<E> header;
    private Node<E> trailer;

    /** current amount of elements in a list*/
    private int size = 0;

    /** Constructor creates a list with header and trailer connected with each other
     *  with no elements between them(means no elements in a list)*/
    public DoublyLinkedList(){
        header = new Node<>(null, null, null);
        trailer = new Node<>(null, null, header);
        header.setNext(trailer);
    }

    /**
     * Method to check whether a list contains elements or doesn't
     * @return false if there are no elements
     *         true if there is at least one element
     */
    public boolean isEmpty(){
        if (size == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    /**
     * Method to add a new element at certain position
     * @param i is an index to where to add a new element
     * @param elem is an element to add
     */
    public void add(int i, E elem){
        if (i >= 0 && i <= size){
            Node<E> cur = header;
            for (int j = 0; j<i; j++){
                cur = cur.getNext();
            }
            Node<E> node = new Node<>(elem, null, null);
            if (i == 0) {
                cur.setPrev(node);
                node.setNext(cur);
                node.setPrev(header);
                header.setNext(node);
            }
            if (i == size){
                cur.setNext(node);
                node.setNext(trailer);
                node.setPrev(cur);
                trailer.setPrev(node);
            }
            if (i > 0 && i < size){
                cur.getNext().setPrev(node);
                node.setNext(cur.getNext());
                node.setPrev(cur);
                cur.setNext(node);
            }

            size += 1;
        }
        else {
            System.out.println("Index out of bounds. ");
        }

    }

    /**
     * Method to add a new element at the beginning of a list(at 0 index)
     * @param elem is an element to add
     */
    public void addFirst(E elem){
        Node<E> node = new Node<>(elem, header.getNext(), header);
        header.getNext().setPrev(node);
        header.setNext(node);
        size += 1;
    }

    /**
     * Method to add a new element at the end of a list
     * @param elem is an element to add
     */
    public void addLast(E elem){
        Node<E> node = new Node<>(elem, trailer, trailer.getPrev());
        trailer.getPrev().setNext(node);
        trailer.setPrev(node);
        size += 1;
    }

    /**
     * Method to delete the certain element from a list
     * If a list doesn't contain an element -> display "Not found"
     * @param elem is a certain element to delete
     */
    public void delete(E elem){
        Node<E> cur = header;
        int j = 0;
        boolean found = false;
        while (j < size && !found){
            cur = cur.getNext();
            if (cur.getElement().equals(elem)){
                found = true;
                cur.getNext().setPrev(cur.getPrev());
                cur.getPrev().setNext(cur.getNext());
                size -= 1;
            }
            j += 1;
        }
        if (!found) {
            System.out.println("Not found. ");
        }
    }

    /**
     * Method to delete an element from the certain position
     * If i is out of bounds of a list -> display "Index out of bounds."
     * @param i is an index of an element to delete
     */
    public void delete(int i){
        if (i >= 0 && i < size) {
            Node<E> cur = header;
            for (int j = 0; j<=i; j++) {
                cur = cur.getNext();
            }
            cur.getNext().setPrev(cur.getPrev());
            cur.getPrev().setNext(cur.getNext());
            size -= 1;
        }
        else {
            System.out.println("Index out of bounds. ");
        }
    }

    /**
     * Method to delete the first element of a list
     * If a list doesn't contain elements -> display "The list was empty."
     */
    public void deleteFirst(){
        if (size != 0){
            header.getNext().getNext().setPrev(header);
            header.setNext(header.getNext().getNext());
            size -= 1;
        }
        else {
            System.out.println("The list was empty");
        }
    }

    /**
     * Method to delete the last element of a list
     * If a list doesn't contain elements -> display "The list was empty."
     */
    public void deleteLast(){
        if (size != 0) {
            trailer.getPrev().getPrev().setNext(trailer);
            trailer.setPrev(trailer.getPrev().getPrev());
            size -= 1;
        }
        else{
            System.out.println("The list was empty.");
        }
    }

    /**
     * Method to set the certain element to the certain position
     * If i is out of bounds of a list -> display "Index out of bounds."
     * @param i is an index where to set
     * @param elem is an element to set
     */
    public void set(int i, E elem){
        if (i >= 0 && i < size){
            Node<E> cur = header;
            for (int j = 0; j<=i; j++){
                cur = cur.getNext();
            }
            Node<E> node = new Node<>(elem, null, null);
            if (i == 0) {
                node.setNext(cur.getNext());
                node.setPrev(header);
                header.setNext(node);
                cur.getNext().setPrev(node);
            }
            if (i == size-1){
                node.setNext(trailer);
                node.setPrev(cur.getPrev());
                trailer.setPrev(node);
                cur.getPrev().setNext(node);
            }
            if (i > 0 && i < size-1){
                node.setNext(cur.getNext());
                node.setPrev(cur.getPrev());
                cur.getPrev().setNext(node);
                cur.getNext().setPrev(node);
            }

        }
        else {
            System.out.println("Index out of bounds. ");
        }

    }

    /**
     * Method to get an element from the certain position
     * If i is out of bounds of a list -> display "Index out of bounds."
     * @param i is an index of element to get from a list
     * @return element at index i
     */
    public E get(int i){
        if (i >= 0 && i < size){
            Node<E> cur = header;
            for (int j = 0; j<=i; j++){
                cur = cur.getNext();
            }
            return cur.getElement();
        }
        else {
            System.out.println("Index out of bounds. ");
            return null;
        }
    }

    /**
     * Method to get current number of elements in a list
     * @return current amount of elements in a list
     */
    public int getSize(){
        return size;
    }

}
