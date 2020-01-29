package server;

import common.Book;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class BookSet {
    private ConcurrentHashMap<String, Book> books;
    private Set< String > st;

    BookSet(){
        books = new ConcurrentHashMap();
        st = new TreeSet<>();
    }

    public void addBook(Book book) {
        books.put(book.getKey(), book);
        st.add(book.getKey());
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
        Collection<Book> arr = books.values();
        ArrayList< Book > brr = new ArrayList<>();
        Set<String> newSt = new TreeSet();
        for(Book book : arr){
            if(book.compareTo(bo) >= 0){
                brr.add(book);
                newSt.add(book.getKey());
            }
        }
        books = new ConcurrentHashMap((Map) brr);
        st = newSt;
    }

    /**
     * Remove all books from Collection which bige than given book
     * @param bo - is Book
     */
    public void remove_greater(Book bo){
        Collection<Book> arr = books.values();
        ArrayList< Book > brr = new ArrayList<>();
        Set<String> newSt = new TreeSet();
        for(Book book : arr){
            if(book.compareTo(bo) <= 0){
                brr.add(book);
                newSt.add(book.getKey());
            }
        }
        books = new ConcurrentHashMap((Map) brr);
        st = newSt;
    }

    /**
     * if given Book is smaller than smalest Book from Collection
     * then add given Book to the Collection
     * @param bo - is Book
     */
    public void add_if_min(Book bo){
        Collection<Book> arr = books.values();
        for(Book book : arr){
            if(book.compareTo(bo) <= 0){
                return;
            }
        }
        books.put(bo.getKey(), bo);
        st.add(bo.getKey());

        /*if((st.size() == 0) || (bo.compareTo(books.get(st.iterator().next())) < 0)){
            st.add(bo.getKey());
            books.put(bo.getKey(), bo);
        }*/
    }

    /**
     * Load Book to File named fileName
     * @param
     */
    public HashMap<String, Book> save(){
        HashMap< String, Book> map = new HashMap<>();
        map.putAll(books);
        return map;
    }

}

















