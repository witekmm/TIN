package client.Controller;

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
    private Stage mainStage;

    void ClientWindowInit(String IP, Integer port, Stage stage) throws Exception {

        ipValue.setText(IP);
        portValue.setText(port.toString());
        mainStage = stage;
        connectionManager = new ConnectionManager(IP, port, this);
        connectionManager.connect();
    }

    public void pressButtonDisconnect(ActionEvent e){
        connectionManager.disconnect();
        openConnectForm();
    }

    private void emptyError(String msg){
        messageArea.appendText(msg + "\n");
        return;
    }

    public void pressButtonSend(ActionEvent e){
        String message = sendText.getText(), groupName = "";
        if(message.isBlank()){
            emptyError("Message is empty!");
        }
        try{
           groupName = groupChoice.getValue().toString();
        }catch(NullPointerException ex){
            emptyError("No group chosen!");
        }
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
        String groupName = "";
        try{
            groupName = groupChoice.getValue().toString();
        }catch(NullPointerException ex){
            emptyError("No group chosen!");
        }
        connectionManager.groupAction(Message.ClientMessage.groupActionTypes.LEAVE, groupName);
    }

    public void pressDeleteGroupButton(){
        String groupName = "";
        try{
            groupName = groupChoice.getValue().toString();
        }catch(NullPointerException ex){
            emptyError("No group chosen!");
        }
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

    ConnectionManager getConnectionManager() {
        return connectionManager;
    }

    public ChoiceBox getGroupChoice() {
        return groupChoice;
    }

    public Label getUserName() {
        return userName;
    }

    Stage getStage() {
        return mainStage;
    }
}

