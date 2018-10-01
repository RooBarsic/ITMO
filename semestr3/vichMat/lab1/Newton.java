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

        double a2 = a * 2;
        double b2 = b * 1;
        PolynomX polynomX1 =  new PolynomX(1, new double[]{b, a});


        if(polynom.getFx(left) * polynomX1.getFx(left) > 0) root = left;
        else if(polynom.getFx(right) * polynomX1.getFx(right) > 0) root = right;
        else root = (left + right) / 2.0;

        while (true){
            numberOfIteration++;
            double root2 = root - (polynom.getFx(root) / polynomX2.getFx(root));
            if((root2 < left) || (right < root2)) root2 = (left + right) / 2.0;
            if(abs(root - root2) < eps){
                root = root2;
                break;
            }
            root = root2;
        }
        return root;
    }
}
