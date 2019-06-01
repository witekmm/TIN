package client.Controller;

import client.Main;
import client.Model.ConnectionManager;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;

import java.io.IOException;

public class ClientViewController {

    public Button sendButton;
    public Button disconnectButton;
    @FXML
    private TextArea messageArea;
    @FXML
    private TextArea sendText;
    @FXML
    private Label ipValue;
    @FXML
    private Label portValue;

    private byte[] buffer;

    private ConnectionManager connectionManager;

    public void ClientWindowInit(String IP, Integer port) throws Exception {

        buffer = new byte[1024];
        ipValue.setText(IP);
        portValue.setText(port.toString());

        connectionManager = new ConnectionManager(IP, port, this);
        connectionManager.connect();
    }

    public void pressButtonDisconnect(ActionEvent e){
        Main.newAlert(Alert.AlertType.INFORMATION, "Disconnection", "You were disconnected").showAndWait();
        connectionManager.disconnect();
        openConnectForm();
    }

    public void pressButtonSend(ActionEvent e){

        String message = sendText.getText(),
                groupName = "tulipany";
        connectionManager.send(message, groupName);
        sendText.clear();
    }

    public TextArea getTextArea(){
        return messageArea;
    }

    private void openConnectForm(){
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/client/View/Connectform.fxml"));
            Stage stage = (Stage) disconnectButton.getScene().getWindow();
            Scene scene = new Scene(loader.load());
            stage.setMinWidth(scene.getWidth());
            stage.setMinHeight(scene.getHeight());
            stage.setScene(scene);
        }catch (IOException io){
            io.printStackTrace();
        }
    }

    public Scene getClientScene(){
        return ipValue.getScene();
    }

    public ConnectionManager getConnectionManager() {
        return connectionManager;
    }
}

