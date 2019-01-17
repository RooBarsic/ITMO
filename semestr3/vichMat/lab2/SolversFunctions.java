import functions.*;

import java.util.ArrayList;

public class SolversFunctions {


    public static Function get_PolinomialFunction_1(InputSotage inputSotage){
        return new PolinomFunction(EquationSolvers.solve1(inputSotage));
    }

    public static Function get_PolinomialFunction_2(InputSotage inputSotage){
        return new PolinomFunction(EquationSolvers.solve2(inputSotage));
    }

    public static Function get_PowerFunction(InputSotage inputSotage){
        InputSotage storage = new InputSotage();

        for(int i = 0; i < inputSotage.size(); i++){
            double x = inputSotage.xrr.get(i);
            x = Math.log(x);
            storage.xrr.add(x);
            double y = inputSotage.yrr.get(i);
            y = Math.log(y);
            storage.yrr.add(y);
        }

        ArrayList< Double> arr = EquationSolvers.solve1(storage);

        return new PowerFunction(Math.pow(Math.E, arr.get(0)), arr.get(1));
    }

    public static Function get_ExponentialFunction(InputSotage inputSotage){
        InputSotage storage = new InputSotage();

        for(int i = 0; i < inputSotage.size(); i++){
            storage.xrr.add(inputSotage.xrr.get(i));
            double y = inputSotage.yrr.get(i);
            y = Math.log(y);
            storage.yrr.add(y);
        }

        ArrayList< Double > arr = EquationSolvers.solve1(storage);

        return new ExponentialFunction(Math.pow(Math.E, arr.get(0)), arr.get(1));
    }

    public static Function get_LogarithmicFunction(InputSotage inputSotage){
        InputSotage storage = new InputSotage();

        for(int i = 0; i < inputSotage.size(); i++){
            storage.yrr.add(inputSotage.yrr.get(i));
            double x = inputSotage.xrr.get(i);
            x = Math.log(x);
            storage.xrr.add(x);
        }

        ArrayList< Double > arr = EquationSolvers.solve1(storage);

        return new LogarithmicFunction(arr.get(0), arr.get(1));
    }
}
