import java.io.PrintWriter;

public class MyLog {
    public static void printlnMessage(PrintWriter printWriter, String message){
        printWriter.println(message);
        printWriter.flush();
    }
    public static void printMessage(PrintWriter printWriter, String message){
        printWriter.print(message);
        printWriter.flush();
    }

    public static void printWrite(PrintWriter printWriter, String message){
        printWriter.write(message);
        printWriter.flush();
    }
}
