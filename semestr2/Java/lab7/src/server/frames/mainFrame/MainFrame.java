package server.frames.mainFrame;

import server.dataBase.DataLog;
import common.MyFrame;
import server.frames.mainFrame.mainFrame.actionListeners.*;

import javax.swing.*;
import java.awt.*;

public class MainFrame extends MyFrame {
    public MainFrame(boolean visible){
        super("Main Frame", 1200, 700);
        frame1.setLayout(new BorderLayout());

        JButton readBooksButton = new JButton("Read Books");
        JButton saveBooksButton = new JButton("Save Books");
        JButton gotoAddBookButton = new JButton("Add Book");
        JButton gotoRemoveBookButton = new JButton("Remove Book");
        JButton gotoRemoveLowerButton = new JButton("Remove Lower");
        JButton gotoRemoveGreaterButton = new JButton("Remove Greater");
        JButton gotoAddIfMinButton = new JButton("Add If Min");
        JButton logOutButton = new JButton("Log out");

        gotoAddIfMinButton.addActionListener(new GotoAddIfMinFrame());
        readBooksButton.addActionListener(new ReadBooksActionListener());
        saveBooksButton.addActionListener(new SaveBooksActionListener());
        gotoAddBookButton.addActionListener(new GotoAddBookFrame());
        gotoRemoveBookButton.addActionListener(new GotoRemoveBookFrame());
        gotoRemoveLowerButton.addActionListener(new GotoRemoveLowerFrame());
        gotoRemoveGreaterButton.addActionListener(new GotoRemoveGreaterFrame());
        logOutButton.addActionListener(new LogOutActionListener(this));

        JPanel panel1 = new JPanel();
        panel1.setLayout(new GridLayout());
        panel1.add(readBooksButton);
        panel1.add(saveBooksButton);
        panel1.add(gotoAddBookButton);
        panel1.add(gotoRemoveBookButton);
        panel1.add(gotoRemoveLowerButton);
        panel1.add(gotoRemoveGreaterButton);
        panel1.add(gotoAddIfMinButton);
        panel1.add(logOutButton);

        frame1.add(panel1, BorderLayout.NORTH);

        JTree jTree = new JTree(DataLog.getBookNames());
        jTree.addTreeSelectionListener(new TestListener(jTree));
        JPanel jPanel = new JPanel();
        jPanel.setSize(1000, 500);
        jPanel.add(jTree);
        frame1.add(jPanel, BorderLayout.CENTER);

        frame1.setVisible(visible);
    }
}
