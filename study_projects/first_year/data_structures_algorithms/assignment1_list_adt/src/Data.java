/**
 * @author Smirnova Marina
 * Class for data about a single team in a tournament
 */
public class Data implements Comparable<Data> {
    /**name of a team*/
    private String name;

    /** name of tournament*/
    private String tour;

    /** amount of games played*/
    private int games;

    /** amount of points scored */
    private int points;

    /** amount of wins */
    private int wins;

    /** amount of ties*/
    private int ties;

    /**amount of loses*/
    private int loses;

    /**amount of goals scored*/
    private int goalsScored;

    /** amount of goals missed*/
    private int goalsMissed;

    /** difference between goalsScored and goalsMissed*/
    private int goalsDif;

    String getName(){return name;}

    String getTour(){return tour;}

    int getGames(){return games;}

    int getPoints(){return points;}

    int getWins(){return wins;}

    int getTies(){return ties;}

    int getLoses(){return loses;}

    int getGoalsScored(){return goalsScored;}

    int getGoalsMissed(){return goalsMissed;}

    int getGoalsDif() {
        setGoalsDif();
        return goalsDif;
    }

    void setName(String name){
        this.name = name;
    }

    void setTour(String tour) {this.tour = tour;}

    void incPoints(int num){
        points += num;
    }

    void incTies(){
        ties += 1;
    }

    void incLoses(){
        loses += 1;
    }

    void incGoalsScored(int num){
        goalsScored += num;
    }

    void incGoalsMissed(int num){
        goalsMissed += num;
    }

    void setGoalsDif(){
        goalsDif = goalsScored - goalsMissed;
    }

    void incGames(){games += 1;}

    void incWins(){wins += 1;}

    /**
     * @param anotherTeam is data about another team with which I compare current team
     * @return 1 or -1
    Returned values of compareTo:
    1: caller is bigger than the actual parameter
    -1: caller is smaller than the actual parameter
     */
    public int compareTo(Data anotherTeam) {
        if (points > anotherTeam.points) {
            return 1;
        }
        if (points < anotherTeam.points){
            return -1;
        }
        if (wins > anotherTeam.wins){
            return 1;
        }
        if (wins < anotherTeam.wins){
            return -1;
        }
        if (goalsDif > anotherTeam.goalsDif){
            return 1;
        }
        if (goalsDif < anotherTeam.goalsDif){
            return -1;
        }
        if (name.toLowerCase().compareTo(anotherTeam.name.toLowerCase()) > 0){
            return 1;
        }
        else {
            return -1;
        }
    }

}
