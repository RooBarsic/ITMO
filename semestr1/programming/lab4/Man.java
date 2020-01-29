import com.sun.istack.internal.NotNull;
import com.sun.istack.internal.Nullable;

import java.util.*;

import static java.lang.Math.abs;

public class Man implements GetName{
    class ManBookMemor{
        private ArrayList< Book > books = new ArrayList< Book >();

        public void addNewBook(@Nullable Book boo){
            if(boo == null) throw new FormatExaption("n", "Man.ManBookMemor.addNewBook");
            books.add(boo);
        }

        public int getNumberOfBooks(){
            return books.size();
        }

        public Book getBookX(int x){
            if((0 <= x) && (x <= books.size())) return books.get(x);
            else throw new FormatExaption("i", "Man.ManBookMemor.getBookX");
        }
    }

    static class ManWordMemo {
        private Set< String > words = new HashSet< String >();
        ManWordMemo(String name){
            if(name == null) throw new FormatExaption("sn", "ManMemo.Constructor");
            words.add(name);
        }
        public void addNew(String s){
            if((s == null) || (s.equals(""))) return;
            words.add(s);
        }
        public String getWordX(int x){
            if((0 <= x) && (x < words.size())) {
                String[] arr = words.toArray(new String[words.size()]);
                return arr[x];
            }
            else throw new FormatExaption("i", "Man.ManWordMemo.getWordX");
        }
        public int getKolWords(){
            return words.size();
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            ManWordMemo that = (ManWordMemo) o;
            return Objects.equals(words, that.words);
        }

        @Override
        public int hashCode() {

            return Objects.hash(words);
        }

        @Override
        public String toString() {
            return "ManWordMemo{" +
                    "words=" + words +
                    '}';
        }
    }

    private ManBookMemor bookMemor;
    private ManWordMemo wordMemor;
    private boolean gubi = true;
    private boolean badFlag = false;
    @NotNull private String manName;
    private Keys manKey;
    private boolean transFlag = false;
    Man(@Nullable String name){
        if(name == null) throw new FormatExaption("sn", "Man.Man");
        manName = name;
        bookMemor = new ManBookMemor();
        wordMemor = new ManWordMemo(name);
    }

    public String getName(){
        return manName;
    }

    public void changeGubiStatus(){
        gubi = !gubi;
    }

    public void ifoundKeyX(Keys x){
        if(x == null) return ;
        manKey = x;
    }

    public boolean manHaveKey(){
        return manKey != null;
    }

    public Keys getManKey(){
        return manKey;
    }

    public void read(Book boo){
        if(boo == null) return ;
        if((boo.getName().equals("Nekromikon")) && (boo.getBookJanr().equals(Janrs.EZOTERIC))) badFlag = true;
        bookMemor.addNewBook(boo);
        for(int i = 0; i < boo.getKolWords(); i++){
            wordMemor.addNew(boo.getWordX(i));
        }
        if ((!transFlag) && (badFlag) && (((new Random()).nextInt() % 100) < 37)) transActive();
    }
    public void sayRandomInfo(){
        sayWord(wordMemor.getWordX(abs((new Random()).nextInt()) % wordMemor.getKolWords()));
        if ((!transFlag) && (badFlag) && (((new Random()).nextInt() % 100) < 37)) transActive();
    }

    public void sayWord(String s){
        class Says{
            Says(String a){
                System.out.println(a);
            }
        }
        if((s == null) && (s.equals(""))) return;
        if(gubi) new Says(s);
            //System.out.println(s);
        if(gubi == false) System.out.println(" Net Gub ");
        if((!transFlag) && (badFlag) && (((new Random()).nextInt() % 100) < 37)) transActive();
    }

    public void transActive(){
        if(!badFlag){
            System.out.println(" Ne chital knigu Nekromikon! ");
            return ;
        }
        transFlag = true;
        int k = abs((new Random()).nextInt()) % 17 + 5;
        for(int i = 0; i < k; i++) {
            sayRandomInfo();
        }
        SayOprovdanie();
        transFlag = false;
    }

    private void SayOprovdanie(){
        if(transFlag && badFlag && gubi) System.out.println("lalala, bla bla. Ya Chital Nekromikon!");
        if(!gubi) System.out.println(" Net gub! ");
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Man man = (Man) o;
        return gubi == man.gubi &&
                badFlag == man.badFlag &&
                transFlag == man.transFlag &&
                Objects.equals(bookMemor, man.bookMemor) &&
                Objects.equals(wordMemor, man.wordMemor) &&
                Objects.equals(manName, man.manName) &&
                manKey == man.manKey;
    }

    @Override
    public int hashCode() {

        return Objects.hash(bookMemor, wordMemor, gubi, badFlag, manName, manKey, transFlag);
    }

    @Override
    public String toString() {
        return "Man{" +
                "bookMemor=" + bookMemor +
                ", wordMemor=" + wordMemor +
                ", gubi=" + gubi +
                ", badFlag=" + badFlag +
                ", manName='" + manName + '\'' +
                ", manKey=" + manKey +
                ", transFlag=" + transFlag +
                '}';
    }
}
