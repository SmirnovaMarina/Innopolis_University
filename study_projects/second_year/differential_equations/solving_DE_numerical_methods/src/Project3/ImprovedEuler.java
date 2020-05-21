package Project3;

public class ImprovedEuler extends Method{

    ImprovedEuler(MyData input){
        super(input);
        series.setName("Improved Euler");
        errorSeries.setName("Improved Euler");
        globalSeries.setName("Improved Euler");
    }

    @Override
    public double calculateY(double x, double y){
        double k1, k2;
        k1 = function_f(x, y);
        k2 = function_f(x+h, y+h*k1);
        return y + (h/2)*(k1+k2);
    }
}
