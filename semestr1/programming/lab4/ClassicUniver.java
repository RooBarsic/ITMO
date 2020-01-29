import com.sun.istack.internal.NotNull;
import com.sun.istack.internal.Nullable;

import java.util.Objects;

class ClassicUniver extends Univer implements CheckKey, GetName{
    @NotNull private String univerName;
    @NotNull private UniverLibrary library;

    ClassicUniver(@Nullable String univerName, int librarySize,@Nullable String libraryName){
        if((univerName == null) || (libraryName == null) || (librarySize < 0))
            throw new FormatExaption("sni","ClassicUniver.ClassicUniver");
        this.univerName = univerName;
        library = new UniverLibrary(librarySize, libraryName);
    }

    public String getName(){
        return univerName;
    }

    public boolean checkKeyForBookBJ(String name, Janrs jan, Keys ke){
        return library.checkKeyForBookBJ(name, jan, ke);
    }

    public String getLibraryName(){
        return library.getName();
    }

    public boolean haveBookBJ(String name, Janrs jan){
        return library.haveBookBJ(name, jan);
    }

    public Book getBookFromLibrary(String name, Janrs jan, Keys ke){
        return library.getBookFromLibrary(name, jan, ke);
    }

    public boolean canAddnewBook(){
        return library.canAddNewBook();
    }

    public void addNewBookB(Book boo, Keys ke) {
        library.addBook(boo, ke);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ClassicUniver that = (ClassicUniver) o;
        return Objects.equals(univerName, that.univerName) &&
                Objects.equals(library, that.library);
    }

    @Override
    public int hashCode() {

        return Objects.hash(univerName, library);
    }

    @Override
    public String toString() {
        return "ClassicUniver{" +
                "univerName='" + univerName + '\'' +
                ", library=" + library +
                '}';
    }
}
