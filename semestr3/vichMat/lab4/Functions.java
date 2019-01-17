public class Functions {

    public static double getFunc(int id, double x){
        double res = 0.;
        switch (id){
            case 1 : res = x; break;
            case 2 : res = x * x; break;
            case 3 : res = Math.cos(x + 3.) + 17.; break;
            case 4 : res = Math.pow(Math.E, x) - 17.; break;
        }
        return res;
    }

    public static String printFuncs(){
        return "f1(x) = x + 5.; f2(x) = x^2; f3(x) = cos(x + 3.) + 17.; f4(x) = e^x - 17.;";
    }
}
