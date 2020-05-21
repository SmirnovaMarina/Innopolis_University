package Project3;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;

import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.chart.NumberAxis;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.scene.text.Text;
import javafx.stage.Screen;
import javafx.stage.Stage;

import javafx.geometry.Rectangle2D;
import javafx.scene.text.Font;


public class ControllerFXML implements Initializable {

    @FXML private Button buttonSolPlot;
    @FXML private Button buttonErrPlot;
    @FXML private Button buttonGlobal;
    @FXML private Button buttonSolFullScreen;
    @FXML private Button buttonErrFullScreen;

    @FXML private TextField x0_field;
    @FXML private TextField x_n_field;
    @FXML private TextField y0_field;
    @FXML private TextField N_field;

    @FXML private AnchorPane chartSolContainer;
    @FXML private AnchorPane chartErrContainer;
    @FXML private AnchorPane globalContainer;

    private NumberAxis solXAxis = new NumberAxis();
    private NumberAxis solYAxis = new NumberAxis();
    private MyChart chartSolution = new MyChart(solXAxis, solYAxis);

    private NumberAxis errXAxis = new NumberAxis();
    private NumberAxis errYAxis = new NumberAxis();
    private MyChart chartError = new MyChart(errXAxis, errYAxis);

    private NumberAxis globalXAxis = new NumberAxis();
    private NumberAxis globalYAxis = new NumberAxis();
    private MyChart chartGlobal = new MyChart(globalXAxis, globalYAxis);

    private ObservableList<String> options = FXCollections.observableArrayList(
                    "Analytical Method", "Euler Method", "Improved Euler", "Runge-Kutta", "ALL");
    @FXML private ComboBox<String> comboMethod = new ComboBox<>(FXCollections.observableArrayList(options));


    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {

        chartSolution.init("Solution's Chart", 500, 550);
        chartError.init("Error's Chart", 500, 550);
        chartSolContainer.getChildren().add(chartSolution);
        chartErrContainer.getChildren().add(chartError);
        chartGlobal.init("Global Error's Chart", 500, 550);
        globalContainer.getChildren().add(chartGlobal);


        comboMethod.setItems(options);
        comboMethod.setValue("Analytical Method");

        x0_field.addEventFilter(KeyEvent.KEY_TYPED, xFilter(x0_field));
        y0_field.addEventFilter(KeyEvent.KEY_TYPED, numericalFilter());
        x_n_field.addEventFilter(KeyEvent.KEY_TYPED, xFilter(x_n_field));
        N_field.addEventFilter(KeyEvent.KEY_TYPED, numericalFilter());
    }

    public void showWarning(){
        BorderPane borderPane = new BorderPane();
        Scene scene = new Scene(borderPane);
        Stage warningWindow = new Stage();
        Text text = new Text("x = 0 is out of valid range for the equation");

        warningWindow.setTitle("Warning");
        warningWindow.setMinHeight(200);
        warningWindow.setScene(scene);

        text.setFont(new Font("Arial", 30));
        borderPane.setCenter(text);

        warningWindow.show();
    }

    private EventHandler<KeyEvent> numericalFilter(){

        EventHandler<KeyEvent> eventHandler = new EventHandler<KeyEvent>() {
            public void handle(KeyEvent keyEvent) {
                if (!"0123456789.-".contains(keyEvent.getCharacter())) {
                    keyEvent.consume();
                }
            }
        };
        return eventHandler;
    }

    private EventHandler<KeyEvent> xFilter(TextField field){
        EventHandler<KeyEvent> eventHandler = new EventHandler<KeyEvent>() {
            public void handle(KeyEvent keyEvent) {

                if (!"0123456789.-".contains(keyEvent.getCharacter())) {
                    keyEvent.consume();
                }
                else{
                    if (keyEvent.getCharacter().equals("0")){
                        if (field.getCharacters().length() == 0){
                            keyEvent.consume();
                            showWarning();
                        }
                    }
                }
            }
        };
        return eventHandler;
    }

    @FXML
    public void buildPlot(ActionEvent event) {
        MyData input = new MyData(x0_field.getText(), x_n_field.getText(),
                y0_field.getText(), N_field.getText());

        buttonSolPlot.setOnMouseClicked(new EventHandler<MouseEvent>() {
            public void handle(MouseEvent me) {
                chartSolution.plot(comboMethod.getValue(), input, 0);
            }
        });

        buttonErrPlot.setOnMouseClicked(new EventHandler<MouseEvent>() {
            public void handle(MouseEvent me) {
                chartError.plot(comboMethod.getValue(), input, 1);
            }
        });

        buttonGlobal.setOnMouseClicked(new EventHandler<MouseEvent>() {
            public void handle(MouseEvent me) {
                chartGlobal.plot(comboMethod.getValue(), input, 2);
            }
        });
    }

    @FXML
    public void buildFullScreenPlot(ActionEvent event){

        BorderPane borderPane = new BorderPane();
        Scene secondScene = new Scene(borderPane);
        Stage newWindow = new Stage();
        Rectangle2D primaryScreenBounds = Screen.getPrimary().getVisualBounds();

        newWindow.setTitle("FullScreen Plot");
        newWindow.setScene(secondScene);

        //set Stage boundaries to visible bounds of the main screen
        newWindow.setX(primaryScreenBounds.getMinX());
        newWindow.setY(primaryScreenBounds.getMinY());
        newWindow.setWidth(primaryScreenBounds.getWidth());
        newWindow.setHeight(primaryScreenBounds.getHeight());

        NumberAxis xAxis = new NumberAxis();
        NumberAxis yAxis = new NumberAxis();
        MyChart chart = new MyChart(xAxis, yAxis);

        MyData input = new MyData(x0_field.getText(), x_n_field.getText(),
                y0_field.getText(), N_field.getText());

        xAxis.setTickUnit((input.getX_n() - input.getX_0()) / input.getN());
        yAxis.setTickUnit((input.getX_n() - input.getX_0()) / input.getN());

        buttonSolFullScreen.setOnMouseClicked(new EventHandler<MouseEvent>() {
            public void handle(MouseEvent me) {
                chart.init("Solution's Chart", newWindow.getWidth(), newWindow.getHeight());
                chart.plot(comboMethod.getValue(), input, 0);
            }
        });

        buttonErrFullScreen.setOnMouseClicked(new EventHandler<MouseEvent>() {
            public void handle(MouseEvent me) {
                chart.init("Error's Chart", newWindow.getWidth(), newWindow.getHeight());
                chart.plot(comboMethod.getValue(), input, 1);
            }
        });

        borderPane.setCenter(chart);
        newWindow.show();
    }

}
