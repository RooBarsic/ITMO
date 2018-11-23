package сlient.client.frames;

import common.MyFrame;
import common.bookComponents.Book;
import common.bookComponents.Colors;
import common.bookComponents.Janrs;
import common.bookComponents.Point;
import server.frames.progressBarFrame.MyProgressFrame;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class ClientMainFrame extends MyFrame {
    private InviseTread inviseTread;
    private JLabel bookNameLabel;
    private JComboBox bookJanrsBox;
    private JComboBox bookColorsBox;
    private int numberOfRows = 40;
    private JLabel labelsArr[][] = new JLabel[numberOfRows + 2][numberOfRows + 2];
    private Book books[][] = new Book[numberOfRows + 2][numberOfRows + 2];

    public ClientMainFrame(){
        super("Client Main Frame", 1200, 1200);
        frame1.setLayout(new BorderLayout());

        JButton loadBooksButton = new JButton("Load Books");
        loadBooksButton.addActionListener(new LoadBookActionListener(this));
        JButton startAnimationButton = new JButton("Start Animation");
        startAnimationButton.addActionListener(new StartAnimationButtonActionListener(this));
        JButton stopAnimationButton = new JButton("Stop Animation");
        stopAnimationButton.addActionListener(new StopAnimationButtonActionListener(this));
        bookJanrsBox = new JComboBox(Janrs.getJanrs());
        bookColorsBox = new JComboBox(Colors.getColors());
        bookNameLabel = new JLabel();
        bookNameLabel.setVisible(false);
        JPanel jTopPanel = new JPanel();
        jTopPanel.add(loadBooksButton);
        jTopPanel.add(startAnimationButton);
        jTopPanel.add(stopAnimationButton);
        jTopPanel.add(bookJanrsBox);
        jTopPanel.add(bookColorsBox);
        jTopPanel.add(bookNameLabel);
        frame1.add(jTopPanel, BorderLayout.NORTH);

        JPanel jLabelsPanel = new JPanel();
        jLabelsPanel.setLayout(new GridLayout(numberOfRows, numberOfRows));

        for(int i = 1; i <= numberOfRows; i++) {
            for (int j = 1; j <= numberOfRows; j++) {
                labelsArr[i][j] = new JLabel("B");
                labelsArr[i][j].setOpaque(true);
                jLabelsPanel.add(labelsArr[i][j]);
                labelsArr[i][j].setVisible(false);
            }
        }
        frame1.add(jLabelsPanel, BorderLayout.CENTER);

        frame1.setVisible(true);
    }

    public void setBook(Book book){
        int x = book.getBookCoordinates().getX();
        int y = book.getBookCoordinates().getY();
        if((1 <= x) && (x <= numberOfRows) && (1 <= y) && (y <= numberOfRows)){
            books[y][x] = book;
            labelsArr[y][x].setForeground(Colors.getColor(book.getBookColor(), 255));
            labelsArr[y][x].setVisible(true);
            labelsArr[y][x].addMouseListener(new ClientMouseListener(book, bookNameLabel));
        }
    }

    public ArrayList<JLabel> getChoosedLabels(){
        String bookJanr = (String) bookJanrsBox.getItemAt(bookJanrsBox.getSelectedIndex());
        String bookColor = (String) bookColorsBox.getItemAt(bookColorsBox.getSelectedIndex());
        ArrayList<JLabel> labelsChosed = new ArrayList<>();
        for(int i = 1; i <= numberOfRows; i++){
            for(int j = 1; j <= numberOfRows; j++){
                if(books[i][j] != null){
                    if((books[i][j].getJanr().name().equals(bookJanr)) &&
                            (books[i][j].getBookColor().name().equals(bookColor))){
                        labelsChosed.add(labelsArr[i][j]);
                    }
                }
            }
        }
        return labelsChosed;
    }

    public ArrayList<Book> getChoosedBooks(){
        String bookJanr = (String) bookJanrsBox.getItemAt(bookJanrsBox.getSelectedIndex());
        String bookColor = (String) bookColorsBox.getItemAt(bookColorsBox.getSelectedIndex());
        ArrayList<Book> booksChosed = new ArrayList<>();
        for(int i = 1; i <= numberOfRows; i++){
            for(int j = 1; j <= numberOfRows; j++){
                if(books[i][j] != null){
                    if((books[i][j].getJanr().name().equals(bookJanr)) &&
                            (books[i][j].getBookColor().name().equals(bookColor))){
                        booksChosed.add(books[i][j]);
                    }
                }
            }
        }
        return booksChosed;
    }

    public void setTread(InviseTread tread){
        inviseTread = tread;
    }

    public void stopTread(){
        if((inviseTread != null) && (inviseTread.isAlive() == true))
            inviseTread.setStopFlag(true);
    }
}
