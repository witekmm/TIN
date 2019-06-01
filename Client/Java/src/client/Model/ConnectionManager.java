package client.Model;

import client.Controller.ClientViewController;
import client.Main;
import client.Message;
import com.google.protobuf.InvalidProtocolBufferException;
import javafx.concurrent.Task;
import javafx.event.ActionEvent;
import javafx.scene.control.Alert;

import java.io.IOException;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class ConnectionManager {

    private Connection connection;
    private String IP;
    private Integer port;
    private Boolean connected;
    private ClientViewController client;
    private String login;
    private String password;

    private Thread receiveThread;

    public ConnectionManager(String _ip, Integer _port, ClientViewController clientViewController) {

        IP = _ip;
        port = _port;
        client = clientViewController;
        connected = false;
        connection = new Connection(IP, port);
    }

    public void connect() throws Exception {
        Task work = new Task<Void>(){
            @Override
            protected Void call() throws Exception {
                ReceiveThreadMethod();
                return null;
            }
        };
        receiveThread = new Thread(work);
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

    public void send(String buffer, String groupName){

        Message.ClientMessage msg = Message.ClientMessage.newBuilder()
                .setGroupActionType(Message.ClientMessage.groupActionTypes.MESSAGE)
                .setMessageType(Message.ClientMessage.messageTypes.GROUP)
                .setMessageContent(buffer)
                .setGroupName(groupName)
                .build();

        byte[] serialized = msg.toByteArray();
        int msgSize = serialized.length;
        byte[] result = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(msgSize).array();

        byte[] send = new byte[result.length + msgSize];
        System.arraycopy(result, 0, send, 0, result.length);
        System.arraycopy(serialized, 0, send, result.length, msgSize);

        try {
            connection.getOut().write(send);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public byte[] receive(){
        byte[] buffer = new byte[1024];
        connection.receive(buffer);
        return buffer;
    }

    private void ReceiveThreadMethod() {

        while(connected){

            int received = 0;

            char[] answer = new char[4];
            try {
                if((received = connection.getIn().read(answer, 0, 4)) == -1){
                    System.out.println("sieknol sie1");
                    break;
                }
            } catch (IOException e) {
                e.printStackTrace();
            }

            byte[] receivedBytes = new String(answer).getBytes();
            ByteBuffer wrapped = ByteBuffer.wrap(receivedBytes);
            wrapped.order(ByteOrder.LITTLE_ENDIAN);
            int answerSize = wrapped.getInt();

            char[] answerMsg = new char[answerSize];
            try {
                if((received = connection.getIn().read(answerMsg, 0, answerSize))==-1){
                    System.out.println("sieknol sie1");
                    break;

                }
            } catch (IOException e) {
                e.printStackTrace();
            }
            Message.ClientMessage response = null;
            try {
                response = Message.ClientMessage.parseFrom(new String(answerMsg).getBytes());
            } catch (InvalidProtocolBufferException e) {
                e.printStackTrace();
            }

            if(received > 0){
                if(response!= null && !response.getMessageContent().isEmpty())
                    client.getTextArea().appendText(response.getMessageContent() + '\n');

                Message.ClientMessage msg = Message.ClientMessage.newBuilder()
                        .setMessageType(Message.ClientMessage.messageTypes.REPLY)
                        .build();

                byte[] serialized = msg.toByteArray();
                int msgSize = serialized.length;
                byte[] result = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(msgSize).array();

                byte[] send = new byte[result.length + msgSize];
                System.arraycopy(result, 0, send, 0, result.length);
                System.arraycopy(serialized, 0, send, result.length, msgSize);

                try {
                    connection.getOut().write(send);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
//            if(received == -1){
//                    disconnect();
//                    System.out.println("sieknol sie");
//            }
        }
    }

    public boolean checkUser(String login, String password) throws IOException {

        this.login = login; this.password = password;
        Message.ClientMessage user = Message.ClientMessage.newBuilder()
                .setLogin(login).setPassword(password)
                .setAuthorizationType(Message.ClientMessage.authorizationTypes.LOG_IN)
                .setMessageType(Message.ClientMessage.messageTypes.AUTHORIZATION)
                .build();

        byte[] msg = user.toByteArray();
        int msgSize = msg.length;
        byte[] result = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(msgSize).array();

        byte[] send = new byte[result.length + msgSize];
        System.arraycopy(result, 0, send, 0, result.length);
        System.arraycopy(msg, 0, send, result.length, msgSize);

        connection.getOut().write(send);

        char[] answer = new char[4];
        connection.getIn().read(answer, 0, 4);

        byte[] receivedBytes = new String(answer).getBytes();
        ByteBuffer wrapped = ByteBuffer.wrap(receivedBytes);
        wrapped.order(ByteOrder.LITTLE_ENDIAN);
        int answerSize = wrapped.getInt();

        char[] answerMsg = new char[answerSize];
        connection.getIn().read(answerMsg, 0, answerSize);

        Message.ClientMessage response = Message.ClientMessage.parseFrom(new String(answerMsg).getBytes());
        return response.getReply() == Message.ClientMessage.replyStatus.POSITIVE;
    }

    public Thread getReceiveThread() {
        return receiveThread;
    }

    public Boolean isConnected(){
        return connected;
    }


}
