package functions;

import java.io.PrintWriter;

/// y = a * Ln(x) + b
public class LogarithmicFunction extends Function{
    private double a;
    private double b;

    public LogarithmicFunction(double a, double b){
        this.a = b;
        this.b = a;
    }

    @Override
    public double calc(double x) {
        return a * Math.log(x) + b;
    }

    @Override
    public void printFunction(PrintWriter printWriter) {
        printWriter.printf("y = %.6f * Ln(x) + %.6f \n", a, b);
        printWriter.flush();
    }
}
