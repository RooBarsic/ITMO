package server.frames.mainFrame.mainFrame.actionListeners;

import server.frames.removeGreater.RemoveGreaterBookFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GotoRemoveGreaterFrame implements ActionListener {

    @Override
    public void actionPerformed(ActionEvent e) {
        new RemoveGreaterBookFrame();
    }
}