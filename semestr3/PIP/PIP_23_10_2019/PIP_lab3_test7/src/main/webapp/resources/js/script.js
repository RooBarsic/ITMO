function drawCanas(id, r){
    var canvas = document.getElementById(id),
        context = canvas.getContext("2d");
    //clean
    context.clearRect(0, 0, canvas.width, canvas.height);

    //HCN
    context.beginPath();
    context.rect(20, 150, 130, 65);
    context.closePath();
    context.strokeStyle = "rgb(179, 255, 255)";
    context.fillStyle = "rgb(179, 255, 255)";
    context.fill();
    context.stroke();
    //hinh tron
    context.beginPath();
    context.moveTo(150, 150);
    context.arc(150, 150, 130, 0.5*Math.PI,0* Math.PI, true);
    context.closePath();
    context.strokeStyle = "rgb(179, 255, 255)";
    context.fillStyle = "rgb(179, 255, 255)";
    context.fill();
    context.stroke();
    //tam giac
    context.beginPath();
    context.moveTo(150, 85);
    context.lineTo(150, 150);
    context.lineTo(215, 150);
    //context.lineTo(215, 150);
    context.closePath();
    context.strokeStyle = "rgb(179, 255, 255)";
    context.fillStyle = "rgb(179, 255, 255)";
    context.fill();
    context.stroke();

    context.beginPath();
    context.fillStyle = "black";
    context.font = "10px Verdana ";
    context.moveTo(150, 0); context.lineTo(150, 300);
    context.moveTo(150, 0); context.lineTo(145, 15);
    context.moveTo(150, 0); context.lineTo(155, 15);
    context.fillText("Y", 160, 10);
    context.moveTo(0, 150); context.lineTo(300, 150);
    context.moveTo(300, 150); context.lineTo(285, 145);
    context.moveTo(300, 150); context.lineTo(285, 155);
    context.fillText("X", 290, 135);

    // деления X
    context.moveTo(145, 20); context.lineTo(155, 20); context.fillText(r, 160, 20);
    context.moveTo(145, 85); context.lineTo(155, 85); context.fillText((r / 2), 160, 78);
    context.moveTo(145, 215); context.lineTo(155, 215); context.fillText(-(r / 2), 160, 215);
    context.moveTo(145, 280); context.lineTo(155, 280); context.fillText(-r, 160, 280);
    // деления Y
    context.moveTo(20, 145); context.lineTo(20, 155); context.fillText(-r, 20, 170);
    context.moveTo(85, 145); context.lineTo(85, 155); context.fillText(-(r / 2), 70, 170);
    context.moveTo(215, 145); context.lineTo(215, 155); context.fillText((r / 2), 215, 170);
    context.moveTo(280, 145); context.lineTo(280, 155); context.fillText(r, 280, 170);

    context.closePath();
    context.strokeStyle = "black";
    context.fillStyle = "black";
    context.stroke();
}

function createCanvas(id, x, y, r){

    drawCanas(id, r);
    context.beginPath();
    context.rect(Math.round(150 + ((x / r) * 130))-2, Math.round(150 - ((y / r) * 130))-2, 4, 4);
    context.closePath();
    context.strokeStyle = "red";
    context.fillStyle = "red";
    context.fill();
    context.stroke();
}

function clicCanvas(canvId,R) {
    var elem = document.getElementById(canvId);
    var br = elem.getBoundingClientRect();
    var left = br.left;
    var top = br.top;
    var event = window.event;
    var x = event.clientX-left;
    var y = event.clientY-top;
    var boolArea = isArea(x, y, R);
    drawPoint(canvId, x, y,R, boolArea);

}

function isArea(x, y, R) {
    x = ((x - 150) / 130) * R;
    y = ((150 - y) / 130) * R;
    if(x>=0 && y<=0 && x*x+y*y<=R*R){
//         document.writeln(1)
        return 'true';
    }
    if(x>=0 && y>=0 && (x+y <R/2)){
        //       document.writeln(2)
        return 'true';
    }
    if(x<=0 && y<=0 && x>=-R && y>=-R/2){
//        document.writeln(3)
        return 'true';
    }
    return 'false';
}

function drawPoint(id, x, y,R, isArea){
    var canvas = document.getElementById(id),
        context = canvas.getContext("2d");

    context.beginPath();
    context.rect(x - 2, y - 2, 4, 4);
    context.closePath();
    if(isArea === 'true'){
        context.strokeStyle = "green";
        context.fillStyle = "green";
    } else {
        context.strokeStyle = "red";
        context.fillStyle = "red";
    }
    context.fill();
    context.stroke();
    document.getElementById('CVform:CVvalueX').value = ((x - 150) / 130) * R;
    document.getElementById('CVform:CVvalueY').value = ((150 - y) / 130) * R;
    document.getElementById('CVform:CVvalueR').value = R;
    document.getElementById('CVform:CVsubmit').click();
    //document.getElementById("form1").submit();
}

function getValueR() {
    var selectedValue = document.getElementById('form1:valueR').value;
    return selectedValue;
}

function check_value(){
    var test_Y = document.getElementById('form1:valueY').value;
    test_Y = test_Y ? test_Y : "aa" ;
    if ( isNaN(test_Y) || (test_Y < -5.00) || (test_Y > 3.00) ){
        document.getElementById('form1:_valueY').style.boxShadow = "0 0 10px red";
        event.preventDefault();
    }
    else{
        document.getElementById('form1:_valueY').style.boxShadow = "0 0 10px white";
    }
    check_X();
}

function check_X(){
    var test_X = document.getElementsByName('form1:valueX');
    for(var i=0;i<test_X.length;i++){
        if (test_X[i].checked) {
            test_X[0].style.boxShadow="0 0 10px white";
            return true;
        }
    }
    document.getElementsByName('form1:valueX')[0].style.boxShadow="0 0 10px red";
    event.preventDefault();
}

function get_R(){
    var R_tmp = document.getElementById('form1:valueR').value;
    var result =1;
    if (R_tmp != null && R_tmp >0) result = R_tmp;

    return result;
}
function checkForm() {
    var test_X = document.getElementsByName('form1:valueX');
    for(var i=0;i<test_X.length;i++){
        if (test_X[i].checked) test_X[i].checked = false;
    }
}
