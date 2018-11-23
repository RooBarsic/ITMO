package сlient;

import common.MessageFrame;
import common.bookComponents.Book;
import common.bookComponents.MyLog;
import server.ServerOwl;

import java.io.PrintWriter;
import java.util.List;
import java.util.Scanner;

public class BookLoaderTread extends Thread {
    private String host;
    private int  port;

    public void run(){

        host = ClientDataLog.host;
        port = ClientDataLog.port;

        Scanner scanner = new Scanner(System.in);
        PrintWriter printer = new PrintWriter(System.out);
        MyLog.printLn(printer, "Lab6.Client");
        try {
            ClientSpeaker tread = new ClientSpeaker(new ClientOwl("get books"), host, port);
            tread.start();
            MyLog.weitThread(15, tread);
            if(tread.isAlive() == true){
                new MessageFrame("Server is not Avalible");
            }
            else {
                ServerOwl answerOwl = tread.getAnswerOwl();
                List<Book> books = answerOwl.getBooks();
                if(books == null){
                    new MessageFrame("Done!!");
                }
                for(Book book : books){
                    if(book != null);
                    ClientDataLog.clientFrame.setBook(book);
                }
            }

        } catch (Exception e){
            System.out.println(" \n You send me 'end of scanning' signal.  Bye user. ");
        }
    }
}
