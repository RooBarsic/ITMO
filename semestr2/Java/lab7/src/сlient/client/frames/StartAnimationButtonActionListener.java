package сlient.client.frames;

import com.sun.security.sasl.ClientFactoryImpl;
import common.MessageFrame;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class StartAnimationButtonActionListener implements ActionListener {
    private ClientMainFrame frame;

    StartAnimationButtonActionListener(ClientMainFrame frame){
        this.frame = frame;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        frame.stopTread();
        InviseTread tread = new InviseTread(frame.getChoosedLabels(), frame.getChoosedBooks());
        tread.start();
        frame.setTread(tread);
    }
}
