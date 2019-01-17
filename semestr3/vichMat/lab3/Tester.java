import javax.xml.crypto.Data;
import java.io.PrintWriter;
import java.util.Scanner;

public class Tester {
    private static PrintWriter printWriter = new PrintWriter(System.out);

    public static void start_test(){
        DataSet dataSet = new DataSet();
        Scanner scanner = new Scanner(System.in);

        MyLog.println(printWriter, " We are going to test our solvers. ");
        MyLog.println(printWriter," Input Data ");
       /*
        MyLog.print(printWriter, " x = ");
        double x = scanner.nextDouble();
        dataSet.inputData(printWriter);

        testLinerSolver(dataSet, x);
        testSquareSolver(dataSet, x);
        testLagranzSolver(dataSet, x);
       //*/
        //testNewtonNonEqualSolver();
        testNewtonEqual_frontSolver();
        testNewtonEqual_backSolver();
    }

    public static void testLinerSolver(DataSet dataSet, double x){
        MyLog.println(printWriter, " Test Liner Solver ");
        double y = Solvers.linerSolver(dataSet, x);
        MyLog.println(printWriter, " y( " + x + " ) = " + y + "\n");
    }

    public static void testSquareSolver(DataSet dataSet, double x){
        MyLog.println(printWriter, " Test Square Solver");
        double y = Solvers.squareSolver(dataSet, x);
        MyLog.println(printWriter, " y( " + x + " ) = " + y + "\n");
    }

    public static void testLagranzSolver(DataSet dataSet, double x){
        MyLog.println(printWriter, " Test Lagranz Solver ");
        double y = Solvers.lagranzSolver(dataSet, x);
        MyLog.println(printWriter, " y( " + x + " ) = " + y + "\n");
    }

    public static void testNewtonNonEqualSolver(){
        MyLog.println(printWriter, " Test Newton non equal Solver ");
        DataSet dataSet = new DataSet();
        Scanner scanner = new Scanner(System.in);

        MyLog.println(printWriter," Input Data ");
        MyLog.print(printWriter, " x = ");
        double x = scanner.nextDouble();
        dataSet.inputData(printWriter);

        double y = Solvers.NewtonForNotEqual(dataSet, x);

        MyLog.println(printWriter, " y( " + x + " ) = " + y + "\n");
    }

    public static void testNewtonEqual_frontSolver(){
        MyLog.println(printWriter, " Test Newton equal Solver extrapolirovanie vpered");
        DataSet dataSet = new DataSet();
        Scanner scanner = new Scanner(System.in);

        MyLog.println(printWriter," Input Data ");
        MyLog.print(printWriter, " x = ");
        double x = scanner.nextDouble();
        dataSet.inputData(printWriter);

        double y = Solvers.NewtonForEqual_front(dataSet, x);

        MyLog.println(printWriter, " y( " + x + " ) = " + y + "\n");
    }

    public static void testNewtonEqual_backSolver(){
        MyLog.println(printWriter, " Test Newton equal Solver extrapolirovanie nazad");
        DataSet dataSet = new DataSet();
        Scanner scanner = new Scanner(System.in);

        MyLog.println(printWriter," Input Data ");
        MyLog.print(printWriter, " x = ");
        double x = scanner.nextDouble();
        dataSet.inputData(printWriter);

        double y = Solvers.NewtonForEqual_back(dataSet, x);

        MyLog.println(printWriter, " y( " + x + " ) = " + y + "\n");
    }

}