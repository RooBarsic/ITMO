package сlient.client.frames;

import common.bookComponents.Book;

import javax.swing.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class ClientMouseListener implements MouseListener {
    private Book book;
    private JLabel bookNameLabel;

    ClientMouseListener(Book book, JLabel label){
        this.book = book;
        bookNameLabel = label;
    }

    @Override
    public void mouseClicked(MouseEvent e) {

    }

    @Override
    public void mousePressed(MouseEvent e) {

    }

    @Override
    public void mouseReleased(MouseEvent e) {

    }

    @Override
    public void mouseEntered(MouseEvent e) {
        bookNameLabel.setText("BookName : " + book.getName() + " Janr : " + book.getJanr().name() + " Color : " +
                book.getBookColor().name());
        bookNameLabel.setVisible(true);
    }

    @Override
    public void mouseExited(MouseEvent e) {
        bookNameLabel.setVisible(false);
    }
}
