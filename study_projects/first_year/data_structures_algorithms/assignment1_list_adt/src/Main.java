/**
 * Class to test the overall program
 * @author Smirnova Marina
 * Number of submission to CodeForces 49926144 : full solution
 */

/**
 * Tests for program:
 * 2
 * World Cup 1998 - Group A
 * 4
 * Brazil
 * Norway
 * Morocco
 * Scotland
 * 6
 * Brazil#2:1#Scotland
 * Norway#2:2#Morocco
 * Scotland#1:1#Norway
 * Brazil#3:0#Morocco
 * Morocco#3:0#Scotland
 * Brazil#1:2#Norway
 * Some strange tournament
 * 5
 * Team A
 * Team B
 * Team C
 * Team D
 * Team E
 * 5
 * Team A#1:1#Team B
 * Team A#2:2#Team C
 * Team A#0:0#Team D
 * Team E#2:1#Team C
 * Team E#1:2#Team D
 *
 *
 * 1
 * tour
 * 3
 * aaa
 * bbb
 * ccc
 * 3
 * aaa#1:1#bbb
 * bbb#1:1#ccc
 * aaa#1:1#ccc
 */

import java.util.Scanner;

public class Main {


    void execute(){
        Tour tour = new Tour();
        tour.readAll();
        tour.sort();
        tour.printList();

        DynamicArray<Data> array = new DynamicArray<>();

    }
    public static void main(String args[]){
        Main main = new Main();
        main.execute();
    }


}

