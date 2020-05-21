public class HeapNode<E> {

    private int degree;
    private int key;
    private E value;
    private HeapNode<E> parent;
    private HeapNode<E> child;
    private HeapNode<E> sibling;

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

    void setDegree(int degree){
        this.degree = degree;
    }

    void setKey(int key){
        this.key = key;
    }

    void setValue(E value){
        this.value = value;
    }

    void setParent(HeapNode<E> parent){
        this.parent = parent;
    }

    void setChild(HeapNode<E> child){
        this.child = child;
    }

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
