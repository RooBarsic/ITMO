import java.awt.*;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        System.out.println("Hello User!");
        System.out.println("We are going to solve ax^3 + bx^2 + cx + d = 0");
        System.out.println("Write polynom parameters : ");

        System.out.print("Write a : ");
        double a = scanner.nextDouble();
        System.out.print("Write b : ");
        double b = scanner.nextDouble();
        System.out.print("Write c : ");
        double c = scanner.nextDouble();
        System.out.print("Write d : ");
        double d = scanner.nextDouble();
        System.out.println(" Make polynom. ");

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

        System.out.print("Write solution parameter, eps :");
        double eps = scanner.nextDouble();

        while (true){
            System.out.println(" Do you want to find roots ? ( yes/no ) ");
            String userAnswer = scanner.next();
            if(userAnswer.equals("yes")){
                System.out.println("Write root interval : ");
                System.out.print("Left interval : ");
                double left = scanner.nextDouble();
                System.out.print("Right interval : ");
                double right = scanner.nextDouble();

                if(!polynom.checkRootInterval(left, right))
                    System.out.println("Wrong interval. Please write another interval. ");

                System.out.println("Which metod do you prefer, Dividing or Newton ?");
                String metod = scanner.next();

                if(metod.equals("Dividing")){
                    FindingRootAlgorithm algo = new BinSearch(polynom);
                    algo.findRootInRange(left, right, eps);
                    System.out.println(" Root x = " + algo.getRoot());
                    System.out.println(" Number of iteration = " + algo.getNumberOfIteration());
                }
                else if(metod.equals("Newton")){
                    FindingRootAlgorithm algo = new Newton(polynom);
                    algo.findRootInRange(left, right, eps);
                    System.out.println(" Root x = " + algo.getRoot());
                    System.out.println(" Number of iteration = " +  algo.getNumberOfIteration());
                }
                else {
                    System.out.println(" I can't understand what you mean. Please Write Dividing or Newton!");
                }
            }
            else if(userAnswer.equals("no")) break;
            else System.out.println("Wrong answer!");
        }
        System.out.println("Bye.");
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
