package functions;

import java.io.PrintWriter;

/// y = a * x^b
public class PowerFunction extends Function{
    private double a;
    private  double b;

    public PowerFunction(double a, double b){
        this.a = a;
        this.b = b;
    }

    @Override
    public double calc(double x) {
        return a * Math.pow(x, b);
    }

    @Override
    public void printFunction(PrintWriter printWriter) {
        printWriter.printf("y = %.6f * x^%.6f \n", a, b);
        printWriter.flush();
    }
}
