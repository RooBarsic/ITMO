package server.frames.mainFrame.mainFrame.actionListeners;

import server.frames.addBook.AddBookFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GotoAddBookFrame implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent e) {
        new AddBookFrame();
    }
}