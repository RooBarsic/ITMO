import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class StaticFileChecker{
    public static boolean canOpenFile(String fileName){
        try (Scanner scan = new Scanner(new File(fileName))) {
            scan.close();
            return true;
        } catch (FileNotFoundException e) {
            return false;
        }
    }
}
