package functions;

import java.io.PrintWriter;

/// y = a * e^(b*x)
public class ExponentialFunction extends Function{
    private double a;
    private double b;

    public ExponentialFunction(double a, double b){
        this.a = a;
        this.b = b;
    }


    @Override
    public double calc(double x) {
        return a * Math.pow(Math.E, (b * x));
    }

    @Override
    public void printFunction(PrintWriter printWriter) {

        printWriter.printf("y = %.6f * e^( %.6f * x) \n", a, b);
        printWriter.flush();
    }
}
