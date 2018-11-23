package server.frames.mainFrame.mainFrame.actionListeners;

import server.frames.removeLower.RemoveLowerBookFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GotoRemoveLowerFrame  implements ActionListener {

    @Override
    public void actionPerformed(ActionEvent e) {
        new RemoveLowerBookFrame();
    }
}