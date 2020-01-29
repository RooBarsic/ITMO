package client;

import com.google.gson.Gson;
import common.Book;

import java.io.Serializable;

public class Box{
    private String command;
    private Book book;

    public Box(int commandType){
        command = Integer.toString(commandType);
    }

    public Box(int commandType, String key){
        command = Integer.toString(commandType) + key;
    }

    public Box(int commandType, Book book){
        Gson json = new Gson();
        command = Integer.toString(commandType) + json.toJson(book, Book.class);
    }

    public String getCommand(){
        return command;
    }
}

/**
 commands
 add Book - 0
 Claen - 1
 save - 2
 Remove all books - 3

 Remove book ( key ) - 4
 remove_lower( book ) - 5
 remove_greater( book ) - 6
 add_if_min( book ) - 7

 */
