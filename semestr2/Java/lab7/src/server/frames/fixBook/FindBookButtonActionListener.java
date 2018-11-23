package server.frames.fixBook;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import common.MessageFrame;
import common.bookComponents.Book;
import server.dataBase.DataLog;

public class FindBookButtonActionListener implements ActionListener {
    private FixBookFrame frame1;
    FindBookButtonActionListener(FixBookFrame frame){
        frame1 = frame;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        frame1.makeRemoveBook();
        if(frame1.getBookForRemovingStatus()) {
            Book book = DataLog.getBook(frame1.getBookForRemoving().getKey());
            if (book == null) new MessageFrame("No book withs this name and janr!");
            else {
                frame1.setBookParams(book);
                new MessageFrame("the book was successfully found");
            }
        }
    }
}
