package client.Controller;

import client.Main;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;

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
            // show client view
        }
        else{
            if(loginAttempts == MAX_LOGIN_ATTEMPTS){
                // back to connection form

            }
            Main.newAlert(Alert.AlertType.WARNING, "Wrong data", "No such user!").showAndWait();
            loginAttempts++;
            return;
        }
    }

    private boolean validateUser(String login, String password) {
        return client.getConnectionManager().checkUser(login, password);
    }
}
