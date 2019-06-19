package myClasses;

import java.util.ArrayList;
import java.util.List;

public class PointsArray {
    private List<PointBean> pointBeanList;
    public PointsArray(){
        pointBeanList = new ArrayList<>();
    }

    public void addNewPointBean(PointBean pointBean){
        pointBeanList.add(pointBean);
    }

    public int getSize(){
        return pointBeanList.size();
    }

    public PointBean getItem(int id){
        if((0 <= id) && (id <= pointBeanList.size())) return pointBeanList.get(id);
        return null;
    }
}

