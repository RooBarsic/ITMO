package client;

import com.google.gson.Gson;
import com.sun.java.swing.plaf.windows.WindowsInternalFrameTitlePane;
import common.Book;

import java.util.Set;

public class JsonKeeper {
    private int numberOfOpenBrackets;
    private String json;
    private  int numderOfNotNull;
    JsonKeeper(){
        json = "";
        numberOfOpenBrackets = 0;
        numderOfNotNull = 0;
    }

    void addNewString(String s){
        String newPart = s;
        for(int i = 0; i < s.length(); i++){
            if((s.charAt(i) != '}') && (s.charAt(i) != '{') && (s.charAt(i) != ' '))
                numderOfNotNull++;
            if(s.charAt(i) == '}'){
                numberOfOpenBrackets--;
                if(numberOfOpenBrackets == 0){
                    newPart = s.substring(0, i + 1);
                    break;
                }
            }
            else if(s.charAt(i) == '{'){
                numberOfOpenBrackets++;
            }
        }
        json += newPart;
    }

    public boolean haveJson(){
        if((json.length() > 0) && (numberOfOpenBrackets == 0)) return true;
        return false;
    }

    public Book getBookFromJson(){
        if(numderOfNotNull == 0) return null;
        try {
            Gson gson = new Gson();
            Book book = gson.fromJson(json, Book.class);
            System.out.println(book.toString());
            return book;
        } catch (Exception e){
            return null;
        }
    }
}
