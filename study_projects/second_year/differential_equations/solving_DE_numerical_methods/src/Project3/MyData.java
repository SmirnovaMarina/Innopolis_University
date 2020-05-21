package Project3;

public class MyData {

    private double x0, x_n, y0, N;

    MyData(String x0, String x_n, String y0, String N){
        this.x0 = Double.parseDouble(x0);
        this.x_n = Double.parseDouble(x_n);
        this.y0 = Double.parseDouble(y0);
        this.N = Double.parseDouble(N);
    }

    public double getX_0(){
        return x0;
    }
    public double getY_0(){
        return y0;
    }
    public double getX_n(){
        return x_n;
    }
    public double getN(){
        return N;
    }
}
