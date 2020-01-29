import java.io.Serializable;

public class HelloController implements Serializable {
    private String mesage;

    public String sayHello(){
        return "Hello " + mesage;
    }

    public String getMesage() {
        return mesage;
    }

    public void setMesage(String mesage) {
        this.mesage = mesage;
    }
}
