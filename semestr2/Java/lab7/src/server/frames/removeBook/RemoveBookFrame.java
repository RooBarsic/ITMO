package server.frames.removeBook;

import common.BookWorkFrame;
import server.actions.CancelActionListener;
import common.bookComponents.Janrs;
import common.MyFrame;

import javax.swing.*;
import java.awt.*;

public class RemoveBookFrame extends BookWorkFrame {

    public RemoveBookFrame(){
        super("Remove Book Frame", 300, 200, "remove");

        setRunButtonActionListener(new RemoveBookButtonActionListener(this));

        frame1.setVisible(true);
        //frame1.pack();
    }
}
