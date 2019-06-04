package client.Controller;

import client.Main;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import java.io.IOException;

public class LoginViewController {

    @FXML
    private TextField loginInput;
    @FXML
    private PasswordField passwordInput;

    private final int MAX_LOGIN_ATTEMPTS = 5;
    private Boolean logged;
    private int loginAttempts;
    private String login, password;
    private ClientViewController client;
    private Scene clientScene;

    void LoginInit(ClientViewController controllerClient, Scene sceneClient) {
        loginAttempts = 0;
        logged = false;
        client = controllerClient;
        clientScene = sceneClient;
        client.getConnectionManager().getReceiveThread().start();
    }

    public void pressButton(ActionEvent e){
        login = loginInput.getText();
        password = passwordInput.getText();

        validateUser(login, password);
    }

    public void acceptLogin(){
        logged = true;
        client.getUserName().setText(login);
        client.getStage().setScene(clientScene);
    }

    public void rejectLogin(String errorMsg){
        if(loginAttempts == MAX_LOGIN_ATTEMPTS){
                Main.newAlert(Alert.AlertType.WARNING, "Disconnected", "Too many attempts failed! Disconnecting!").showAndWait();
        }
        Main.newAlert(Alert.AlertType.WARNING, "Wrong data", "Wrong input! " + errorMsg).showAndWait();
        loginAttempts++;
    }

    private void validateUser(String login, String password) {
        try {
            client.getConnectionManager().checkUser(login, password, this);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
