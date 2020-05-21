public class TaskInfo {

    private String dateStr;
    private int dd, mm, yy;
    private String task;
    private int priority;

    TaskInfo(String dateStr, String task, String priority){
        this.task = task;
        this.dateStr = dateStr;
        setDate(dateStr);
        this.priority = Integer.parseInt(priority);
    }

    TaskInfo(String dateStr){
        this.dateStr = dateStr;
    }

    String getDateStr(){
        return dateStr;
    }

    String getTask(){
        return task;
    }

    int getPriority(){
        return priority;
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

    void setDateStr(String str){
        dateStr = str;
    }

    void setTask(String str){
        task = str;
    }

    void setDate(String str){
        String temp;
        temp = str.substring(0,2);
        dd = Integer.parseInt(temp);
        temp = str.substring(3, 5);
        mm = Integer.parseInt(temp);
        temp = str.substring(6);
        yy = Integer.parseInt(temp);
    }

}
