package functions;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class MyLog {
    private static PrintWriter fileWriter = null;

    public static void setOutFile(){
        try {
            fileWriter = new PrintWriter(new File("ans.txt"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public static boolean checkFile(String fileName){
        try {
            Scanner scanner = new Scanner(new File(fileName));
            return true;
        } catch (FileNotFoundException e) {
            return false;
        }
    }




    public static void print(PrintWriter printWriter, String message){
        printWriter.print(message);
        printWriter.flush();

        fileWriter.print(message);
        fileWriter.flush();
    }

    public static void print(PrintWriter printWriter, double message){
        printWriter.print(message);
        printWriter.flush();

        fileWriter.print(message);
        fileWriter.flush();
    }

    public static void print(PrintWriter printWriter, int message){
        printWriter.print(message);
        printWriter.flush();

        fileWriter.print(message);
        fileWriter.flush();
    }

    public static void println(PrintWriter printWriter, String message){
        printWriter.println(message);
        printWriter.flush();

        fileWriter.println(message);
        fileWriter.flush();
    }

    public static void println(PrintWriter printWriter, double message){
        printWriter.println(message);
        printWriter.flush();

        fileWriter.println(message);
        fileWriter.flush();
    }

    public static void println(PrintWriter printWriter, int message){
        printWriter.println(message);
        printWriter.flush();

        fileWriter.println(message);
        fileWriter.flush();
    }
}
