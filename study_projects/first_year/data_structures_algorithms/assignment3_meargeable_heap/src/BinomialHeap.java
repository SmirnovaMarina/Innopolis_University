public class BinomialHeap<E> implements MergeableHeap<E>{

    private HeapNode<E> head;

    BinomialHeap(){
        head = new HeapNode<E>();
    }

    public HeapNode<E> getHead(){
        return head;
    }

    public void setHead(HeapNode<E> HeapNode){
        head = HeapNode;
    }

    public boolean isEmpty(){
        if (head.getSibling() == null){
            return true;
        }
        return false;
    }

    public HeapNode<E> max(){

        HeapNode<E> HeapNode = new HeapNode<E>();
        HeapNode<E> cur = head.getSibling();
        int max = Integer.MIN_VALUE;

        if (cur == null){
            System.out.println("empty");
        }

        while (cur != null){

            if (cur.getKey() > max) {
                max = cur.getKey();
                HeapNode = cur;
            }
            cur = cur.getSibling();
        }

        return HeapNode;
    }

    /**
     * Method links 2 roots of binomial trees B(k-1) with the same degree (k-1);
     * HeapNode z becomes the root of a binomial tree B(k) with degree k;
     * HeapNode y becomes the leftmost child of binomial tree B(k)
     * @param y is the root HeapNode of binomial tree
     * @param z is the root HeapNode of another binomial tree
     */
    public void link(HeapNode<E> y, HeapNode<E> z){
        y.setParent(z);
        y.setSibling(z.getChild());
        z.setChild(y);
        z.incDegree();
    }

    public HeapNode<E> mergeRootLists(BinomialHeap<E> heap2){

        BinomialHeap<E> newHeap = new BinomialHeap<>();

        HeapNode<E> curNew = newHeap.getHead();
        HeapNode<E> cur1 = head;
        HeapNode<E> cur2 = heap2.getHead();

        if (isEmpty()){
            newHeap.setHead(heap2.getHead());
        }
        else {
            if (heap2.isEmpty()) {
                newHeap.setHead(head);
            }
            else{
                cur1 = cur1.getSibling();
                cur2 = cur2.getSibling();
                while(cur1 != null && cur2 != null){

                    if (cur1.getDegree() < cur2.getDegree()) {
                        curNew.setSibling(cur1);
                        curNew = curNew.getSibling();
                        cur1 = cur1.getSibling();
                    } else {
                        curNew.setSibling(cur2);
                        curNew = curNew.getSibling();
                        cur2 = cur2.getSibling();
                    }
                }

                if (cur1 == null && cur2 != null){
                    curNew.setSibling(cur2);
                }
                if (cur2 == null && cur1 != null){
                    curNew.setSibling(cur1);
                }
            }
        }

        //newHeap.printHeap();
        return newHeap.getHead();
    }

    public void merge(BinomialHeap<E> heap2){

        BinomialHeap<E> newHeap = new BinomialHeap<>();
        newHeap.setHead(mergeRootLists(heap2));
        //System.out.println("newHeap after merge of 2 root lists");
        //newHeap.printHeap();

        if (newHeap.getHead().getSibling() != null){

                HeapNode<E> cur = newHeap.getHead().getSibling();
                HeapNode<E> prev = null;
                HeapNode<E> next = cur.getSibling();

                while (next != null) {
                    if ((cur.getDegree() != next.getDegree()) || (next.getSibling() != null && next.getSibling().getDegree() == cur.getDegree())) {
                        prev = cur;
                        cur = next;
                    } else {
                        if (cur.getKey() >= next.getKey()) {
                            cur.setSibling(next.getSibling());
                            link(next, cur);
                        } else {
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
                //System.out.println("new heap after merge");
                //newHeap.printHeap();
                setHead(newHeap.getHead());
                //System.out.println("initial heap after sethead of newhead");
                //printHeap();
        }
    }

    public void insert(int key, E value){

        BinomialHeap<E> newHeap = new BinomialHeap<>();
        HeapNode<E> HeapNode = new HeapNode<>(value, key);
        newHeap.getHead().setSibling(HeapNode);

        merge(newHeap);
    }

    public HeapNode<E> findPreMax(){

        int max = Integer.MIN_VALUE;
        HeapNode<E> cur = head;
        HeapNode<E> maxPreHeapNode = new HeapNode<E>();

        while (cur.getSibling() != null){
            if (cur.getSibling().getKey() > max){
                max = cur.getSibling().getKey();
                maxPreHeapNode = cur;
            }
            cur = cur.getSibling();
        }

        return maxPreHeapNode;
    }

    public HeapNode<E> removeMax(){

        if (isEmpty()){
            return null;
        }

        HeapNode<E> maxPreHeapNode = findPreMax();
        //System.out.println("maxpreNode key"+maxPreHeapNode.getKey());
        HeapNode<E> maxHeapNode = maxPreHeapNode.getSibling();
        //System.out.println("maxNode key "+maxHeapNode.getValue());
        maxPreHeapNode.setSibling(maxHeapNode.getSibling());
        /*
            create a new heap consisting of children of max HeapNode;
            set its head to be the rightmost child(to preserve increasing order of
            degrees of binomial trees in the new heap
         */
        BinomialHeap<E> newHeap = new BinomialHeap<>();
        HeapNode<E> cur = maxHeapNode.getChild();
        HeapNode<E> auxilNext = null;
        HeapNode<E> auxilPrev = null;
        if (cur != null) {
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

        }

        newHeap.getHead().setSibling(cur);
        merge(newHeap);
        return maxHeapNode;
    }

    public HeapNode<E> traverseTree(HeapNode<E> root){

        HeapNode<E> cur = root;
        while(cur.getDegree() > 0){
            cur = cur.getChild();
        }
        return cur;
    }

    public void printHeap(){
        HeapNode<E> curRoot = head.getSibling();
        HeapNode<E> cur;

        if (curRoot == null){
            System.out.println("empty heap");
        }

        while (curRoot != null) {
            System.out.print("curRoot value is " + curRoot.getValue()+" ");
            System.out.print("curRoot key is " + curRoot.getKey()+" ");
            System.out.println("curRoot degree is "+curRoot.getDegree()+" ");

            cur = traverseTree(curRoot);
            System.out.println("cur key after traverse"+cur.getKey());

                while (cur != curRoot) {
                    System.out.print("cur value is " + cur.getValue()+" ");
                    System.out.println("cur key is " + cur.getKey());

                    while (cur.getSibling() != null) {
                        cur = cur.getSibling();
                        System.out.print("cur value is " + cur.getValue()+" ");
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
