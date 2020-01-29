        // 17:41

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

//import static MyLog.printlnMessage;

public class Main {

    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        PrintWriter printer = new PrintWriter(System.out);
        String fileName = args[0];
        if (!StaticFileChecker.canOpenFile(fileName)) {
            MyLog.printlnMessage(printer,"File <" + fileName + "> not exist!");
            return;
        }
        BooksSet books = BooksSet.GetFromFile(fileName);    // exit if wrong format
        if(books == null){
            MyLog.printlnMessage(printer," Wrong csv format! ");
            return;
        }

        MyLog.printlnMessage(printer,"Hello User! Your file is " + fileName);

        /// /home/farrukh/Рабочий стол/fuu.txt

        Main.printAvailableCommands(printer);

        while (true) {
            MyLog.printMessage(printer,"~$");
            //System.out.print("~$");
            String commandName = scanner.next();
            switch (commandName) {
                case "help":
                    Main.printAvailableCommands(printer);
                    break;
                case "clear":
                    books.clear();
                    break;
                case "load":
                    if(!StaticFileChecker.canOpenFile(fileName))
                        MyLog.printlnMessage(printer, "File <" + fileName + "> not exist!");
                    else {
                        BooksSet newBooks = BooksSet.GetFromFile(fileName);
                        if(newBooks == null){
                            MyLog.printlnMessage(printer, " Wrong csv format! ");
                        }
                        else books = newBooks;
                    }
                    break;
                case "save":
                    books.save(fileName);
                    break;
                case "remove":
                    String bookKey = scanner.next();
                    books.remove(bookKey);
                    break;
                case "remove_lower": {
                        Book book = BookLoader.loadNewBook(scanner, printer);
                        if (book == null) {
                            MyLog.printlnMessage(printer," Can't load gson! Wrong gson format! ");
                        } else {
                            books.remove_lower(book);
                        }
                    } break;
                case "remove_greater": {
                        Book book = BookLoader.loadNewBook(scanner, printer);
                        if (book == null) {
                            MyLog.printlnMessage(printer, " Can't load gson! Wrong gson format! ");
                        } else {
                            books.remove_greater(book);
                        }
                    } break;
                case "add_if_min": {
                        Book book = BookLoader.loadNewBook(scanner, printer);
                        if (book == null) {
                            MyLog.printlnMessage(printer, " Can't load gson! Wrong gson format! ");
                        } else {
                            books.add_if_min(book);
                        }
                    } break;
                case "exit":
                    books.save(fileName);
                    MyLog.printlnMessage(printer,"Bye Barsic!");
                    return;
                case "out":
                    books.outt();
                    break;
                default:
                    MyLog.printlnMessage(printer, "Wrong Command Format!");
                    Main.printAvailableCommands(printer);
            }
            books.save(fileName);
        }
    }

    private static void printAvailableCommands(PrintWriter printWriter) {
        MyLog.printlnMessage(printWriter,"Available commands " + Main.getAvailableCommandsPrompt());
    }

    private static String getAvailableCommandsPrompt() {
        return "Commands:\n"
                + "help\n"
                + "clear\n"
                + "load\n"
                + "save\n"
                + "remove key\n"
                + "remove_lower book\n"
                + "remove_greater book\n"
                + "add_if_min book\n"
                + "exit\n";
    }
}

/*
FOLK
{"mxKolWords":115,"bookName":"123","bookJanr":"FOLK","words":["fkgjdfg","aaa","bb", "tttt"]}
{"mxKolWords":113,"bookName":"123","bookJanr":"CLASSIC","words":["sdgkd","sfgdfs","sg"]}
K1234 CLASSIC 3 sdgkd sfgdfs sg
K12345678 FOLK 4 Lola az xona baromad.
K12 CLASSIC 6 sdgkd sfgdfs sdf sg Barsic Lola
K1234567 CLASSIC 2 sdgkd sdf
K123456 CLASSIC 4 sdgkd sfgdfs sdf sg
K12345 CLASSIC 1 sdgkd
K123 CLASSIC 7 sdgkd sfgdfs sg Ali Said Akram Akbar
K1 CLASSIC 7 sdgkd sfgdfs sg Ali Said Akram Akbar
t1234 CLASSIC 3 sdgkd sfgdfs sg
t12345678 FOLK 4 Lola az xona baromad.
t12 CLASSIC 6 sdgkd sfgdfs sdf sg Barsic Lola
t1234567 CLASSIC 2 sdgkd sdf
t123456 CLASSIC 4 sdgkd sfgdfs sdf sg
t12345 CLASSIC 1 sdgkd
t123 CLASSIC 7 sdgkd sfgdfs sg Ali Said Akram Akbar
t1 CLASSIC 7 sdgkd sfgdfs sg Ali Said Akram Akbar
K1234#CLASSIC#3#sdgkd#sfgdfs#sg
K12345678#FOLK#4#Lola#az#xona#baromad.
K12#CLASSIC#6#sdgkd#sfgdfs#sdf#sg#Barsic#Lola
K1234567#CLASSIC#2#sdgkd#sdf
K123456#CLASSIC#4#sdgkd#sfgdfs#sdf#sg
K12345#CLASSIC#1#sdgkd
K123#CLASSIC#7#sdgkd#sfgdfs#sg#Ali#Said#Akram#Akbar
K1#CLASSIC#7#sdgkd#sfgdfs#sg#Ali#Said#Akram#Akbar
t1234#CLASSIC#3#sdgkd#sfgdfs#sg
t12345678#FOLK#4#Lola#az#xona#baromad.
t12#CLASSIC#6#sdgkd#sfgdfs#sdf#sg#Barsic#Lola
t1234567#CLASSIC#2#sdgkd#sdf
t123456#CLASSIC#4#sdgkd#sfgdfs#sdf#sg
t12345#CLASSIC#1#sdgkd
t123#CLASSIC#7#sdgkd#sfgdfs#sg#Ali#Said#Akram#Akbar
t1#CLASSIC#7#sdgkd#sfgdfs#sg#Ali#Said#Akram#Akbar
 */
