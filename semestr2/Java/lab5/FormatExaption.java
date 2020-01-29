import java.security.SecureRandom;

public class FormatExaption extends IllegalArgumentException {
    FormatExaption(String info,String message){
        super(" in " + message + " - Error!! " + openString(info));
    }
    private static String openString(String s){
        String t = "";
        for(char x : s.toCharArray()){
            t += getClas(x);
        }
        return t;
    }
    private static String getClas(char e){
        switch (e){
            case 'i': return "int ";
            case 'l': return "Long ";
            case 'n': return "NULL ";
            default: return "? ";
        }
    }
}
