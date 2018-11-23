package server.frames.mainFrame.mainFrame.actionListeners;

import server.frames.fixBook.FixBookFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GotoFixBookFrame implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent e) {
        new FixBookFrame();
    }
}