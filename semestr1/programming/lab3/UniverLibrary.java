import com.sun.istack.internal.Nullable;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Objects;

class UniverLibrary extends Library implements GetName, CheckKey{
    private int mxKolBooks;
    private String libraryName;
    private ArrayList< LibraryBook > allBooks = new ArrayList< LibraryBook >();

    UniverLibrary(int size, @Nullable String name) {
        if((size < 0) || (name == null)) throw new IllegalArgumentException("in UniverLibrary.UniverLibrary");
        mxKolBooks = size;
        libraryName = name;
    }

    public String getName() {
        return libraryName;
    }

    public int getKolBooks() {
        return allBooks.size();
    }

    public boolean canAddNewBook() {
        return allBooks.size() != mxKolBooks;
    }

    public void addBook(@Nullable Book boo, @Nullable Keys ke){
        if((boo == null) || (ke == null)) throw new IllegalArgumentException("in UniverLibrary.addBook!");
        if(allBooks.size() < mxKolBooks){
            allBooks.add(new LibraryBook(boo, ke));
        } else System.out.println(" Can't add new book ");
    }

    public boolean haveBookBJ(String bookName, Janrs jan) {
        if((bookName == null) || (jan == null)) throw new IllegalArgumentException("in UniverLibrary.haveBookBJ!");
        for(int i = 0, kol = (int)allBooks.size(); i < kol; i++){
            if((allBooks.get(i).getName().equals(bookName)) && (allBooks.get(i).getBookJanr() == jan))
                return true;
        }
        return false;
    }

    public boolean checkKeyForBookBJ(String bookName, Janrs jan, Keys ke) {
        if((bookName == null) || (jan == null) || (ke == null))  throw new IllegalArgumentException("in UniverLibrary.checkKeyForBookBJ");
        for(int i = 0, kol = (int)allBooks.size(); i < kol; i++){
            if((allBooks.get(i).getName().equals(bookName)) && (allBooks.get(i).getBookJanr().equals(jan))) {
                return (allBooks.get(i).checkKey(ke));
            }
        }
        return false;
    }

    public Book getBookFromLibrary(String bookName, Janrs jan, Keys ke){
        if((bookName == null) || (jan == null) || (ke == null))  throw new IllegalArgumentException("in UniverLibrary.getBookFromLibarary!");
        for (int i = 0, kol = (int)allBooks.size(); i < kol; i++) {
            if ((allBooks.get(i).getName().equals(bookName)) && (allBooks.get(i).getBookJanr().equals(jan))) {
                if (allBooks.get(i).checkKey(ke)) {
                    Book bi = allBooks.get(i).getBook(ke);
                    allBooks.remove(i);
                    return bi;
                }
            }
        }
        if (!this.haveBookBJ(bookName, jan)) System.out.println("Net takoi knigi");
        else System.out.println("Neverki klych");
        return null;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        UniverLibrary that = (UniverLibrary) o;
        return mxKolBooks == that.mxKolBooks &&
                Objects.equals(libraryName, that.libraryName) &&
                Objects.equals(allBooks, that.allBooks);
    }

    @Override
    public int hashCode() {

        return Objects.hash(mxKolBooks, libraryName, allBooks);
    }

    @Override
    public String toString() {
        return "UniverLibrary{" +
                "mxKolBooks=" + mxKolBooks +
                ", libraryName='" + libraryName + '\'' +
                ", allBooks=" + allBooks +
                '}';
    }
}
