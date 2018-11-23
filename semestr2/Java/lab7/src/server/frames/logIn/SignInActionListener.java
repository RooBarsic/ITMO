package server.frames.logIn;

import common.MessageFrame;
import server.dataBase.DataLog;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SignInActionListener implements ActionListener {
    private LogInFrame logInFrame;

    public SignInActionListener(LogInFrame logInFrame){
        this.logInFrame = logInFrame;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if(DataLog.checkUser(logInFrame.getLogin(), logInFrame.getPassword())){
            logInFrame.setVisibleFalse();
            DataLog.mainFrame.setVisibleTrue();
        }
        else {
            new MessageFrame(" Wrong user name or password! ");
        }
        System.out.println(" Sombody  cliced sign in.");
    }
}
