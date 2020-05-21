package Project3;

public class RungeKutta extends Method {

    RungeKutta(MyData input){
        super(input);
        series.setName("Runge-Kutta");
        errorSeries.setName("Runge-Kutta");
        globalSeries.setName("Runge-Kutta");
    }

    @Override
    public double calculateY(double x, double y){
        double k1, k2, k3, k4;

        k1 = function_f(x, y);
        k2 = function_f( x+h/2, y+k1*h/2);
        k3 = function_f(x+h/2, y+k2*h/2);
        k4 = function_f(x+h, y+k3*h);
        return y + (h/6)*(k1 + 2*k2 + 2*k3+ k4);
    }
}
