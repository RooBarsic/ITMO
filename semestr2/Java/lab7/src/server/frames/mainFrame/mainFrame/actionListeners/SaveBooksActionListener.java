package server.frames.mainFrame.mainFrame.actionListeners;

import common.MessageFrame;
import server.dataBase.DataLog;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SaveBooksActionListener  implements ActionListener {

    @Override
    public void actionPerformed(ActionEvent e) {
        DataLog.saveBooksToFile();
        new MessageFrame("Saving done");
    }
}