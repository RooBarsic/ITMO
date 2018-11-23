package server.frames.removeGreater;

import common.BookWorkFrame;
import server.actions.CancelActionListener;
import server.actions.FillBookButtonActionListener;
import common.bookComponents.Book;
import common.MyFrame;
import javax.swing.*;
import java.awt.*;

public class RemoveGreaterBookFrame extends BookWorkFrame {

    public RemoveGreaterBookFrame(){
        super("Remove Greater Book Frame", 300, 200, "remove greater");

        setRunButtonActionListener(new RemoveGreaterButtonActionListener(this));

        frame1.setVisible(true);
        //frame1.pack();
    }
}
