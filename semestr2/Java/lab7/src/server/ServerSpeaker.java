package server;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class ServerSpeaker  extends Thread{
    private DatagramSocket ds;
    private DatagramPacket pack;
    private ServerOwl messageOwl;

    ServerSpeaker(DatagramSocket ds, DatagramPacket packet, ServerOwl messageOwl){
        this.ds = ds;
        this.messageOwl = messageOwl;
        pack = packet;
    }

    public void run(){
        try {
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ObjectOutputStream oos = new ObjectOutputStream(baos);
            oos.writeObject(messageOwl);
            oos.flush();

            byte[] b = baos.toByteArray();
            DatagramPacket AnswerPack = new DatagramPacket(b, b.length, pack.getAddress(), pack.getPort());
            ds.send(AnswerPack);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
