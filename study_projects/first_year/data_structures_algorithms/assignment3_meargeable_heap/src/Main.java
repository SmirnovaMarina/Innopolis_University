/**
 * @author Smirnova Marina
 * Codeforces submission number:  52891387
 *
 * Tests for program:
 * 1.
 * 6
 * 10.04.19 DSA_Read_Leacture 15
 * 10.04.19 DSA_Read_Tutorial 10
 * 10.04.19 DSA_Assigment 25
 * 12.04.19 DSA_Visist_Lab 20
 * 12.04.19 DSA_Do_Lab_Task 10
 * DO 12.04.19
 *
 * 2.
 * 6
 * 11.04.19 Motivation_Letter 15
 * 12.04.19 Read_article 10
 * 12.04.19 Presentation 25
 * 12.04.19 Solution_Analyses 25
 * DO 12.04.19
 * DO 11.04.19
 *
 */

import java.util.Scanner;

/**
 *  Class to execute the whole program
 */
public class Main {

    /**
     * Interface consisting of basic functions for implementation of a mergeable heap
     * @param <E> generic parameter
     */
    public interface MergeableHeap<E> {

        HeapNode<E> getHead();

        void setHead(HeapNode<E> HeapNode);

        boolean isEmpty();

        Pair<E> max();

        void merge(BinomialHeap<E> heap2);

        void insert(int key, E value);

        HeapNode<E> removeMax();

    }

    /**
     * Class for returning a key-value pair of a heap node
     * @param <E> generic parameter
     */
    public class Pair<E> {

        private int key;
        private E value;

        Pair(){
            key = 0;
            value = null;
        }

        Pair(int key, E value){
            this.key = key;
            this.value = value;
        }

        int getKey(){
            return key;
        }

        E getValue(){
            return value;
        }
    }

    /**
     * Class for a single element in a mergeable heap;
     * Each element is a node in a binomial heap
     * @param <E> generic parameter
     */
    public class HeapNode<E> {

        private int degree; // the depth of a binomial tree
        private int key; // integer key for denoting priority of a node
        private E value; // value stored in each node of a binomial tree
        private HeapNode<E> parent; // parent node at the next level up
        private HeapNode<E> child; // the leftmost child node
        private HeapNode<E> sibling; // the next(to the right) node at the same level

        HeapNode(){
            degree = -1;
            key = -1;
            value = null;
            parent = null;
            child = null;
            sibling = null;
        }

        HeapNode(E value, int key){
            degree = 0;
            this.key = key;
            this.value = value;
            parent = null;
            child = null;
            sibling = null;
        }

        /**
         * Method to set the degree of a node
         * @param degree is a given degree
         */
        void setDegree(int degree){
            this.degree = degree;
        }

        /**
         * Method to set the key of a node
         * @param key is a given key
         */
        void setKey(int key){
            this.key = key;
        }

        /**
         * Method to set the value of a node
         * @param value is a given value
         */
        void setValue(E value){
            this.value = value;
        }

        /**
         * Method to set the parent node
         * @param parent is a given node
         */
        void setParent(HeapNode<E> parent){
            this.parent = parent;
        }

        /**
         * Method to set the child node
         * @param child is a given node
         */
        void setChild(HeapNode<E> child){
            this.child = child;
        }

        /**
         * Method to set the sibling node
         * @param sibling is a given node
         */
        void setSibling(HeapNode<E> sibling){
            this.sibling = sibling;
        }

        int getKey(){
            return key;
        }

        E getValue(){
            return value;
        }

        int getDegree(){
            return degree;
        }

        HeapNode<E> getParent(){
            return parent;
        }

        HeapNode<E> getChild(){
            return child;
        }

        HeapNode<E> getSibling(){
            return sibling;
        }

        void incDegree(){
            degree += 1;
        }

    }

    /**
     * Class for implementation of a mergeable MAX heap by a binomial heap
     * @param <E> generic parameter
     */
    public class BinomialHeap<E> implements MergeableHeap<E> {

        private HeapNode<E> head; // node whose sibling node is the first binomial tree in the heap

        BinomialHeap() {
            head = new HeapNode<E>();
        }

        public HeapNode<E> getHead() {
            return head;
        }

        public void setHead(HeapNode<E> HeapNode) {
            head = HeapNode;
        }

        /**
         * Method to check whether the heap is empty or not
         * @return true if the heap is empty; false if heap is not empty
         */
        public boolean isEmpty() {
            if (head.getSibling() == null) {
                return true;
            }
            return false;
        }

        /**
         * Method to find the node with the max key
         * @return pair key-value of the node with the max key
         */
        public Pair<E> max() {

            HeapNode<E> HeapNode = new HeapNode<E>();
            HeapNode<E> cur = head.getSibling();
            int max = Integer.MIN_VALUE;

            while (cur != null) {

                if (cur.getKey() > max) {
                    max = cur.getKey();
                    HeapNode = cur;
                }
                cur = cur.getSibling();
            }

            Pair<E> pair = new Pair<>();
            try{
                pair = new Pair<>(HeapNode.getKey(), HeapNode.getValue());
            } catch(NullPointerException e){
                System.out.println("The heap was empty.");
            }

            return pair;
        }

        /**
         * Method links 2 roots of binomial trees B(k-1) with the same degree (k-1);
         * HeapNode z becomes the root of a binomial tree B(k) with degree k;
         * HeapNode y becomes the leftmost child of binomial tree B(k)
         *
         * @param y is the root HeapNode of binomial tree
         * @param z is the root HeapNode of another binomial tree
         */
        public void link(HeapNode<E> y, HeapNode<E> z) {
            y.setParent(z);
            y.setSibling(z.getChild());
            z.setChild(y);
            z.incDegree();
        }

        /**
         * Method to merge root lists of two binomial heaps
         * @param heap2 is the second heap which we merge with
         * @return merged binomial heap with repeated degrees of root nodes
         */
        public HeapNode<E> mergeRootLists(BinomialHeap<E> heap2) {

            BinomialHeap<E> newHeap = new BinomialHeap<>();

            HeapNode<E> curNew = newHeap.getHead();
            HeapNode<E> cur1 = head;
            HeapNode<E> cur2 = heap2.getHead();

            if (isEmpty()) {
                newHeap.setHead(heap2.getHead());
            } else {
                if (heap2.isEmpty()) {
                    newHeap.setHead(head);
                } else {
                    cur1 = cur1.getSibling();
                    cur2 = cur2.getSibling();
                    while (cur1 != null && cur2 != null) {

                        if (cur1.getDegree() <= cur2.getDegree()) {
                            curNew.setSibling(cur1);
                            curNew = curNew.getSibling();
                            cur1 = cur1.getSibling();
                        } else {
                            curNew.setSibling(cur2);
                            curNew = curNew.getSibling();
                            cur2 = cur2.getSibling();
                        }
                    }

                    if (cur1 == null && cur2 != null) {
                        curNew.setSibling(cur2);
                    }
                    if (cur2 == null && cur1 != null) {
                        curNew.setSibling(cur1);
                    }
                }
            }

            return newHeap.getHead();
        }

        /**
         * Method to merge two binomial  heaps
         * @param heap2 is the second heap which we merge with
         */
        public void merge(BinomialHeap<E> heap2) {

            BinomialHeap<E> newHeap = new BinomialHeap<>();
            newHeap.setHead(mergeRootLists(heap2)); // new heap is a merged binomial heap with repeated degrees of root nodes

            try{

                HeapNode<E> cur = newHeap.getHead().getSibling();
                HeapNode<E> prev = null;
                HeapNode<E> next = cur.getSibling();

                while (next != null) {

                    // if two root nodes have different degrees or there are three roots with the same degree in a row
                    if ((cur.getDegree() != next.getDegree()) || (next.getSibling() != null && next.getSibling().getDegree() == cur.getDegree())) {
                        prev = cur;
                        cur = next;
                    } else {
                        // if key of cur is greater, than next key, then it becomes a parent of next node
                        if (cur.getKey() >= next.getKey()) {
                            cur.setSibling(next.getSibling());
                            link(next, cur);
                        } else {
                            // if key of cur is smaller, than next key, then it becomes a child of next node
                            if (prev == null) {
                                newHeap.getHead().setSibling(next);
                            } else {
                                prev.setSibling(next);
                            }
                            link(cur, next);
                            cur = next;
                        }
                    }
                    next = cur.getSibling();
                }

                // the first(the current) heap becomes the merged heap
                setHead(newHeap.getHead());
            } catch (NullPointerException e){
                System.out.println("The new heap was empty.");
            }
        }

        /**
         * Method to insert a new key-value pair into the binomial heap
         * @param key is priority of a node
         * @param value is value of a node to store
         */
        public void insert(int key, E value) {

            BinomialHeap<E> newHeap = new BinomialHeap<>();
            HeapNode<E> HeapNode = new HeapNode<>(value, key);
            newHeap.getHead().setSibling(HeapNode);

            merge(newHeap); // merge old heap and heap with the new node
        }

        /**
         * Method to find a node occurring before the node with max key
         * @return a node occurring before the node with max key
         */
        public HeapNode<E> findPreMax() {

            int max = Integer.MIN_VALUE;
            HeapNode<E> cur = head;
            HeapNode<E> maxPreHeapNode = new HeapNode<E>();

            while (cur.getSibling() != null) {
                if (cur.getSibling().getKey() > max) {
                    max = cur.getSibling().getKey();
                    maxPreHeapNode = cur;
                }
                cur = cur.getSibling();
            }

            return maxPreHeapNode;
        }

        /**
         * Method to remove a node with max key
         * @return a node with max key
         */
        public HeapNode<E> removeMax() {

            if (isEmpty()) {
                return null;
            }

            HeapNode<E> maxPreHeapNode = findPreMax();
            HeapNode<E> maxHeapNode = maxPreHeapNode.getSibling();
            maxPreHeapNode.setSibling(maxHeapNode.getSibling()); // delete max node
        /*
            create a new heap consisting of children of max HeapNode;
            set its head to be the rightmost child(to preserve increasing order of
            degrees of binomial trees in the new heap)
         */
            BinomialHeap<E> newHeap = new BinomialHeap<>();
            HeapNode<E> cur = maxHeapNode.getChild();
            HeapNode<E> auxilNext = null;
            HeapNode<E> auxilPrev = null;
            try {
                if (cur != null) {
                    auxilNext = cur.getSibling();
                }
                while (auxilNext != null) {
                    cur.setSibling(auxilPrev);
                    auxilPrev = cur;
                    cur = auxilNext;
                    auxilNext = cur.getSibling();
                }
                cur.setSibling(auxilPrev);

            } catch (NullPointerException e){
                System.out.println("The max node does not have children");
            }

            newHeap.getHead().setSibling(cur);
            merge(newHeap); // merge heap with max node children and the heap which we delete max node's tree from
            return maxHeapNode;
        }

        /**
         * Method to find a node that has the longest path to the root;
         * Only for testing and debugging
         * @param root is a root node of a binomial tree
         * @return the leftmost leaf node
         */
        public HeapNode<E> traverseTree(HeapNode<E> root) {

            HeapNode<E> cur = root;
            while (cur.getDegree() > 0) {
                cur = cur.getChild();
            }
            return cur;
        }

        /**
         * Method to print pair key-value of a heap;
         * Only for debugging and testing
         */
        public void printHeap() {
            HeapNode<E> curRoot = head.getSibling();
            HeapNode<E> cur;

            if (curRoot == null) {
                System.out.println("empty heap");
            }

            while (curRoot != null) {
                System.out.print("curRoot value is " + curRoot.getValue() + " ");
                System.out.print("curRoot key is " + curRoot.getKey() + " ");
                System.out.println("curRoot degree is " + curRoot.getDegree() + " ");

                cur = traverseTree(curRoot);
                System.out.println("cur key after traverse" + cur.getKey());

                while (cur != curRoot) {
                    System.out.print("cur value is " + cur.getValue() + " ");
                    System.out.println("cur key is " + cur.getKey());

                    while (cur.getSibling() != null) {
                        cur = cur.getSibling();
                        System.out.print("cur value is " + cur.getValue() + " ");
                        System.out.println("cur key is " + cur.getKey());

                    }
                    System.out.println("the end of the layer");
                    cur = cur.getParent();
                }

                System.out.println("the end of curRoot");
                curRoot = curRoot.getSibling();
            }
        }
    }

    /**
     * Class for containing information about a task
     */
    public class TaskInfo {

        private String dateStr; // date in String representation
        private int dd, mm, yy; // date in integer representation; dd-day, mm-month, yy-year
        private String task;
        private int priority;

        TaskInfo(String dateStr, String task, String priority){
            this.task = task;
            this.dateStr = dateStr;
            setDate(dateStr);
            this.priority = Integer.parseInt(priority);
        }

        TaskInfo(String dateStr){
            this.dateStr = dateStr;
        }

        String getDateStr(){
            return dateStr;
        }

        String getTask(){
            return task;
        }

        int getPriority(){
            return priority;
        }

        int getDd(){
            return dd;
        }

        int getMm(){
            return mm;
        }

        int getYy(){
            return yy;
        }

        void setDateStr(String str){
            dateStr = str;
        }

        void setTask(String str){
            task = str;
        }

        void setDate(String str){
            String temp;
            temp = str.substring(0,2);
            dd = Integer.parseInt(temp);
            temp = str.substring(3, 5);
            mm = Integer.parseInt(temp);
            temp = str.substring(6);
            yy = Integer.parseInt(temp);
        }

    }

    /**
     * Class that represents each element(a single TO-DO list) in a list of TO-DO lists
     * @param <E> generic parameter
     */
    public class ListNode<E> {

        private BinomialHeap<E> toDo; // TO-DO list implemented with a binomial heap
        private ListNode<E> next; // next TO-DO list
        private String date; // date of a TO-DO list
        private int dd, mm, yy;

        ListNode(){
            next = null;
            toDo = null;
            date = null;
            dd = 0;
            mm = 0;
            yy = 0;
        }

        ListNode(TaskInfo taskInfo){
            next = null;
            toDo = new BinomialHeap<>();
            this.date = taskInfo.getDateStr();
            this.dd = taskInfo.getDd();
            this.mm = taskInfo.getMm();
            this.yy = taskInfo.getYy();
        }

        void setToDo(BinomialHeap<E> heap){
            toDo = heap;
        }

        void setNext(ListNode<E> node){
            next = node;
        }

        void setDate(String date){
            this.date = date;
        }

        void setDd(int dd){
            this.dd = dd;
        }

        void setMm(int mm){
            this.mm = mm;
        }

        void setYy(int yy){
            this.yy = yy;
        }

        ListNode<E> getNext(){ return next; }

        BinomialHeap<E> getToDo(){
            return toDo;
        }

        String getDate(){
            return date;
        }

        int getDd(){
            return dd;
        }

        int getMm(){
            return mm;
        }

        int getYy(){
            return yy;
        }

        boolean isEmpty(){
            if (toDo.isEmpty()){
                return true;
            }
            return false;
        }

        /**
         * Method to compare dates of two TO-DO lists
         * @param node is a TO-DO list which we compare with
         * @return true if this date is older, than node's date
         *         otherwise, false
         */
        boolean isSmaller(ListNode<E> node){
            if (yy < node.getYy()){
                return true;
            }
            if (yy > node.getYy()){
                return false;
            }
            if (mm < node.getMm()){
                return true;
            }
            if (mm > node.getMm()){
                return false;
            }
            if (dd < node.getDd()){
                return true;
            }
            if (dd > node.getDd()){
                return false;
            }
            return false;
        }

        /**
         * Method to print tasks of a single TO-DO list in descending order of priority;
         * Also to construct a binomial heap containing tasks of all TO-DO lists
         * @param commonHeap is a binomial heap containing tasks of all TO-DO lists
         */
        public void printToDo(BinomialHeap<E> commonHeap){

            HeapNode<E> cur;

            while (!isEmpty()){
                cur = this.getToDo().removeMax();
                commonHeap.insert(cur.getKey(), cur.getValue());
                System.out.println("\t"+cur.getValue());
            }

        }

    }

    /**
     * Class that implements list of TO-DO lists by singly linked list
     * @param <E> generic parameter
     */
    public class ListOfLists<E> {

        private ListNode<String> listHead; // list's node that contain the first TO-DO list
        private int size = 0;

        ListOfLists() {
            listHead = null;
        }

        ListNode<String> getListHead() {
            return listHead;
        }

        void setListHead(ListNode<String> node) {
            listHead = node;
        }

        /**
         * Method to determine whether there is a TO-DO list of a certain date in the list of lists
         * @param taskInfo is information about a task, especially date
         * @return null if there is no a TO-DO list of a certain date;
         *         otherwise, node with such TO-DO list
         */
        ListNode<String> findDate(TaskInfo taskInfo) {

            ListNode<String> cur = listHead;

            while (cur != null) {
                if (cur.getDate().equals(taskInfo.getDateStr())) {
                    return cur;
                }
                cur = cur.getNext();
            }

            return cur;
        }

        /**
         * Method to find a correct position of a TO-DO in the list of lists
         * according to ascending order of dates
         * @param node is a given node which we find position of
         * @return node that should be in the list before a given node
         */
        ListNode<String> findPosition(ListNode<String> node) {

            ListNode<String> cur = listHead;
            ListNode<String> prev = null;

            while (cur != null && cur.isSmaller(node)) {
                prev = cur;
                cur = cur.getNext();
            }
            return prev;
        }

        /**
         * Method to insert a TO-DO list into the list of lists
         * @param node represents a TO-DO list to be added into the list of lists
         */
        void insertNode(ListNode<String> node) {

            ListNode<String> pos = findPosition(node);
            if (pos == null) {
                // insert in the beginning
                node.setNext(listHead);
                listHead = node;
            } else {
                node.setNext(pos.getNext());
                pos.setNext(node);
            }
        }

        /**
         * Method to add task in a list of lists
         * @param taskInfo is information about a task to be added
         */
        void addTask(TaskInfo taskInfo) {

            ListNode<String> newNode = findDate(taskInfo);

            if (newNode == null) {
                // create ListNode with task; insert newNode into the list
                newNode = new ListNode<>(taskInfo);
                newNode.getToDo().insert(taskInfo.getPriority(), taskInfo.getTask());
                // insert to the right position in listOfLists (ascending order of dates)
                insertNode(newNode);
                size += 1;
            } else {
                newNode.getToDo().insert(taskInfo.getPriority(), taskInfo.getTask());
            }
        }

        /**
         * Method to delete task from a certain TO-DO list
         * @param taskInfo is information about a task to be deleted
         */
        void removeTask(TaskInfo taskInfo) {

            ListNode<String> cur = findDate(taskInfo);
            if (cur != null) {
                cur.getToDo().removeMax();
            }
        }

        /**
         * Method to print TO-DO lists in the list of lists
         * For testing and debugging only
         */
        void printList() {

            ListNode<String> cur = listHead;

            while (cur != null) {
                System.out.println("cur date is " + cur.getDate());
                System.out.println("cur heap is");
                cur.getToDo().printHeap();
                System.out.println("the end of node");
                cur = cur.getNext();
            }
        }

    }

    /* global variables */
    ListOfLists<String> listOfLists; // list of TO-DO lists
    BinomialHeap<String> commonHeap; // heap for merging all tasks

    /**
     * Method to read input: tasks and commands
     * @param listOfLists is a list that will hold TO-DO lists
     * @param <E> generic parameter; will be String, because values of a TO-DO list is of type String
     */
    public <E> void read(ListOfLists<E> listOfLists){

       Scanner scanner = new Scanner(System.in);
       String line;
       String strArray[];
       int i = 0;
       int n = scanner.nextInt();
       String date;
       scanner.nextLine();

       while (i<n){

           line = scanner.nextLine();
           strArray = line.split(" ");

           // there are 3 components in a line -> create a new task
           if (strArray.length == 3){
                TaskInfo task = new TaskInfo(strArray[0], strArray[1], strArray[2]);
                listOfLists.addTask(task);
           }
           // otherwise there are 2 components -> delete task
           else{
               TaskInfo task = new TaskInfo(strArray[1]);
               listOfLists.removeTask(task);
           }

           i++;
       }
    }

    /**
     * Method to print all TO-DO lists one by one
     * @param listOfLists is a list that will hold TO-DO lists
     * @param commonHeap is a binomial heap that contains all tasks of all TO-DO lists
     */
    public void printToDoLists(ListOfLists<String> listOfLists, BinomialHeap<String> commonHeap){

        ListNode<String> cur = listOfLists.getListHead();

        while(cur != null){

            System.out.println("TODOList "+ cur.getDate());
            cur.printToDo(commonHeap);
            cur = cur.getNext();
        }
    }

    /**
     * Method to print a commonHeap which contains all tasks of all TO-DO lists
     */
    public void printMergedList(){

        System.out.println("TODOList ");

        HeapNode<String> cur;
        while(!commonHeap.isEmpty()){
            cur = commonHeap.removeMax();
            System.out.println("\t"+cur.getValue());
        }

    }

    /**
     * Method to execute the whole program
     * @param args is array of strings representing commands for execution of a program
     */
    public static void main(String args[]){

        Main main = new Main();
        main.listOfLists = main.new ListOfLists<>();
        main.commonHeap = main.new BinomialHeap<>();
        main.read(main.listOfLists);
        main.printToDoLists(main.listOfLists, main.commonHeap);
        main.printMergedList();
    }
}
