/**
 * Class that implement ADS list by dynamic array
 * @author Smirnova Marina
 *
 */
public class DynamicArray<E> implements List<E> {

    /** capacity of array by default*/
    private final int defCapacity = 10;

    /** current capacity of an array*/
    private int capacity;

    private E[] array;

    /** current amount of elements in an array*/
    private int size = 0;

    /**
     * Constructor that uses capacity
     * @param capacity is capacity of an array
     */
    DynamicArray(int capacity){
        array = (E[])new Object[capacity];
        this.capacity = capacity;
    }

    DynamicArray(){
        array = (E[]) new Object[defCapacity];
        capacity = defCapacity;
    }

    /**
     * Method for determining whether an array contains elements or not
     * @return true if an array is empty;
     *         false if an array contains at least 1 elem
     */
    public boolean isEmpty(){
        if (size == 0){
            return true;
        }
        else{
            return false;
        }
    }

    /**
     * Method for allocating more space for an array
     * by doubling the capacity of an array
     * @param capacity is a current capacity of an array, before resizement
     */
    public void resize(int capacity){
        E[] resizedArray = (E[]) new Object[capacity*2];
        for (int i = 0; i<size; i++){
            resizedArray[i] = array[i];
        }
        array = resizedArray;
        this.capacity = capacity*2;
    }

    /**
     * Method for adding a new element to the certain position in an array
     * @param i is position where to insert a new element to the list
     * @param elem is a new element for insertion
     */
    public void add(int i, E elem){
        if (i>=capacity){
            resize(capacity);
        }
        int j = size;
        while (j>i){
            array[j] = array[j-1];
            j -= 1;
        }
        array[i] = elem;
        size += 1;
    }

    /**
     * Method for adding a new element in the beginning of an array([0] position)
     * @param elem a new element for adding
     */
    public void addFirst(E elem){
        if (size == capacity){
            resize(capacity);
        }
        int i = size;
        while (i > 0){
            array[i] = array[i-1];
            i -= 1;
        }
        array[0] = elem;
        size += 1;
    }

    /**
     * Method for adding a new element to the end of an array
     * If array is full -> resize and add to the end position
     * @param elem a new element for adding
     */
    public void addLast(E elem){
        if (size == capacity){
            resize(capacity);
        }
        array[size] = elem;
        size += 1;
    }

    /**
     * Method for deleting an element
     * If an element is not found -> display "Not found."
     * @param elem is an element that we want to delete
     */
    public void delete(E elem){
        boolean found = false;
        int i = 0;
        while (found == false && i<size){
            if (array[i].equals(elem)){
                found = true;
                delete(i);
                size -= 1;
            }
            i += 1;
        }
        if (!found){
            System.out.println("Not found. ");
        }
    }

    /**
     * Method for deleting an element from the certain position
     * If index is out of bounds of an array -> display "Index out of bounds."
     * @param i is an index of element that we want to delete
     */
    public void delete(int i){
        if (i >= 0 && i<size){
            if (i == size-1) {
                deleteLast();
            }
            else {
                int j = i;
                while (j < size - 1) {
                    array[j] = array[j + 1];
                    j += 1;
                }
                size -= 1;
            }
        }
        else {
            System.out.println("Index out of bounds. ");
        }
    }

    /**
     * Method for deleting the first element from an array
     * If an array does't have elements -> display "The list was empty. "
     */
    public void deleteFirst(){
        int i = 0;
        if (size > 0){
            do {
                array[i] = array[i+1];
                i += 1;
            } while (i < size-1);
            size -= 1;
        }
        else {
            System.out.println("The list was empty. ");
        }
    }

    /**
     * Method for deleting last element of an array
     * If array doesn't contain elements -> display "The list was empty"
     */
    public void deleteLast(){
        if (size == 0){
            System.out.println("The list was empty. ");
        }
        else {
            array[size-1] = null;
            size -= 1;
        }
    }

    /**
     * Method for setting the element at the certain position
     * @param i is an index where to set an element
     * @param elem is an element to set to the certain position
     */
    public void set(int i, E elem){
        if (i >= 0 && i<size){
            array[i] = elem;
        }
        else {
            System.out.println("Index out of bound. ");
        }
    }

    /**
     * Method for getting an element at the certain position
     * If an index is out of bounds of an array -> display "Index out of bounds"
     * @param i is an index of element that we want to get
     * @return element of an array at i position
     */
    public E get(int i){
        if (i >= 0 && i < size){
            return array[i];
        }
        else {
            System.out.println("Index out of bounds. ");
            return null;
        }
    }

    /**
     * Method for getting number of elements in an array
     * @return current amount of elements in an array
     */
    public int getSize(){
        return size;
    }

}
