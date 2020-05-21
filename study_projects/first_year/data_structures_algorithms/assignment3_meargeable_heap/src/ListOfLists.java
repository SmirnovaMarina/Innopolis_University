/**
 * Class that implements list of TO-DO lists by doubly linked list
 * @author Smirnova Marina
 *
 */
public class ListOfLists<E> {

    private ListNode<String> listHead;
    private int size = 0;

    ListOfLists(){
        listHead = null;
    }

    ListNode<String> getListHead(){
        return listHead;
    }

    int getSize(){
        return size;
    }

    void setListHead(ListNode<String> node){
        listHead = node;
    }

    ListNode<String> findDate(TaskInfo taskInfo){

        ListNode<String> cur = listHead;

        while(cur != null){
            if (cur.getDate().equals(taskInfo.getDateStr())){
                return cur;
            }
            cur = cur.getNext();
        }

        return cur;
    }

    ListNode<String> findPosition(ListNode<String> node){

        ListNode<String> cur = listHead;
        ListNode<String> prev = null;

        while (cur != null && cur.isSmaller(node)){
            prev = cur;
            cur = cur.getNext();
        }
        return prev;
    }

    void insertNode(ListNode<String> node){

        ListNode<String> pos = findPosition(node);
        if (pos == null){
            // insert in the beginning
            node.setNext(listHead);
            listHead = node;
        }
        else{
            node.setNext(pos.getNext());
            pos.setNext(node);
        }
    }

    void addTask(TaskInfo taskInfo){

        ListNode<String> newNode = findDate(taskInfo);

        if (newNode == null){
            //System.out.println("-------------");
            // create ListNode with task; insert newNode into the list
            //System.out.println("date is not found "+taskInfo.getDateStr());
            newNode = new ListNode<>(taskInfo);
            newNode.getToDo().insert(taskInfo.getPriority(), taskInfo.getTask());
            //System.out.println("to do after insertion");
            //newNode.getToDo().printHeap();
            //System.out.println("-------------");
            // insert to the right position in listOfLists (ascending order of dates)
            insertNode(newNode);
            size += 1;
        }
        else{
            newNode.getToDo().insert(taskInfo.getPriority(), taskInfo.getTask());
        }
    }

    void removeTask(TaskInfo taskInfo){

        ListNode<String> cur = findDate(taskInfo);
        if (cur != null){
            cur.getToDo().removeMax();
        }
    }

    void printList(){

        ListNode<String> cur = listHead;

        while(cur != null){
            System.out.println("cur date is "+cur.getDate());
            System.out.println("cur heap is");
            cur.getToDo().printHeap();
            System.out.println("the end of node");
            cur = cur.getNext();
        }
    }

}