package Project3;

public class EulerMethod extends Method{

    EulerMethod(MyData input){
        super(input);
        series.setName("Euler Method");
        errorSeries.setName("Euler Method");
        globalSeries.setName("Euler Method");
    }

    @Override
    public double calculateY(double x, double y){
        return y + h*function_f(x, y);
    }
}
