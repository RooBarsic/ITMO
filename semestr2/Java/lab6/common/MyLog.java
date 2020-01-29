package common;

import com.oracle.xmlns.internal.webservices.jaxws_databinding.ExistingAnnotationsType;

import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class MyLog {
    public static void printLn(PrintWriter printWriter, String message){
        printWriter.println(message);
        printWriter.flush();
    }

    public static void print(PrintWriter printWriter, String message){
        printWriter.print(message);
        printWriter.flush();
    }

    public static String getMessage(byte[] b){

        List<Byte> arr = new ArrayList<>();
        for(int i = 0; i < b.length; i++){
            if(b[i] != 0) arr.add(b[i]);
        }
        byte[] bn = new byte[arr.size()];
        for(int i = 0; i < arr.size(); i++){
            bn[i] = arr.get(i);
        }
        return new String(bn);
    }

    public static void weitThread(int x, Thread thread){
        if(thread.isAlive() == false) return;
        for(int i = 1; i <= x; i++){
            try {
                if(i % 3 == 0) System.out.println(i + " seconds left. ");
                TimeUnit.SECONDS.sleep(1);
            } catch (InterruptedException e) {
                //System.out.println("weitThread has been interrupted.");
            }
            if(thread.isAlive() == false) break;
        }
    }
}
