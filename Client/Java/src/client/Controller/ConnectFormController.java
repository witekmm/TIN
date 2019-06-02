package client.Controller;

import client.Utils.IPValidator;
import client.Main;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import java.net.SocketException;

public class ConnectFormController {

    @FXML
    private TextField ipText, portText;
    @FXML
    private Button connectButton;

    public void pressButton(ActionEvent e){

        String ip = ipText.getText();
        Integer port;
        if(ip.equals("test")){
            ip = "169.254.203.113";
            port = 50011;
        }
        else {
            if (!checkIP(ip)) return;
            port = checkPort(portText.getText());
            if (port == null) return;
        }
        openClientWindow(ip, port);
    }

    private Boolean checkIP(String ip){
        if(ip.isBlank()){
            Main.newAlert(Alert.AlertType.ERROR, "Invalid IP", "No IP provided!")
                    .showAndWait();
            return false;
        }
        else{
            IPValidator validator = new IPValidator();
            if(!validator.validate(ip)){
                Main.newAlert(Alert.AlertType.ERROR, "Invalid IP", "Wrong IP format!")
                        .showAndWait();
                return false;
            }
        }
        return true;
    }

    private Integer checkPort(String port){
        Integer portNr;
        if(port.isBlank()){
            Main.newAlert(Alert.AlertType.ERROR, "Invalid port", "No port provided!")
                    .showAndWait();
            return null;
        }
        else{
            try {
                portNr = Integer.parseInt(portText.getText());
                if(portNr < 1024 || portNr > 65500){
                    throw new Exception("Port value must be between 1024 and 65500!");
                }
            }
            catch(NumberFormatException ee){
                Main.newAlert(Alert.AlertType.ERROR, "Invalid port", "Port must be a number!")
                        .showAndWait();
                return null;
            }
            catch(Exception e){
                Main.newAlert(Alert.AlertType.ERROR, "Invalid port", e.getMessage())
                        .showAndWait();
                return null;
            }
        }
        return portNr;
    }

    private void openClientWindow(String ip, Integer port){

        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/client/View/ClientView.fxml"));
            Stage stage = (Stage) connectButton.getScene().getWindow();
            Scene sceneClient = new Scene(loader.load());
            ClientViewController controllerClient = loader.getController();
            controllerClient.ClientWindowInit(ip, port, stage);
            stage.setMinWidth(sceneClient.getWidth());
            stage.setMinHeight(sceneClient.getHeight());
            // when stage is closed
            stage.setOnCloseRequest(we -> {
                if(controllerClient.getConnectionManager().isConnected() )
                    controllerClient.getConnectionManager().disconnect();
            });

            loader = new FXMLLoader(getClass().getResource("/client/View/LoginView.fxml"));
            Scene sceneLogin = new Scene(loader.load());
            LoginViewController controllerLogin = loader.getController();
            stage.setScene(sceneLogin);
            controllerLogin.LoginInit(controllerClient, sceneClient);
        }
        catch(SocketException e) {
            Main.newAlert(Alert.AlertType.ERROR, "Socket error", "Connection error. Couldn't connect to socket!")
                .showAndWait();
        }
        catch(Exception ex) {
            Main.newAlert(Alert.AlertType.CONFIRMATION, "Connection", "Connection to server: " + ex.getMessage())
                    .showAndWait();
        }
    }
}
