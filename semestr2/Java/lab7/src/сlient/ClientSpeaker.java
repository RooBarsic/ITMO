package сlient;

import server.ServerOwl;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.DatagramChannel;

public class ClientSpeaker extends Thread{
    private String host;
    private int port;
    private ClientOwl messageOwl;
    private ServerOwl answerOwl;

    ClientSpeaker(ClientOwl messageOwl, String host, int port){
        this.messageOwl = messageOwl;
        this.host = host;
        this.port = port;
    }

    public ServerOwl getAnswerOwl() {
        return answerOwl;
    }

    public void run(){

        System.out.println(" Sending message in process. ");
        //System.out.println(" Get start sending message = " + message);
        try {
            //System.out.println(" step 1 - done. ");
            InetSocketAddress serverAddress = new InetSocketAddress(host, port);
            DatagramChannel channel = DatagramChannel.open();
            channel.bind(null);

            //System.out.println(" step 2.1 - done. ");
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            //System.out.println(" step 2.2 - done. ");
            ObjectOutputStream oos = new ObjectOutputStream(baos);
            //System.out.println(" step 2.3 - done. ");
            //if(messageOwl == null) System.out.println(" message owl is null. ");
            //else System.out.println(" message owl is not null. ");
            oos.writeObject(messageOwl);
            //System.out.println(" step 2.4 - done. ");
            oos.flush();

            //System.out.println(" step 3 - done. ");
            byte[] messageBytes = baos.toByteArray();
            //System.out.println("message : " + messageBytes);
            ByteBuffer messageBuffer = ByteBuffer.wrap(messageBytes);
            channel.send(messageBuffer, serverAddress);

            //System.out.println(" step 4 - done. ");
            byte[] responseBytes = new byte[500000];
            ByteBuffer responseBuffer = ByteBuffer.wrap(responseBytes);
            channel.receive(responseBuffer);

            //System.out.println(" step 5 - done. ");
            //System.out.println(" Answer : " + responseBytes);

            //System.out.println(" step 6 - done. ");
            ByteArrayInputStream bais = new ByteArrayInputStream(responseBytes);
            ObjectInputStream ois = new ObjectInputStream(bais);
            answerOwl = (ServerOwl) ois.readObject();

            //System.out.println(" step 7 - done. ");
            //System.out.println(" Finished sending message = " + message);
        } catch (IOException e) {
            answerOwl = null;
            //System.out.println( " Errorrr >> in Speaker; pos 1; I got bad Owl (.");
            //e.printStackTrace();
        } catch (ClassNotFoundException e) {
            answerOwl = null;
            //System.out.println( " Errorrr >> in Speaker;  pos 2; server send incorrect Owl.");
            //e.printStackTrace();
        }
    }
}