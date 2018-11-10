import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class InOut {
    private Scanner consoleSanner;
    private PrintWriter consolePrinter;
    private PrintWriter filePrinter;

    InOut(String outputFileName){
        consoleSanner = new Scanner(System.in);
        consolePrinter = new PrintWriter(System.out);
        try {
            filePrinter = new PrintWriter(new File(outputFileName));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    // File out put --------------------------------------------
    public void printFile(int x){
        filePrinter.print(x);
        filePrinter.flush();
    }

    public void printlnFile(int x){
        filePrinter.println(x);
        filePrinter.flush();
    }

    public void printFile(double d){
        filePrinter.printf("%.4f", d);
        filePrinter.flush();
    }

    public void printlnFile(double d){
        filePrinter.printf("%.4f \n", d);
        filePrinter.flush();
    }

    public void printFile(String s){
        filePrinter.print(s);
        filePrinter.flush();
    }

    public void printlnFile(String s){
        filePrinter.println(s);
        filePrinter.flush();
    }

    // Console input -----------------------------------------------------
    public int getInt(){
        int x = consoleSanner.nextInt();
        printlnFile("user : " + Integer.toString(x));
        return x;
    }

    public double getDouble(){
        double x = consoleSanner.nextDouble();
        printFile("user : ");
        printlnFile(x);
        return x;
    }

    public String getString(){
        String s = consoleSanner.next();
        printlnFile("user : " + s);
        return s;
    }

    // Console output -----------------------------------------------------
    public void print(int x){
        consolePrinter.print(x);
        consolePrinter.flush();
        printFile("program : " + Integer.toString(x));
    }

    public void println(int x){
        consolePrinter.println(x);
        consolePrinter.flush();
        printlnFile("program : " + Integer.toString(x));
    }

    public void print(String s){
        consolePrinter.print(s);
        consolePrinter.flush();
        printFile(s);
    }

    public void println(String s){
        consolePrinter.println(s);
        consolePrinter.flush();
        printlnFile(s);
    }

    public void print(double d){
        consolePrinter.printf("%.4f", d);
        consolePrinter.flush();
        printFile(d);
    }

    public void println(double d){
        consolePrinter.printf("%.4f \n", d);
        consolePrinter.flush();
        printlnFile(d);
    }

    public void printD7(double d){
        consolePrinter.printf("%.11f", d);
        consolePrinter.flush();
        filePrinter.printf("%.11f", d);
        filePrinter.flush();
    }

    public void printlnD7(double d){
        consolePrinter.printf("%.11f \n", d);
        consolePrinter.flush();
        filePrinter.printf("%.11f \n", d);
        filePrinter.flush();
    }
}
