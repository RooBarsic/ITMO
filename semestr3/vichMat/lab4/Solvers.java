import java.io.PrintWriter;

public class Solvers {
    public static void solverGo(PrintWriter printWriter, int solverId, int functionId, double a, double b){
        int n = 4;
        double eps = 0.000001;
        double I0 = useSolver(solverId, functionId, n, a, b);
        double I1 = useSolver(solverId, functionId, 2 * n, a, b);
        int k = 1;
        while(Math.abs(I1 - I0) > eps){
            k++;
            n *= 2;
            I0 = I1;
            I1 = useSolver(solverId, functionId, 2 * n, a, b);
        }
        MyLog.print(printWriter, " k = ");
        MyLog.println(printWriter, k);
        MyLog.print(printWriter, " n = ");
        MyLog.println(printWriter, Integer.toString(n));
        MyLog.print(printWriter, " Integral = ");
        MyLog.println(printWriter, I1);
    }

    private static double useSolver(int solverId, int functionId, int n, double a, double b){
        switch (solverId){
            case 1 : return rectanglesLeft(functionId, n, a, b);
            case 2 : return rectanglesRight(functionId, n, a, b);
            case 3 : return rectanglesMiddle(functionId, n, a, b);
            case 4 : return trapezoidMethod(functionId, n, a, b);
            default: return SimpsonMethod(functionId, n, a, b);
        }
    }

    public static double rectanglesLeft(int functionId, int n, double a, double b){
        double sum = 0.;
        double h = (b - a) / (n * 1.);
        for(int i = 0; i < n; i++){
            sum += Functions.getFunc(functionId, a + h * (i * 1.));
        }
        sum *= h;
        return sum;
    }

    public static double rectanglesRight(int functionId, int n, double a, double b){
        double sum = 0.;
        double h = (b - a) / (n * 1.);
        for(int i = 1; i <= n; i++){
            sum += Functions.getFunc(functionId, a + h * (i * 1.));
        }
        sum *= h;
        return sum;
    }

    public static double rectanglesMiddle(int functionId, int n, double a, double b){
        double sum = 0.;
        double h = (b - a) / (n * 1.);
        for(int i = 1; i <= n; i++){
            double x = ((a + h * (i * 1.)) + (a + h * ((i - 1) * 1.))) / 2.;
            //double x = a + (h * (i * 1.)) - (h / 2.);
            sum += Functions.getFunc(functionId, x);
        }
        sum *= h;
        return sum;
    }

    public static double trapezoidMethod(int functionId, int n, double a, double b){
        double sum = 0.;
        double h = (b - a) / (n * 1.);
        for(int i = 1; i < n; i++){
            sum += Functions.getFunc(functionId, a + h * (i * 1.));
        }
        sum *= 2.;
        sum += Functions.getFunc(functionId, a) + Functions.getFunc(functionId, b);
        sum = (sum * h) / 2.;
        return sum;
    }

    public static double SimpsonMethod(int functionId, int n, Double a, Double b){
        Double sum = Functions.getFunc(functionId, a) + Functions.getFunc(functionId, b);
        Double h = (b - a) / (n * 1.);
        for(int i = 1; i < n; i++){
            if(i % 2 == 1) sum += 4. * Functions.getFunc(functionId, a + h * (i * 1.));
            else sum += 2. * Functions.getFunc(functionId, a + h * (i * 1.));
        }
        sum = (sum * h) / 3.;
        return sum;
    }
}
//524288
//512