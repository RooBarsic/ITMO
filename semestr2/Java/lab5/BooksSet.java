import com.oracle.xmlns.internal.webservices.jaxws_databinding.ExistingAnnotationsType;

import java.io.*;
import java.util.*;

public class BooksSet {
    private final Map<String, Book> mp_a = new HashMap<>();
    //private final Set<String> st_a = new TreeSet<>(Comparator.comparingInt(String::length));
    private final Set<String> st_a = new TreeSet<String>(){
        public int comparator(String a, String b) {
            return a.length() - b.length();
        }
    };

    BooksSet(){}

    BooksSet(ArrayList<Book> arr){
        for(int i = 0; i < arr.size(); i++){
            mp_a.put(arr.get(i).getName() + arr.get(i).getBookJanr().name(), arr.get(i));
            st_a.add(arr.get(i).getName() + arr.get(i).getBookJanr().name());
            //System.out.println(arr.get(i).getName() + arr.get(i).getBookJanr().name());
        }
    }


    /**
     * Clean all Collection
     */
    public void clear() {
        mp_a.clear();
        st_a.clear();
    }

    /**
     * Remove Book with key ke from Collection
     * @param ke - is String
     */
    public void remove(String ke){
        mp_a.remove(ke);
        st_a.remove(ke);
    }

    /**
     * Remove all books from Collecction which smaller than given book
     * @param bo - is Book
     */
    public void remove_lower(Book bo){
        ArrayList<String> arr = new ArrayList<>();
        for(String iter : st_a){
            //System.out.println(iter + " " + mp_a.get(iter).compareTo(bo));
            if(mp_a.get(iter).compareTo(bo) < 0)
                arr.add(iter);
        }
        for(int i = 0; i < arr.size(); i++){
            //System.out.println(arr.get(i));
            mp_a.remove(arr.get(i));
            st_a.remove(arr.get(i));
        }
    }

    /**
     * Remove all books from Collection which bige than given book
     * @param bo - is Book
     */
    public void remove_greater(Book bo){
        ArrayList<String> arr = new ArrayList<>();
        for(String iter : st_a){
            if(bo.compareTo(mp_a.get(iter)) < 0)
                arr.add(iter);
        }
        for(int i = 0; i < arr.size(); i++){
            mp_a.remove(arr.get(i));
            st_a.remove(arr.get(i));
        }
    }

    /**
     * if given Book is smaller than smalest Book from Collection
     * then add given Book to the Collection
     * @param bo - is Book
     */
    public void add_if_min(Book bo){
        if((st_a.size() == 0) || (bo.compareTo(mp_a.get(st_a.iterator().next())) < 0)){
            st_a.add(bo.getName() + bo.getBookJanr().name());
            mp_a.put(bo.getName() + bo.getBookJanr().name(), bo);
        }
    }

    /**
     * Load Book to File named fileName
     * @param fileName
     */
    public void save(String fileName){
        OutLoader out = new OutLoader();
        if(out.importToFile(fileName, mp_a))
            System.out.println(mp_a.size() + " books was successfully loadede to file! ");
        else System.out.println(" Can't load books to file! ");
    }

    /**
     * Load Books from file named fileName and return new BookSet
     * return null if file named fileName not exist or if wrong csv format
     * @param fileName
     * @return - new BookSet
     * @throws FileNotFoundException
     */
    static BooksSet GetFromFile(String fileName) throws FileNotFoundException {
        if(!StaticFileChecker.canOpenFile(fileName)) return null;
        Loader loadFrom = new Loader(fileName);
        ArrayList<Book> books = new ArrayList<>();
        try {
            while (loadFrom.hasNext()) {
                String name = loadFrom.getString();
                String jana = loadFrom.getString();
                int kol = loadFrom.getInt();
                String[] arr = new String[kol];
                for (int i = 0; i < kol; i++) {
                    arr[i] = loadFrom.getString();
                }
                books.add(new Book(name, Janrs.valueOf(jana), kol, arr));
                //System.out.println(name + " " + Janrs.valueOf(jana).name() + " " + kol);
            }
            System.out.println(books.size() + " books from file \"" + fileName + "\" was successfully downloaded! ");
            return new BooksSet(books);
        } catch (Exception e){
            System.out.println(" Can't' load books from " + fileName);
            return null;
        }
    }

    /**
     * For developer - print information about avalible boosk in BooksSet
     */
    public void outt() {
        System.out.println(" set_size = " + st_a.size() + " map_size = " + mp_a.size());
        System.out.println(" Book out format \n" + "Name janr numberOfWords");
        for (Book iter : mp_a.values()) {
            System.out.println(iter.getName() + " " + iter.getBookJanr().name() + " " + iter.getKolWords() + " words ");
        }
    }
}
