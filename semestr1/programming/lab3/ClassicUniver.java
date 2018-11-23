import java.util.Objects;

class ClassicUniver extends Univer implements CheckKey, GetName{
    private String univerName;
    private UniverLibrary library;

    ClassicUniver(String univerName, int librarySize, String libraryName){
        if((univerName == null) || (libraryName == null) || (librarySize < 0)) throw new IllegalArgumentException("in ClassicUniver.ClassicUniver");
        this.univerName = univerName;
        library = new UniverLibrary(librarySize, libraryName);
    }

    public String getName(){
        if(univerName == null) return "";
        return univerName;
    }

    public boolean checkKeyForBookBJ(String name, Janrs jan, Keys ke){
        if(library == null){
            System.out.println(" Library does not exist! ");
            return false;
        }
        return library.checkKeyForBookBJ(name, jan, ke);
    }

    public String getLibraryName(){
        if(library == null) return null;
        return library.getName();
    }

    public boolean haveBookBJ(String name, Janrs jan){
        if(library == null){
            System.out.println(" Library does not exist! ");
            return false;
        }
        return library.haveBookBJ(name, jan);
    }

    public Book getBookFromLibrary(String name, Janrs jan, Keys ke){
        if(library == null){
            System.out.println(" Library does not exist! ");
            return null;
        }
        return library.getBookFromLibrary(name, jan, ke);
    }

    public boolean canAddnewBook(){
        if(library == null){
            System.out.println(" Library does not exist! ");
            return false;
        }
        return library.canAddNewBook();
    }

    public void addNewBookB(Book boo, Keys ke) {
        if(library == null){
            System.out.println(" Library does not exist! ");
            return ;
        }
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
