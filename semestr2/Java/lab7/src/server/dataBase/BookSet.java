package server.dataBase;

import common.bookComponents.Book;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class                            BookSet {
    private ConcurrentHashMap<String, Book> books;
    private Set< String > st;

    public BookSet(){
        books = new ConcurrentHashMap();
        st = new TreeSet<>();
    }

    public void addBook(Book book) {
        books.put(book.getKey(), book);
        st.add(book.getKey());
    }

    public Book getBook(String key){
        return books.get(key);
    }

    public int getNumberOfBooks(){
        return books.size();
    }

    /**
     * Clean all Collection
     */
    public void clean(){
        books.clear();
        st.clear();
    }

    /**
     * Remove Book with key ke from Collection
     * @param ke - is String
     */
    public void remove(String ke){
        books.remove(ke);
        st.remove(ke);
    }

    /**
     * Remove all books from Collecction which smaller than given book
     * @param bo - is Book
     */
    public void remove_lower(Book bo){
        books.values().stream().forEach((a)->{
            if(a.compareTo(bo) < 0){
                st.remove(a.getKey());
                books.remove(a.getKey());
            }
        });
    }

    /**
     * Remove all books from Collection which bige than given book
     * @param bo - is Book
     */
    public void remove_greater(Book bo){
        books.values().forEach((a)->{
            if(a.compareTo(bo) > 0){
                st.remove(a.getKey());
                books.remove(a.getKey());
            }
        });
    }

    /**
     * if given Book is smaller than smalest Book from Collection
     * then add given Book to the Collection
     * @param bo - is Book
     */
    public void add_if_min(Book bo){
        if(bo == null) return;
        Book minBook = books.values().stream().min(Book::compareTo).orElse(null);
        if((minBook == null) || (bo.compareTo(minBook) < 0))  addBook(bo);
    }

    /**
     * Load Book to File named fileName
     * @param
     */
    public List<Book> save(){
        List<Book> list = new ArrayList<>(books.values());
        list.sort(Book::compareTo);
        return list;
    }

}



