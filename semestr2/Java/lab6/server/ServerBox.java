package server;

import com.google.gson.Gson;
import common.Book;

public class ServerBox {
    private String message;
    private int commandType;
    private String key;
    private Book book;
    private boolean flag;

    ServerBox(String message){
        try {
            Gson json = new Gson();
            this.message = message;
            commandType = Integer.parseInt(String.valueOf(message.charAt(0)));
            if(commandType == 3) key = message.substring(1, message.length());
            else book = json.fromJson(message.substring(1, message.length()), Book.class);
            flag = true;
        }
        catch (Exception e){
            flag = false;
        }
    }

    public boolean isFlag() {
        return flag;
    }

    public int getCommandType() {
        return commandType;
    }

    public Book getBook() {
        return book;
    }

    public String getKey() {
        return key;
    }
}
