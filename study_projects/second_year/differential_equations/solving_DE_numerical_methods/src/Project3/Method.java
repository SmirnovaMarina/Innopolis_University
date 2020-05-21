package Project3;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.chart.XYChart;

public class Method implements MethodInterface{

    protected XYChart.Series series;
    protected ObservableList<XYChart.Data<Double, Double>> data;

    protected XYChart.Series errorSeries;
    protected ObservableList<XYChart.Data<Double, Double>> errorData;

    protected XYChart.Series globalSeries;
    protected ObservableList<XYChart.Data<Double, Double>> globalData;

    protected double x_i;
    protected double x_n;
    protected double y_i;
    protected double h;
    protected double c_const;
    protected double y_appExact;
    protected double local_e_i;
    protected double global_e_i;

    protected Boolean isReverse;

    Method(MyData input){

        y_i = input.getY_0();
        y_appExact = input.getY_0();
        local_e_i = 0;
        global_e_i = 0;

        if (input.getX_0() < input.getX_n()){
            isReverse = false;
            x_i = input.getX_0();
            this.x_n = input.getX_n();
            h = (x_n - x_i) / input.getN();
            c_const = (x_i+y_i) * Math.exp(x_i)/x_i;
        }
        if(input.getX_0() > input.getX_n()){
            isReverse = true;
            x_i = -input.getX_0();
            this.x_n = input.getX_n();
            h = (x_i - x_n) / input.getN();
            c_const = (-x_i-y_i) * Math.exp(x_i)/x_i;
        }

        series = new XYChart.Series();
        data = FXCollections.observableArrayList();
        errorSeries = new XYChart.Series();
        errorData = FXCollections.observableArrayList();
        globalSeries = new XYChart.Series();
        globalData = FXCollections.observableArrayList();
    }

    public double getX_i(){
        return x_i;
    }
    public double getX_n(){
        return x_n;
    }
    public double getY_i(){
        return y_i;
    }
    public double getH(){
        return h;
    }
    public double getC_const(){
        return c_const;
    }
    public double getY_appExact(){
        return y_appExact;
    }
    public double getLocal_e_i(){
        return local_e_i;
    }
    public double getGlobal_e_i(){
        return global_e_i;
    }
    public XYChart.Series getSeries(){ return series; }
    public XYChart.Series getErrorSeries(){
        return errorSeries;
    }
    public XYChart.Series getGlobalSeries(){
        return globalSeries;
    }
    public ObservableList<XYChart.Data<Double, Double>> getData(){ return data; }
    public ObservableList<XYChart.Data<Double, Double>> getErrorData(){
        return errorData;
    }
    public ObservableList<XYChart.Data<Double, Double>> getGlobalData(){
        return globalData;
    }

    public double function_f(double x_i, double y_i){
        if (!isReverse){
            return (y_i/x_i - y_i - x_i);
        }
        return (y_i/x_i + y_i - x_i);
    }

    public double exactSolution(double x_i){
        if (!isReverse){
            return -x_i+x_i/Math.exp(x_i)*c_const;
        }
        return x_i+x_i/Math.exp(x_i)*c_const;
    }

    public double calculateY(double x, double y){
        return y;
    }

    public void addData(double x, double y, double e, double ge){
        if (isReverse){
            data.add(new XYChart.Data<>(-x, y));
            errorData.add(new XYChart.Data<>(-x, e));
            globalData.add(new XYChart.Data<>(-x, ge));
        }
        else{
            data.add(new XYChart.Data<>(x, y));
            errorData.add(new XYChart.Data<>(x, e));
            globalData.add(new XYChart.Data<>(x, ge));
        }
    }

    public void solve(MyData input){

        double temp_global = 0;

        while(x_i <= x_n) {
            if (x_i != 0){
                addData(x_i, y_i, local_e_i, global_e_i);

                temp_global = global_e_i;
                y_appExact = calculateY(x_i, y_appExact);
                y_i = calculateY(x_i, y_i);
                x_i = x_i + h;
                global_e_i = Math.abs(y_i - exactSolution(x_i));
                local_e_i = (global_e_i - temp_global);
            }
        }

        addData(x_i, y_i, local_e_i, global_e_i);

        series.setData(data);
        errorSeries.setData(errorData);
        globalSeries.setData(globalData);
    }
}