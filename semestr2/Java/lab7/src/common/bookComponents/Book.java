package common.bookComponents;

import java.io.Serializable;
import java.util.ArrayList;

public class Book implements GetName, GetJanr, Serializable {
    private String bookName;
    private Janrs bookJanr;
    private Point bookCoordinates;
    private Colors bookColor;
    private long creatingTime;
    private ArrayList<String > words;

    public Book(String bookName, Janrs bookJanr, Point bookCoordinates, Colors bookColor){
        this.bookName = bookName;
        this.bookJanr = bookJanr;
        this.bookCoordinates = bookCoordinates;
        this.bookColor = bookColor;
        words = new ArrayList<>();
    }

    public Book(String bookName, Janrs janr, Point coordinate, long creatingTime, int numberOfWords, String[] words){
        this.bookName = bookName;
        bookJanr = janr;
        bookCoordinates = coordinate;
        this.creatingTime = creatingTime;
        this.words = new ArrayList<>();
        for(int i = 0; i < numberOfWords; i++){
            this.words.add(words[i]);
        }
    }

    public Colors getBookColor(){
        return bookColor;
    }

    public long getCreatingTime(){
        return creatingTime;
    }

    public String getName(){
        return bookName;
    }

    public Janrs getJanr(){
        return bookJanr;
    }

    public int getNumberOfWords(){
        return words.size();
    }

    public Point getBookCoordinates(){
        return bookCoordinates;
    }

    public String getWordX(int x){
        if((x < 0) || (words.size() <= x)) return null;
        return words.get(x);
    }

    public String getKey(){
        String key = bookName;
        key += bookJanr.name();
        key += bookColor.name();
        key += Integer.toString(bookCoordinates.getX());
        key += Integer.toString(bookCoordinates.getY());
        return key;
    }

    public int compareTo(Book b){
        return this.getKey().length() - b.getKey().length();
    }

    @Override
    public String toString() {
        return "Book{" +
                "bookName='" + bookName + '\'' +
                ", bookJanr=" + bookJanr +
                ", bookCoordinates=" + bookCoordinates +
                ", bookColor=" + bookColor +
                ", creatingTime=" + creatingTime +
                ", words=" + words +
                '}';
    }
}


/*
book = new Book(bookName, Janrs.valueOf(bookJanr),
                        new Point(Integer.parseInt(X_cordinate), Integer.parseInt(Y_cordinate)),
                        Integer.parseInt(creatingTime), numberOfWords, words);
 */