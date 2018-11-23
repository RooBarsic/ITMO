package server.dataBase;

import java.io.*;
import java.util.List;
import java.util.Scanner;

public class FileUsersController {
    private String fileName;
    private boolean flag;

    FileUsersController(String fileName){
        this.fileName = fileName;
    }

    public void readUsers(){
        try (Scanner scanner = new Scanner(new File(fileName))){
            while (scanner.hasNext()){
                String userName = scanner.next();
                String userPassword = scanner.next();
                DataLog.addNewUser(userName, userPassword);
            }
        } catch (Exception e) {
            flag = false;
            e.printStackTrace();
        }
    }

    public void saveNewUser(String userLogin, String userPassword){
        try(FileWriter sw = new FileWriter(fileName,true)){
            sw.write(userLogin + " " + userPassword + "\n");
            sw.close();
        }catch(Exception e){
            //System.out.print(e.getMessage());
        }
    }

    public void saveUsers(){
        try (PrintWriter printWriter = new PrintWriter(new File(fileName))){
            //new MessageFrame("Saving in progress...");
            List<String> users = DataLog.getUsersInfo();
            if(users.size() == 0) return;
            for(int i = 0; i < users.size(); i += 2){
                printWriter.println(users.get(i) + " " + users.get(i + 1));
            }
            flag = true;
            printWriter.close();
        } catch (Exception e) {
            flag = false;
            e.printStackTrace();
        }
    }
}
