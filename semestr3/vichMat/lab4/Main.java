import java.awt.print.Printable;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        PrintWriter printWriter = new PrintWriter(System.out);
        MyLog.println(printWriter, "Hello user!");
        solve(scanner, printWriter);
        MyLog.println(printWriter, "Bye. Happy new year.");
    }

    public static void solve(Scanner scanner, PrintWriter printWriter){
        boolean flag = true;
        while (flag){
            MyLog.println(printWriter, "We are going to work with : ");
            MyLog.println(printWriter, Functions.printFuncs());
            MyLog.println(printWriter, "Write function id : ");
            MyLog.print(printWriter, " function id = ");
            int functionId = scanner.nextInt();
            while(!((1 <= functionId) && (functionId <= 4))){
                MyLog.println(printWriter, "Wrong function id. Please choose one from 1 - 4.");
            }

            MyLog.println(printWriter, "Write interval of integration (A; B): ");
            MyLog.print(printWriter, " A = ");
            double a = scanner.nextDouble();
            MyLog.print(printWriter, " B = ");
            double b = scanner.nextDouble();

            MyLog.println(printWriter, "Choose one of ways to solve ");
            MyLog.println(printWriter, " Algorithms : rectanglesLeft(1), rectanglesRight(2), rectanglesMiddle(3), " +
                    "trapezoidMethod(4), SimpsonMethod(5)");
            MyLog.println(printWriter, " write algorithm number (1-5). ");
            int algorithmId = scanner.nextInt();
            while(!((1 <= algorithmId) || (algorithmId <= 5))){
                MyLog.println(printWriter, "Wrong number. Please write algorithm number, number in a range 1 - 5 . ");
                algorithmId = scanner.nextInt();
            }

            Solvers.solverGo(printWriter, algorithmId, functionId, a, b);

            MyLog.println(printWriter, " Dou you want continue ? ( yes/no ) ");
            String userAns = scanner.next();
            while(!((userAns.equals("yes")) || (userAns.equals("no")))){
                userAns = scanner.next();
            }
            if(userAns.equals("no")) flag = false;
        }
    }

}
