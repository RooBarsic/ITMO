import java.io.File;
import java.util.Scanner;

public class MyLog {
    public static double a, b, c, d;
    public static boolean checkFile(String fileName){
        try (Scanner scanner = new Scanner(new File(fileName))){
             a = scanner.nextDouble();
             b = scanner.nextDouble();
             c = scanner.nextDouble();
             d = scanner.nextDouble();
            return true;
        } catch (Exception e){
            return false;
        }
    }
}
