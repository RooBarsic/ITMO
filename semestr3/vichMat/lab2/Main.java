import functions.*;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        System.out.println("Hello User. We are going to work now.");

        //System.out.println(Math.E);
        //MyLog.setOutFile();
        //solve();

        TestTaskJava.testIt();

        /*Function function = new ExponentialFunction(2.123, 3.456);
        function.printFunction(new PrintWriter(System.out));

        function = new LogarithmicFunction(2.123, 3.456);
        function.printFunction(new PrintWriter(System.out));

        function = new PolinomFunction(2, new double[]{2.123, 4.245});
        function.printFunction(new PrintWriter(System.out));

        function = new PolinomFunction(3, new double[]{2.123, 3.456, 4,4554});
        function.printFunction(new PrintWriter(System.out));

        function = new PowerFunction(2.123, 3.456);
        function.printFunction(new PrintWriter(System.out));*/
//dodo();
        System.out.println("\n Bye.");
    }

    public static void dodo(){
        Scanner scanner = null;
        PrintWriter printWrite = null;
        try {
            scanner = new Scanner(new File("test.txt"));
            printWrite = new PrintWriter(new File("rtest.txt"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        int n = scanner.nextInt();
        System.out.println(" n = " + n);
        double[] xrr = new double[n], yrr = new double[n];
        for(int i = 0; i < n; i++){
            xrr[i] = scanner.nextDouble();
        }
        for(int i = 0; i < n; i++){
            yrr[i] = scanner.nextDouble();
        }

        printWrite.println(n);
        printWrite.flush();
        for(int i = 0; i < n; i++){
            printWrite.println(xrr[i] + " " + yrr[i]);
            printWrite.flush();

        }
        printWrite.flush();
    }

    public static void solve(){
        InputSotage inputSotage = new InputSotage();
        Scanner scanner = new Scanner(System.in);
        PrintWriter printer = new PrintWriter(System.out);

        MyLog.println(printer, "I should get data from console or from file ?");
        String userAnswer1 = scanner.next();
        while((!userAnswer1.equals("console")) && (!userAnswer1.equals("file"))){
            MyLog.println(printer, "I can't understand you answer! ");
            MyLog.println(printer, "So I should get data from console or from file ?");
            userAnswer1 = scanner.next();
        }

        if(userAnswer1.equals("file")){
            MyLog.println(printer, "Write file name");
            String fileName = scanner.next();
            if(MyLog.checkFile(fileName)) inputSotage.getData(fileName);
            else {
                MyLog.println(printer, "Wrong file or file data!");
            }
        }
        else inputSotage.getData();

        // solving ------------------------------------------------------
        Function polinom_1 = SolversFunctions.get_PolinomialFunction_1(inputSotage);
        Function polinom_2 = SolversFunctions.get_PolinomialFunction_2(inputSotage);
        Function power_func = SolversFunctions.get_PowerFunction(inputSotage);
        Function exp_func = SolversFunctions.get_ExponentialFunction(inputSotage);
        Function log_func = SolversFunctions.get_LogarithmicFunction(inputSotage);

        //*
        polinom_1.printFunction(printer);
        MyLog.print(printer, "S = ");
        MyLog.println(printer, polinom_1.calcS(inputSotage));
        MyLog.print(printer, "SquareEror = ");
        MyLog.println(printer, polinom_1.calcSquareEror(inputSotage));
        MyLog.println(printer, "");

        polinom_2.printFunction(printer);
        MyLog.print(printer, "S = ");
        MyLog.println(printer, polinom_2.calcS(inputSotage));
        MyLog.print(printer, "SquareEror = ");
        MyLog.println(printer, polinom_2.calcSquareEror(inputSotage));
        MyLog.println(printer, "");

        power_func.printFunction(printer);
        MyLog.print(printer, "S = ");
        MyLog.println(printer, power_func.calcS(inputSotage));
        MyLog.print(printer, "SquareEror = ");
        MyLog.println(printer, power_func.calcSquareEror(inputSotage));
        MyLog.println(printer, "");

        exp_func.printFunction(printer);
        MyLog.print(printer, "S = ");
        MyLog.println(printer, exp_func.calcS(inputSotage));
        MyLog.print(printer, "SquareEror = ");
        MyLog.println(printer, exp_func.calcSquareEror(inputSotage));
        MyLog.println(printer, "");

        log_func.printFunction(printer);
        MyLog.print(printer, "S = ");
        MyLog.println(printer, log_func.calcS(inputSotage));
        MyLog.print(printer, "SquareEror = ");
        MyLog.println(printer, log_func.calcSquareEror(inputSotage));
        MyLog.println(printer, "");

        //*/
    }
}
