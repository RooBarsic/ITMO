import com.google.gson.Gson;
import com.oracle.xmlns.internal.webservices.jaxws_databinding.ExistingAnnotationsType;

import java.io.PrintWriter;
import java.util.Scanner;

public class BookLoader {
    public static Book loadNewBook(Scanner scanner, PrintWriter printer){
        String jsonPart;
        JsonChecker jsonKeeper = new JsonChecker();
        jsonPart = scanner.nextLine();
        jsonKeeper.addString(jsonPart);
        while(!jsonKeeper.jsonEnded()){
            MyLog.printlnMessage(printer,"Json was not ended! Wating for continue ... ");
            jsonPart = scanner.nextLine();
            jsonKeeper.addString(jsonPart);
        }
        Gson json = new Gson();
        try {
            Book book = json.fromJson(jsonKeeper.getJson(), Book.class);
            return book;
        } catch (Exception e){
            return null;
        }
    }
}
