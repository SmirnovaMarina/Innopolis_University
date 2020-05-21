import java.util.Scanner;

/**
 * Class for implementation operations with tournaments
 * @author Smirnova Marina
 *
 */
public class Tour {
    /** a list of references to dynamic arrays that contain teams;
     * for each tournament creates a new node
     */
    DoublyLinkedList<DynamicArray> listOfTours = new DoublyLinkedList<>();

    /**
     * Method for reading data about all tournaments from console
     */
    void readAll(){
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.nextLine();
        for (int i = 0; i < n; i++) {
            DynamicArray<Data> dynamicArray = new DynamicArray<>();
            read(dynamicArray, scanner);
            listOfTours.addFirst(dynamicArray);
        }
    }

    /**
     * Method for reading from console for a single tournament
     * @param list a list of references to dynamic arrays that contain teams;
     * for each tournament creates a new node
     * @param scanner
     */
    void read(List<Data> list, Scanner scanner){
        int teams;
        int games;
        Data data;
        String tour = scanner.nextLine();
        teams = scanner.nextInt();
        scanner.nextLine();
        for (int j = 0; j<teams; j++) {
            data = new Data();
            data.setName(scanner.nextLine());
            data.setTour(tour);
            list.addFirst(data);
        }

        games = scanner.nextInt();
        scanner.nextLine();
        String string;
        String arraySplit[];
        int wins1 = 0;
        int wins2 = 0;
        int tie = 0;
        int goals1;
        int goals2;
        Data cur1, cur2;

        for (int k = 0; k<games; k++){
            string = scanner.nextLine();
            arraySplit = string.split("[#:]");
            goals1 = Integer.parseInt(arraySplit[1]);
            goals2 = Integer.parseInt(arraySplit[2]);
            cur1 = List.find(arraySplit[0], list);
            cur2 = List.find(arraySplit[3], list);

            cur1.incGames();
            cur2.incGames();

            cur1.incGoalsScored(goals1);
            cur2.incGoalsScored(goals2);
            cur1.incGoalsMissed(goals2);
            cur2.incGoalsMissed(goals1);
            cur1.setGoalsDif();
            cur2.setGoalsDif();

            if (goals1 > goals2){
                cur1.incWins();
                cur2.incLoses();
                cur1.incPoints(3);
            }
            else {
                if (goals1 == goals2){
                    cur1.incTies();
                    cur2.incTies();
                    cur1.incPoints(1);
                    cur2.incPoints(1);
                }
                else{
                    cur1.incLoses();
                    cur2.incWins();
                    cur2.incPoints(3);
                }
            }

        }
    }

    /**
     * Method that implements sorting algorithm for each tournament
     */
    void sort(){
        int n = listOfTours.getSize();
        for(int i = 0; i<n; i++){
            List.sortTeams(listOfTours.get(i));
        }
    }

    /**
     * prints data about a single tournament
     * @param list contains data about a single tournament;
     *             data about each team in a tournament
     */
    void print(List<Data> list){
        int n = list.getSize();
        Data cur;

        cur = list.get(0);
        System.out.println(cur.getTour());
        for (int i = 0; i < n; i++){
            cur = list.get(i);

            System.out.print((i+1) +") ");
            System.out.print(cur.getName()+" ");
            System.out.print(cur.getPoints()+"p, ");
            System.out.print(cur.getGames()+"g ");
            System.out.print("("+cur.getWins()+"-");
            System.out.print(cur.getTies()+"-"+cur.getLoses()+"), ");
            System.out.print(cur.getGoalsDif()+"gd ");
            System.out.print("("+cur.getGoalsScored()+"-"+cur.getGoalsMissed()+")");
            System.out.println();
        }
    }

    /**
     * prints data about all tournaments(the whole list of tournaments)
     */
    void printList(){
        int n = listOfTours.getSize();
        DynamicArray<Data> cur;

        for (int i = n-1; i>=0; i--){
            cur = listOfTours.get(i);
            print(cur);
            System.out.println();
        }
    }
}
