package functions;

import java.io.PrintWriter;

public abstract class Function {

    public abstract double calc(double x);
    public abstract void printFunction(PrintWriter printWriter);

    public double calcS(InputSotage inputSotage ){
        double s = 0.;
        for(int i = 0; i < inputSotage.size(); i++){
            double x = inputSotage.xrr.get(i);
            double y = inputSotage.yrr.get(i);

            s += (calc(x) - y) * (calc(x) - y);
        }

        return s;
    }

    public double calcSquareEror(InputSotage inputSotage){
        double res = 0.;
        for (int i = 0; i < inputSotage.size(); i++){
            double x = inputSotage.xrr.get(i);
            double y = inputSotage.yrr.get(i);

            res += (calc(x) - y) * (calc(x) - y);
        }
        res = res / (inputSotage.size() * 1.);

        res = Math.sqrt(res);
        return res;
    }
}
