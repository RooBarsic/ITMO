import functions.InputSotage;

import java.util.ArrayList;

public class EquationSolvers {

    // a0 + a1*x
    public static ArrayList<Double> solve1(InputSotage inputSotage){
        return solver3(inputSotage);
        /*
        int m = 1;
        double A1, A2, B1, B2, Y1, Y2, a0, a1;
        A1 = inputSotage.size();
        A2 = inputSotage.getSumXpow(1);
        B1 = inputSotage.getSumXpow(1);
        B2 = inputSotage.getSumXpow(2);

        Y1 = inputSotage.getSumYpow(1);
        Y2 = inputSotage.getSumY_Xpow(1);

        a0 = ((Y1 * B1) - (A1 * Y2)) / ((A2 * B1) - (A1 * B2));
        a1 = ((B2 * Y1) - (A2 * Y2)) / ((B2 * A1) - (B1 * A2));

        ArrayList<Double> arr = new ArrayList<>();
        arr.add(a0);
        arr.add(a1);

        return arr;
        //*/
    }

    public static ArrayList<Double> solver3(InputSotage inputSotage){
        double A1, A2, B1, B2, Y1, Y2;
        double a0, a1;
        double det, det0, det1;

        A1 = inputSotage.size();
        A2 = inputSotage.getSumXpow(1);
        B1 = inputSotage.getSumXpow(1);
        B2 = inputSotage.getSumXpow(2);

        Y1 = inputSotage.getSumYpow(1);
        Y2 = inputSotage.getSumY_Xpow(1);


        det = countDet(A1, A2, B1, B2);
        det0 = countDet(Y1, Y2, B1, B2);
        det1 = countDet(A1, A2, Y1, Y2);

        a0 = det0 / det;
        a1 = det1 / det;

        ArrayList<Double> arr = new ArrayList<>();
        arr.add(a0);
        arr.add(a1);

        return arr;
    }

    // a0 + a1*x + a2*x^2
    public static ArrayList<Double> solve2(InputSotage inputSotage){
        double A1, A2, A3, B1, B2, B3, C1, C2, C3, Y1, Y2, Y3;
        double a0, a1, a2;
        double det, det0, det1, det2;
        A1 = inputSotage.size() * 1.;
        A2 = inputSotage.getSumXpow(1);
        A3 = inputSotage.getSumXpow(2);

        B1 = inputSotage.getSumXpow(1);
        B2 = inputSotage.getSumXpow(2);
        B3 = inputSotage.getSumXpow(3);

        C1 = inputSotage.getSumXpow(2);
        C2 = inputSotage.getSumXpow(3);
        C3 = inputSotage.getSumXpow(4);

        Y1 = inputSotage.getSumYpow(1);
        Y2 = inputSotage.getSumY_Xpow(1);
        Y3 = inputSotage.getSumY_Xpow(2);

        det = countDet(A1, A2, A3, B1, B2, B3, C1, C2, C3);
        det0 = countDet(Y1, A2, A3, Y2, B2, B3, Y3, C2, C3);
        det1 = countDet(A1, Y1, A3, B1, Y2, B3, C1, Y3, C3);
        det2 = countDet(A1, A2, Y1, B1, B2, Y2, C1, C2, Y3);

        a0 = det0 / det;
        a1 = det1 / det;
        a2 = det2 / det;

        ArrayList<Double> arr = new ArrayList<>();
        arr.add(a0);
        arr.add(a1);
        arr.add(a2);

        return arr;
    }

    public static double countDet(double A1, double A2, double B1, double B2){
        return (A1 * B2) - (A2 * B1);
    }

    /*public static double countDet(double A1, double A2, double A3,
                           double B1, double B2, double B3,
                           double C1, double C2, double C3){
        return (A1 * countDet(B2, B3, C2, C2)) - (A2 * countDet(B1, B3, C1, C3)) + (A3 * countDet(B1, B2, C1, C2));
    } //*/

    public static double countDet(double A1, double A2, double A3,
                                  double B1, double B2, double B3,
                                  double C1, double C2, double C3){
        return (A1 * B2 * C3) + (B1 * C2 * A3) + (A2 * B3 * C1) -
                (A3 * B2 * C1) - (A1 * C2 * B3) - (C3 * B1 * A2);
    }
}
