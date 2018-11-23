import java.util.*;

public class ManWordMemo {
    private Set< String > words = new HashSet< String >();
    ManWordMemo(String name){
        words.add(name);
    }
    public void addNew(String s){
        if((s == null) || (s.equals(""))) throw new IllegalArgumentException("in ManWordMemo.addNew");
        words.add(s);
    }
    public String getWordX(int x){
        if((0 <= x) && (x < words.size())) {
            String[] arr = words.toArray(new String[words.size()]);
            return arr[x];
        }
        else throw new IllegalArgumentException("in ManWordMemo.getWordX");
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
