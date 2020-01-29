import java.util.*;

class Book implements GetName, GetJanr{
    private static final int NUMBER_OF_EXTRA_WORDS = 110;
    private int mxKolWords;
    private String bookName;
    private Janrs bookJanr;
    private ArrayList< String > words;

    Book(String name, Janrs jan, int kol, String[] arr){
        if((name == null) || (jan == null) || (kol < 0) || (arr == null)) throw new FormatExaption("nnin", " in Book.Book");
        bookName = name;
        bookJanr = jan;
        mxKolWords = kol + NUMBER_OF_EXTRA_WORDS;
        words = new ArrayList< String >();
        for(int i = 0; i < kol; i++){
            words.add(arr[i]);
        }
    }
    public int compareTo(Book bo){
        String a, b;
        a = bookName + bookJanr.name();
        b = bo.bookName + bo.bookJanr.name();
        return a.length() - b.length();
    }

    public String getName() {
        return bookName;
    }

    public Janrs getBookJanr() {
        return bookJanr;
    }

    public int getMxKolWords() {
        return mxKolWords;
    }

    public int getKolWords() {
        return words.size();
    }

    public boolean canAddNewWord() {
        return words.size() < mxKolWords;
    }

    public void addNewWord(String s) {
        if (words.size() < mxKolWords) words.add(s);
    }

    public String getWordX(int x) {
        if (0 <= x && x < words.size()) return words.get(x);
        else {
            System.out.println(" Net takoi Slova ");
            return null;
        }
    }

    protected String[] getAllWords(){
        return words.toArray(new String[words.size()]);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Book book = (Book) o;
        return mxKolWords == book.mxKolWords && Objects.equals(bookName, book.bookName) && bookJanr == book.bookJanr && Objects.equals(words, book.words);
    }

    @Override
    public int hashCode() {

        return Objects.hash(mxKolWords, bookName, bookJanr, words);
    }

    @Override
    public String toString() {
        return "Book{" + "mxKolWords=" + mxKolWords + ", bookName='" + bookName + '\'' + ", bookJanr=" + bookJanr + ", words=" + words + '}';
    }
}
