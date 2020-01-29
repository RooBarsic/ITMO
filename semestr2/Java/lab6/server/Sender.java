package server;

import com.google.gson.Gson;
import common.Book;
import common.SingleOwl;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.util.*;

public class Sender extends Thread{
    private String key;
    private DatagramPacket datagramPacket;
    private DatagramSocket datagramSocket;
    private ArrayList<Book> books = null;

    Sender(HashMap< String, Book > books, DatagramSocket soket, DatagramPacket paket){
        key = paket.getAddress().getHostAddress() + paket.getPort();
        datagramPacket = paket;
        datagramSocket = soket;
        this.books = new ArrayList();
        for(Book book : books.values()){
            this.books.add(book);
        }
        Collections.sort(this.books, new Comparator<Book>() {
            public int compare(Book o1, Book o2) {
                return (int) (o1.getBookCoordinates().get_rast_kv(0, 0) -
                                        o2.getBookCoordinates().get_rast_kv(0, 0));
            }
        });
    }

    public void run(){
        System.out.println(" I'm going to send " + books.size() + " books. ");
        if(books.size() == 0){
            System.out.println(" no books for sending. ");
            new ServerSpeaker(datagramSocket, datagramPacket, "nobooks").start();
        }
        Gson json = new Gson();
        try {
            for(Book book : books) {
                SingleOwl messageOwl = new SingleOwl("book", book);
                ByteArrayOutputStream baos = new ByteArrayOutputStream();
                ObjectOutputStream oos = new ObjectOutputStream(baos);
                oos.writeObject(messageOwl);
                oos.flush();

                byte[] b = baos.toByteArray();
                DatagramPacket AnswerPack = new DatagramPacket(b, b.length, datagramPacket.getAddress(),
                        datagramPacket.getPort());
                datagramSocket.send(AnswerPack);
            }

            SingleOwl messageOwl = new SingleOwl("nobooks");
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ObjectOutputStream oos = new ObjectOutputStream(baos);
            oos.writeObject(messageOwl);
            oos.flush();

            byte[] b = baos.toByteArray();
            DatagramPacket AnswerPack = new DatagramPacket(b, b.length, datagramPacket.getAddress(),
                    datagramPacket.getPort());
            datagramSocket.send(AnswerPack);

        } catch (IOException e) {
            System.out.println("Sender run slippp");
            e.printStackTrace();
        }
    }
}



