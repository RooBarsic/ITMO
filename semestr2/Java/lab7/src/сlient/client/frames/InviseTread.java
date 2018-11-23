package сlient.client.frames;

import common.MessageFrame;
import common.bookComponents.Book;
import common.bookComponents.Colors;
import сlient.ClientMain;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class InviseTread  extends Thread {
    private boolean stopFlag;
    private ArrayList<JLabel> labels;
    private ArrayList<Book> books;

    InviseTread(ArrayList<JLabel> labels, ArrayList<Book> books){
        this.labels = labels;
        this.books = books;
    }

    public void setStopFlag(boolean stopFlag) {
        this.stopFlag = stopFlag;
    }

    @Override
    public void run() {
        stopFlag = false;
        //System.out.println(" kol books = " + labels.size());
        //new MessageFrame("Start");
        for(int id = 250; id >= 0; id -= 25) {
            int kol = 0;
            for (int i = 0; i < labels.size(); i++) {
                JLabel label = labels.get(i);
                Book book = books.get(i);
                if (label != null) {
                    kol++;
                    setLabelInviseId(label, book, id);
                }
            }
            try {
                Thread.sleep(150);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if(stopFlag) return;
        }
        //new MessageFrame("Middle");
        for(int id = 0; id <= 250; id += 25) {
            int kol = 0;
            for (int i = 0; i < labels.size(); i++) {
                JLabel label = labels.get(i);
                Book book = books.get(i);
                if (label != null) {
                    kol++;
                    setLabelInviseId(label, book, id);
                }
            }
            try {
                Thread.sleep(375);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if(stopFlag) return;
        }
        //new MessageFrame("End");
    }

    public void setLabelInviseId(JLabel label, Book book, int id){
        label.setForeground(Colors.getColor(book.getBookColor(), id));

    }
}
