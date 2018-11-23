package сlient.client.frames;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class StopAnimationButtonActionListener implements ActionListener {
    private ClientMainFrame frame;

    StopAnimationButtonActionListener(ClientMainFrame frame){
        this.frame = frame;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        frame.stopTread();
    }
}
