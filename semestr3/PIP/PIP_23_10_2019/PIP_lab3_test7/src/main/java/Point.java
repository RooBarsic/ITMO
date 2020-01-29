import org.jetbrains.annotations.Contract;

import javax.persistence.Entity;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.persistence.*;
import java.io.Serializable;

//@Entity
//@Table(name = "point")
public class Point {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    @Column(name = "id", nullable = false)
    private int id;
    @Column(name = "valuex", nullable = false)
    private double valueX;
    @Column(name = "valuey", nullable = false)
    private double valueY;
    @Column(name = "valuer", nullable = false)
    private double valueR;
    @Column(name = "ok", nullable = false)
    private boolean ok;

    public Point(double valueX, double valueY, double valueR, boolean ok){
        this.valueX = valueX;
        this.valueY = valueY;
        this.valueR = valueR;
        this.ok = ok;
    }

    public double getValueR() {
        return valueR;
    }

    public double getValueX() {
        return valueX;
    }

    public double getValueY() {
        return valueY;
    }

    public void setValueR(double valueR) {
        this.valueR = valueR;
    }

    public void setValueY(double valueY) {
        this.valueY = valueY;
    }

    public void setValueX(double valueX) {
        this.valueX = valueX;
    }

    public String getOk() {
        if (this.ok) return "true";
        return  "false";
    }

    public void setOk(boolean ok) {
        this.ok = ok;
    }

    public Point(){}
}
