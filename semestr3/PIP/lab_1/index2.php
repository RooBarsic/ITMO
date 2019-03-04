<?php
//if(session_status() <= 0) session_start();
if (!isset($_SESSION['history'])) {
    $_SESSION['history'] = array();
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title> Karimov Farrukh Tojidinovich P3202 var:18204 </title>
    <link href="styles.css" rel="stylesheet" type="text/css"/>
    <script type="text/javascript" src="jquery-3.3.1.min.js"></script>
    <script type="text/javascript" src="Script.js"></script>
</head>
<body>
<table>
    <tr>
        <td id="left">
            <h3>
                <h2> Задание : ( Сегодня
                    <?php
                    echo date('d.m.y');
                    ?> )
                </h2>
                Разработать PHP-скрипт, определяющий попадание точки на координатной плоскости в заданную область, и создать HTML-страницу, которая формирует данные для отправки их на обработку этому скрипту.

                Параметр R и координаты точки должны передаваться скрипту посредством HTTP-запроса. Скрипт должен выполнять валидацию данных и возвращать HTML-страницу с таблицей, содержащей полученные параметры и результат вычислений - факт попадания или непопадания точки в область.

                Кроме того, ответ должен содержать данные о текущем времени и времени работы скрипта.
            </h3>
            <form method="POST" action="./check2.php">
                Изменение X : <input id="x_" type="number" placeholder="(-3,...,5)" name="x_"> <br/>
                Изменение Y :
                -3 <input name="y_" class="cradio" value="-3" type="radio">
                -2 <input name="y_" class="cradio" value="-2" type="radio">
                -1 <input name="y_" class="cradio" value="-1" type="radio">
                0 <input name="y_" class="cradio" value="0" type="radio">
                1 <input name="y_" class="cradio" value="1" type="radio">
                2 <input name="y_" class="cradio" value="2" type="radio">
                3 <input name="y_" class="cradio" value="3" type="radio">
                4 <input name="y_" class="cradio" value="4" type="radio">
                5 <input name="y_" class="cradio" value="5" type="radio">
                <br/>
                Изменение R :
                <input name="r_" class="cradius" id="R_1" value="1"  type="submit">
                <input name="r_" class="cradius" id="R_1_5" value="1.5" type="submit">
                <input name="r_" class="cradius" id="R_2" value="2" type="submit">
                <input name="r_" class="cradius" id="R_2_5" value="2.5" type="submit">
                <input name="r_" class="cradius" id="R_3" value="3" type="submit">
            </form>
        </td>
        <td id="right"> cord(1;3) </td>
    </tr>
</table>
<table id="result_table">
    <tr>
        <td> x </td>
        <td> y </td>
        <td> R </td>
        <td> Result </td>
        <td> time now </td>
        <td> time to work </td>
    </tr>
    <?php foreach ($_SESSION['history'] as $value) { ?>
        <tr>
            <td> <?php echo $value[0] ?> </td>
            <td> <?php echo $value[1] ?> </td>
            <td> <?php echo $value[2] ?> </td>
            <td> <?php echo $value[3] ?> </td>
            <td> <?php echo $value[4] ?> </td>
            <td> <?php echo number_format($value[5], 10, ".", "")*1000000 ?> </td>
        </tr>
    <?php } ?>
</table>
</body>
</html>