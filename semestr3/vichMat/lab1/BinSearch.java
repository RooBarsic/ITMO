import static java.lang.Math.abs;

public class BinSearch extends FindingRootAlgorithm{

    BinSearch(PolynomX polynom) {
        super(polynom);
    }

    protected double findRoot(double left, double right, double eps){
        if(abs(polynom.getFx(left)) < eps) return left;
        if(abs(polynom.getFx(right)) < eps) return right;
        while(right - left >= eps){
            numberOfIteration++;

            double midle = (left + right) / 2.0;
            double A = polynom.getFx(left);
            double M = polynom.getFx(midle);

            if(abs(M) < eps) return midle;
            else if(((A < 0) && (0 < M)) || ((A > 0) && (0 > M))) right = midle;
            else left = midle;
        }
        return left;
    }
}
