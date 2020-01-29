import javax.annotation.ManagedBean;
import javax.ejb.EJB;
import javax.inject.Inject;
import javax.validation.constraints.NotNull;
import java.io.PrintWriter;

public class PointController {
    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    private String userName;
    private double x;
    private double y;
    private double r;
    private String result;
    private long timeToWork;
    private DBConnector dbConnector = new DBConnector();

    public PointController(){
        this.userName = "Guest";
        this.x = 0;
        this.y = 0;
        this.r = 0;
        this.result = "False";
        this.timeToWork = -1;
    }


    public PointController(double x, double y, double r, String result){
        this.x = x;
        this.y = y;
        this.r = r;
        this.result = result;
    }

    public PointController(double x, double y, double r, int timeToWork, String result){
        this.x = x;
        this.y = y;
        this.r = r;
        this.timeToWork = timeToWork;
        this.result = result;
    }


    public double getR() {
        return r;
    }

    public void setR(double r) {

        this.r = r;
    }

    public void setR(@NotNull String r){

        this.r = Double.parseDouble(r);
    }

    public double getY() {
        return y;
    }

    public void setY(double y) {

        this.y = y;
    }

    public double getX() {
        return x;
    }

    public void setX(double x) {

        this.x = x;
    }

    public void printMyPoint(){
        System.out.println(" Printing :::  x = " + x + " y = " + y + " r = " + r + " ------------");
    }

    public String getResult() {
        return result;
    }

    public void setResult(String result) {
        this.result = result;
    }

    public long getTimeToWork() {
        return timeToWork;
    }

    public void setTimeToWork(long timeToWork) {
        this.timeToWork = timeToWork;
    }

    public void savePoint(){
        printMyPoint();
        System.out.println(" start saving ");
        if((userName != null) && (!userName.equals(""))){
            long startTime = System.currentTimeMillis() ;//System.currentTimeMillis();
                System.out.println(" normal 1");

                if ((0 <= x) && (x <= r)) {
                    if ((0 <= y) && (y <= r))
                        result = "Yes";
                    else if ((y <= 0) && (y >= (-r / 2.) + (x / 2.)))
                        result = "Yes";
                    else
                        result = "No";
                } else if ((Math.sqrt((x * x) + (y * y)) * 2. <= r) && (-r / 2. <= x) && (x <= 0) && (0 <= y) && (y <= r / 2.)){
                    result = "Yes";
                }
                else
                    result = "No";

                timeToWork = (System.currentTimeMillis() - startTime);

                dbConnector.initDb();
            dbConnector.saveResult(userName, x, y, r, result, timeToWork);
            System.out.println(" ---- savin to DB is OK    userName = " + userName);
        }
    }
}

//background-image: url("https://images4.alphacoders.com/758/thumb-1920-75844.jpg");
