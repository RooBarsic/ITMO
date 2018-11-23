package server.actions;

import common.MyFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class FillBookButtonActionListener implements ActionListener {
    private MyFrame frame1;

    public FillBookButtonActionListener(MyFrame frame){
        frame1 = frame;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        frame1.setVisibleTrue();
    }
}
