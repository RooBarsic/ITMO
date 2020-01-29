package client;

import com.google.gson.Gson;
import common.Book;
import common.MyLog;
import common.SingleOwl;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.DatagramChannel;
import java.util.ArrayList;

public class BookKeeper extends Thread{
    private String host;
    private int port;
    private int numberOfBooks = 0;
    private SingleOwl messageOwl = null;
    private ArrayList<Book> books;

    BookKeeper(String hostName, int port, int numberOfBooks, SingleOwl messageOwl){
        host = hostName;
        this.port = port;
        this.numberOfBooks = numberOfBooks;
        this.messageOwl = messageOwl;
        books = new ArrayList<>();
    }

    public void run(){
        System.out.println("Get Start weiting books = ");
        try {
            InetSocketAddress serverAddress = new InetSocketAddress(host, port);
            DatagramChannel channel = DatagramChannel.open();
            channel.bind(null);

            //System.out.println(" step 2.1 - done. ");
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            //System.out.println(" step 2.2 - done. ");
            ObjectOutputStream oos = new ObjectOutputStream(baos);
            //System.out.println(" step 2.3 - done. ");
            if(messageOwl == null) System.out.println(" in bookKeeper message owl is null. ");
            else System.out.println(" message owl is not null. ");
            oos.writeObject(messageOwl);
            //System.out.println(" step 2.4 - done. ");
            oos.flush();

            byte[] messageBytes = baos.toByteArray();
            ByteBuffer messageBuffer = ByteBuffer.wrap(messageBytes);
            channel.send(messageBuffer, serverAddress);
            System.out.println(" message owl : " + messageBytes);

            while(true) {
                //System.out.println(" step 4 - done. ");
                byte[] responseBytes = new byte[500];
                ByteBuffer responseBuffer = ByteBuffer.wrap(responseBytes);
                channel.receive(responseBuffer);

                System.out.println(" answer owl : " + responseBytes);
                try {

                    ByteArrayInputStream bais = new ByteArrayInputStream(responseBytes);
                    ObjectInputStream ois = new ObjectInputStream(bais);

                    //System.out.println(" step 6.1 - done. ");
                    SingleOwl answerOwl = (SingleOwl) ois.readObject();
                    //System.out.println(" step 6.2 - done. ");
                    if(answerOwl.getMessage().equals("nobooks")) break;
                    //System.out.println(" step 6.3 - done. ");
                    System.out.println( Integer.toString(books.size() + 1) + " got new book");
                    //System.out.println(" step 6.4 - done. ");
                    books.add(answerOwl.getBook());
                    //System.out.println(" step 6.5 - done. ");
                } catch (ClassNotFoundException e) {
                    //e.printStackTrace();
                    //System.out.println("got bad owl. ");
                }
                //System.out.println(" step 7 - done. ");
            }
            //System.out.println(" step 8 - done. ");
            System.out.println(" finished getting books = " + ". We got " + books.size() + " books.");
        } catch (IOException e) {
            //e.printStackTrace();
            System.out.println( " Errorrr >> in BookKeeper;  pos 2; server send incorrect Owl.");
        }
    }

    public ArrayList<Book> getBooks(){
        return books;
    }
}
