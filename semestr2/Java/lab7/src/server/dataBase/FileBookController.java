package server.dataBase;

import common.bookComponents.Book;
import com.google.gson.Gson;

import java.io.*;
import java.util.List;
import java.util.Scanner;

public class FileBookController {
    private String fileName;
    private boolean flag;

    FileBookController(String fileName){
        this.fileName = fileName;
    }

    public void readBooks(){
        try (Scanner scanner = new Scanner(new File(fileName))){
            int kol = scanner.nextInt();
            //new MessageFrame("Reading in progress...");
            Gson json = new Gson();
            for(int i = 1; i <= kol; i++){
                String jsonBook = scanner.next();
                Book book = json.fromJson(jsonBook, Book.class);
                DataLog.addBook(book);
            }
            scanner.close();
        } catch (Exception e) {
            flag = false;
            e.printStackTrace();
        }
    }

    public void saveBooks(){
        try (PrintWriter printWriter = new PrintWriter(new File(fileName))){
            //new MessageFrame("Saving in progress...");
            List<Book> books = DataLog.getBooks();
            int numberOfBooks = books.size();
            printWriter.println(numberOfBooks);
            printWriter.flush();
            if(numberOfBooks == 0) return;
            Gson json = new Gson();
            String jsonBook;
            for(Book book : books){
                jsonBook = json.toJson(book);
                printWriter.println(jsonBook);

            }
            flag = true;
            printWriter.close();
        } catch (Exception e) {
            flag = false;
            e.printStackTrace();
        }
    }
}
