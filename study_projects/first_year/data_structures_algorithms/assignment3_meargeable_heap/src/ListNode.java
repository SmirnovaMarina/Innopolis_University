public class ListNode<E> {

    private BinomialHeap<E> toDo;
    private ListNode<E> next;
    private String date;
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

    ListNode<E> getNext(){
        return next;
    }

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

    public void printToDo(){

        BinomialHeap<E> copy = new BinomialHeap<>(); // create empty heap
        copy.merge(this.getToDo());

        HeapNode<E> cur;

        while (!copy.isEmpty()){
            cur = copy.removeMax();
            System.out.println("\t"+cur.getValue());
        }
    }

}
