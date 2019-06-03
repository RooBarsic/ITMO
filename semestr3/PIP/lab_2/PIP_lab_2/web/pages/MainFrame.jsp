<%--
  Created by IntelliJ IDEA.
  User: farrukh
  Date: 24.05.19
  Time: 21:39
  To change this template use File | Settings | File Templates.
--%>

<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <meta charset="UTF-8">
    <title>PIP laba 2, Author : Farrukh Karimov P3202, Var : 200133</title>
</head>
<body>
<table id="zoneTable">
    <tr id="zoneHat"> <td>
        <header id="hat">
            <h1> Karimov Farrukh Tojidinovich P3202 Var : 200133 </h1>
        </header>
    </td> </tr>
    <tr id="zoneContent"> <td>
        <table class="contentTable">
            <tr>
                <td class="contentTableTd"> <div id="app">
                    Tut bedet uslovie <br/>
                    Значение X :
                    <select id="X">
                        <option> -2 </option>
                        <option> -1.5 </option>
                        <option> -1 </option>
                        <option> -0.5 </option>
                        <option> 0 </option>
                        <option> 0.5 </option>
                        <option> 1 </option>
                        <option> 1.5 </option>
                        <option> 2 </option>
                    </select>
                    <br/>
                    Значение Y : <input id="Y" placeholder="(-5...5)" type="text" v-on:blur="check_Y"> <br/>
                    <h4 style="color: red;"> {{ validationMessage }} </h4>
                    <br/>
                    Значение R :
                    1   <input type="radio" name="r1" value="1" v-on:click="setR_1">
                    1.5 <input type="radio" name="r1" value="1.5"  v-on:click="setR_1_5">
                    2   <input type="radio" name="r1" value="2"  v-on:click="setR_2">
                    2.5 <input type="radio" name="r1" value="2.5"  v-on:click="setR_2_5">
                    3   <input type="radio" name="r1" value="3"  v-on:click="setR_3">
                    <br/>
                    <h4 style="color: red;">  {{ radiusMessage }} </h4>
                    <br/>
                    <button v-on:click="submitData"> send </button>
                </div> </td>
                <td class="contentTableTd">
                    <canvas id="plotCanvas" height="300" width="300" onclick="newPoint(event)"> Your brouser can't work with canvas </canvas>
                </td>
            </tr>
            <tr>
                <td class="contentTableTd">
                    <table class="contentTable">
                        <tr>
                            <td class="contentTableTd"> X </td>
                            <td class="contentTableTd"> Y </td>
                            <td class="contentTableTd"> R </td>
                            <td class="contentTableTd"> Result </td>
                            <td class="contentTableTd"> Time To Work </td>
                        </tr>
                        <%@ page import="myClasses.PointsArray" %>
                        <%@ page import="myClasses.PointBean" %>
                        <%  PointsArray pointsArray = (PointsArray) request.getSession().getAttribute("PointsArrayBean");
                            if(pointsArray != null){
                                for (int i = 0; i < pointsArray.getSize(); i++){
                                    PointBean pointBean = pointsArray.getItem(i);
                                    String row = "<tr>";
                                    row += "<td class=\"contentTableTd\">" + pointBean.getX() + "</td>";
                                    row += "<td class=\"contentTableTd\">" + pointBean.getY() + "</td>";
                                    row += "<td class=\"contentTableTd\">" + pointBean.getR() + "</td>";
                                    if(pointBean.getResult().equals("Yes"))
                                        row += "<td class=\"contentTableTd\" style=\"color: green;\">" + pointBean.getResult() + "</td>";
                                    else row += "<td class=\"contentTableTd\" style=\"color: red;\">" + pointBean.getResult() + "</td>";
                                    row += "<td class=\"contentTableTd\">" + pointBean.getTimeToWork() + "</td>";

                                    out.println(row);
                                }
                            }
                            else out.print("PointsArrau === NULLL !!!! ");
                        %>
                    </table>
                </td>
                <td>
                </td>
            </tr>
        </table>

    </td></tr>
    <tr id="zoneFooter"><td>
        <footer id="footer">
            <div align="center">
                <br/>
                <table class="footerTable">
                    <td> <h4>
                        Создатели Farrukh Karimov. <br/>
                        При поддержке Barsic.Enterprise.
                    </h4> </td>
                </table>
            </div>
        </footer>
    </td></tr>
</table>

<link href="../styles/style1.css" rel="stylesheet" type="text/css"/>
<script src="https://cdn.jsdelivr.net/npm/vue/dist/vue.js"></script>
<script type="text/javascript" src="../js/jquery-3.3.1.min.js"></script>
<script type="text/javascript" src="../js/script.js"></script>
</body>
</html>
