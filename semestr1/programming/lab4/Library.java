
abstract class Library {
    public abstract int getKolBooks();
    public abstract boolean canAddNewBook();
    public abstract boolean haveBookBJ(String bookName, Janrs jan);

    @Override
    public String toString() {
        return "Library{}";
    }
}
