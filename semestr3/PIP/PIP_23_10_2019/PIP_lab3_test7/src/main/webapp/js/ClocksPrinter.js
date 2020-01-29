var HH = 30;
var WW = 450;

jQuery(document).ready(function(){
    dravClocks(new Date());
});


var dravClocks = function(){
    var date = new Date();

    var cvs = document.getElementById("plotClocks");
    var ctx = cvs.getContext("2d");

    ctx.clearRect(0, 0, WW, HH);

    ctx.fillStyle = "green";
    ctx.fillRect(0,0,WW,HH);

    ctx.fillStyle = "red";
    ctx.font = "24px Verdana";
    var str = "";
    if(date.getDate() > 9) str += date.getDate() + ".";
    else str += "0" + date.getDate() + ".";
    if(date.getMonth() > 9) str += date.getMonth() + ".";
    else str += "0" + date.getMonth() + ".";
    str += date.getFullYear() + "<->";
    if(date.getHours() > 9) str += date.getHours() + ":";
    else str += "0" + date.getHours() + ":";
    if(date.getMinutes() > 9) str += date.getMinutes() + ":";
    else str += "0" + date.getMinutes() + ":";
    if(date.getSeconds() > 9) str += date.getSeconds();
    else str += "0" + date.getSeconds();
    ctx.fillText(" Time : " + str, 0, 23);
};

setInterval(dravClocks, 6000);
