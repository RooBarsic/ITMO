package server.frames.removeBook;

import common.MessageFrame;
import common.bookComponents.Book;
import server.dataBase.DataLog;
import server.frames.mainFrame.MainFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RemoveBookButtonActionListener implements ActionListener {
    RemoveBookFrame frame;

    RemoveBookButtonActionListener(RemoveBookFrame frame){
        this.frame = frame;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        frame.makeBook();
        if(frame.getSavedBookStatus()){
            Book book = frame.getSavedBook();
            // set book into BookSet!!! ----------------------------
            Book book1 = DataLog.getBook(book.getKey());
            if(book1 == null) new MessageFrame("Book not found");
            else {
                DataLog.remove(book.getKey());
                new MessageFrame("Done! ");
                frame.setVisibleFalse();

                DataLog.mainFrame.setVisibleFalse();
                DataLog.mainFrame = new MainFrame(true);
            }
        }
    }
}
