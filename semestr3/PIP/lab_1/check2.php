<?php
session_start();
//if(session_status() <= 0) session_start();
$currentTime = date("H:i:s", strtotime('-1 hour'));
$start = microtime(true);

$x = $_POST['x_'];
$y = $_POST['y_'];
$r = $_POST['r_'];

$res = check($x, $y, $r);
$time = microtime(true) - $start;


$_result = array($x, $y, $r, $res, $currentTime, $time);
if (!isset($_SESSION['history'])) {
    $_SESSION['history'] = array();
}

//number_format($value[5], 10, ".", "")*1000000
array_push($_SESSION['history'], $_result);
include "./index.php";



function check($x, $y, $r){
    if (($x <= 0) && ($y <= 0)) {
        if (($x * $x) + ($y * $y) <= $r * $r) return 'true';
    }
    else if((0 <= $x) && (0 <= $y)){
        if($y <= $r - $x) return  'true';
    }
    else if((0 <= $x) && ($x <= $r) && (-$r <= $y * 2) && ($y <= 0))
        return 'true';
    return 'false';
}

?>