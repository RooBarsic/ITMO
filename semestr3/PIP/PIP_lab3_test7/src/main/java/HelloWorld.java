// Import required java libraries

import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import javax.ws.rs.Path;

public class HelloWorld extends HttpServlet {

    private String message;

    public void init() throws ServletException {
        // Do required initialization
        message = "Hello World via Servlet";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        System.out.println(" \nZ Fula Helo World ------------------ ");

        response.setContentType("text/html");

        // Actual logic goes here.
        PrintWriter out = response.getWriter();
        out.println("<h1>Hello World via Servlet</h1>");
        out.println("<p>"+ new Date().toString() +"</p>");
        out.flush();
    }

}
