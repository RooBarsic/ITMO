import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.PrimitiveIterator;

public class MyLog {
    private static PrintWriter fileWriter;

    public static void setParams(){
        try {
            fileWriter = new PrintWriter(new File("res.txt"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    private static void fprint(String s){
        fileWriter.print(s);
        fileWriter.flush();
    }

    private static void fprintln(String s){
        fileWriter.println(s);
        fileWriter.flush();
    }

    private static void fprint(double x){
        fileWriter.printf("%.6f", x);
        fileWriter.flush();
    }

    private static void fprintln(double x){
        fileWriter.printf("%.6f \n", x);
        fileWriter.flush();
    }

    public static void print(PrintWriter printer, String s){
        printer.print(s);
        printer.flush();

        fprint(s);
    }

    public static void print(PrintWriter printer, double d){
        printer.printf("%.6f ", d);
        printer.flush();

        fprint(d);
    }

    public static void println(PrintWriter printer, String s){
        printer.println(s);
        printer.flush();

        fprintln(s);
    }

    public static void println(PrintWriter printer, double d){
        printer.printf("%.6f \n", d);
        printer.flush();

        fprintln(d);
    }
}
