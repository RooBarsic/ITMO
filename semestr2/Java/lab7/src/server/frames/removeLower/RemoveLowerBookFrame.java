package server.frames.removeLower;

import common.BookWorkFrame;
import server.actions.CancelActionListener;
import server.actions.FillBookButtonActionListener;
import common.bookComponents.Book;
import common.MyFrame;
import javax.swing.*;
import java.awt.*;

public class RemoveLowerBookFrame extends BookWorkFrame {

    public RemoveLowerBookFrame(){
        super("Remove Lower Book Frame", 300, 200, "remove lover");

        setRunButtonActionListener(new RemoveLowerButtonActionListener(this));

        frame1.setVisible(true);
        //frame1.pack();
    }
}
