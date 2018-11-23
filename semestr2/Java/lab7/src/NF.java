import com.sun.xml.internal.messaging.saaj.soap.JpegDataContentHandler;
import server.frames.logIn.SignUpActionListener;

import javax.swing.*;
import java.awt.*;

public class NF {
    NF(){
        JFrame frame = new JFrame("Sing in or Sign up");
        frame.setSize(1200, 1200);
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        frame.setLayout(new BorderLayout());

        JPanel panel1 = new JPanel();
        panel1.add(new JButton("aa1"));
        panel1.add(new JButton("aa2"));
        panel1.add(new JButton("aa3"));
        panel1.add(new JButton("aa4"));
        panel1.add(new JButton("aa5"));
        frame.add(panel1, BorderLayout.NORTH);


        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(20,20));
        //---------------------------------------------------------------------------------------

        //-----------------------------------------------------------------------------------------
        frame.add(panel, BorderLayout.CENTER);
        frame.setVisible(true);
    }
}
