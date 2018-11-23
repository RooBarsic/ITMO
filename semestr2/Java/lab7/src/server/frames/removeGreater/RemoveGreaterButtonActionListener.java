package server.frames.removeGreater;

import common.MessageFrame;
import common.bookComponents.Book;
import server.dataBase.DataLog;
import server.frames.mainFrame.MainFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RemoveGreaterButtonActionListener implements ActionListener {
    private RemoveGreaterBookFrame frame1;

    RemoveGreaterButtonActionListener(RemoveGreaterBookFrame frame){
        frame1 = frame;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        frame1.makeBook();
        if(frame1.getSavedBookStatus()){
            Book book = frame1.getSavedBook();
            // set book into BookSet!!! ----------------------------
            DataLog.remove_greater(book);
            new MessageFrame("Done! ");
            frame1.setVisibleFalse();

            DataLog.mainFrame.setVisibleFalse();
            DataLog.mainFrame = new MainFrame(true);
        }
    }
}
