package Project3;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 *
 */
public class Main extends Application {

        @Override
        public void start(Stage primaryStage) throws Exception{
            Parent root = FXMLLoader.load(getClass().getResource("first.fxml"));
            primaryStage.setTitle("Assignment");
            Scene primaryScene = new Scene(root, 1500, 680);
            primaryStage.setScene(primaryScene);
            primaryStage.centerOnScreen();

            primaryStage.show();
        }

        public static void main(String[] args) {
            launch(args);
        }
}
