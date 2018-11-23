package common;

import common.MyFrame;
import common.bookComponents.Book;
import common.bookComponents.Colors;
import common.bookComponents.Janrs;
import common.bookComponents.Point;
import server.actions.CancelActionListener;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class BookWorkFrame extends MyFrame {
    private JTextField bookNameField;
    private JComboBox bookJanrsBox;
    private JSpinner bookXcoordinateField;
    private JSpinner bookYcoordinateField;
    private JComboBox bookColorsBox;
    private JButton runButton;
    private Book savedBook;

    public BookWorkFrame(String frameName, int width, int height, String nameOfRunButton) {
        super(frameName, width, height);
        frame1.setLayout(new GridBagLayout());

        JLabel bookNameLabel = new JLabel("Book name : ");
        JLabel bookJanrLabel = new JLabel("Book janr : ");
        JLabel bookXcoordinateLabel = new JLabel("Book X coordinate : ");
        JLabel bookYcoordinateLabel = new JLabel("Book Y coordinate : ");
        JLabel bookColorLabel = new JLabel("Book color : ");

        bookNameField = new JTextField();
        bookJanrsBox = new JComboBox(Janrs.getJanrs());
        bookXcoordinateField = new JSpinner(new SpinnerNumberModel(10, 1, 40, 1));
        bookYcoordinateField = new JSpinner(new SpinnerNumberModel(10, 1, 40, 1));
        bookColorsBox = new JComboBox(Colors.getColors());

        runButton = new JButton(nameOfRunButton);
        JButton cancel = new JButton("Cancel");
        cancel.addActionListener(new CancelActionListener(this));

        frame1.add(bookNameLabel, new GridBagConstraints(0, 0, 100, 100, 100, 100,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookNameField, new GridBagConstraints(1, 0, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookJanrLabel, new GridBagConstraints(0, 1, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookJanrsBox, new GridBagConstraints(1, 1, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookXcoordinateLabel, new GridBagConstraints(0, 2, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookXcoordinateField, new GridBagConstraints(1, 2, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookYcoordinateLabel, new GridBagConstraints(0, 3, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookYcoordinateField, new GridBagConstraints(1, 3, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookColorLabel, new GridBagConstraints(0, 4, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(bookColorsBox, new GridBagConstraints(1, 4, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(cancel, new GridBagConstraints(0, 5, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
        frame1.add(runButton, new GridBagConstraints(1, 5, 1, 1, 1, 1,
                GridBagConstraints.NORTH,
                GridBagConstraints.HORIZONTAL, new Insets(2, 2, 2, 2), 0, 0));
    }

    public void setRunButtonActionListener(ActionListener listener){
        runButton.addActionListener(listener);
    }

    public boolean getSavedBookStatus(){
        return (savedBook != null);
    }

    public Book getSavedBook(){
        return savedBook;
    }

    public void makeBook(){
        savedBook = null;
        String bookName = bookNameField.getText();
        String bookJanr = (String) bookJanrsBox.getItemAt(bookJanrsBox.getSelectedIndex());
        int bookXcoordinate = (int) bookXcoordinateField.getValue();
        int bookYcoordinate = (int) bookYcoordinateField.getValue();
        String bookColor = (String) bookColorsBox.getItemAt(bookColorsBox.getSelectedIndex());

        System.out.print("  bookName = " + bookName);
        System.out.print("  bookJanr = " + bookJanr);
        System.out.print("  X coordinate = " + bookXcoordinate);
        System.out.print("  y Coordinate = " + bookYcoordinate);
        System.out.println("  book color = " + bookColor);

        if((bookName == null) || (bookName.equals(""))) new MessageFrame("Wrong Book Name");
        else if((bookJanr == null) || (bookJanr.equals("")) || (!Janrs.checkJanr(bookJanr)))
            new MessageFrame("Wrong Janr Type");
        else if(!(1 <= bookXcoordinate) && (bookXcoordinate <= 40))
            new MessageFrame("Wrong X coordinate");
        else if(!(1 <= bookYcoordinate) && (bookYcoordinate <= 40))
            new MessageFrame("Wrong Y coordinate");
        else if((bookColor == null) || (bookColor.equals("")) || (!Colors.checkColor(bookColor)))
            new MessageFrame("Wrong color name");
        else {
            savedBook = new Book(bookName, Janrs.valueOf(bookJanr), new Point(bookXcoordinate,
                    bookYcoordinate), Colors.valueOf(bookColor));
        }
    }
}
