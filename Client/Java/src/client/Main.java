package client;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("View/Connectform.fxml"));
        primaryStage.setTitle("New connection");
        primaryStage.setScene(new Scene(root));
        primaryStage.setMinHeight(363);
        primaryStage.setMinWidth(533);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }

    public static Alert newAlert(Alert.AlertType type, String title, String content){
        Alert alert = new Alert(type);
        alert.setTitle(title);
        alert.setContentText(content);
        return alert;
    }


}
