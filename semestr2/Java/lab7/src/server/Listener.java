package server;

import common.bookComponents.Book;
import common.bookComponents.MyLog;
import server.dataBase.DataLog;
import сlient.ClientOwl;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.Inet4Address;
import java.net.SocketException;
import java.util.Scanner;

public class Listener extends Thread {

    public void run() {
        Scanner scanner = new Scanner(System.in);
        PrintWriter printer = new PrintWriter(System.out);

        MyLog.printLn(printer, "Lab6.Server");
        MyLog.print(printer, "Get home port : ");
        int port = Integer.parseInt(scanner.next());

        DatagramSocket ds = null;
        try {
            System.out.println(" Server addres : " + Inet4Address.getLocalHost().getHostAddress());
            ds = new DatagramSocket(port);
        } catch (Exception e) {
            e.printStackTrace();
        }
        while (true) {
            byte[] responseBytes = new byte[500];
            DatagramPacket pack = new DatagramPacket(responseBytes, 500);
            System.out.println("\n start listening, kol books = " + DataLog.getNumberOfBooks());
            try {
                ds.receive(pack);
            } catch (IOException e) {
                e.printStackTrace();
            }

            ClientOwl messageOwl = null;
            try {
                ByteArrayInputStream bais = new ByteArrayInputStream(pack.getData());
                ObjectInputStream ois = new ObjectInputStream(bais);
                messageOwl = (ClientOwl) ois.readObject();
            } catch (Exception e) {
                e.printStackTrace();
                MyLog.printLn(printer, "Got bad owl. Stop listening. ");
            }


            if (messageOwl != null) {
                ServerOwl ansverOwl = new ServerOwl(DataLog.getBooks());
                new ServerSpeaker(ds, pack, ansverOwl).start();
            }
        }
    }
}
