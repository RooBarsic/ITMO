package server.frames.fixBook;

import common.MessageFrame;
import common.bookComponents.Book;
import server.dataBase.DataLog;
import server.frames.mainFrame.MainFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SaveChangesButtonActionListener implements ActionListener {
    private FixBookFrame frame1;

    SaveChangesButtonActionListener(FixBookFrame frame){
        frame1 = frame;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        frame1.makeBook();
        if(frame1.getBookForSavingStatus() == true){
            Book book1 = frame1.getBookForRemoving();
            DataLog.remove(book1.getKey());
            Book book2 = frame1.getBookForSaving();
            DataLog.addBook(book2);
            frame1.setVisibleFalse();
            new MessageFrame("Done! ");
            frame1.setVisibleFalse();

            DataLog.mainFrame.setVisibleFalse();
            DataLog.mainFrame = new MainFrame(true);
        }
    }
}
