package functions;

import java.io.PrintWriter;
import java.util.ArrayList;

public class PolinomFunction extends Function {
    private ArrayList<Double> koef;

    public PolinomFunction(ArrayList<Double> koefs){
        koef = koefs;
    }

    public PolinomFunction(int n, double[] koefs){
        koef = new ArrayList<>();
        for(int i = 0; i < n; i++){
            koef.add(koefs[i]);
        }
    }

    @Override
    public double calc(double x) {
        double res = 0.;
        double p = 1.;
        for(int i = 0; i < koef.size(); i++){
            res += koef.get(i) * p;
            p = (p * x);
        }
        return res;
    }

    @Override
    public void printFunction(PrintWriter printWriter) {
        printWriter.print("y = ");
        for(int i = 0; i < koef.size(); i++){
            if(0 < i) printWriter.print(" + ");
            printWriter.printf("%.6f * x^%d", koef.get(i), i);
        }
        printWriter.print("\n");
        printWriter.flush();
    }
}
