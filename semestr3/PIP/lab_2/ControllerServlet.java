import sun.rmi.server.Dispatcher;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "ControllerServlet")
public class ControllerServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            String strX = request.getParameter("x");
            String strY = request.getParameter("y");
            String strR = request.getParameter("r");
            System.out.println(" GET new request x = " + strX + " y = " + strY + " r = " + strR + " page = " + request.getParameter("page"));

            if ((strX != null) && (strY != null) && (strR != null)) {
                Double x = Double.parseDouble(strX);
                Double y = Double.parseDouble(strY);
                Double r = Double.parseDouble(strR);
                //response.sendRedirect("./AreaCheckServlet");
                RequestDispatcher dispatcher = request.getRequestDispatcher("./AreaCheckServlet");
                dispatcher.forward(request, response);
            } else if (request.getParameter("page") != null) {
                //response.sendRedirect("./pages/MainFrame.jsp");
                RequestDispatcher dispatcher = request.getRequestDispatcher("./pages/MainFrame.jsp");
                dispatcher.forward(request, response);
            }
        }
        catch(Exception e){
            System.out.println(" Some error in control servlet");
            e.printStackTrace();
        }
    }
}
