import myClasses.PointBean;
import myClasses.PointsArray;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

@WebServlet(name = "AreaCheckServlet")
public class AreaCheckServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            System.out.println(" ### new Point ");

            PointsArray pointsArray = (PointsArray) request.getSession().getAttribute("PointsArrayBean");
            if (pointsArray == null) pointsArray = new PointsArray();

            long startTime = (long) (new Date()).getTime() ;//System.currentTimeMillis();
            String strX = request.getParameter("x");
            String strY = request.getParameter("y");
            String strR = request.getParameter("r");
            System.out.println(" GET new request x = " + strX + " y = " + strY + " r = " + strR + " page = " + request.getParameter("page"));

            if ((strX != null) && (strY != null) && (strR != null)) {
                Double x = Double.parseDouble(strX);
                Double y = Double.parseDouble(strY);
                Double r = Double.parseDouble(strR);
                System.out.println(" normal 1");

                PointBean pointBean = null;

                if ((0 <= x) && (x <= r)) {
                    if ((0 <= y) && (y <= r))
                        pointBean = new PointBean(x, y, r, "Yes");
                    else if ((y <= 0) && (y >= (-r / 2.) + (x / 2.)))
                        pointBean = new PointBean(x, y, r, "Yes");
                    else pointBean = new PointBean(x, y, r, "No");
                } else if ((Math.sqrt((x * x) + (y * y)) * 2. <= r) && (-r / 2. <= x) && (x <= 0) && (0 <= y) && (y <= r / 2.)){
                    pointBean = new PointBean(x, y, r, "Yes");
                }
                else
                    pointBean = new PointBean(x, y, r, "No");

                if (pointBean != null) {
                    pointBean.setTimeToWork((int)((long) (new Date()).getTime() - startTime));
                    pointsArray.addNewPointBean(pointBean);

                    PrintWriter printWriter = new PrintWriter(response.getWriter());
                    if(pointBean.getResult().equals("Yes")) printWriter.print("1");
                    else printWriter.print("0");
                    printWriter.flush();
                }

                request.getSession().setAttribute("PointsArrayBean", pointsArray);
                System.out.println("   $$ pointsArray = " + pointsArray);

            }
            if (request.getParameter("page") != null) {
                System.out.println("normal 2 send redirection ");
                response.sendRedirect("./pages/MainFrame.jsp");
                //RequestDispatcher dispatcher = request.getRequestDispatcher("./pages/MainFrame.jsp");
                //dispatcher.forward(request, response);
            }
        }
        catch (Exception e){
            System.out.println("Some exaption in Area Check");
            e.printStackTrace();
        }
    }
}
