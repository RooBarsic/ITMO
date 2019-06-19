package myClasses;

public class PointBean {
    private double x, y, r;
    private String result;
    private int timeToWork;

    public PointBean(double x, double y, double r, String result){
        this.x = x;
        this.y = y;
        this.r = r;
        this.result = result;
    }

    public PointBean(double x, double y, double r, int timeToWork, String result){
        this.x = x;
        this.y = y;
        this.r = r;
        this.timeToWork = timeToWork;
        this.result = result;
    }

    public double getX(){
        return x;
    }

    public double getR() {
        return r;
    }

    public double getY() {
        return y;
    }

    public String getResult() {
        return result;
    }

    public int getTimeToWork() {
        return timeToWork;
    }

    public void setTimeToWork(int timeToWork){
        this.timeToWork = timeToWork;
    }
}

