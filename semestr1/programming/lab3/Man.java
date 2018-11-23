import java.util.Objects;
import java.util.Random;

import static java.lang.Math.abs;

class Man implements GetName{
    private ManBookMemor bookMemor;
    private ManWordMemo wordMemor;
    private boolean gubi = true;
    private boolean badFlag = false;
    private String manName;
    private Keys manKey;
    private boolean transFlag = false;

    Man(String name){
        manName = name;
        bookMemor = new ManBookMemor();
        wordMemor = new ManWordMemo(name);
    }

    public String getName(){
        if(manName == null) return "";
        return manName;
    }

    public void changeGubi(){
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
        if((boo.getName().equals("Nekromikon")) && (boo.getBookJanr().equals(Janrs.Ezoteric))) badFlag = true;
        bookMemor.addNewBook(boo);
        for(int i = 0; i < boo.getKolWords(); i++){
            wordMemor.addNew(boo.getWordX(i));
        }
        if((!transFlag) && (((new Random()).nextInt() % 100) < 37)) transActive();
    }
    public void sayRandomInfo(){
        if(wordMemor.getKolWords() == 0) System.out.println(" No Any Info! ");
        else sayWord(wordMemor.getWordX(abs((new Random()).nextInt()) % wordMemor.getKolWords()));
        if((!transFlag) && (((new Random()).nextInt() % 100) < 37)) transActive();
    }

    public void sayWord(String s){
        if(s == null) return;
        if(gubi) System.out.println(s);
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

    public void getWordInfo(){
        System.out.println(" kol Words = " + wordMemor.getKolWords());
        for(int i = 0; i < wordMemor.getKolWords(); i++){
            System.out.println(wordMemor.getWordX(i));
        }
        System.out.println(" End of outing words! ");
    }

    private void SayOprovdanie(){
        if(badFlag && gubi) System.out.println("lalala, bla bla. Ya Chital Nekromikon!");
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
