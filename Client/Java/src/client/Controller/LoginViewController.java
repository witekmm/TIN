package client.Controller;

import client.Main;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
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

    public void LoginInit(ClientViewController controllerClient) {
        loginAttempts = 0;
        logged = false;
        client = controllerClient;
    }

    public void pressButton(ActionEvent e){
        login = loginInput.getText();
        password = passwordInput.getText();

        if(validateUser(login, password)){
            logged = true;
            client.getUserName().setText(login);
            Scene clientScene = client.getClientScene();
            Stage stage = (Stage) loginInput.getScene().getWindow();
            client.getConnectionManager().getReceiveThread().start();
            stage.setScene(clientScene);
        }
        else{
            if(loginAttempts == MAX_LOGIN_ATTEMPTS){
                Main.newAlert(Alert.AlertType.WARNING, "Disconnected", "Too many attempts failed! Disconnecting!").showAndWait();
            }
            Main.newAlert(Alert.AlertType.WARNING, "Wrong data", "No such user!").showAndWait();
            loginAttempts++;
            return;
        }
    }

    private boolean validateUser(String login, String password) {
        try {
            return client.getConnectionManager().checkUser(login, password);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return false;
    }
}
