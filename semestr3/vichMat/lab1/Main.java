import java.awt.*;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        InOut multiScanner = new InOut("Result.txt");
        multiScanner.println("Hello User!");
        multiScanner.println("We are going to solve ax^3 + bx^2 + cx + d = 0");
        multiScanner.println(" I should read polynome parameters from file or from console ? ( file/console )");
        String fileOrConsole = multiScanner.getString();
        while((!fileOrConsole.equals("file")) && (!fileOrConsole.equals("console"))){
            multiScanner.println("I can't understand you :( ");
            multiScanner.println(" I should read polynome parameters from file or from console ? ( file/console )");
            multiScanner.println(" As answer - please write file or console.");
            fileOrConsole = multiScanner.getString();
        }

        // Getting polynome parameters --------------------------------------------------------------
        double a, b, c, d;
        if(fileOrConsole.equals("console")) {
            multiScanner.println("Write polynom parameters : ");
            multiScanner.print("Write a : ");
            a = multiScanner.getDouble();
            multiScanner.print("Write b : ");
            b = multiScanner.getDouble();
            multiScanner.print("Write c : ");
            c = multiScanner.getDouble();
            multiScanner.print("Write d : ");
            d = multiScanner.getDouble();
            multiScanner.print("We are going to worke with polynom : ");
            multiScanner.print(a);
            multiScanner.print("x^3");
            if(b >= 0) multiScanner.print(" + ");
            multiScanner.print(b);
            multiScanner.print("x^2");
            if(c >= 0) multiScanner.print(" + ");
            multiScanner.print(c);
            multiScanner.print("x");
            if(d >= 0) multiScanner.print(" + ");
            multiScanner.println(d);
        }
        else {
            multiScanner.println("Please, write file name : ");
            String fileName = multiScanner.getString();
            while(MyLog.checkFile(fileName) == false){
                multiScanner.println("File " + fileName + " is incorrect. Please check this file and try again.");
                multiScanner.println("Please, write file name : ");
                fileName = multiScanner.getString();
            }
            a = MyLog.a;
            b = MyLog.b;
            c = MyLog.c;
            d = MyLog.d;
            multiScanner.print("We are going to worke with polynom : ");
            multiScanner.print(a);
            multiScanner.print("x^3");
            if(b >= 0) multiScanner.print(" + ");
            multiScanner.print(b);
            multiScanner.print("x^2");
            if(c >= 0) multiScanner.print(" + ");
            multiScanner.print(c);
            multiScanner.print("x");
            if(d >= 0) multiScanner.print(" + ");
            multiScanner.println(d);
        }

        // Building Polynom ------------------------------------------------------------------------
        multiScanner.println(" Make polynom. ");
        String mask = Double.toString(a) + "x%5E3%2B" + Double.toString(b);
        mask += "x%5E2%2B" + Double.toString(c) + "x%2B" + Double.toString(d);
        try {
            Desktop des = Desktop.getDesktop();
            des.browse(new URI("http://www.wolframalpha.com/input/?i=plot+" + mask));
        } catch (IOException | URISyntaxException e2) {
            // e2.printStackTrace();
        }
// -2,7x^3 - 1,48x^2 + 19,23x + 6,35
        PolynomX polynom = new PolynomX(3, new double[]{d, c, b, a});

        multiScanner.print("Write solution parameter, eps :");
        double eps = multiScanner.getDouble();

        while (true){
            multiScanner.println(" Do you want to find roots ? ( yes/no ) ");
            String userAnswer = multiScanner.getString();
            if(userAnswer.equals("yes")){
                multiScanner.println("Write root interval : ");
                multiScanner.print("Left interval : ");
                double left = multiScanner.getDouble();
                multiScanner.print("Right interval : ");
                double right = multiScanner.getDouble();

                if(!polynom.checkRootInterval(left, right)) {
                    multiScanner.println("Wrong interval. Please write another interval. ");
                    continue;
                }
                multiScanner.println("Which metod do you prefer, Dividing or Newton ?");
                String metod = multiScanner.getString();

                if(metod.equals("Dividing")){
                    FindingRootAlgorithm algo = new BinSearch(polynom);
                    algo.findRootInRange(left, right, eps);
                    multiScanner.println(" Root x = " + algo.getRoot());
                    multiScanner.print("F(x) = ");
                    multiScanner.printlnD7(polynom.getFx(algo.getRoot()));
                    multiScanner.println(" Number of iteration = " + algo.getNumberOfIteration());
                }
                else if(metod.equals("Newton")){
                    FindingRootAlgorithm algo = new Newton(polynom);
                    algo.findRootInRange(left, right, eps);
                    multiScanner.println(" Root x = " + algo.getRoot());
                    multiScanner.print("F(x) = ");
                    multiScanner.printlnD7(polynom.getFx(algo.getRoot()));
                    multiScanner.println(" Number of iteration = " +  algo.getNumberOfIteration());
                }
                else {
                    multiScanner.println(" I can't understand what you mean. Please Write Dividing or Newton!");
                }
            }
            else if(userAnswer.equals("no")) break;
            else multiScanner.println("Wrong answer!");
        }
        multiScanner.println("Bye.");
    }
}
/*
1,0
2,84
-5,606
-14,766
0,0000001
yes
0,0 5,0
 */
