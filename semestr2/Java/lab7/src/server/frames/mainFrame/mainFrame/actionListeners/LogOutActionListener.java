package server.frames.mainFrame.mainFrame.actionListeners;

import server.dataBase.DataLog;
import server.frames.logIn.LogInFrame;
import server.frames.mainFrame.MainFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LogOutActionListener  implements ActionListener {
    private MainFrame frame1;

    public LogOutActionListener(MainFrame frame){
        frame1 = frame;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        DataLog.saveBooksToFile();
        frame1.setVisibleFalse();
        new LogInFrame();
    }
}