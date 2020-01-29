import com.sun.istack.internal.NotNull;
import com.sun.istack.internal.Nullable;
import jdk.nashorn.internal.runtime.ECMAException;

import java.lang.*;
import java.util.Objects;

public class LibraryBook extends Book{
    @NotNull private final Keys key;

    LibraryBook(String name,Janrs jan, int kol, String[] arr, Keys key){
        super(name, jan, kol, arr);
        if(key == null) try {
            throw new BadKey();
        } catch (BadKey badKey) {
            badKey.printStackTrace();
            key = Keys.BARSIC;
        }
        this.key = key;
    }
    LibraryBook(@NotNull Book boo, @NotNull Keys key){
        super(boo.getName(), boo.getBookJanr(), boo.getKolWords(), boo.getAllWords());
        if(boo == null) throw new FormatExaption("n", "LibraryBook.Constryctor");
        if(key == null) try {
            throw new BadKey();
        } catch (BadKey badKey) {
            badKey.printStackTrace();
            key = Keys.BARSIC;
        }
        this.key = key;
    }

    public boolean checkKey(@Nullable Keys ke) {
        try{
            return ke.equals(key);
        } catch (BadKey e){
            return false;
        }
    }

    public Book getBook(Keys ke) throws BadKey{
        Book bee = null;
        try {
            if(ke.equals(key)) bee = (Book) this;
        } catch (Exception e){
            bee = null;
        } finally {
            return bee;
        }
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

    @Override
    public String toString() {
        return "LibraryBook{" +
                "key=" + key +
                '}';
    }
}
