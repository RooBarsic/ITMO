package server.frames.logIn;

import common.MyFrame;

import javax.swing.*;
import java.awt.*;

public class LogInFrame extends MyFrame {
    private JTextField jLogin;
    private JPasswordField jPassword;
    public LogInFrame() {
        super("Sing in or Sign up", 200, 100);
        frame1 = new JFrame("Sing in or Sign up");
        frame1.setSize(200, 100);
        frame1.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame1.setLocationRelativeTo(null);
        frame1.setLayout(new GridBagLayout());

        JLabel loginLabel = new JLabel("Login :");
        JLabel passwordLabel = new JLabel("Password :");

        jLogin = new JTextField();
        jPassword = new JPasswordField();

        JButton signIn = new JButton("Sign in");
        signIn.addActionListener(new SignInActionListener(this));
        JButton signUp = new JButton("Sign up");
        signUp.addActionListener(new SignUpActionListener());
        frame1.add(loginLabel, new GridBagConstraints(0, 0, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(jLogin, new GridBagConstraints(1, 0, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(passwordLabel, new GridBagConstraints(0, 1, 1, 1, 1, 1,
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
        //frame1.pack();
    }

    public String getLogin(){
        return jLogin.getText();
    }

    public String getPassword(){
        return new String(jPassword.getPassword());
    }
}

