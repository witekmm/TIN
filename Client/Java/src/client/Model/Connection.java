package client.Model;

import client.Main;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import java.io.*;
import java.net.Socket;
import java.net.SocketException;
import java.util.Optional;

public class Connection {

    private final int MAX_ATTEMPTS = 5;
    private Socket socket;
    private String IP;
    private Integer port;
    private DataOutputStream out;
    private BufferedReader in;
    public Connection(String _ip, Integer _port) {
        IP = _ip;
        port = _port;
    }

    public int connect(){

        int attempts = 0;
        while(socket == null || !socket.isConnected()) {
            try {
                socket = new Socket(IP, port);
                in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                out = new DataOutputStream(socket.getOutputStream());
            } catch (IOException e) {

                Optional<ButtonType> result = Main.newAlert(Alert.AlertType.CONFIRMATION, "Connection error. Attempt: " + attempts, e.getMessage())
                        .showAndWait();
                if(result.isPresent())
                    if(result.get() == ButtonType.CANCEL)
                        return -2;
            }
            if(attempts == MAX_ATTEMPTS)
                return -1;
            attempts++;
        }
        return 0;
    }

    public void end() throws IOException {
        socket.close();
    }

    public void send(byte[] msg){
        try {
            out.write(msg);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public int receive(char[] answerBuffer, int offset, int length){
        try {
            return in.read(answerBuffer, offset, length);
        } catch (SocketException e){
            return -1;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return -1;
    }

    public Socket getSocket() {
        return socket;
    }

    public DataOutputStream getOut() {
        return out;
    }

    public BufferedReader getIn() {
        return in;
    }
}
