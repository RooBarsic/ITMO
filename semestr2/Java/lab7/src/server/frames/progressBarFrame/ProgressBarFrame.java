package server.frames.progressBarFrame;

import javax.swing.*;
import java.awt.*;

public class ProgressBarFrame {
    private JFrame frame1;
    private JProgressBar jProgressBar;
    private int value;

    public ProgressBarFrame(int min, int max, int value){
        this.value = value;

        frame1 = new JFrame("Progress");
        frame1.setSize(200, 100);
        frame1.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame1.setLocationRelativeTo(null);
        frame1.setLayout(new GridLayout());

        jProgressBar = new JProgressBar();
        jProgressBar.setMaximum(min);
        jProgressBar.setMaximum(max);
        jProgressBar.setStringPainted(true);
        jProgressBar.setValue(value);

        frame1.add(jProgressBar);
        frame1.setVisible(true);
    }

    public void setValue(int x){
        jProgressBar.setValue(x);
        value = x;
    }

    public void nextStep(){
        value++;
        if(value <= jProgressBar.getMaximum()) jProgressBar.setValue(value);
    }

    public void setVisibleTrue(){
        frame1.setVisible(true);
    }

    public void setVisibleFalse(){
        frame1.setVisible(false);
    }
}
