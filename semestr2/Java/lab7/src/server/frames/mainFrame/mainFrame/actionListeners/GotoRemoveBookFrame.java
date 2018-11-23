package server.frames.mainFrame.mainFrame.actionListeners;

import server.frames.removeBook.RemoveBookFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GotoRemoveBookFrame  implements ActionListener {

    @Override
    public void actionPerformed(ActionEvent e) {
        new RemoveBookFrame();
    }
}