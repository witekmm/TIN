package client.Model;

import client.Controller.ClientViewController;
import client.Main;
import client.Message;
import javafx.scene.control.Alert;

import java.io.IOException;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.util.Arrays;

public class ConnectionManager {

    private Connection connection;
    private String IP;
    private Integer port;
    private Boolean connected;
    private ClientViewController client;

    private Thread receiveThread;

    public ConnectionManager(String _ip, Integer _port, ClientViewController clientViewController) {

        IP = _ip;
        port = _port;
        client = clientViewController;
        connected = false;
        connection = new Connection(IP, port);
    }

    public void connect() throws Exception {
        receiveThread = new Thread();
        int connResult = connection.connect();
        if (connResult != 0) {

            if (connResult == -1)
                throw new SocketException();
            if (connResult == -2)
                throw new Exception("Canceled");
        }
        connected = true;
    }

    public void disconnect(){
        try {
            connection.end();
        } catch (IOException e) {
            Main.newAlert(Alert.AlertType.ERROR, "Disconnection error!", e.getMessage())
                    .showAndWait();
        }
        connected = false;
    }

    public void send(byte[] buffer){
        connection.send(buffer);
    }

    public byte[] receive(){
        byte[] buffer = new byte[1024];
        connection.receive(buffer);
        return buffer;
    }

    private void ReceiveThreadMethod() throws InterruptedException {

        byte[] buffer = new byte[1024];
        while(connected){

            int received = connection.receive(buffer);
            String message = Arrays.toString(buffer);
            if(received > 0){
                client.getTextArea().appendText(message + '\n');
            }

            // check if connected - if not close client
            // receiveThread.join();
        }
    }

    public boolean checkUser(String login, String password) throws IOException {

        Message.ClientMessage user = Message.ClientMessage.newBuilder()
                .setLogin(login).setPassword(password)
                .setAuthorizationType(Message.ClientMessage.authorizationTypes.LOG_IN)
                .setMessageType(Message.ClientMessage.messageTypes.AUTHORIZATION)
                .build();

        byte[] msg = user.toByteArray();
        int bytesToSend = msg.length;

        connection.getOut().write(4);
//        while(bytesToSend != 0){
            connection.getOut().write(Arrays.toString(msg), 0, bytesToSend);
//        }

        char[] answer = new char[4];
        int received = 0;
        // wrap
        received = connection.getIn().read(answer, 0, 4);

        byte[] receivedBytes = new String(answer).getBytes();
        int answerSize = ByteBuffer.wrap(receivedBytes).getInt();

        char[] answerMsg = new char[answerSize];
        int rec = 0;
        while(answerSize != 0){
            received = connection.getIn().read(answerMsg, rec, answerSize);
            rec += received;
            answerSize -= received;
        }

        Message.ClientMessage response = Message.ClientMessage.parseFrom(new String(answerMsg).getBytes());
        if (response.getMessageType() != Message.ClientMessage.messageTypes.REPLY)
            System.out.println("Cos nie halo");
        return response.getReply() == Message.ClientMessage.replyStatus.POSITIVE;
    }

    public Thread getReceiveThread() {
        return receiveThread;
    }
}
