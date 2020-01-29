import org.postgresql.Driver;

import javax.enterprise.context.ApplicationScoped;
import javax.enterprise.context.SessionScoped;
import javax.faces.bean.ManagedBean;
import java.io.Serializable;
import java.sql.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class DBConnector implements Serializable {
    private final String DB_USER_NAME = "farruxkarimov";
    private final String DB_USER_PASSWORD = "";
    private final String DB_URL = "jdbc:postgresql://localhost:5432/piplab3";

    private boolean isDbChanged = true;
    private List<PointController> cachedResult = new ArrayList<>();

    public DBConnector(){
//        try {
//            Connection connection;
//            Driver driver = new org.postgresql.Driver();
//            DriverManager.registerDriver(driver);
//            connection = DriverManager.getConnection(DB_URL, DB_USER_NAME, DB_USER_PASSWORD);
//            if(!connection.isClosed()){
//                System.out.println(" Connection done!! ");
//            }
//            connection.close();
//            if(connection.isClosed()){
//                System.out.println(" Connecccction closed !! ");
//            }
//            connection.close();
//        } catch (SQLException e) {
//            e.printStackTrace();
//        }
        initDb();
    }

    public int getUSerId(String userName){
        try(Connection connection = DriverManager.getConnection(DB_URL, DB_USER_NAME, DB_USER_PASSWORD);
            Statement statement = connection.createStatement()){


        } catch (SQLException e) {
            e.printStackTrace();
        }
        return -1;
    }

    public void addUser(String userName){
        try(Connection connection = DriverManager.getConnection(DB_URL, DB_USER_NAME, DB_USER_PASSWORD);
            Statement statement = connection.createStatement()){
            ResultSet resultSet = statement.executeQuery("select * from rafa;");
            while(resultSet.next()){
                System.out.println("id = " + resultSet.getInt(1) + " name = " + resultSet.getString(2));
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private Connection getConnection(){
        try {
            return DriverManager.getConnection(DB_URL, DB_USER_NAME, DB_USER_PASSWORD);
        } catch (SQLException e) {
            System.out.println(" Can't get connection!!! Error ::::: ");
            e.printStackTrace();
            return null;
        }
    }

    private boolean chechkTablesStatus(){
        try(Connection connection = getConnection();
            Statement statement = connection.createStatement()){
            statement.executeQuery("select * from results25;");
            statement.executeQuery("select * from users_default_ids;");
            return true;
        } catch (SQLException e) {
            System.out.println("Tables Are not created");
            e.printStackTrace();
            return false;
        }
    }

    public void initDb(){
        if(chechkTablesStatus()) return;
        try (Connection connection = getConnection();
             Statement statement = connection.createStatement()){
            try{
                statement.executeQuery("create table users_default_ids(id int primary key, jsessionid varchar(256));");
            }
            catch (Exception e){
            }

            try {
                statement.executeQuery("create table results25(id serial primary key, userlogin varchar(256), x float, y float, r float, result varchar(5), timeToWork int);");
            }
            catch (Exception e) {
            }
        } catch (SQLException e) {
            System.out.println(" Error ----------- ");
            e.printStackTrace();
        }
    }

    public int createNewUser(final String jsessionid) {
        try (Connection connection = getConnection();
             Statement statement = connection.createStatement()) {
            ResultSet resultSet = statement.executeQuery("select * from users_default_ids where jsessionid = '" + jsessionid + "';");
            int id = -1;
            while(resultSet.next()){
                id = resultSet.getInt(1);
            }
            if(id != -1){
                return id;
            }

            resultSet = statement.executeQuery("select count(*) from users_default_ids;");

            int numberOfUSers = 0;
            while(resultSet.next()) {
                numberOfUSers = resultSet.getInt(1);
            }
            statement.execute("insert into users_default_ids(id, jsessionid) values (" + numberOfUSers
                    + ", '" + jsessionid + "');");
//            statement.executeQuery("insert into users_default_ids(id, jsessionid) values("
//                    + numberOfUSers + ",'" + jsessionid + "');").next();
            isDbChanged =true;
            //cachedResultcachedResult.clear();
            return numberOfUSers;
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    private int idt = 1;

    public void saveResult(String userLogin, double x, double y, double r, String result, long timeToWork){
        try(Connection connection = getConnection();
            Statement statement = connection.createStatement()){
            idt++;
            String row = "insert into results25(login, x, y, r, res, timeToWork) values (" +
                    "'" + userLogin+ "'," + x + "," + y + "," + r + ",'" + result + "'," + timeToWork + ");";
            isDbChanged =true;
            cachedResult.add(new PointController(x, y, r, timeToWork, result));

            System.out.println( " sql row :: " + row + "    isDbChanged = " + isDbChanged);
            statement.execute(row);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private int numColl = 0;

    public List<PointController> getResultsHistory(String userlogin){
        System.out.println("    \n --------------- ------- Somebody ask for History : isDbChanged = " + isDbChanged + " -------------- \n");

            try (Connection connection = getConnection();
                 Statement statement = connection.createStatement()) {
                cachedResult.clear();
                System.out.println(" sql ::: " + "select * from results25 where login = '" + userlogin + "'; ");
                ResultSet resultSet = statement.executeQuery("select * from results25 where login = '" + userlogin + "'; ");
                while (resultSet.next()) {
                    PointController resultRow = new PointController(resultSet.getDouble(2), resultSet.getDouble(3), resultSet.getDouble(4), resultSet.getInt(6), resultSet.getString(5));
                    cachedResult.add(resultRow);
                    System.out.println(" ---------------------- ?????????? Add user " + cachedResult.size() + " -------------- ");
                }
                numColl++;
                System.out.println(" ----------  Collected All users. numCall = " + numColl + " ---------------- ");
                isDbChanged = false;
            } catch (SQLException e) {
                e.printStackTrace();
                return Collections.emptyList();
            }
        return cachedResult;
    }
}


//  PointController@1011ae4e
