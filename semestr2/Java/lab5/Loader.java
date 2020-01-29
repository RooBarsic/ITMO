import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Loader {
    private String s = "";

    private int pos = 0;
    Loader(String fileName) throws FileNotFoundException {
        try (Scanner scan = new Scanner(new File(fileName))) {
            while (scan.hasNextLine()){
                if(s.length() > 0) s += "#";
                s += scan.nextLine();
            }
            scan.close();
        }
    }

    public String getString(){
        int l = pos;
        while ((pos < s.length()) && (s.charAt(pos) != '#')){
            pos++;
        }
        String out = s.substring(l, pos);
        //System.out.println(" string " + l + " " + pos + " " + out);
        pos++;
        return out;
    }

    public int getInt() throws Exception{
        int l = pos;
        while ((pos < s.length()) && (s.charAt(pos) != '#')){
            if(!(('0' < s.charAt(pos)) && (s.charAt(pos) < '9')))
                throw new IllegalArgumentException("Wrong csv format!");
            pos++;
        }
        String out = s.substring(l, pos);
        //System.out.println(" int " + l + " " + pos + " " + out);
        pos++;
        return Integer.parseInt(out);
    }

    public boolean hasNext(){
        return pos < s.length();
    }
}
