package server;

import common.Book;
import common.MyLog;
import common.SingleOwl;

import java.io.*;
import java.net.*;
import java.util.*;

public class ServerMain {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        PrintWriter printer = new PrintWriter(System.out);
        BookSet bookSet = new BookSet();

        MyLog.printLn(printer, "Lab6.Server");
        MyLog.print(printer, "Get home port : ");
        int port = Integer.parseInt(scanner.next());

        System.out.println(" Server addres : " + Inet4Address.getLocalHost().getHostAddress());
        HashMap< String, Sender> taskSolvers = new HashMap<>();
        DatagramSocket ds = new DatagramSocket(port);
        while (true) {
            byte[] responseBytes = new byte[500];
            DatagramPacket pack = new DatagramPacket(responseBytes, 500);
            System.out.println( "\n start listening, kol books = " + bookSet.getNumberOfBooks());
            ds.receive(pack);

            SingleOwl answerOwl = null;
            try {
                ByteArrayInputStream bais = new ByteArrayInputStream(pack.getData());
                ObjectInputStream ois = new ObjectInputStream(bais);
                answerOwl = (SingleOwl) ois.readObject();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
                MyLog.printLn(printer, "Got bad owl. Stop listening. ");
            }

            if(answerOwl == null) continue;

            System.out.println( " got message from client ( new owl ). ");
            System.out.println( " got command, id = " + answerOwl.getCommandType());
            HashMap< String, Book> books = null;
            switch ((answerOwl.getCommandType())){
                case 0:
                    bookSet.addBook(answerOwl.getBook());
                    break;
                case 1:
                    bookSet.clean();
                    break;
                case 2:
                    books = bookSet.save();
                    break;
                case 3:
                    bookSet.remove(answerOwl.getBookKey());
                    break;
                case 4:
                    bookSet.remove_lower(answerOwl.getBook());
                    break;
                case 5:
                    bookSet.remove_greater(answerOwl.getBook());
                    break;
                case 6:
                    bookSet.add_if_min(answerOwl.getBook());
                    break;
            }

            if(answerOwl.getCommandType() == 2){
                if(books.size() == 0){
                    new ServerSpeaker(ds, pack,"nobooks").start();
                }
                else {
                    Sender taskSolver = new Sender(books, ds, pack);
                    taskSolver.start();
                }
            }
            else if(answerOwl.getCommandType() == 7){
                ServerSpeaker speaker = new ServerSpeaker(ds, pack, Integer.toString(bookSet.getNumberOfBooks()));
                speaker.start();
                System.out.println( " I send numberOfBooks = " + bookSet.getNumberOfBooks() + " to client. " );
            }
            else {
                ServerSpeaker speaker = new ServerSpeaker(ds, pack, "done");
                speaker.start();
                System.out.println( " I send 'done' to client. " );
            }


        }
    }
