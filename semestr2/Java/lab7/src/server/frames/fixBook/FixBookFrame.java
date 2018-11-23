package server.frames.fixBook;

import common.MessageFrame;
import server.actions.CancelActionListener;
import common.bookComponents.*;
import common.bookComponents.Point;
import common.MyFrame;

import javax.swing.*;
import java.awt.*;

public class FixBookFrame extends MyFrame {
    private Book bookForRemoving;
    private Book bookForSaving;
    private JTextField bookNameField = new JTextField();
    private JComboBox bookJanrBox;
    private JTextField bookXcoordinateField = new JTextField();
    private JTextField bookYcoordinateField = new JTextField();
    private JComboBox bookColorBox;
    private JTextField getBookNameField;
    private JComboBox getBookJanrBox;
    private JTextField getBookXcoordinateField = new JTextField();
    private JTextField getBookYcoordinateField = new JTextField();
    private JComboBox getBookColorBox;


    public FixBookFrame(){
        super("Fix Book", 600, 600);
        frame1.setLayout(new GridBagLayout());

        JLabel getBookNameLabel = new JLabel("Get book name: ");
        JLabel getBookJanreLabel = new JLabel("Get book janr: ");
        JLabel getBookXcoordinateLabel = new JLabel("Get book X coordinate : ");
        JLabel getBookYcoordinateLabel = new JLabel("Get book Y coordinate : ");
        JLabel getBookColorLabel = new JLabel("Get book color : ");
        JLabel bookNameLabel = new JLabel("Book name : ");
        JLabel bookJanrLabel = new JLabel("Book janr : ");
        JLabel bookXcoordinateLabel = new JLabel("Book X coordinate : ");
        JLabel bookYcoordinateLabel = new JLabel("Book Y coordinate : ");
        JLabel bookColorLabel = new JLabel("Book color : ");

        getBookNameField = new JTextField();
        getBookJanrBox = new JComboBox(Janrs.getJanrs());
        getBookXcoordinateField = new JTextField();
        getBookYcoordinateField = new JTextField();
        getBookColorBox = new JComboBox(Colors.getColors());

        bookNameField = new JTextField();
        bookJanrBox = new JComboBox(Janrs.getJanrs());
        bookXcoordinateField = new JTextField();
        bookYcoordinateField = new JTextField();
        bookColorBox = new JComboBox(Colors.getColors());

        JButton findBookButton = new JButton("find book");
        findBookButton.addActionListener(new FindBookButtonActionListener(this));
        JButton saveChangesButton = new JButton("save changes");
        saveChangesButton.addActionListener(new SaveChangesButtonActionListener(this));
        JButton cancel = new JButton("Cansel");
        cancel.addActionListener(new CancelActionListener(this));


        frame1.add(getBookNameLabel, new GridBagConstraints(0, 0, 100, 100, 100, 100,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(getBookNameField, new GridBagConstraints(1, 0, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(getBookJanreLabel, new GridBagConstraints(0, 1, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(getBookJanrBox, new GridBagConstraints(1, 1, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(getBookXcoordinateLabel, new GridBagConstraints(0, 3, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(getBookXcoordinateField, new GridBagConstraints(1, 3, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(getBookYcoordinateLabel, new GridBagConstraints(0, 4, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(getBookYcoordinateField, new GridBagConstraints(1, 4, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(getBookColorLabel, new GridBagConstraints(0, 5, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(getBookColorBox, new GridBagConstraints(1, 5, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));



        frame1.add(findBookButton, new GridBagConstraints(0, 6, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookNameLabel, new GridBagConstraints(0, 7, 100, 100, 100, 100,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookNameField, new GridBagConstraints(1, 7, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookJanrLabel, new GridBagConstraints(0, 8, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookJanrBox, new GridBagConstraints(1, 8, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookXcoordinateLabel, new GridBagConstraints(0, 9, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookXcoordinateField, new GridBagConstraints(1, 9, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookYcoordinateLabel, new GridBagConstraints(0, 10, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookYcoordinateField, new GridBagConstraints(1, 10, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookColorLabel, new GridBagConstraints(0, 11, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookColorBox, new GridBagConstraints(1, 11, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(cancel, new GridBagConstraints(0, 12, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(saveChangesButton, new GridBagConstraints(1, 12, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));

        frame1.setVisible(true);
        //frame1.pack();
    }

    public void setBookParams(Book book){
        bookForRemoving = book;
        bookNameField.setText(book.getName());
        bookJanrBox.setSelectedItem(book.getJanr().name());
        bookXcoordinateField.setText(Integer.toString(book.getBookCoordinates().getX()));
        bookYcoordinateField.setText(Integer.toString(book.getBookCoordinates().getY()));
        bookColorBox.setSelectedItem(book.getBookColor().name());
    }

    public boolean getBookForRemovingStatus(){
        return (bookForRemoving != null);
    }

    public void makeRemoveBook(){
        bookForRemoving = null;
        String bookName = getBookNameField.getText();
        String bookJanr = (String) getBookJanrBox.getItemAt(bookJanrBox.getSelectedIndex());
        String bookXcoordinate = getBookXcoordinateField.getText();
        String bookYcoordinate = getBookYcoordinateField.getText();
        String bookColor = (String) getBookColorBox.getItemAt(bookColorBox.getSelectedIndex());

        System.out.println(" bookName = " + bookName);
        System.out.println(" bookJanr = " + bookJanr);
        System.out.println(" X coordinate = " + bookXcoordinate);
        System.out.println(" y Coordinate = " + bookYcoordinate);
        System.out.println(" book color = " + bookColor);

        if((bookName == null) || (bookName.equals(""))) new MessageFrame("Wrong Book Name");
        else if((bookJanr == null) || (bookJanr.equals("")) || (!Janrs.checkJanr(bookJanr)))
            new MessageFrame("Wrong Janr Type");
        else if((bookXcoordinate == null) || (bookXcoordinate.equals("")) || (!MyLog.checkInt(bookXcoordinate)))
            new MessageFrame("Wrong X coordinate");
        else if((bookYcoordinate == null) || (bookYcoordinate.equals("")) || (!MyLog.checkInt(bookYcoordinate)))
            new MessageFrame("Wrong Y coordinate");
        else if((bookColor == null) || (bookColor.equals("")) || (!MyLog.checkColor(bookColor)))
            new MessageFrame("Wrong color name");
        else {
            bookForRemoving = new Book(bookName, Janrs.valueOf(bookJanr), new Point(Integer.parseInt(bookXcoordinate),
                    Integer.parseInt(bookYcoordinate)), Colors.valueOf(bookColor));
        }
    }

    public Book getBookForRemoving(){
        return bookForRemoving;
    }

    public Book getBookForSaving(){
        return bookForSaving;
    }

    public void makeBook(){
        bookForSaving = null;
        String bookName = bookNameField.getText();
        String bookJanr = (String) bookJanrBox.getItemAt(bookJanrBox.getSelectedIndex());
        String bookXcoordinate = bookXcoordinateField.getText();
        String bookYcoordinate = bookYcoordinateField.getText();
        String bookColor = (String) bookColorBox.getItemAt(bookColorBox.getSelectedIndex());

        System.out.println(" bookName = " + bookName);
        System.out.println(" bookJanr = " + bookJanr);
        System.out.println(" X coordinate = " + bookXcoordinate);
        System.out.println(" y Coordinate = " + bookYcoordinate);
        System.out.println(" book color = " + bookColor);

        if((bookName == null) || (bookName.equals(""))) new MessageFrame("Wrong Book Name");
        else if((bookJanr == null) || (bookJanr.equals("")) || (!Janrs.checkJanr(bookJanr)))
            new MessageFrame("Wrong Janr Type");
        else if((bookXcoordinate == null) || (bookXcoordinate.equals("")) || (!MyLog.checkInt(bookXcoordinate)))
            new MessageFrame("Wrong X coordinate");
        else if((bookYcoordinate == null) || (bookYcoordinate.equals("")) || (!MyLog.checkInt(bookYcoordinate)))
            new MessageFrame("Wrong Y coordinate");
        else if((bookColor == null) || (bookColor.equals("")) || (!MyLog.checkColor(bookColor)))
            new MessageFrame("Wrong color name");
        else {
            bookForSaving = new Book(bookName, Janrs.valueOf(bookJanr), new Point(Integer.parseInt(bookXcoordinate),
                    Integer.parseInt(bookYcoordinate)), Colors.valueOf(bookColor));
        }
    }

    public boolean getBookForSavingStatus(){
        return (bookForSaving != null);
    }

}
