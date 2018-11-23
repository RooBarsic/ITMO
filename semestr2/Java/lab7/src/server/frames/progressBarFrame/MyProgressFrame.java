package server.frames.progressBarFrame;

import javax.swing.*;
import java.awt.*;

public class MyProgressFrame {
    private JFrame frame;
    private JLabel label;
    private int value;
    private int maxValue;

    public MyProgressFrame(int x, int max){
        frame = new JFrame("Progress");
        frame.setSize(200, 100);
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        frame.setLayout(new GridLayout());

        value = x;
        maxValue = max;
        label = new JLabel(Integer.toString(x) + " from " + Integer.toString(max));

        frame.add(label);
        frame.setVisible(true);
    }

    public void nextStep(){
        value++;
        label.setText(Integer.toString(value) + " from " + Integer.toString(maxValue));
    }

    public void frameOff(){
        frame.setVisible(false);
    }
}
