package сlient.client.frames;

import сlient.BookLoaderTread;
import сlient.ClientMain;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoadBookActionListener implements ActionListener {
    private ClientMainFrame frame;

    LoadBookActionListener(ClientMainFrame frame){
        this.frame = frame;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        new BookLoaderTread().start();
    }
}
