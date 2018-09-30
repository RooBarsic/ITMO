

public abstract class FindingRootAlgorithm {
    protected PolynomX polynom;
    protected double root;
    protected int numberOfIteration;

    FindingRootAlgorithm(PolynomX polynom){
        this.polynom = polynom;
    }

    public void findRootInRange(double left, double right, double eps){
        numberOfIteration = 0;
        if(polynom.checkRootInterval(left, right))
            root = findRoot(left, right, eps);
    }

    protected abstract double findRoot(double left, double right, double eps);

    public double getRoot(){
        return root;
    }

    public int getNumberOfIteration(){
        return numberOfIteration;
    }
}
