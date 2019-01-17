import java.io.File;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class DataSet {
    public ArrayList<Double> xrr;
    public ArrayList<Double> yrr;
    public double x0;

    DataSet() {
        xrr = new ArrayList<>();
        yrr = new ArrayList<>();
    }

    private void input(Scanner scanner){
        int n = scanner.nextInt();
        for(int i = 1; i <= n; i++){
            Double x = scanner.nextDouble();
            Double y = scanner.nextDouble();

            xrr.add(x);
            yrr.add(y);
        }

        order();
    }

    public void inputData(PrintWriter printWriter){
        Scanner scanner = new Scanner(System.in);
        MyLog.print(printWriter, " x = ");
        x0 = scanner.nextDouble();
        MyLog.print(printWriter, "n = ");

        input(scanner);
    }

    public void inputData(String fileName){
        try(Scanner scanner = new Scanner(new File(fileName))) {
            x0 = scanner.nextDouble();
            input(scanner);
        }
        catch (Exception e){ }
    }

    public void order(){
        for(int i = 0; i < xrr.size(); i++){
            for(int j = i + 1; j < xrr.size(); j++){
                if(xrr.get(i) > xrr.get(i)){
                    double a = xrr.get(i);
                    xrr.set(i, xrr.get(j));
                    xrr.set(j, a);

                    a = yrr.get(i);
                    yrr.set(i, yrr.get(j));
                    yrr.set(j, a);

                }
            }
        }
    }

    public DataSet copy(){
        DataSet dataSet = new DataSet();
        for(int i = 0; i < xrr.size(); i++){
            dataSet.xrr.add(xrr.get(i));
            dataSet.yrr.add(yrr.get(i));
        }
        return dataSet;
    }
}
