package Project3;

import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;

public class MyChart extends LineChart<Number, Number> {

    MyChart(NumberAxis xAxis, NumberAxis yAxis){
        super(xAxis, yAxis);
    }

    public void init(String title, double maxW, double maxH){
        setMaxSize(maxW, maxH);
        setPrefHeight(maxH);
        setTitle(title);
        getXAxis().setLabel("x axis");
        getYAxis().setLabel("y axis");
        setCreateSymbols(false);
    }

    public void plot(String methodName, MyData input, int solutionErrorGlobal) {

        getXAxis().setTickLength((input.getX_n() - input.getX_0()) / input.getN());

        Method method;

        if (methodName.equals("ALL")) {

            method = new AnalyticalMethod(input);
            method.solve(input);

            EulerMethod eulerMethod = new EulerMethod(input);
            eulerMethod.solve(input);

            ImprovedEuler improvedEuler = new ImprovedEuler(input);
            improvedEuler.solve(input);

            RungeKutta rungeKutta = new RungeKutta(input);
            rungeKutta.solve(input);

            getData().clear();
            if (solutionErrorGlobal == 0){
                getData().addAll(rungeKutta.getSeries());
                getData().addAll(improvedEuler.getSeries());
                getData().addAll(eulerMethod.getSeries());
                getData().addAll(method.getSeries());
            }
            else{
                if (solutionErrorGlobal == 1){
                    getData().addAll(rungeKutta.getErrorSeries());
                    getData().addAll(improvedEuler.getErrorSeries());
                    getData().addAll(eulerMethod.getErrorSeries());
                    getData().addAll(method.getErrorSeries());
                }
                else {
                    getData().addAll(rungeKutta.getGlobalSeries());
                    getData().addAll(improvedEuler.getGlobalSeries());
                    getData().addAll(eulerMethod.getGlobalSeries());
                    getData().addAll(method.getGlobalSeries());
                }
            }

        } else {
            switch (methodName) {
                case "Analytical Method":
                    method = new AnalyticalMethod(input);
                    break;
                case "Euler Method":
                    method = new EulerMethod(input);
                    break;
                case "Improved Euler":
                    method = new ImprovedEuler(input);
                    break;
                case "Runge-Kutta":
                    method = new RungeKutta(input);
                    break;
                default:
                    method = new Method(input);
                    break;
            }
            method.solve(input);
            getData().clear();
            if (solutionErrorGlobal == 0){
                getData().addAll(method.getSeries());
            }
            else{
                if (solutionErrorGlobal == 1){
                    getData().addAll(method.getErrorSeries());
                }
                else{
                    getData().addAll(method.getGlobalSeries());
                }
            }
        }
    }
}
