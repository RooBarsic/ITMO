package server.frames.addIfMin;

import common.BookWorkFrame;
import server.actions.CancelActionListener;
import server.actions.FillBookButtonActionListener;
import common.bookComponents.Book;
import common.MyFrame;

import javax.swing.*;
import java.awt.*;

public class AddIfMinFrame extends BookWorkFrame {
    public AddIfMinFrame(){
        super("Add IF Min Book Frame", 600, 100, "add if min");

        setRunButtonActionListener(new AddIfMinButtonActionListener(this));

        frame1.setVisible(true);
        //frame1.pack();
    }
}
