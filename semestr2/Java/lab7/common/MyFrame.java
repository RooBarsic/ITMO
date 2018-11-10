package common;

import javax.swing.*;

public class MyFrame {
    protected JFrame frame1;

    public MyFrame(String frameName, int width, int height){
        frame1 = new JFrame(frameName);
        frame1.setSize(width, height);
        frame1.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame1.setLocationRelativeTo(null);
    }

    public void setVisibleFalse(){
        frame1.setVisible(false);
    }

    public void setVisibleTrue(){
        frame1.setVisible(true);
    }


}

