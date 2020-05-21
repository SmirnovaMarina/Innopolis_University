/**
 * Interface of a ADS list
 * @author Smirnova Marina
 *
 */
public interface List<E> {

    boolean isEmpty();

    int getSize();

    void add(int i, E e);

    void addFirst(E e);

    void addLast(E e);

    void delete(E e);

    void delete(int i);

    void deleteFirst();

    void deleteLast();

    void set(int i, E e);

    E get(int i);

    /**
     * Method for selection sorting of a list
     * @param list data structure which we want to sort
     * @param <E> any type
     *
     */
    static <E extends Comparable> void sortTeams(List<E> list){
        int size = list.getSize();
        E max;
        int maxPos = 0;
        E cur;

        for (int i = 0; i<size; i++){
            max = list.get(i);
            maxPos = i;
            for (int j = i; j<size; j++){
                cur = list.get(j);
                if (cur.compareTo(max) == 1){
                    max = cur;
                    maxPos = j;
                }
            }

            list.delete(maxPos);
            list.add(i, max);
        }
    }
    /**
     * Method to find a team in a list by its name
     * @param name is a name of team that we want to find in a list
     * @param list
     * @return cur is a data element in a list that matches the name of a team
     */
    static Data find(String name, List<Data> list){

        int i = 0;
        int size = list.getSize();
        Data cur;

        while (i<size){
            cur = list.get(i);
            if (cur.getName().equals(name)){
                return cur;
            }
            i += 1;
        }
        return null;
    }
}
