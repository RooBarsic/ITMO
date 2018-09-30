import static java.lang.StrictMath.abs;

public class Newton extends FindingRootAlgorithm{

    Newton(PolynomX polynom) {
        super(polynom);
    }

    @Override
    protected double findRoot(double left, double right, double eps) {
        double a = polynom.getKoef(3) * 3.;
        double b = polynom.getKoef(2) * 2.;
        double c = polynom.getKoef(1);
        PolynomX polynomX2 = new PolynomX(2, new double[]{c, b, a});
        root = left;
        while (true){
            numberOfIteration++;
            //-2,7x^3 - 1,48x^2 + 19,23x + 6,35

            double root2 = root - (polynom.getFx(root) / polynomX2.getFx(root));
            if(abs(root - root2) < eps){
                root = root2;
                break;
            }
            root = root2;
        }
        return root;
    }
}
