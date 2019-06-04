package client.Model;

import client.Controller.ClientViewController;
import client.Controller.LoginViewController;
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
    private volatile Boolean serverConnection;
    private ClientViewController client;
    private ObservableList<String> groups;
    private Thread receiveThread;
    private LoginViewController loginController;

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
            protected Void call() {
                ReceiveThreadMethod();
                return null;
            }
        };
        receiveThread = new Thread(work);
        int connResult = connection.connect();
        if (connResult != 0) {

            if (connResult == -1) // max connections reached, couldn't connect
                throw new SocketException();
            if (connResult == -2) // connection canceled by user
                throw new Exception("Canceled");
        }
        connected = serverConnection = true;
    }

    public void disconnect(){
        Main.newAlert(Alert.AlertType.INFORMATION, "Disconnection", "You were disconnected").showAndWait();
        serverConnection = false;
        try {
            connection.end();
        } catch (IOException e) {
            Main.newAlert(Alert.AlertType.ERROR, "Disconnection error!", e.getMessage())
                    .showAndWait();
        }
        connected = false;
    }

    public void groupAction(Message.ClientMessage.groupActionTypes type, String groupName){
        Message.ClientMessage group = Message.ClientMessage.newBuilder()
                .setMessageType(Message.ClientMessage.messageTypes.GROUP)
                .setGroupActionType(type)
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

        byte[] message = new byte[result.length + msgSize];
        System.arraycopy(result, 0, message, 0, result.length);
        System.arraycopy(serialized, 0, message, result.length, msgSize);

        connection.send(message);
    }

    private int getMsgLength(char[] answer){
        byte[] receivedBytes = new String(answer).getBytes();
        ByteBuffer wrapped = ByteBuffer.wrap(receivedBytes);
        wrapped.order(ByteOrder.LITTLE_ENDIAN);
        return wrapped.getInt();
    }

    private void ReceiveThreadMethod() {

        while(connected){
            int received, toRead = 4, bytesRead = 0;
            char[] answer = new char[4];
            while(toRead != 0) {
                if ((received = connection.receive(answer, 0, 4)) == -1) {
                    break;
                }
                toRead -= received;
            }
            int answerSize = getMsgLength(answer);
            char[] answerMsg = new char[answerSize];
            toRead = answerSize;
            while(toRead != 0) {
                if((received = connection.receive(answerMsg, 0, answerSize)) == -1){
                    break;
                }
                toRead -= received;
                bytesRead += received;
            }

            Message.ClientMessage response = null;
            try {
                response = Message.ClientMessage.parseFrom(new String(answerMsg).getBytes());
            } catch (InvalidProtocolBufferException e) {
                e.printStackTrace();
            }

            if(bytesRead > 0){
                assert response != null;
                handleResponse(response);
            }
        }
        sendNoConnection();
    }

    private void sendNoConnection(){
        Thread t = new Thread(() -> Platform.runLater(() -> {
            if(serverConnection) {
                Main.newAlert(Alert.AlertType.INFORMATION, "Disconnection", "Server connection lost! You were disconnected").showAndWait();
                try {
                    connection.end();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            client.openConnectForm();
        }));
        t.start();
    }

    private void loginUser(Boolean correctData, Message.ClientMessage response){
        Thread t = new Thread(() -> Platform.runLater(() -> {
            if(correctData){
                ObservableList<String> groups = FXCollections.observableArrayList(response.getGroupsList());
                client.getGroupChoice().setItems(groups);
                loginController.acceptLogin();
            }
            else{
                loginController.rejectLogin(response.getReplyContent());
            }
        }));
        t.start();
    }

    private void handleResponse(Message.ClientMessage response){
        if(response.getReply() == Message.ClientMessage.replyStatus.POSITIVE) {
            if(response.getAuthorizationType() == Message.ClientMessage.authorizationTypes.LOG_IN)
                loginUser(true, response);
            else if(response.getGroupActionType() != Message.ClientMessage.groupActionTypes.NOGROUPTYPE)
                groupReply(response.getGroupName(), response.getGroupActionType());
        }
        else if(response.getReply() == Message.ClientMessage.replyStatus.NEGATIVE){
            if(!response.getGroupName().isEmpty() && !response.getReplyContent().isEmpty() && response.getMessageType() == Message.ClientMessage.messageTypes.REPLY) {
                groupReply(response.getGroupName(), Message.ClientMessage.groupActionTypes.MESSAGE);
            }
            if(response.getAuthorizationType() == Message.ClientMessage.authorizationTypes.LOG_IN)
                loginUser(false, response);
        }
        if(response.getMessageType() == Message.ClientMessage.messageTypes.GROUP){
            if(response.getGroupActionType() == Message.ClientMessage.groupActionTypes.REQUEST)
                createJoinGroupAlert(response.getUserName(), response.getGroupName());
            else if(response.getGroupActionType() == Message.ClientMessage.groupActionTypes.ACCEPT)
                groupReply(response.getGroupName(), response.getGroupActionType());
            else if(response.getGroupActionType() == Message.ClientMessage.groupActionTypes.DECLINE)
                groupReply(response.getGroupName(), response.getGroupActionType());
        }
        if(response.getMessageType()!= Message.ClientMessage.messageTypes.REPLY)
            sendReply();

        if(!response.getMessageContent().isEmpty())
            client.getTextArea().appendText(response.getUserName() +  ": " + response.getMessageContent() + '\n');

        if(!response.getReplyContent().isEmpty() && response.getAuthorizationType() != Message.ClientMessage.authorizationTypes.LOG_IN)
            client.getTextArea().appendText("Error: " + response.getReplyContent() + '\n');
    }

    private void groupReply(String groupName, Message.ClientMessage.groupActionTypes type){
        Platform.runLater(()-> {
            ObservableList newList = client.getGroupChoice().getItems();
            switch(type) {
                case CREATE: {
                    client.getTextArea().appendText("Group: '" + groupName + "' created!" + '\n');
                    newList.add(groupName);
                    break;
                }
                case DELETE: {
                    client.getTextArea().appendText("Group: '" + groupName + "' deleted!" + '\n');
                    newList.remove(groupName);
                    break;
                }
                case LEAVE: {
                    client.getTextArea().appendText("Group: '" + groupName + "' left!" + '\n');
                    newList.remove(groupName);
                    break;
                }
                case ACCEPT: {
                    client.getTextArea().appendText("Request accepted. Joined group: '" + groupName + "'" + '\n');
                    newList.add(groupName);
                    break;
                }
                case DECLINE: {
                    client.getTextArea().appendText("Request to join group: '" + groupName + "' rejected!\n");
                    break;
                }
                case REQUEST: {
                    client.getTextArea().appendText("Request to join group: '" + groupName + "' send!\n");
                    break;
                }
                case MESSAGE: {
                    newList.remove(groupName);
                    break;
                }
            }
            client.getGroupChoice().setItems(newList);
            client.getGroupChoice().getSelectionModel().clearSelection();
        });
    }

    private void createJoinGroupAlert(String userName, String groupName){

        Thread t = new Thread(() -> Platform.runLater(() -> {
            Alert alert = Main.newAlert(Alert.AlertType.CONFIRMATION, "Request", "User: " + userName +
                    " wants to join group: " + groupName);
            ButtonType buttonAccept = new ButtonType("Accept"),
                        buttonDecline = new ButtonType("Decline");
            alert.getButtonTypes().setAll(buttonAccept, buttonDecline);
            Optional<ButtonType> option = alert.showAndWait();

            Message.ClientMessage.groupActionTypes type = Message.ClientMessage.groupActionTypes.DECLINE;
            if (option.isPresent() && option.get() == buttonAccept) {
                type = Message.ClientMessage.groupActionTypes.ACCEPT;
            }
            Message.ClientMessage msg = Message.ClientMessage.newBuilder()
                    .setMessageType(Message.ClientMessage.messageTypes.GROUP)
                    .setGroupActionType(type)
                    .setUserName(userName)
                    .setGroupName(groupName)
                    .build();

            serializeAndSend(msg);
        }));
        t.start();
    }
    public void checkUser(String login, String password, LoginViewController _loginController) throws IOException {
        loginController = _loginController;
        sendLoginRequest(login, password);
    }

    public Thread getReceiveThread() { return receiveThread; }
    public Boolean isConnected(){
        return connected;
    }
    public ObservableList<String> getGroups() { return groups; }
}
