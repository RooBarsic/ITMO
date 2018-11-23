package server.frames.addBook;

import common.BookWorkFrame;
import server.actions.FillBookButtonActionListener;
import common.bookComponents.Book;
import common.MyFrame;
import javax.swing.*;
import java.awt.*;

public class AddBookFrame extends BookWorkFrame {

    public AddBookFrame(){
        super("Add Book Frame", 275, 275, "save");

        setRunButtonActionListener(new AddNewBookActionListener(this));

        frame1.setVisible(true);
        //frame1.pack();
    }
}
