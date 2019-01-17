import java.io.PrintWriter;
import java.lang.management.MemoryUsage;
import java.util.Scanner;
import java.util.regex.MatchResult;

public class Main {

    public static void main(String[] args) {
        System.out.println("Hello. We are going to solve problems) ");
        MyLog.setParams();

        //Tester.start_test();
        solve();

        System.out.println(" Bye. Happy new year.");
    }

    public static double x0;
    public static DataSet dataSet;
    public static void solve(){
        PrintWriter printWriter = new PrintWriter(System.out);
        Scanner scanner = new Scanner(System.in);
        readInfo(scanner, printWriter);
        boolean flag = true;
        while(flag){
            MyLog.println(printWriter, "You can use this commands : #new_data " +
                    "#new_x #exit #liner #square #lagranz #Newton #Newton_front #Newton_back");
            MyLog.println(printWriter, "");
            MyLog.print(printWriter, "command : ");
            String command = scanner.next();
            switch (command){
                case "#new_data" : readInfo(scanner, printWriter);
                    break;
                case "#exit" : flag = false;
                    break;
                case "#new_x" : x0 = scanner.nextDouble();
                    break;
                case "#liner" : printResult(Solvers.linerSolver(dataSet, x0), printWriter);
                    break;
                case "#square" : printResult(Solvers.squareSolver(dataSet, x0), printWriter);
                    break;
                case "#lagranz" : printResult(Solvers.lagranzSolver(dataSet, x0), printWriter);
                    break;
                case "#Newton" : printResult(Solvers.NewtonForNotEqual(dataSet, x0), printWriter);
                    break;
                case "#Newton_front" : printResult(Solvers.NewtonForEqual_front(dataSet, x0), printWriter);
                    break;
                case "#Newton_back" : printResult(Solvers.NewtonForEqual_back(dataSet, x0), printWriter);
                    break;
                default: MyLog.println(printWriter, " I don't know this command. ");
            }
        }
        MyLog.println(printWriter, "bye... ");
    }

    public static void printResult(double y, PrintWriter printWriter){
        MyLog.print(printWriter, "y(x0) = ");
        MyLog.println(printWriter, y);
    }
    public static void readInfo(Scanner scanner, PrintWriter printWriter){
        MyLog.println(printWriter, "I would read data from file or from console ? ( file/console) ");
        String userAnswer = scanner.next();
        while(!((userAnswer.equals("file")) || (userAnswer.equals("console")))){
            MyLog.println(printWriter, "I can't understand you.(");
            MyLog.println(printWriter, "I would read data from file or from console ? ( file/console) ");
            userAnswer = scanner.next();
        }
        dataSet = new DataSet();
        if(userAnswer.equals("file")){
            MyLog.print(printWriter, "file name : ");
            String inputFileName = scanner.next();
            dataSet.inputData(inputFileName);
        }
        else {
            dataSet.inputData(printWriter);
        }
        x0 = dataSet.x0;
    }
}

/*

0,615  0,594

7
0,593 0,5320
0,598 0,5356
0,605 0,5406
0,613 0,5462
0,619 0,5504
0,627 0,5559
0,632 0,5594


0,512   0,751
7
0,50 1,5320
0,55 2,5356
0,60 3,5406
0,65 4,5462
0,70 5,5504
0,75 6,5559
0,80 7,5594

0,35
5
0,1   1,25
0,2   2,38
0,3   3,79
0,4   5,44
0,5   7,14


0,22
5
0,15   1,25
0,2    2,38
0,33   3,79
0,47   5,44
0,62   7,14
 */