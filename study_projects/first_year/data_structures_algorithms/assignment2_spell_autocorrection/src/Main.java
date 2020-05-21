/**
 * Class with the algorithm and processing data the overall program
 * @author Smirnova Marina
 * Number of submission to CodeForces:
 * A. 50867514 full solution
 * B. 50899705 full solution
 *
 * Tests for Task A:
 * 10
 * cat cat
 * cut cat
 * cat clot
 * giraffe pirate
 * assynmment assignment
 * persnetadg percentage
 *
 * Tests for Task B:
 * 5
 * cat cut clot plot blog
 * bloat
 */

import java.util.Scanner;

public class Main {

    /**
     * Class that implements ADS list by doubly linked list
     * @author Smirnova Marina
     *
     */
    public class List {

        /** header node is linked with the first element
         *  trailer is linked with the last element */
        private Node header;
        private Node trailer;

        /** current amount of elements in a list*/
        private int size = 0;

        /** Constructor creates a list with header and trailer connected with each other
         *  with no elements between them(means no elements in a list)*/
        List(){
            header = new Node(null, null, null);
            trailer = new Node(null, null, header);
            header.setNext(trailer);
        }

        void addFirst(String string){
            Node node = new Node(string, header.getNext(), header);
            header.getNext().setPrev(node);
            header.setNext(node);
            size += 1;

        }

        /**
         * Method to get current number of elements in a list
         * @return current amount of elements in a list
         */
        int getSize(){
            return size;
        }

        /**
         * Method to compare and add a new word at certain position
         * Organize a list of words in lexicographical order
         * @param string is an element to add
         */
        void compareAndInsert(String string){
            Node newNode = new Node(string, null, null);
            Node compareWith = header;
            int condition;
            int position = 0;

            do{
                position += 1;
                compareWith = compareWith.getNext();
                condition = string.compareTo(compareWith.getWord());

            } while(condition > 0 && position < size);

            if (position == size && condition>0){
                newNode.setNext(trailer);
                newNode.setPrev(compareWith);
                compareWith.setNext(newNode);
                trailer.setPrev(newNode);
            }
            else {
                newNode.setNext(compareWith);
                newNode.setPrev(compareWith.getPrev());
                compareWith.getPrev().setNext(newNode);
                compareWith.setPrev(newNode);
            }
            size += 1;
        }

        /**
         * Method to delete all elements of a list
         */
        void removeAll(){
            header.setNext(trailer);
            trailer.setPrev(header);
            size = 0;
        }

        /**
         * Method to print all elements of a list
         */
        void printList(){
            Node current = header.getNext();
            for (int i = 0; i<size; i++){
                if (i != size-1){
                    System.out.print(current.getWord()+" ");
                }
                else {
                    System.out.print(current.getWord());
                }

                current = current.getNext();
            }
        }

        boolean findWord(String word){
            Node current = header;
            int i = 0;

            while (i<size){
                current = current.getNext();
                i += 1;
                if (current.getWord().equals(word)){
                    current.incFrequency();
                    return true;
                }
            }
            return false;
        }

        public String estimateDictionary(String word){
            Node current = header;
            int mistakes;
            int maxFreq = 0;
            int min = Integer.MAX_VALUE;
            String correction = "";

            for (int i = 0; i<size; i++){
                current = current.getNext();
                mistakes = estimate(word, current.getWord());
                if (mistakes<min){
                    min = mistakes;
                    correction = current.getWord();
                    maxFreq = current.getFrequency();
                }
                else {
                    if (mistakes == min){
                        if (current.getFrequency()>maxFreq){
                            maxFreq = current.getFrequency();
                            correction = current.getWord();
                        }
                    }
                }
            }
            return correction;
        }
    }

    /**
     * Class for nodes of a doubly linked list
     * @author Smirnova Marina
     *
     */
    public class Node {

        /** content of a node*/
        private String word;
        private int frequency = 0;

        /** next is the next node
         * prev is the previous node*/
        private Node next;
        private Node prev;

        Node(String string, Node next, Node prev){
            this.next = next;
            this.prev = prev;
            word = string;
        }


        String getWord(){
            return word;
        }

        int getFrequency(){
            return frequency;
        }

        Node getNext(){
            return next;
        }

        Node getPrev(){
            return prev;
        }

        void setWord(String string){
            word = string;
        }

        void incFrequency(){
            frequency += 1;
        }

        void setNext(Node next){
            this.next = next;
        }

        void setPrev(Node prev){
            this.prev = prev;
        }

    }

    /**
     * Method to define a min value from
     * @param firstCase number of operations
     * @param secondCase number of operations
     * @param thirdCase number of operations
     * @return min value from these arguments
     */
    public int minNumOfOper(int firstCase, int secondCase, int thirdCase){

        if (firstCase<=secondCase){
            if (firstCase<=thirdCase){
                return firstCase;
            }
            else {
                return thirdCase;
            }
        }
        else {
            if (secondCase<=thirdCase){
                return secondCase;
            }
            else {
                return thirdCase;
            }
        }
    }

    /**
     * Method to define a min value from two arguments
     * @param firstCase number of operations
     * @param secondCase number of operations
     * @return a min value from these two arguments
     */
    public int min(int firstCase, int secondCase){

        if (firstCase>secondCase){
            return secondCase;
        }
        return firstCase;
    }

    /**
     * Method to determine whether a character of one string is equal to a character
     * of another string
     * @param ithSymOfStr1 a single character from a string
     * @param jthSymOfStr2 a single character from another string
     * @return int value 0 if characters are equal; otherwise 1
     */
    public int match(char ithSymOfStr1, char jthSymOfStr2){
        if (ithSymOfStr1 == jthSymOfStr2){
            return 0;
        }
        return 1;
    }

    /**
     * Method to estimate the minimal number of misspellings in a word
     *
     * Kinds of mistakes are an extra character, replacement of adjacent characters,
     * deletion of a character and an incorrect character.
     * Therefore, operations are insertion, replacement, deletion and substitution
     *
     * It uses a Damerau Levenshtein Distance algorithm to calculate amount of mistakes
     *
     * @param str1 a string to compare
     * @param str2 a string to compare with str1
     * @return a number of misspellings
     */
    public int estimate(String str1, String str2){

        String stringS; // small string
        String stringL; // long string

        /**
         * matrix of number operations to get one string(small one) from another(long one)
         */
        int matrixOfOper[][];
        int M,N; // dimensions of matrixOfOper

        int firstCase, secondCase, thirdCase; // vars for amount of operations in three cases

        /**
         * determine which string is longer and initialize the matrix with [M][N] dimensions,
         * where M >= N
         */
        if (str1.length()>str2.length()){
            stringL = str1;
            stringS = str2;
        }
        else {
            stringL = str2;
            stringS = str1;
        }
        M = stringL.length();
        N = stringS.length();
        matrixOfOper = new int[M+1][N+1];
        matrixOfOper[0][0] = 0; // 0 operations to get empty string from empty string

        for (int i = 0; i<M+1; i++){
            for (int j = 0; j<N+1; j++){

                // j insertions to get j character string
                if (i == 0 && j>0){
                    matrixOfOper[i][j] = j;
                }
                // i deletions to get an empty string
                if (j==0 && i>0){
                    matrixOfOper[i][j] = i;
                }

                // firstly, check for deletion, insertion and substitution
                if (i>0 && j>0){

                    firstCase = matrixOfOper[i-1][j]+1; // for deletion
                    secondCase = matrixOfOper[i][j-1]+1; // for insertion
                    thirdCase = matrixOfOper[i-1][j-1] + match(stringL.charAt(i-1), stringS.charAt(j-1)); // for substitutions
                    matrixOfOper[i][j] = minNumOfOper(firstCase, secondCase, thirdCase);
                }

                /** check for transpositions, only if char at ith position of long string
                 * is equal to jth character of a small string
                 */
                if (i>1 && j>1 && stringL.charAt(i-1)==stringS.charAt(j-1-1) && stringL.charAt(i-1-1)==stringS.charAt(j-1)){
                    matrixOfOper[i][j] = min(matrixOfOper[i][j], matrixOfOper[i-2][j-2]+match(stringL.charAt(i-1), stringS.charAt(j-1)));
                }
            }
        }

        return matrixOfOper[M][N]; // the number of mistakes
    }

    /**
     * Method to read strings of two words, find amount of misspellings between them
     * and display this amount for each pair
     * Task 1 method
     */
    public void writeMisspellings(){
        int n;
        String line;
        String array[];

        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        scanner.nextLine();
        for (int i = 0; i<n; i++){
            line = scanner.nextLine();
            array = line.split(" ");
            System.out.println(estimate(array[0], array[1]));
        }
    }

    /**
     * Method to suggest the most suitable corrections with the smallest amount of
     * misspellings
     * Task 2 method
     */
    public void suggestCorrections(){
        int n;
        int min = Integer.MAX_VALUE;
        int mistakes;
        Scanner scanner = new Scanner(System.in);
        String checkWord;
        String dictionary[]; // array of given words

        /** list DS for fast deletion of all elements and fast insertion*/
        List listOfSuggestions = new List();

        n = scanner.nextInt();
        scanner.nextLine();
        dictionary = new String[n];

        for (int i = 0; i<n; i++){
            dictionary[i] = scanner.next();
        }
        scanner.nextLine();
        checkWord = scanner.nextLine();
        for (int i = 0; i<n; i++){
            mistakes = estimate(checkWord, dictionary[i]);
            if (mistakes<min){
                min = mistakes;
                listOfSuggestions.removeAll();
                listOfSuggestions.addFirst(dictionary[i]);
            }
            else {
                if (mistakes==min){
                    listOfSuggestions.compareAndInsert(dictionary[i]);
                }
            }
        }
        listOfSuggestions.printList();
    }

    /**
     * Method to check whether a character is a letter a-z or not
     * @param ch character to check
     * @return int value 1 if ch ia a letter a-z; otherwise return 0
     */
    public int isALetter(char ch){
        if (ch > 96 && ch < 123){
            return 1;
        }
        return 0;
    }

    /**
     * Method to read source text and form a dictionary
     * @param dictionary list of words with their frequency
     */
    public void readSourceText(List dictionary){
        Scanner scanner = new Scanner(System.in);
        String source = scanner.nextLine();
        int len = source.length();
        String word;
        int i = 0;

        while (i<len){
            if (isALetter(source.charAt(i))==1) {
                word = "";
                while (i<len && isALetter(source.charAt(i)) == 1) {
                    word = word + source.charAt(i);
                    i += 1;
                }
                if (!dictionary.findWord(word)) {
                    dictionary.addFirst(word);
                }
            }
            else {
                while (i<len && isALetter(source.charAt(i))==0){
                    i += 1;
                }
            }
        }
    }

    /**
     * Method to read text that should be corrected
     * @param dictionary list of words with their dictionary
     */
    public void readText(List dictionary){
        Scanner scanner = new Scanner(System.in);
        String text = scanner.nextLine();
        int len = text.length();
        String word;
        String output;
        int i = 0;

        while (i<len){
            if (isALetter(text.charAt(i))==1){
                word = "";
                while (i<len && isALetter(text.charAt(i))==1){
                    word = word + text.charAt(i);
                    i += 1;
                }
                output = dictionary.estimateDictionary(word);
                System.out.print(output);

            }
            else {
                while (i<len && isALetter(text.charAt(i))==0){
                    System.out.print(text.charAt(i));
                    i += 1;
                }
            }
        }
    }

    public static void main(String args[]){

        Main main = new Main();
        //main.writeMisspellings(); //method for Task A
        //main.suggestCorrections(); //method for Task B

    }

}
