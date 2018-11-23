import com.sun.istack.internal.NotNull;
import com.sun.istack.internal.Nullable;
import sun.awt.util.IdentityLinkedList;

import java.lang.*;
import java.util.Objects;

public class LibraryBook extends Book{
    @NotNull private final Keys key;

    LibraryBook(String name,Janrs jan, int kol, String[] arr, Keys key) {
        super(name, jan, kol, arr);
        if(key == null) throw new IllegalArgumentException("in LibraryBook.LibraryBook");
        this.key = key;
    }
    LibraryBook(@NotNull Book boo, @NotNull Keys key){
        super(boo.getName(), boo.getBookJanr(), boo.getKolWords(), boo.getAllWords());
        if((boo == null) || (key == null)) throw new IllegalArgumentException();
        this.key = key;
    }

    public boolean checkKey(Keys ke) {
        return key.equals(ke);
    }

    public Book getBook(Keys ke){
        if(ke == null) throw new IllegalArgumentException(" in LibraryBook.getBook ! ");
        if(key.equals(ke)) return (Book) this;
        return null;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        LibraryBook that = (LibraryBook) o;
        return key == that.key;
    }

    @Override
    public int hashCode() {

        return Objects.hash(super.hashCode(), key);
    }
}
