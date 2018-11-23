package server;

import server.dataBase.DataLog;
import server.frames.logIn.LogInFrame;
import server.frames.mainFrame.MainFrame;
import сlient.client.frames.ClientMainFrame;

import java.io.FileNotFoundException;

public class ServerMain {
    public static void main(String[] args) throws InterruptedException, FileNotFoundException {
        System.out.println("Server");
        DataLog.setLogs("books.txt", "users.txt");
        System.out.println("Hello World!");
        DataLog.addNewUser("Barsic", "123");
        DataLog.readBooksFromFile(false);
        DataLog.readUsersFromFile();
        DataLog.mainFrame = new MainFrame(false);
        //new FixBookFrame();
        LogInFrame ff = new LogInFrame();
        new Listener().start();
        //new FillBookInfoFrame(true);
        //new AddBookFrame();



        return;
    }

}
