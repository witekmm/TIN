module Client {

    requires javafx.fxml;
    requires javafx.controls;

    opens client;
    opens client.Controller;
    opens client.View;

}