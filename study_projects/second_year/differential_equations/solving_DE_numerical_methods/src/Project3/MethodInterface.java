package Project3;

public interface MethodInterface {

    double function_f(double x_i, double y_i);

    double exactSolution(double x_i);

    double calculateY(double x, double y);

    void addData(double x, double y, double e, double ge);

    void solve(MyData input);
}
