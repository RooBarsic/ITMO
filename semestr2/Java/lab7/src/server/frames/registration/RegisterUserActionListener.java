package server.frames.registration;

import server.dataBase.DataLog;
import common.*;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RegisterUserActionListener implements ActionListener {
    private RegistrationFrame frame;

    public RegisterUserActionListener(RegistrationFrame frame){
        this.frame = frame;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        System.out.println(" new user, login : " + frame.getUserLogin() + " password : " + frame.getUserPassword());
        if(frame.getUserLogin() == null) new MessageFrame("Wrong username");
        else if(frame.getUserLogin().equals("")) new MessageFrame("Wrong username");
        else if(frame.getUserPassword() == null) new MessageFrame("Wrong password");
        else if(frame.getUserPassword().equals("")) new MessageFrame("Bad password");
        else {
            int result = DataLog.addNewUser(frame.getUserLogin(), frame.getUserPassword());
            if (result == 1){
                new MessageFrame("Registration succesfuly done");
                frame.setVisibleFalse();
            }
            else if (result == 0) new MessageFrame("This username already exist");
            else new MessageFrame("Wrong username or password");
        }
    }
}
