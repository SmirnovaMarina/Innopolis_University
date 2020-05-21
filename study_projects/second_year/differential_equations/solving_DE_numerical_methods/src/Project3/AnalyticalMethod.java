package Project3;

public class AnalyticalMethod extends Method {

    AnalyticalMethod(MyData input){
        super(input);
        series.setName("Analytical Method");
        errorSeries.setName("Analytical Method");
        globalSeries.setName("Analytical Method");
    }

    @Override
    public double calculateY(double x, double y){
        return exactSolution(x+h);
    }
}
