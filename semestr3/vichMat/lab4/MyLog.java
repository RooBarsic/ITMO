import java.io.PrintWriter;

public class MyLog {

    public static void print(PrintWriter printWriter, String s){
        printWriter.print(s);
        printWriter.flush();
    }

    public static void println(PrintWriter printWriter, String s){
        printWriter.println(s);
        printWriter.flush();
    }

    public static void print(PrintWriter printWriter, double d){
        printWriter.printf("%.7f", d);
        printWriter.flush();
    }

    public static void println(PrintWriter printWriter, double d){
        printWriter.printf("%.7f \n", d);
        printWriter.flush();
    }
}
