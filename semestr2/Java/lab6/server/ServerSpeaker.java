package server;

import common.SingleOwl;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.nio.channels.DatagramChannel;

public class ServerSpeaker extends Thread{
    private DatagramSocket ds;
    private String message;
    private DatagramPacket pack;

    ServerSpeaker(DatagramSocket ds, DatagramPacket packet, String message){
        this.ds = ds;
        this.message = message;
        pack = packet;
    }

    public void run(){
        try {
            SingleOwl messageOwl = new SingleOwl(message);

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
