package common;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class SingleOwl implements Serializable {
    private int commandType;
    private String bookKey;
    private Book book;
    private String message;

    public SingleOwl(int x){
        commandType = x;
        book = null;
    }

    public SingleOwl(int x, String key){
        commandType = x;
        bookKey = key;
    }

    public SingleOwl(int x, Book book){
        commandType = x;
        this.book = book;
    }

    public SingleOwl(String message){
        this.message = message;
    }

    public SingleOwl(String message, Book book){
        this.message = message;
        this.book = book;
    }

    public int getCommandType(){
        return commandType;
    }

    public String getBookKey() { return bookKey; }

    public String getMessage() { return message; }

    public Book getBook(){
        return book;
    }
}
