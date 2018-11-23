import com.sun.istack.internal.Nullable;

import java.util.ArrayList;

public class ManBookMemor{
    private ArrayList< Book > books = new ArrayList< Book >();

    public @Nullable void addNewBook(Book boo){
        if(boo == null) throw new IllegalArgumentException("in ManBookMemor.addNewBook ");
        books.add(boo);
    }

    public int getKolBooks(){
        return books.size();
    }


    public Book getBookX(int x){
        if((0 <= x) && (x <= books.size())) return books.get(x);
        else throw new IllegalArgumentException("in MAnBookMemor.getBookX");
    }
}
