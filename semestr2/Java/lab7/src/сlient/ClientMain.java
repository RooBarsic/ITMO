package сlient;

import common.bookComponents.MyLog;
import сlient.client.frames.ClientMainFrame;

import java.io.PrintWriter;
import java.util.Scanner;

public class ClientMain {
    public static void main(String[] args){
        System.out.println("Client");
        ClientDataLog.clientFrame = new ClientMainFrame();
        Scanner scanner = new Scanner(System.in);
        PrintWriter printer = new PrintWriter(System.out);
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
        ClientDataLog.host = host;
        ClientDataLog.port = port;
        new BookLoaderTread().start();
    }
}
