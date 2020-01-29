package client;

import com.oracle.xmlns.internal.webservices.jaxws_databinding.ExistingAnnotationsType;
import common.Book;
import common.MyLog;
import common.SingleOwl;

import java.io.File;
import java.io.PrintWriter;
import java.util.List;
import java.util.Scanner;

public class ClientMain {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        PrintWriter printer = new PrintWriter(System.out);
        MyLog.printLn(printer, "Lab6.Client");
        String fileName = args[0];
        //String fileName = "/home/farrukh/books.txt";
        FileController fileController = new FileController(fileName);
        if((new File(fileName)).exists() == false){
            MyLog.printLn(printer, "File " + fileName + " - is not exist!! ");
            return;
        }
        if(fileController.isFlag() == false){
            MyLog.printLn(printer, "File " + fileName + " - povrezden!! ");
            return;
        }

        try {
            MyLog.print(printer, "Write server addres : ");
            String host = scanner.next();
            int port;
            try {
                MyLog.print(printer, "write server port : ");
                port = Integer.parseInt(scanner.next());
            } catch (Exception e){
                System.out.print(" \n Wrong port number. Please try fixed it, and try again later. ");
                return;
            }


            List<Book> books = fileController.getBooks();
            MyLog.printLn(printer, "Start sending books from file to server. ");
            for(Book book : books){
                SingleOwl bookOwl = new SingleOwl(0, book);
                Speaker tread = new Speaker(bookOwl, host, port);
                tread.start();
                MyLog.weitThread(15, tread);

                if(tread.isAlive() == true){
                    MyLog.printLn(printer, " Server is not avalible. Sending was canseled. Try again later.");
                    tread.interrupt();
                    return;
                }
                else {
                    MyLog.printLn(printer, "Server Accepted book. ");
                }
            }
            MyLog.printLn(printer, "Finish sending books from file to server. Server Accepted books; ");

            while (true) {
                avalibleCommands(printer);
                MyLog.print(printer, "Print command : ");
                String commandType = scanner.next();
                int commandNumber = 100;
                Box commandBox = null;
                SingleOwl messageOwl = null;
                switch (commandType) {
                    case "clean":
                        commandNumber = 1;
                        break;
                    case "save":
                        commandNumber = 2;
                        break;
                    case "remove_book":
                        commandNumber = 3;
                        break;
                    case "remove_lower":
                        commandNumber = 4;
                        break;
                    case "remove_greater":
                        commandNumber = 5;
                        break;
                    case "add_if_min":
                        commandNumber = 6;
                        break;
                    case "exit":
                        MyLog.printLn(printer, "Bye.");
                        return;
                    default:
                        MyLog.printLn(printer, "wrong command! Please try again.");
                        //avalibleCommands(printer);
                }
                if (commandNumber <= 2) messageOwl = new SingleOwl(commandNumber);
                else if (commandNumber == 3) {
                    MyLog.printLn(printer, "Write key of book : ");
                    messageOwl = new SingleOwl(commandNumber, scanner.next());
                } else if (commandNumber <= 6) {
                    MyLog.printLn(printer, "Write book in json format. ");
                    JsonKeeper jsonKeeper = new JsonKeeper();
                    while (!jsonKeeper.haveJson()) {
                        MyLog.print(printer, "weiting for json, json is not full : ");
                        jsonKeeper.addNewString(scanner.nextLine());
                    }
                    Book book = jsonKeeper.getBookFromJson();
                    if (book == null)
                        MyLog.printLn(printer, " Wrong json format! Please try again! ");
                    else messageOwl = new SingleOwl(commandNumber, book);
                }
                if (messageOwl != null) {
                    if (commandNumber != 2) {
                        Speaker tread = new Speaker(messageOwl, host, port);
                        tread.start();
                        MyLog.weitThread(15, tread);
                        if (tread.isAlive() == true) {
                            MyLog.printLn(printer, " Server is not avalible. Sending was canseled. Try again later.");
                            tread.interrupt();
                        }
                        else {
                            MyLog.printLn(printer, " Server Accepted command.");
                            SingleOwl answerOwl = tread.getAnswerOwl();
                            if(answerOwl != null)
                                MyLog.printLn(printer, " Server answer : " + answerOwl.getMessage());
                        }

                    }
                    else {
                        Speaker numberOfBooks = new Speaker(new SingleOwl(7), host, port);
                        numberOfBooks.start();
                        MyLog.weitThread(15, numberOfBooks);
                        if (numberOfBooks.isAlive() == true) {
                            MyLog.printLn(printer, " Server is not avalible. Sending was canseled. Try again later.");
                            numberOfBooks.interrupt();
                        } else {
                            MyLog.printLn(printer, " Server Accepted command. We are weting for " + numberOfBooks.getAnswerOwl().getMessage() + " books. ");
                            int kolBooks = Integer.parseInt(numberOfBooks.getAnswerOwl().getMessage());
                            if (kolBooks > 0) {
                                BookKeeper tread = new BookKeeper(host, port, kolBooks, messageOwl);
                                tread.start();
                                MyLog.weitThread(15 * kolBooks, tread);
                                if (tread.isAlive() == true) {
                                    MyLog.printLn(printer, " Server is not avalible. Keeping was canseled. Try again later.");
                                    tread.interrupt();
                                    fileController.printeBooksToFile(tread.getBooks());
                                } else {
                                    fileController.printeBooksToFile(tread.getBooks());
                                }
                            }
                            else MyLog.printLn(printer, "Server is empty.");
                        }
                    }
                }
            }
        } catch (Exception e){
            System.out.println(" \n You send me 'end of scanning' signal.  Bye user. ");
        }
    }
    /**
     commands
     add Book - 0
     Claen - 1

     get kol Books - 7
     save - 2

     remove_book ( key ) - 3
     remove_lower( book ) - 4
     remove_greater( book ) - 5
     add_if_min( book ) - 6

     Book1#CLASSIC#3#5#1233#3#aaa#bbb#ccc

     */

    public static void avalibleCommands(PrintWriter printWriter){
        MyLog.printLn(printWriter, "\n You can use this comands : \n" +
                "clean \n" +
                "save \n" +
                "remove_book key \n" +
                "remove_lower book \n" +
                "remove_greater book \n" +
                "add_if_min book \n" +
                "exit \n");
    }
}
