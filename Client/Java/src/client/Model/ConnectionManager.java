package client.Model;

import client.Controller.ClientViewController;
import client.Main;
import client.Message;
import com.google.protobuf.InvalidProtocolBufferException;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.concurrent.Task;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import java.io.IOException;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Optional;

public class ConnectionManager {

    private Connection connection;
    private String IP;
    private Integer port;
    private Boolean connected;
    private ClientViewController client;
    private ObservableList<String> groups;
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
//            if(receiveThread.isAlive())
//                receiveThread.st
            connection.end();
        } catch (IOException e) {
            Main.newAlert(Alert.AlertType.ERROR, "Disconnection error!", e.getMessage())
                    .showAndWait();
        }
        connected = false;
    }

    public void createGroup(String groupName){
        Message.ClientMessage group = Message.ClientMessage.newBuilder()
                .setMessageType(Message.ClientMessage.messageTypes.GROUP)
                .setGroupActionType(Message.ClientMessage.groupActionTypes.CREATE)
                .setGroupName(groupName)
                .build();

        serializeAndSend(group);
    }

    public void joinGroup(String groupName) {
        Message.ClientMessage group = Message.ClientMessage.newBuilder()
                .setMessageType(Message.ClientMessage.messageTypes.GROUP)
                .setGroupActionType(Message.ClientMessage.groupActionTypes.REQUEST)
                .setGroupName(groupName)
                .build();

        serializeAndSend(group);
    }

    public void leaveGroup(String groupName) {
        Message.ClientMessage group = Message.ClientMessage.newBuilder()
                .setMessageType(Message.ClientMessage.messageTypes.GROUP)
                .setGroupActionType(Message.ClientMessage.groupActionTypes.LEAVE)
                .setGroupName(groupName)
                .build();

        serializeAndSend(group);
    }

    public void deleteGroup(String groupName) {
        Message.ClientMessage group = Message.ClientMessage.newBuilder()
                .setMessageType(Message.ClientMessage.messageTypes.GROUP)
                .setGroupActionType(Message.ClientMessage.groupActionTypes.DELETE)
                .setGroupName(groupName)
                .build();

        serializeAndSend(group);
    }

    public void sendMessage(String buffer, String groupName){

        Message.ClientMessage msg = Message.ClientMessage.newBuilder()
                .setGroupActionType(Message.ClientMessage.groupActionTypes.MESSAGE)
                .setMessageType(Message.ClientMessage.messageTypes.GROUP)
                .setMessageContent(buffer)
                .setGroupName(groupName)
                .build();

        serializeAndSend(msg);
    }

    private void sendLoginRequest(String login, String password){
        Message.ClientMessage user = Message.ClientMessage.newBuilder()
                .setLogin(login).setPassword(password)
                .setAuthorizationType(Message.ClientMessage.authorizationTypes.LOG_IN)
                .setMessageType(Message.ClientMessage.messageTypes.AUTHORIZATION)
                .build();

        serializeAndSend(user);
    }

    private void sendReply(){
        Message.ClientMessage msg = Message.ClientMessage.newBuilder()
                .setMessageType(Message.ClientMessage.messageTypes.REPLY)
                .build();

        serializeAndSend(msg);
    }

    private void serializeAndSend(Message.ClientMessage msg){
        byte[] serialized = msg.toByteArray();
        int msgSize = serialized.length;
        byte[] result = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(msgSize).array();

        byte[] send = new byte[result.length + msgSize];
        System.arraycopy(result, 0, send, 0, result.length);
        System.arraycopy(serialized, 0, send, result.length, msgSize);

        connection.send(send);
    }

    private int getMsgLength(char[] answer){
        byte[] receivedBytes = new String(answer).getBytes();
        ByteBuffer wrapped = ByteBuffer.wrap(receivedBytes);
        wrapped.order(ByteOrder.LITTLE_ENDIAN);
        return wrapped.getInt();
    }

    private void ReceiveThreadMethod() {

        while(connected){

            int received;
            char[] answer = new char[4];

            if((received = connection.receive(answer, 0, 4)) == -1){
                break;
            }

            int answerSize = getMsgLength(answer);
            char[] answerMsg = new char[answerSize];
            if((received = connection.receive(answerMsg, 0, answerSize)) == -1){
                break;
            }

            Message.ClientMessage response = null;
            try {
                response = Message.ClientMessage.parseFrom(new String(answerMsg).getBytes());
            } catch (InvalidProtocolBufferException e) {
                e.printStackTrace();
            }

            if(received > 0){
                assert response != null;
                handleResponse(response);
            }
        }
    }

    private void handleResponse(Message.ClientMessage response){
        if(!response.getMessageContent().isEmpty())
            client.getTextArea().appendText(response.getUserName() +  ": " + response.getMessageContent() + '\n');

        if(!response.getReplyContent().isEmpty())
            client.getTextArea().appendText("Error: " + response.getReplyContent() + '\n');

        if(response.getReply() == Message.ClientMessage.replyStatus.POSITIVE) {
            groupReply(response, response.getGroupActionType());
        }

        if(response.getGroupActionType() == Message.ClientMessage.groupActionTypes.REQUEST) {
            createJoinGroupAlert(response.getUserName(), response.getGroupName());
        }

        if(response.getGroupActionType() == Message.ClientMessage.groupActionTypes.ACCEPT){
            groupReply(response, response.getGroupActionType());
        }

        if(response.getMessageType()!= Message.ClientMessage.messageTypes.REPLY) {
            sendReply();
        }
    }

    private void groupReply(Message.ClientMessage response, Message.ClientMessage.groupActionTypes reply){

        ObservableList newList = client.getGroupChoice().getItems();
        if(reply == Message.ClientMessage.groupActionTypes.CREATE){
            client.getTextArea().appendText("Group: '" + response.getGroupName() + "' created!" + '\n');
            newList.add(response.getGroupName());
        }
        else if(reply == Message.ClientMessage.groupActionTypes.DELETE){
            client.getTextArea().appendText("Group: '" + response.getGroupName() + "' deleted!" + '\n');
            newList.remove(response.getGroupName());
        }
        else if(reply == Message.ClientMessage.groupActionTypes.LEAVE){
            client.getTextArea().appendText("Group: '" + response.getGroupName() + "' left!" + '\n');
            newList.remove(response.getGroupName());
        }
        else if(reply == Message.ClientMessage.groupActionTypes.ACCEPT){
            client.getTextArea().appendText("Request accepted. Joined group: " + response.getGroupName() + '\n');
            newList.add(response.getGroupName());
        }
        client.getGroupChoice().setItems(newList);
        client.getGroupChoice().setValue("");
    }

    private void createJoinGroupAlert(String userName, String groupName){

        Thread t = new Thread(() -> Platform.runLater(() -> {
            Alert alert = Main.newAlert(Alert.AlertType.CONFIRMATION, "Request", "User: " + userName +
                    " wants to join group: " + groupName);
            ButtonType buttonAccept = new ButtonType("Accept"),
                        buttonDecline = new ButtonType("Decline");
            alert.getButtonTypes().setAll(buttonAccept, buttonDecline);
            Optional<ButtonType> option = alert.showAndWait();

            Message.ClientMessage msg;
            if (option.isPresent() && option.get() == buttonAccept) {
                msg = Message.ClientMessage.newBuilder()
                        .setMessageType(Message.ClientMessage.messageTypes.GROUP)
                        .setGroupActionType(Message.ClientMessage.groupActionTypes.ACCEPT)
                        .setUserName(userName)
                        .setGroupName(groupName)
                        .build();
            } else {
                msg = Message.ClientMessage.newBuilder()
                        .setMessageType(Message.ClientMessage.messageTypes.GROUP)
                        .setGroupActionType(Message.ClientMessage.groupActionTypes.DECLINE)
                        .setUserName(userName)
                        .setGroupName(groupName)
                        .build();
            }
            serializeAndSend(msg);
        }));
        t.start();
    }
    public boolean checkUser(String login, String password) throws IOException {
        sendLoginRequest(login, password);

        char[] answer = new char[4];
        connection.receive(answer, 0, 4);

        int answerSize = getMsgLength(answer);
        char[] answerMsg = new char[answerSize];
        connection.getIn().read(answerMsg, 0, answerSize);

        Message.ClientMessage response = Message.ClientMessage.parseFrom(new String(answerMsg).getBytes());
        ObservableList<String> groups = FXCollections.observableArrayList(response.getGroupsList());
        client.getGroupChoice().setItems(groups);
        return response.getReply() == Message.ClientMessage.replyStatus.POSITIVE;
    }

    public Thread getReceiveThread() { return receiveThread; }
    public Boolean isConnected(){
        return connected;
    }
    public ObservableList<String> getGroups() { return groups; }
}
