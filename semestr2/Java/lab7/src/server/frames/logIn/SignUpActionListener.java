package server.frames.logIn;

import server.frames.registration.RegistrationFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SignUpActionListener implements ActionListener {
    public SignUpActionListener(){
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        new RegistrationFrame();
        System.out.println(" Sombody  cliced sign up.");
    }
}
