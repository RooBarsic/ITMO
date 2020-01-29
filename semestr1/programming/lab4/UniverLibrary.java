import com.sun.istack.internal.NotNull;
import com.sun.istack.internal.Nullable;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Objects;

class UniverLibrary extends Library implements GetName, CheckKey{
    @NotNull private int mxKolBooks;
    @NotNull private String libraryName;
    private ArrayList< LibraryBook > allBooks = new ArrayList< LibraryBook >();

    UniverLibrary(int size, @Nullable String name) {
        if((size < 0) || (name == null)) throw new FormatExaption("isn", "UniverLibrary.UniverLibrary");
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

    public void addBook(@Nullable Book boo, @Nullable Keys ke) throws BadKey{
        if(boo == null){
            System.out.println("Can't add this book!");
        }
        else if(allBooks.size() < mxKolBooks){
            allBooks.add(new LibraryBook(boo, ke));
            Collections.sort(allBooks, new Comparator<LibraryBook>() {
                @Override
                public int compare(LibraryBook t1, LibraryBook t2) {
                    return (t1.getKolWords() < t2.getKolWords()) ? 0 : -1;
                }
            });
        } else System.out.println(" Can't add new book ");
    }

    public boolean haveBookBJ(String bookName, Janrs jan) {
        if(jan == null) jan = Janrs.CLASSIC;
        if(bookName == null) throw new FormatExaption("sn", "UniverLibrary.haveBookBJ");
        for(int i = 0, kol = (int)allBooks.size(); i < kol; i++){
            if((allBooks.get(i).getName().equals(bookName)) && (allBooks.get(i).getBookJanr() == jan))
                return true;
        }
        return false;
    }

    public boolean checkKeyForBookBJ(String bookName, Janrs jan, Keys ke) {
        if(jan == null) jan = Janrs.CLASSIC;
        if((bookName == null) || (ke == null))  throw new FormatExaption("sn", "UniverLibrary.checkKeyForBookBJ");
        for(int i = 0, kol = (int)allBooks.size(); i < kol; i++){
            if((allBooks.get(i).getName().equals(bookName)) && (allBooks.get(i).getBookJanr().equals(jan))) {
                return (allBooks.get(i).checkKey(ke));
            }
        }
        return false;
    }

    public Book getBookFromLibrary(String bookName, Janrs jan, Keys ke){
        if(jan == null) jan = Janrs.CLASSIC;
        if((bookName == null) || (ke == null))  throw new FormatExaption("sn","UniverLibrary.getBookFromLibarary");
        for (int i = 0, kol = (int)allBooks.size(); i < kol; i++) {
            if ((allBooks.get(i).getName().equals(bookName)) && (allBooks.get(i).getBookJanr().equals(jan))) {
                if (allBooks.get(i).checkKey(ke)) {
                    Book bi = allBooks.get(i).getBook(ke);
                    if(bi == null) System.out.println(" eto NULL !! ");
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



