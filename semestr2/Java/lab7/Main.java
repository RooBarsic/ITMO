import common.bookComponents.Janrs;
import server.dataBase.DataLog;
import server.frames.addBook.AddBookFrame;
import server.frames.fixBook.FixBookFrame;
import server.frames.logIn.LogInFrame;
import server.frames.logIn.SignInActionListener;
import server.frames.logIn.SignUpActionListener;
import server.frames.mainFrame.MainFrame;
import server.frames.removeBook.RemoveBookFrame;
import server.frames.removeGreater.RemoveGreaterBookFrame;
import server.frames.removeLower.RemoveLowerBookFrame;
import sun.util.locale.provider.JRELocaleConstants;
import сlient.client.frames.ClientMainFrame;

import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws InterruptedException, FileNotFoundException {
        DataLog.setLogs("books.txt", "users.txt");
        System.out.println("Hello World!");
        DataLog.addNewUser("Barsic", "123");
        DataLog.readBooksFromFile(false);
        DataLog.readUsersFromFile();
        DataLog.mainFrame = new MainFrame(false);
        //new MainFrame(true);
        //new FixBookFrame();
        //LogInFrame ff = new LogInFrame();

        //new FillBookInfoFrame(true);
        //new AddBookFrame();

        //new MainFrame(true);
        //new ClientMainFrame();
        //fff();
        //new AddBookFrame();
        AAA a = new AAA();
        new Trrr(a).start();
        new Trr2(a).start();
        return;
    }

    public static void ddd() {
        JFrame frame1 = new JFrame("Sing in or Sign up");
        frame1.setSize(500, 500);
        frame1.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame1.setLocationRelativeTo(null);
        frame1.setLayout(new GridBagLayout());

        JLabel loginLabel = new JLabel("Login :");
        JLabel passwordLabel = new JLabel("Password :");

        JTextField jLogin = new JTextField();
        JPasswordField jPassword = new JPasswordField();

        JButton signIn = new JButton("Sign in");
        JButton signUp = new JButton("Sign up");
        signUp.addActionListener(new SignUpActionListener());
        frame1.add(loginLabel, new GridBagConstraints(10, 10, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(jLogin, new GridBagConstraints(1, 0, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(passwordLabel, new GridBagConstraints(2, 0, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(jPassword, new GridBagConstraints(1, 1, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(signUp, new GridBagConstraints(0, 2, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(signIn, new GridBagConstraints(1, 2, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));

        frame1.setVisible(true);

    }

    public static void fff() {
        JFrame frame = new JFrame("test Frame");
        frame.setSize(500, 500);
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        frame.setLayout(new GridBagLayout());

        JLabel jLabel = new JLabel("Hello");
        //jLabel.setForeground(new Color(0, 0, 0, 200));
        frame.add(jLabel);
        //frame.add(new JLabel("Bye"));

        frame.setVisible(true);

        Scanner scanner = new Scanner(System.in);

        while(true){
            int x = scanner.nextInt();
            jLabel.setForeground(new Color(0, 0, 0, x));
        }
    }


}


class Trrr extends Thread{
    AAA x;
    Trrr(AAA b){
        x = b;
    }
    public void run(){
        x.m1();
    }
}

class Trr2 extends Thread{
    AAA y;
    Trr2(AAA b){
        y = b;
    }
    public void run(){
        y.m2();
    }
}


class AAA{
    static final Janrs janrs = Janrs.FOLK;
    void m1(){
        synchronized (janrs){
            System.out.println(" I in Tread. Tread now slipp");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(" tread wake up");
        }
    }

    void m2(){
        System.out.println(janrs.name() + " kuku ");
    }
}
