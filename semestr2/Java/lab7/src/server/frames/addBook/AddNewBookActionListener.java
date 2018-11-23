package server.frames.addBook;

import common.MessageFrame;
import common.bookComponents.Book;
import server.dataBase.DataLog;
import server.frames.mainFrame.MainFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AddNewBookActionListener implements ActionListener {
    private AddBookFrame frame1;

    AddNewBookActionListener(AddBookFrame frame1){
        this.frame1 = frame1;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        frame1.makeBook();
        if(frame1.getSavedBookStatus()){
            Book book = frame1.getSavedBook();
            // set book into BookSet!!! ----------------------------
            DataLog.addBook(book);
            new MessageFrame("Done! ");
            frame1.setVisibleFalse();

            DataLog.mainFrame.setVisibleFalse();
            DataLog.mainFrame = new MainFrame(true);
        }
    }
}
