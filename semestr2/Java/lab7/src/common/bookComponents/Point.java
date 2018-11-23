package common.bookComponents;

import java.io.Serializable;

public class Point implements Serializable {
    private int x;
    private int y;
    public Point(int x, int y){
        this.x = x;
        this.y = y;
    }

    public int getX(){
        return x;
    }

    public int getY(){
        return y;
    }

    public long get_rast_kv(Point b){
        return ((x - b.x) * (x - b.x)) + ((y - b.y) * (y - b.y));
    }

    public long get_rast_kv(int bx, int by){
        return ((x - bx) * (x - bx)) + ((y - by) * (y - by));
    }

    long compareTo(Point b){
        return (this.get_rast_kv(0, 0) - b.get_rast_kv(0, 0));
    }
}