import java.io.BufferedOutputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Map;

import static java.lang.Math.max;

public class OutLoader {
    public boolean importToFile(String fileName, Map<String, Book> mp_a)  {
        try(FileOutputStream out=new FileOutputStream(fileName);
            BufferedOutputStream outt = new BufferedOutputStream(out))
        {
            max(1, 2);
            byte[] buffer;
            for(Book iter : mp_a.values()){
                String outString = "";
                outString += iter.getName() + "#";
                outString += iter.getBookJanr().name() + "#";
                outString += iter.getKolWords() + "#";

                for(int i = 0; i < iter.getKolWords(); i++){
                    outString += iter.getWordX(i);
                    if(i + 1 != iter.getKolWords()) outString += "#";
                }
                buffer = (outString).getBytes();
                outt.write(buffer, 0, buffer.length);
                outt.write("\n".getBytes());
            }
            outt.close();
            out.close();
            return true;
        } catch (IOException e) {
            System.out.println("Wrong file name!!");
            return false;
        }
    }
}
