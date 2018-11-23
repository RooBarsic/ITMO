package server.frames.mainFrame;

import common.MessageFrame;
import common.bookComponents.Book;
import server.dataBase.DataLog;

import javax.print.attribute.standard.MediaSize;
import javax.swing.*;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;

public class TestListener implements TreeSelectionListener {
    private JTree tree;

    TestListener(JTree tree){
        this.tree = tree;
    }

    @Override
    public void valueChanged(TreeSelectionEvent e) {
        Object parent = tree.getSelectionPath().getParentPath().getLastPathComponent();
        Object child = tree.getSelectionPath().getLastPathComponent();
        int b = tree.getModel().getIndexOfChild(parent, child);
        Book book = DataLog.getBookById(b);

        new NewTestFrame(book);
    }
}
