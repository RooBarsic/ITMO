class PolynomX {
    private int n;
    private double[] koef;

    PolynomX(int n, double args[]){
        this.n = n;
        koef = args;
    }

    double getFx(double x){
        double result = koef[0];
        double xpow = 1.;
        for(int i = 1; i <= n; i++){
            xpow *= x;
            result += xpow * koef[i];
        }
        return result;
    }

    public double getKoef(int id){
        if((0 <= id) && (id <= n)) return koef[id];
        return 0;
    }

    boolean checkRootInterval(double left, double right){
        if(right < left) return false;
        double A = getFx(left);
        double B = getFx(right);
        if(((A > 0) && (B > 0)) || ((A < 0) && (B < 0))) return false;
        return true;
    }

}
