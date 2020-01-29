
var x0 = 150, y0 = 150;
var x = 0;
var y = null;
var r = 0;

var app = new Vue({
    el : '#app',
    data : {
        validationMessage : '',
        radiusMessage : '',
        conectionStatus : ''
    },
    methods : {
        check_Y : function(ev){
            this.validationMessage = '';
            var strY = document.getElementById("Y").value;
            var wrongIntervalFlag = 0;
            var wrongSumbolsFlag = 0;
            var numberOfPoints = 0;
            var numberOfAfterPointDigits = 0;
            for(var i = 0; i < strY.length; i++){
                if(!(('0' <= strY[i]) && (strY[i] <= '9'))){
                    if(strY[i] == '.') numberOfPoints++;
                    else if(strY[i] == '-'){
                        if(i != 0) wrongIntervalFlag = 1;
                    }
                    else wrongSumbolsFlag = 1;
                }
                if((numberOfPoints != 0) && (strY[i] != '.')) numberOfAfterPointDigits++;
            }
            if(wrongSumbolsFlag || numberOfPoints > 1) this.validationMessage = "*Внимание : Y - это число!!";
            else if(strY.length == 0) this.validationMessage = '*Внимание : неопределённое значение Y';
            else if((wrongIntervalFlag) || ((parseInt(strY) <= -5) || (5 <= parseInt(strY))))
                this.validationMessage = '*Внимание : диапазон Y (-5; 5)';
            else if(numberOfAfterPointDigits > 3) this.validationMessage = '*Внимание : слишком много цифр после запятой';
            else y = parseFloat(strY);
        },
        setR_1 : function(ev){
            r = 1;
            this.radiusMessage = '';
            dravIMG();
        },
        setR_1_5 : function(ev){
            r = 1.5;
            this.radiusMessage = '';
            dravIMG();
        },
        setR_2 : function(ev){
            r = 2;
            this.radiusMessage = '';
            dravIMG();
        },
        setR_2_5 : function(ev){
            r = 2.5;
            this.radiusMessage = '';
            dravIMG();
        },
        setR_3 : function(ev){
            r = 3;
            this.radiusMessage = '';
            dravIMG();
        },
        submitData : function(ev){
            //alert("keke r = " + r);

            if(r == 0) this.radiusMessage = '*Внимание : не выбрано значение R !! ';
            if(y == null) this.validationMessage = "*Внимание : не выбрано значение Y !! ";

            if((r != 0) && (y != null) && (this.validationMessage.length == 0)){
                x = parseFloat(document.getElementById("X").value);
                $.ajax({
                    url:     "../ControllerServlet",           //url страницы (action_ajax_form.php)
                    type:     "GET", //метод отправки
                    data: {
                        x : x,
                        y : y,
                        r : r,
                        page : 'Okay'
                    },
                    success: function(response) { //Данные отправлены успешно
                        //app.conectionStatus = "<h4 style=\"color: green;\"> access </h4>";
                        //alert("Priwel otvet %)");
                        location.reload();
                    },
                    error: function(response) { // Данные не отправлены
                        app.conectionStatus = "Some error with connection";
                        alert("%% Some error with connection");
                    }
                });
            }
        }
    }
})

jQuery(document).ready(function(){

    // check R  --------------------------------------------------------------------------
    document.getElementById("form1:valueR")
        .addEventListener("change", function (ev) {
            var test_R = document.getElementsByName('form1:valueR');
            var reportStr = "";
            for(var i = 0; i < 5; i++){
                reportStr += " i = " + i + " " + test_R[i] + " " + test_R[i].checked;
                if(test_R[i].checked){
                    r = i + 1;
                }
            }
            console.log(reportStr);
            dravIMG();
        }, false);

    // check Y  ---------------------------------------------------------------------
    document.getElementById("form1:valueY")
        .addEventListener("change", function (ev) {
            var test_Y = document.getElementById('form1:valueY').value;
            //alert("  Hala y = " + test_Y);

            var validationMessage = "";
            var strY = document.getElementById('form1:valueY').value;
            var wrongIntervalFlag = 0;
            var wrongSumbolsFlag = 0;
            var numberOfPoints = 0;
            var numberOfAfterPointDigits = 0;
            for(var i = 0; i < strY.length; i++){
                if(!(('0' <= strY[i]) && (strY[i] <= '9'))){
                    if(strY[i] == '.') numberOfPoints++;
                    else if(strY[i] == '-'){
                        if(i != 0) wrongIntervalFlag = 1;
                    }
                    else wrongSumbolsFlag = 1;
                }
                if((numberOfPoints != 0) && (strY[i] != '.')) numberOfAfterPointDigits++;
            }
            if(wrongSumbolsFlag || numberOfPoints > 1) validationMessage = "*Внимание : Y - это число!!";
            else if(strY.length == 0) validationMessage = '*Внимание : неопределённое значение Y';
            else if((wrongIntervalFlag) || ((parseInt(strY) <= -3) || (3 <= parseInt(strY))))
                validationMessage = '*Внимание : диапазон Y (-5; 5)';
            else if(numberOfAfterPointDigits > 3) validationMessage = '*Внимание : слишком много цифр после запятой';
            else y = parseFloat(strY);

            if(validationMessage != ""){
                //alert(" Bad Y :( ");
            }

        }, false);


    var test_R = document.getElementsByName('form1:valueR');
    var reportStr = "";
    for(var i = 0; i < 5; i++){
        reportStr += " i = " + i + " " + test_R[i] + " " + test_R[i].checked;
        if(test_R[i].checked){
            r = i + 1;
        }
    }
    console.log(reportStr);
    dravIMG();
});

function newPoint (ev){
    sendPoint(ev.offsetX, ev.offsetY);
}

function sendPoint(x, y){
    if(r != 0){
        var cvs = document.getElementById("plotCanvas");
        var ctx = cvs.getContext("2d");
        ctx.fillStyle = "black";
        ctx.fillRect(x-1, y-1, 2, 2);


        $.ajax({
            url:     "../ControllerServlet",           //url страницы (action_ajax_form.php)
            type:     "GET", //метод отправки
            data: {
                userName : "Guest",
                x : ((x - x0)/25).toString(),
                y : ((y0 - y)/25).toString(),
                r : r.toString()
            },
            success: function(response) { //Данные отправлены успешно
                //app.conectionStatus = "<h4 style=\"color: green;\"> access </h4>";
                //alert("%% Priwel ontet");
                if(response.toString() == "1") {
                    var cvs = document.getElementById("plotCanvas");
                    var ctx = cvs.getContext("2d");
                    ctx.fillStyle = "#fc1102";
                    ctx.fillRect(x-1, y-1, 2, 2);
                }
                else {
                    var cvs = document.getElementById("plotCanvas");
                    var ctx = cvs.getContext("2d");
                    ctx.fillStyle = "#05fcf8";
                    ctx.fillRect(x-1, y-1, 2, 2);
                }
            },
            error: function(response) { // Данные не отправлены
                app.conectionStatus = "Some error with connection";
                alert("%% Some Error. Resp ans = " + response.toString());
            }
        });
    }
}

function dravIMG(){
    var cvs = document.getElementById("plotCanvas");
    var ctx = cvs.getContext("2d");
    ctx.clearRect(0, 0, 300, 300);

    ctx.fillStyle = "green";
    ctx.fillRect(0,0,300,300);

    if(r != 0){
        var R = r * 25;

        // Рисуем квадрат
        ctx.fillStyle = "yellow";
        ctx.fillRect(x0, y0, R/2., -R);

        // Рисуем треугольник
        ctx.beginPath();
        ctx.moveTo(x0, y0);
        ctx.lineTo(x0, y0 - R);
        ctx.lineTo(x0 - R, y0);
        ctx.fill();


        // Рисуем дугу
        ctx.beginPath();
        ctx.lineTo(x0, y0);
        ctx.arc(x0, y0, R/2, Math.PI/2, -Math.PI, false);
        ctx.fill();

        // Рисуем координатные оси
        ctx.fillStyle = "#0416f9";
        ctx.fillRect(0, y0, 300, 1);
        ctx.fillRect(x0, 0, 1, 300);
    }
    else {
        ctx.fillStyle = "red";
        ctx.font = "17px Verdana";
        ctx.fillText(" R not chosed!!", 10, 50);
    }
}





function check_X(){
    var test_X = document.getElementsByName('form1:valueX');
    //alert(" x : = " + test_X);
    for(var i=0;i<test_X.length;i++){
        if (test_X[i].checked) {
            test_X[0].style.boxShadow="0 0 10px white";
            return true;
        }
    }
    document.getElementsByName('form1:valueX')[0].style.boxShadow="0 0 10px red";
    event.preventDefault();
}


function moveToMainFrame() {
    window.location = "../MainFrame.xhtml";
}
