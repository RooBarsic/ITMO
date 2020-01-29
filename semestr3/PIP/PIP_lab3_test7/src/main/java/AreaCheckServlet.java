
import javax.inject.Inject;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

@WebServlet("/ControllerServlet")
public class AreaCheckServlet extends HttpServlet {
    private DBConnector dbConnector = new DBConnector();

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            System.out.println(" ### new Point ");

            int user_id = -1;
            String jsessionId = "";
            for(Cookie cookie : request.getCookies()){
                if(cookie.getName().equals("user_id")){
                    user_id = Integer.parseInt(cookie.getValue());
                }
                else if(cookie.getName().equals("JSESSIONID")){
                    jsessionId = cookie.getValue();
                }
            }
            if(user_id == -1){
                user_id = dbConnector.createNewUser(jsessionId);
                Cookie cookie = new Cookie("user_id", Integer.toString(user_id));
                cookie.setMaxAge(-1);
                response.addCookie(cookie);
            }


            //PointsArray pointsArray = (PointsArray) request.getSession().getAttribute("PointsArrayBean");
            //if (pointsArray == null) pointsArray = new PointsArray();

            long startTime = System.currentTimeMillis() ;//System.currentTimeMillis();
            String strX = request.getParameter("x");
            String strY = request.getParameter("y");
            String strR = request.getParameter("r");
            String userName = request.getParameter("userName");
            System.out.println(" GET new request x = " + strX + " y = " + strY + " r = " + strR + " page = " + request.getParameter("page"));

            if ((strX != null) && (strY != null) && (strR != null) && (userName != null) && (!userName.equals("")) && (!strX.equals("")) && (!strY.equals("")) && (!strR.equals(""))) {
                Double x = Double.parseDouble(strX);
                Double y = Double.parseDouble(strY);
                Double r = Double.parseDouble(strR);
                System.out.println(" normal 1");

                PointController pointBean = null;

                if ((0. <= y) && (y <= r)) {
                    if ((0. <= x) && (x <= r / 2.))
                        pointBean = new PointController(x, y, r, "Yes");
                    else if ((-r + y <= x) && (x <= 0.))
                        pointBean = new PointController(x, y, r, "Yes");
                    else pointBean = new PointController(x, y, r, "No");
                } else if ((Math.sqrt((x * x) + (y * y)) <= r / 2.) && (-r / 2. <= x) && (x <= 0) && (-r/2. <= y) && (y <= 0)){
                    pointBean = new PointController(x, y, r, "Yes");
                }
                else
                    pointBean = new PointController(x, y, r, "No");

                if (pointBean != null) {
                    pointBean.setTimeToWork((System.currentTimeMillis() - startTime));
                    dbConnector.saveResult(userName, x, y, r, pointBean.getResult(), pointBean.getTimeToWork());
                    //pointsArray.addNewPointBean(pointBean);

                    PrintWriter printWriter = new PrintWriter(response.getWriter());
                    if(pointBean.getResult().equals("Yes")) printWriter.print("1");
                    else printWriter.print("0");
                    printWriter.flush();
                }

                //request.getSession().setAttribute("PointsArrayBean", pointsArray);
                System.out.println("   $$ save results in tabel ");
                System.out.println("  Info ::: user_id = " + user_id + " jsessionid = " + jsessionId + " x = " + x + " y = " + y + " r = " + r + " result = " + pointBean.getResult() + " timeToWork = " + pointBean.getTimeToWork() + "   userNAme = " + userName);

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
