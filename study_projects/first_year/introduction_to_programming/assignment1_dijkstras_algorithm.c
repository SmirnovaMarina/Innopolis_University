#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX_STACK 50
#define MAX_INT 2000

/*
    Global Variables
*/
int **graphPtr; // matrix for representation of connections between cities
int *labels; 
int init; // initial city
int dest; // destination city
int cityNum; 

int stack[MAX_STACK]; // for constructing a single path
int cityCount = 0;
int paths = 0; // amount of the shortest paths
int secondTime = 0; // firstly, traverse to find amount of paths; secondly, to build paths

FILE *input;
FILE *output;
int error = 0; // for error checking; each error has its value


/*
    Method to stop loop execution of Dijkstra algorithm
    If all vertices are visited 
    then array cloud has 1 at each [i] position -> return 1
    Otherwise return 0
*/
int checkCloud(int cloud[])
{
    int count = 0;
    for (int i = 0; i<cityNum; i++){
        if (cloud[i] == 1){
            count += 1;
        }
    }

    if (count == cityNum){
        return 1;
    }
    else {
        return 0;
    }
}

/*
    Find min label in array of labels
    This label should be owned by vertex that is not in cloud yet
*/
int findMin(int cloud[])
{
    int min = MAX_INT;
    int minIndex = 0;
    for (int i = 0; i<cityNum; i++){
        // ( <= ) to check disjoint vertices
        if (labels[i] <= min && cloud[i] == 0){ 
            min = labels[i];
            minIndex = i;
        }
    }
    return minIndex;
}

/*
  Method to print paths in the input file using stack
*/
void printPath()
{
    fprintf(output, "%d. ",paths);
    for (int i = cityCount; i>0; i--){ // replace i>=0 with i>0
        if (stack[i] > -1){
            if (stack[i] != dest){
                fprintf(output, "%d -> ", stack[i]);
            }
            else {
                fprintf(output, "%d",stack[i]);
            }
        }
        
    }
    fprintf(output, "%d\n", dest);

}

/*
    Traverse the graph using array of labels
    Traversal goes from destination city towards initial
    Construct the shortest paths
*/
void traverse(int from)
{
    int curLabel = labels[from];
    int weight;

    /*
      If initial city was reached, then print content of stack(path)
      Otherwise, continue traversal
    */
    if (from == init){
        
        paths += 1;
        if (secondTime == 1) {
            printPath();    
        }
    }
    else {
        
        for (int i = 0; i<cityNum; i++){
            weight = graphPtr[from][i]; // replace destination and initial; check paths adj vertex->curlabel
            if (from != i) {
                if ((curLabel - weight) == labels[i]){

                    cityCount += 1;
                    stack[cityCount] = i;

                    traverse(i);
                    /*
                      Return to a higher layer of a tree of paths
                      Pop the last city from the stack
                      Decrease size of stack
                    */
                    if (stack[cityCount] != dest){
                        stack[cityCount] = -1;
                        cityCount -= 1;
                    }
                }
            }
        }
        
    }

}

/*
    Algorithm to find length of the shortest path from init city to dest city
*/
int dijkstra()
{
    int vertices = cityNum;  
    
    /*
        labels:
        0 for init vertex
        INT_MAX for other vertices for the very beginning(greater than max value for distance)
        < 0 for visited vertices
    */
    labels = (int *) calloc(cityNum, sizeof(int));
    for (int i = 0; i<vertices; i++){
        labels[i] = MAX_INT;
    }
    labels[init] = 0;

    int cloud[vertices]; // array of visited vertices
    int minIndex; // index of vertex with min label
    int weight; // length of road from one city to another

    /* 
        cloud[i] == 0 means the ith vertex wasn't checked yet
        cloud[i] == 1 means the ith vertex was visited
    */
    for (int i = 0; i<vertices; i++){
        cloud[i] = 0;
    }

    while (checkCloud(cloud) == 0){
        minIndex = findMin(cloud);
        for (int i = 0; i<vertices; i++){
            weight = graphPtr[i][minIndex];
            if (weight > 0){
                if ((labels[minIndex]+weight) < labels[i]) {
                    labels[i] = labels[minIndex]+weight;
                }
            }
        }

        cloud[minIndex] = 1; // vertex is visited
    }

    return labels[dest]; // the value of the shortest path
}

/*
    Method to print in output file certain type of an error according to int value
    of argument error
*/
void printError(int error)
{
    output = fopen("output.txt", "w");
    switch (error){
        case 1:
            fprintf(output,"%s","Number of cities is out of range");
            break;
        case 2:
            fprintf(output,"%s","Chosen initial city does not exist");
            break;
        case 3:
            fprintf(output,"%s","Chosen destination city does not exist");
            break;
        case 4:
            fprintf(output,"%s","Matrix size does not suit to the number of cities");
            break;
        case 5:
            fprintf(output,"%s","The distance between some cities is out of range");
            break;
        case 6:
            fprintf(output,"%s","Initial and destination cities are not connected");
            break;
        case 7: 
            fprintf(output,"%s","Structure of the input is invalid");
            break;
    }
    fclose(output);
}

/*
    Method to print overall result of a program
*/
void print()
{
    int res = dijkstra();

    /*
        If there is no path between init and dest city, 
        dijkstra() returns MAX_INT
    */
    output = fopen("output.txt", "w");
    if (res == MAX_INT){
        error = 6;
        printError(error);
    }
    else {
        fprintf(output, "The shortest path is %d.\n", res);
        stack[0] = dest;
        for (int i = 1; i<50; i++){
            stack[i] = -1;
        }

        traverse(dest); // firstly, traverse to find number of the shortest paths
        fprintf(output, "Number of shortest paths is %d: \n", paths);
        paths = 0;
        secondTime = 1;
        cityCount = 0; 
        traverse(dest); // second time, traverse to print paths
    }
    
    fclose(output);
}

/*
    Method to determine whether a character is a digit
*/
int isADigit(char ch){
    int code = (int)ch;
    if((code >= 48) && (code<=57)){
        return 1;
    }
    return 0;
}

/*
    Method to determine whether a character is a space
*/
int isASpaces(char ch)
{
    if (ch  == ' '){
        return 1;
    }
    return 0;
}

/*
    Method to determine whether a character is a new line char
*/
int isANewLine(char ch)
{
    int code = (int)ch;
    if (ch == '\n'){
        return 1;
    }
    return 0;
}

/*
    Method to determine whether a character is a minus sign char
*/
int isMinusSign(char ch)
{
    if (ch == '-'){
        return 1;
    }
    return 0;
}

/*
    Method to determine whether a character is not a digit, " ", "\n" and "-"
*/
int isInvalidChar(char ch)
{
    if (isADigit(ch)==0 && isANewLine(ch)==0 && isASpaces(ch)==0 && isMinusSign(ch)==0){
        return 1;
    }
    return 0;
}

/*
    Method to whether number of cities is in the range[5..50]
*/
int checkCityNum(int num)
{
    if (num > 50 || num < 5) { 
        return 1; 
    }
    return 0;
}

/*
    Method to check whether init and dest cities are within their range[0..cityNum]
*/
int checkInitDest(int num)
{
    if (num >= cityNum){
        return 1;
    }
    return 0;
}

/*
    Method to read the first line from input file
*/
void readFirstLine()
{
    char ch; 
    char firstLine[10]; // 8 max positions for numbers, 1 for \n and 1 for '\0'
    int count = 0; // overall amount of chars in the first line
    int spacesCount = 0; // counter of spaces
    int newLineCount = 0; // counter of "\n" chars
    int spacesPos[2]; // positions of space characters in the first line
    int j, k; // for iterations
    int num; // for reading dest, init and cityNum

    // read the first line entirely
    ch = getc(input);
    firstLine[0] = ch;
    count += 1;
    while (ch != '\n' && count < 10){
        ch = getc(input);
        firstLine[count] = ch;
        
        count += 1;
    }

    ch = getc(input); // will read the newline sym of the second line or invalid character
    if (ch != '\n') {
        error = 7;
    }
    
    // if the line does not contain enough chars
    if (error == 0){
        if (count < 6){
            error = 7;
        }
    }

    // if the line contains invalid chars -> invalid input
    j = 0;
    if (error == 0){
        while (j<count){
            ch = firstLine[j];

            if (isInvalidChar(ch) == 1){
                error = 7;
                break;
            }
            j += 1;
        }
    }

    // if there are more than 2 spaces -> invalid input
    j = 0;
    if (error == 0){
        while (j<count){
            ch = firstLine[j];
            if (isASpaces(ch)==1){
                spacesCount += 1;
            }
            j += 1;
        }
        if (spacesCount != 2){
            error = 7;
        }
    }

    // if there are more than 1 "\n" -> invalid input
    j = 0;
    if (error == 0){
        while (j<count){
            ch = firstLine[j];
            if (isANewLine(ch)==1){
                newLineCount += 1;
            }
            j += 1;
        }
        if (newLineCount != 1){
            error = 7;
        }
    }

    // if spaces are on incorrect positions -> invalid input
    j = 0;
    k = 0;
    if (error == 0){
        while (j<count){
            ch = firstLine[j];
            if (isASpaces(ch) == 1){
                spacesPos[k] = j;
                k += 1;
            }
            j += 1;
        }
        if (spacesPos[0] < 1 || spacesPos[0] > 2){
            error = 7;
        }
        if (spacesPos[1] < 3 || spacesPos[1] > 5){
            error = 7;
        }
    }

    // check correctness of value of cityNum
    if (error == 0){
        j = spacesPos[0]-1;
        num = 0;
        while (j >= 0){
            ch = firstLine[j];
            num = num + ((int)ch - 48)*(int)pow(10.0, spacesPos[0]-1-j);
            j -= 1;
        }
        cityNum = num;
        if (checkCityNum(cityNum) == 1){
            error = 1;
        }
    }

    // check correctness of value of init city
    if (error == 0){
        j = spacesPos[1]-1;
        num = 0;
        while (j > spacesPos[0]){
            ch = firstLine[j];
            num = num + ((int)ch - 48)*(int)pow(10.0, spacesPos[1]-1-j);
            j -= 1;
        }
        init = num;
        if (checkInitDest(init) == 1){
            error = 2;
        }
    }

    // check correctness of value of dest city
    if (error == 0){
        j = count - 1 - 1;
        num = 0;
        while (j > spacesPos[1]){
            ch = firstLine[j];
            num = num + ((int)ch - 48)*(int)pow(10.0, count-2-j);
            j -= 1;
        }
        dest = num;
        if (checkInitDest(dest) == 1){
            error = 3;
        }
    }
    
}

/*
    Method to determine if a char is "*" 
*/
int isAsterisk(char ch)
{
    if (ch == '*'){
        return 1;
    }
    return 0;
}

/*
    Method to determine whether a char is not valid char for matrix of roads
*/
int isInvalidMatrixChar(char ch)
{
    if (isADigit(ch)==0 && isAsterisk(ch)==0 && isANewLine(ch)==0 && isASpaces(ch)==0 && isMinusSign(ch)==0){
        return 1;
    }
    return 0;
}

/*
    Method to determine whether a char is a zero digit
*/
int isZero(char ch)
{
    if (ch == '0'){
        return 1;
    }
    return 0;
}

/*
    Method to read a single line of a matrix
    It uses an argument lineCount to determine the number of matrix's line it's reading
*/
char readLine(int lineCount)
{
    char ch;
    int length = 0; // length of a line it reads
    char line[255]; // line of the matrix itself
    int num; // variable to hold value of roads
    int segmentCount = 0; // counter of segments separated by " "
    int countDigits; // counter of digits 
    int countAsterisc; // counter of "*"
    int zeroFirstDigit; // check values as '05' with '0' on the first position

    do {
        ch = getc(input);
        line[0] = ch;
        length = 1;

        // read each segment separately
        do {
            line[length] = ch;
            length += 1;
            ch = getc(input);
        } while (ch != ' ' && ch != '\n' && ch != EOF);
        // will get ' ' or \n in line
        length -= 1;

        // if "-" is found -> out of range error
        for (int i = 0; i<length; i++){
            if (isMinusSign(line[i]) == 1){
                error = 5;
            }
        } 
        
        // if invalid char is found -> error
        if (error == 0){
            for (int i = 0; i<length; i++){
                if (isInvalidMatrixChar(line[i]) == 1){
                    error = 7;
                }
            }
        }

        // check whether a segment is a number or "*"
        if (error == 0){
            countDigits = 0;
            countAsterisc = 0;
            zeroFirstDigit = 0;

            for (int i = 0; i<length;i++){
                if (isADigit(line[i])== 1){
                    countDigits += 1;
                }
                if (isZero(line[i])==1 && i==0){
                    zeroFirstDigit = 1;
                }
                if (isAsterisk(line[i])==1){
                    countAsterisc += 1;
                }
            }

            // if a segment has a '0' on the first position
            if (zeroFirstDigit == 1){
                error = 7;
            }

            // if a number is out of range(has 3 digits) -> error
            if (error == 0 && countDigits>2 && countAsterisc == 0) {
                error = 5;
            }

            // there are digits and "*" simultaneously -> error
            if (error == 0 &&countDigits>0 && countAsterisc != 0){
                error = 7;
            }

            // if there are more than 1 "*" -> error
            if (countAsterisc > 1){
                error = 7;
            }

            // check the value of the number
            if (error == 0 && countAsterisc == 0){
                
                // if the number has 2 digits
                if (countDigits == 2){
                    num = ((int)line[0]-48)*10 + (int)line[1]-48;
                }
                // if the number has only 1 digit
                else {
                    num = (int)line[0] - 48;
                }
                // if the value is out of range[1..20] -> error
                if (num > 20){
                    error = 5;
                }
                // if the number is valid, then write to the right position in the matrix of roads
                if (error == 0){
                    graphPtr[lineCount][segmentCount] = num;
                }    
            }
            // there is no road between cities write down -1 in the right posotion of the matrix of roads
            if (error == 0 && countAsterisc == 1){
                graphPtr[lineCount][segmentCount] = -1;
            }

            // if the size of the input matrix is excessive -> error
            segmentCount += 1;
                if (segmentCount > cityNum){
                error = 4;
            }
        }

    } while (ch != '\n' && ch != EOF);
    return ch;

}

/*
    Method to read a matrix of roads between cities from input file
*/
void readMatrix()
{
    char ch;
    int lineCount; // counter for rows of the matrix
    
    // allocate space for matrix of weights and routes
    graphPtr = (int **) calloc(cityNum, sizeof(int *));
    for (int i = 0; i<cityNum; i++){
        graphPtr[i] = (int *) calloc(cityNum, sizeof(int));
    } 

    lineCount = 0;
    ch = '\n';

    // read from input file line by line using readLine()
    // if error occurs -> break; furter print error
    while (ch != EOF){
        if (error == 0){
            ch = readLine(lineCount); 
            lineCount += 1; 
        }
        else {
            break;
        }
        if (lineCount > cityNum){
            error = 4;
            break;
        }
    }

    /*
    Check the diagonal values of the matrix
    If all diagonal values == 0, then the matrix is correct
    Otherwise, structure of input is incorrect
    */
    if (error == 0){
        int i = 0;
        int j = 0;
        while (error == 0 && i<cityNum){
            j = 0;
            while (error == 0 && j<cityNum){
                if (i == j){
                    if (graphPtr[i][j] != 0){
                        error = 7;
                    }
                }
                j += 1;
            }
            i += 1;
        }
    }

}

/*
    Method to read all content from input file
*/
void read()
{
    input = fopen("input.txt", "r");
    readFirstLine();
    if (error == 0){
        readMatrix();
    }
    fclose(input);
}

/*
    Method to execute an entire program
*/
int main()
{   
    read();
    if (error > 0){
        printError(error);
    }
    else {
        print();
    }

    return 0;
}