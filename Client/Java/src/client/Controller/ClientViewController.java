package client.Controller;

import client.Main;
import client.Message;
import client.Model.ConnectionManager;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.stage.Stage;
import java.io.IOException;

public class ClientViewController {

    public Button sendButton;
    public Button disconnectButton;
    public Button createGroupButton;
    public volatile ChoiceBox groupChoice;
    @FXML
    private TextArea messageArea;
    @FXML
    private TextArea sendText;
    @FXML
    private Label ipValue;
    @FXML
    private Label portValue;
    @FXML
    private Label userName;
    @FXML
    private TextField groupNameRequest;
    private ConnectionManager connectionManager;

    public Stage getStage() {
        return mainStage;
    }

    private Stage mainStage;

    public void ClientWindowInit(String IP, Integer port, Stage stage) throws Exception {

        ipValue.setText(IP);
        portValue.setText(port.toString());
        mainStage = stage;
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
                groupName = groupChoice.getValue().toString();
        connectionManager.sendMessage(message, groupName);
        sendText.clear();
    }

    public void pressButtonCreateGroup(ActionEvent e){
        String groupName = groupNameRequest.getText();
        groupNameRequest.setText("");
        connectionManager.groupAction(Message.ClientMessage.groupActionTypes.CREATE, groupName);
    }

    public void pressJoinGroupButton(){
        String groupName = groupNameRequest.getText();
        groupNameRequest.setText("");
        connectionManager.groupAction(Message.ClientMessage.groupActionTypes.REQUEST, groupName);
    }

    public void pressLeaveGroupButton(){
        String groupName = groupChoice.getValue().toString();
        connectionManager.groupAction(Message.ClientMessage.groupActionTypes.LEAVE, groupName);
    }

    public void pressDeleteGroupButton(){
        String groupName = groupChoice.getValue().toString();
        connectionManager.groupAction(Message.ClientMessage.groupActionTypes.DELETE, groupName);
    }

    public TextArea getTextArea(){
        return messageArea;
    }

    public void openConnectForm(){
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/client/View/Connectform.fxml"));
            Scene scene = new Scene(loader.load());
            mainStage.setScene(scene);
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

    public ChoiceBox getGroupChoice() {
        return groupChoice;
    }

    public Label getUserName() {
        return userName;
    }

}

