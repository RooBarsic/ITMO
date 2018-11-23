package server.frames.removeLower;

import common.MessageFrame;
import common.bookComponents.Book;
import server.dataBase.DataLog;
import server.frames.mainFrame.MainFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RemoveLowerButtonActionListener implements ActionListener {
    private RemoveLowerBookFrame frame1;

    RemoveLowerButtonActionListener(RemoveLowerBookFrame frame){
        frame1 = frame;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        frame1.makeBook();
        if(frame1.getSavedBookStatus()){
            Book book = frame1.getSavedBook();
            // set book into BookSet!!! ----------------------------
            DataLog.remove_lower(book);
            new MessageFrame("Done! ");
            frame1.setVisibleFalse();

            DataLog.mainFrame.setVisibleFalse();
            DataLog.mainFrame = new MainFrame(true);
        }
    }
}
