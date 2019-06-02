module Client {

    requires javafx.fxml;
    requires javafx.controls;
    requires java.logging;
    requires jdk.unsupported;

    opens client;
    opens client.Controller;
    opens client.View;

}