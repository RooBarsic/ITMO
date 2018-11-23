package server.frames.registration;

import server.actions.CancelActionListener;
import common.MyFrame;

import javax.swing.*;
import java.awt.*;

public class RegistrationFrame extends MyFrame {
    private JTextField jLoginField;
    private JPasswordField jPasswordField;

    public RegistrationFrame(){
        super("Registration frame", 500, 500);
        frame1.setLayout(new GridBagLayout());

        JLabel infoLabel = new JLabel("Please fill fields belowe");
        JLabel userLoginLabel = new JLabel("Login :");
        JLabel userPasswordLabel = new JLabel("Password :");

        jLoginField = new JTextField();
        jPasswordField = new JPasswordField();

        JButton cansel = new JButton("Cansel");
        cansel.addActionListener(new CancelActionListener(this));
        JButton registerNewUser = new JButton("Register New User");
        registerNewUser.addActionListener(new RegisterUserActionListener(this));

        frame1.add(infoLabel, new GridBagConstraints(1, 0, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(userLoginLabel, new GridBagConstraints(0, 1, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(jLoginField, new GridBagConstraints(1, 1, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(userPasswordLabel, new GridBagConstraints(0, 2, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(jPasswordField, new GridBagConstraints(1, 2, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(cansel, new GridBagConstraints(0, 3, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(registerNewUser, new GridBagConstraints(1, 3, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));

        frame1.setVisible(true);
        frame1.pack();
    }

    public String getUserLogin(){
        return jLoginField.getText();
    }

    public String getUserPassword(){
        return new String(jPasswordField.getPassword());
    }
}
