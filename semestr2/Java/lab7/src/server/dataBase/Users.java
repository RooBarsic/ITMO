package server.dataBase;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Users {
    private Map<String, String> users;
    private ArrayList<String > usersInfo;

    Users(){
        usersInfo = new ArrayList<>();
        users = new HashMap<>();
    }

    public boolean checkUser(String login, String password){
        String user = users.get(login);
        if(user == null) return false;
        if(user.equals(password)) return true;
        return false;

    }

    public int addNewUser(String login, String password){
        String user = users.get(login);
        if((login == null) || (password == null)) return 2; // wrong username or password
        if(user != null) return 0;                          // username olready exist
        users.put(login, password);                         // done
        usersInfo.add(login);
        usersInfo.add(password);
        DataLog.saveNewUser(login, password);
        return 1;
    }

    public ArrayList<String > getUsersInfo(){
        return usersInfo;
    }
}
