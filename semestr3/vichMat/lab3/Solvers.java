import javax.xml.crypto.Data;
import java.io.PrintWriter;
import java.util.ArrayList;

public class Solvers {

    public static double linerSolver(DataSet dataSet, double x){
        double x1, y1, x2, y2;
        x1 = y1 = x2 = y2 = 0;
        for(int i = 1; i < dataSet.xrr.size(); i++){
            if((dataSet.xrr.get(i - 1) <= x) && (x <= dataSet.xrr.get(i))){
                x1 = dataSet.xrr.get(i - 1);
                y1 = dataSet.yrr.get(i - 1);
                x2 = dataSet.xrr.get(i);
                y2 = dataSet.yrr.get(i);
                break;
            }
        }

        System.out.println(" x1 = " + x1 + " y1 = " + y1 + "" +
                "\n x2 = " + x2 + " y2 = " + y2);
        double a = (y2 - y1) / (x2 - x1);
        double b = y1 - (a * x1);

        System.out.println(" a = " + a + " b = " + b);
        return (a * x) + b;
    }

    public static double squareSolver(DataSet dataSet, double x){
        double x1, x2, x3, y1 = 0, y2, y3;
        x1 = x2 = x3 = y1 = y2 = y3 = 0;
        for(int i = 2; i < dataSet.xrr.size(); i++){
            if((dataSet.xrr.get(i - 2) <= x) && (x <= dataSet.xrr.get(i))){
                x1 = dataSet.xrr.get(i - 2);
                x2 = dataSet.xrr.get(i - 1);
                x3 = dataSet.xrr.get(i);
                y1 = dataSet.yrr.get(i - 2);
                y2 = dataSet.yrr.get(i - 1);
                y3 = dataSet.yrr.get(i);
                break;
            }
        }

        double A1, A2, A3, B1, B2, B3, C1, C2, C3;
        double a0, a1, a2;
        double det, det0, det1, det2;
        A1 = x1 * x1;
        A2 = x1;
        B1 = x2 * x2;
        B2 = x2;
        C1 = x3 * x3;
        C2 = x3;
        A3 = B3 = C3 = 1;

        det = countDet(A1, A2, A3, B1, B2, B3, C1, C2, C3);
        det0 = countDet(y1, A2, A3, y2, B2, B3, y3, C2, C3);
        det1 = countDet(A1, y1, A3, B1, y2, B3, C1, y3, C3);
        det2 = countDet(A1, A2, y1, B1, B2, y2, C1, C2, y3);

        a2 = det0 / det;
        a1 = det1 / det;
        a0 = det2 / det;

        System.out.println("a0 = " + a0 + "\n a1 = " + a1 + " \n a2 = " + a2);

        return a0 + (a1 * x) + (a2 * x * x);
    }

    public static double lagranzSolver(DataSet dataSet, double x){
        double res = 0.;
        for(int i = 0; i < dataSet.xrr.size(); i++){
            double a = 1., b = 1.;
            for(int j = 0; j < dataSet.xrr.size(); j++){
                if(i != j){
                    a *= (x - dataSet.xrr.get(j));
                    b *= (dataSet.xrr.get(i) - dataSet.xrr.get(j));
                }
            }

            res += (a * dataSet.yrr.get(i)) / b;
        }

        return res;
    }

    public static double NewtonForNotEqual(DataSet dataSet, double x){
        double res1 = NewtonForNotEqualSingleConut(dataSet, x);

        DataSet dataSet2 = dataSet.copy();
        dataSet2.xrr.remove(0);
        dataSet2.yrr.remove(0);
        double res2 = NewtonForNotEqualSingleConut(dataSet2, x);

        double res = (res1 + res2 ) / 2.;

        System.out.println("res1 = " + res1 + "\n res2 = " + res2 + " \n result = " + res);

        return res;
    }

    public static double NewtonForNotEqualSingleConut(DataSet dataSet, double x){
        double res = 0.;
        ArrayList<Integer> arr = new ArrayList<>();
        for(int i = 0; i < dataSet.xrr.size(); i++){
            double p = 1.;
            for(int j = 0; j < i; j++){
                p *= (x - dataSet.xrr.get(j));
            }
            arr.add(i);
            p *= fx(dataSet, arr);
            res += p;
        }
        return res;
    }

    public static double fx(DataSet dataSet, ArrayList<Integer > arr){
        if(arr.size() == 1) return dataSet.yrr.get(arr.get(0));
        double res = 0.;
        ArrayList<Integer> brr = new ArrayList<>();
        ArrayList<Integer> crr = new ArrayList<>();
        for(int i = 0; i < arr.size(); i++){
            if(i != 0) brr.add(arr.get(i));
            if(i != arr.size() - 1) crr.add(arr.get(i));
        }
        res = fx(dataSet, brr) - fx(dataSet, crr);
        res = res / (dataSet.xrr.get(arr.get(arr.size() - 1)) - dataSet.xrr.get(arr.get(0)));
        return res;
    }

    public static double countDet(double A1, double A2, double A3,
                                  double B1, double B2, double B3,
                                  double C1, double C2, double C3){
        return (A1 * B2 * C3) + (B1 * C2 * A3) + (A2 * B3 * C1) -
                (A3 * B2 * C1) - (A1 * C2 * B3) - (C3 * B1 * A2);
    }

    public static double NewtonForEqual_front(DataSet dataSet, double x){
        int n = dataSet.xrr.size() - 1;
        double[][] dety = getDetY(dataSet);
        double t = (x - dataSet.xrr.get(0)) / (dataSet.xrr.get(1) - dataSet.xrr.get(0));
        double res = dataSet.yrr.get(0);
        double p = 1.;
        double fact = 1.;
        for(int i = 0; i < n; i++){
            p *= (t - i);
            fact *= (i + 1.);
            res += ((p * dety[0][i + 1]) / fact);
        }

        return res;
    }

    public static double NewtonForEqual_back(DataSet dataSet, double x){
        int n = dataSet.xrr.size() - 1;
        double[][] dety = getDetY(dataSet);
        System.out.println(" sz = " + dataSet.xrr.size());
        double t = (x - dataSet.xrr.get(n)) / (dataSet.xrr.get(1) - dataSet.xrr.get(0));
        double res = dataSet.yrr.get(n);
        double p = 1.;
        double fact = 1.;
        for(int i = 0; i < n; i++){
            p *= (t + i);
            fact *= (i + 1.);

            res += ((p * dety[n - i - 1][i + 1]) / fact);
        }

        return res;
    }

    public static double[][] getDetY(DataSet dataSet) {
        int n = dataSet.xrr.size() - 1;
        double[][] dety = new double[n + 1][n + 1];
        for (int i = 0; i < n; i++) {
            dety[i][1] = dataSet.yrr.get(i + 1) - dataSet.yrr.get(i);
        }
        for (int j = 2; j <= n; j++) {
            for (int i = 0; i <= n - j; i++) {
                dety[i][j] = dety[i + 1][j - 1] - dety[i][j - 1];
            }
        }

        for(int i = 0; i < n; i++){
            for(int j = 1; j <= n - i; j++){
                System.out.print(dety[i][j] + " ");
            }
            System.out.println();
        }
        return dety;
    }
}
