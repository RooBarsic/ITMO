package functions;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class InputSotage {
    public ArrayList<Double> xrr, yrr;

    public InputSotage(){
        xrr = new ArrayList<>();
        yrr = new ArrayList<>();
    }

    public void getData(){
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        for(int i = 1; i <= n; i++){
            xrr.add(scanner.nextDouble());
            yrr.add(scanner.nextDouble());
        }
    }

    public  void getData(String fileName){
        try {
            Scanner scanner = null;
            scanner = new Scanner(new File(fileName));
            int n = scanner.nextInt();
            for(int i = 1; i <= n; i++){
                xrr.add(scanner.nextDouble());
                yrr.add(scanner.nextDouble());
            }
        } catch (FileNotFoundException e) {
            System.out.println(" Wrong file name or wrong file data!!! ");
        }
    }

    public int size(){
        return xrr.size();
    }

    public double getSumXpow(int p){
        double sum = 0.;
        for(int i = 0; i < xrr.size(); i++){
            sum += mpower(xrr.get(i), p);
        }
        return sum;
    }

    public double getSumYpow(int p){
        double sum = 0.;
        for(int i = 0; i < yrr.size(); i++){
            sum += mpower(yrr.get(i), p);
        }
        return sum;
    }

    public double getSumY_Xpow(int p){
        double sum = 0.;
        for(int i = 0; i < yrr.size(); i++){
            sum += yrr.get(i) * mpower(xrr.get(i), p);
        }
        return sum;
    }

    double mpower(double a, int b){
        double res = 1.;
        for(int i = 1; i <= b; i++){
            res *= a;
        }
        return res;
    }

    public void copu(InputSotage inputSotage){
        if(inputSotage == null) return;
        xrr.clear();
        yrr.clear();
        for(int i = 0; i < inputSotage.size(); i++){
            xrr.add(inputSotage.xrr.get(i));
            yrr.add(inputSotage.yrr.get(i));
        }
    }

    public void out(PrintWriter printWriter){
        for(int i = 0; i < xrr.size(); i++){
            printWriter.print(xrr.get(i) + " " + yrr.get(i) + "\n");
        }
        printWriter.flush();
    }
}
