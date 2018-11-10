package server.actions;

import common.MyFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CancelActionListener implements ActionListener {
    private MyFrame frame;
    public CancelActionListener(MyFrame frame){
        this.frame = frame;
    }


    @Override
    public void actionPerformed(ActionEvent e) {
        frame.setVisibleFalse();
    }
}
