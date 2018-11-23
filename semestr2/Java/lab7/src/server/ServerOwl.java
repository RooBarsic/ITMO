package server;

import common.bookComponents.Book;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class ServerOwl implements Serializable {
    private List<Book> books;

    public ServerOwl(List<Book> books) {
        this.books = books;
    }

    public List<Book> getBooks(){
        return books;
    }
}
