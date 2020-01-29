package client;

import com.google.gson.Gson;
import common.Book;
import common.Janrs;
import common.Point;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class FileController {

    public class GetBookFromCSV{
        private String csv;
        private int pos = 0;

        GetBookFromCSV(String csv){
            this.csv = csv;
            //System.out.println(" csv = " + csv);
        }

        public String getString(){
            if(pos >= csv.length()) return null;
            int l = pos;
            while ((pos < csv.length()) && (csv.charAt(pos) != '#')){
                pos++;
            }
            String result = csv.substring(l, pos);
            pos++;
            //System.out.println(" csv getString result = " + result);
            return result;
        }

        public String getInt(){
            if(pos > csv.length()) return null;
            int l = pos;
            while ((pos < csv.length()) && (csv.charAt(pos) != '#') &&
                    ('0' <= csv.charAt(pos)) && (csv.charAt(pos) <= '9')){
                pos++;
            }
            if((pos < csv.length()) && (csv.charAt(pos) != '#')) return null;
            String result = csv.substring(l, pos);
            pos++;
            return result;
        }
    }

    private String fileName;
    private boolean flag;
    private ArrayList<Book> books;

    FileController(String fileName){
        this.fileName = fileName;
        books = new ArrayList<>();
        try (Scanner scanner = new Scanner(new File(fileName))){
            while(scanner.hasNextLine()){
                String bobok = scanner.nextLine();
                System.out.println(bobok);
                GetBookFromCSV csv = new GetBookFromCSV(bobok);

                String bookName = csv.getString();
                String bookJanr = csv.getString();
                String X_cordinate = csv.getInt();
                String Y_cordinate = csv.getInt();
                String creatingTime = csv.getInt();
                String kol = csv.getInt();
                System.out.println(bookName + " " + bookJanr + " " + X_cordinate + " " + Y_cordinate + " "
                        + creatingTime + " " + kol);
                if((bookName == null) || (bookJanr == null) || (X_cordinate == null) ||
                        (Y_cordinate == null) || (kol == null)){
                    flag = false;
                    System.out.println( " Error 1 ");
                    return;
                }
                int numberOfWords = Integer.parseInt(kol);
                if(numberOfWords <= 0){
                    flag = false;
                    System.out.println( " Error 2 ");
                    return;
                }
                String [] words = new String[numberOfWords];
                for(int i = 0; i < numberOfWords; i++){
                    String word = csv.getString();
                    if(word == null){
                        System.out.println( " Error 3 ");
                        flag = false;
                        return;
                    }
                    words[i] = word;
                }
                Book book = new Book(bookName, Janrs.valueOf(bookJanr),
                        new Point(Integer.parseInt(X_cordinate), Integer.parseInt(Y_cordinate)),
                        Integer.parseInt(creatingTime), numberOfWords, words);
                books.add(book);
                Gson json = new Gson();
                System.out.println(" json = " + json.toJson(book, Book.class));
            }
            flag = true;
            scanner.close();
        } catch (FileNotFoundException e) {
            flag = false;
            e.printStackTrace();
        }
    }

    public boolean isFlag() {
        return flag;
    }

    public ArrayList<Book> getBooks(){
        return books;
    }

    public void printeBooksToFile(List< Book > books){
        try(FileOutputStream out=new FileOutputStream(fileName);
            BufferedOutputStream outt = new BufferedOutputStream(out)){
            byte[] buffer;
            for(Book iter : books){
                String outString = "";
                outString += iter.getName() + "#";
                outString += iter.getJanr().name() + "#";
                outString += Integer.toString(iter.getBookCoordinates().getX()) + "#";
                outString += Integer.toString(iter.getBookCoordinates().getY()) + "#";
                outString += Long.toString(iter.getCreatingTime()) + "#";
                outString += Integer.toString(iter.getNumberOfWords()) + "#";
                for(int i = 0; i < iter.getNumberOfWords(); i++){
                    outString += iter.getWordX(i);
                    if(i + 1 != iter.getNumberOfWords()) outString += "#";
                }

                buffer = (outString).getBytes();
                outt.write(buffer, 0, buffer.length);
                outt.write("\n".getBytes());
            }
            outt.close();
            out.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


/**
 * try(FileOutputStream out=new FileOutputStream(fileName);
 *             BufferedOutputStream outt = new BufferedOutputStream(out))
 *         {
 *             max(1, 2);
 *             byte[] buffer;
 *             for(Book iter : mp_a.values()){
 *                 String outString = "";
 *                 outString += iter.getName() + "#";
 *                 outString += iter.getBookJanr().name() + "#";
 *                 outString += iter.getKolWords() + "#";
 *
 *                 for(int i = 0; i < iter.getKolWords(); i++){
 *                     outString += iter.getWordX(i);
 *                     if(i + 1 != iter.getKolWords()) outString += "#";
 *                 }
 *                 buffer = (outString).getBytes();
 *                 outt.write(buffer, 0, buffer.length);
 *                 outt.write("\n".getBytes());
 *             }
 *             outt.close();
 *             out.close();
 *             return true;
 *         } catch (IOException e) {
 *             System.out.println("Wrong file name!!");
 *             return false;
 *         }
 *
 *
 *         Book1#CLASSIC#3#5#1233#3#aaa#bbb#ccc
 */
