package testingBeans;

import java.util.List;

import javax.annotation.PostConstruct;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.bean.ViewScoped;
import java.io.Serializable;
import java.util.ArrayList;

public class MyString implements Serializable {
    private String myStr = "fala";
    private List<String> myList = new ArrayList<>();

    @PostConstruct
    public void init() {
        myList = new ArrayList<>();
    }

    public String getMyStr() {
        return myStr;
    }

    public void setMyStr(String myStr) {
        this.myStr = myStr;
    }

    public List<String> getMyList() {
        return myList;
    }

    public void setMyList(List<String> myList) {
        this.myList = myList;
    }

    public void addString(String str){
        myList.add(str);
    }
}
