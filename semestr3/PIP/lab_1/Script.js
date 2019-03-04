jQuery('document').ready(function () {
    var x, y, r;

    jQuery('.cradio').on("input", function () {
        alert(" Y - was chosed \n" + "value = " + this.value );
        y = parseFloat(this.value);
    });

    jQuery('#x_').on("focusout", function () {
        alert(" X was choused ");
        var str = jQuery('#x_').val();
        if(check_x(str) == -1) alert("Please write number X ");
        else if(check_x(str) == 0) alert("Wrong X, please write number ");
        else if(check_x(str) == 1) alert("Correct X ");
    });

jQuery(".cradius").on('click', function(){
    var str = jQuery('#x_').val();
    if(check_x(str) == -1) alert("Please write number X ");
    else if(check_x(str) == 0) alert("Wrong X, please write number ");
    else if(check_x(str) == 1) alert("Correct X ");
});

function check_x(str){
    if(str.length == 0) return -1;
    //alert(str);
    //alert(str.length);
    var point = 0;
    for(var i = 0; i < str.length; i++){
        //alert(str.charAt(i));
        if(str.charAt(i) == '-'){
            if(i != 0){
                //alert(" Bad X ");
                return 0;
            }
        }
        else if(str.charAt(i) == '.'){
            point++;
            if((i == 0) || (point > 1)){
                //alert(" Bad X ");
                return 0;
            }
        }
        else if(!(('0' <= str.charAt(i)) && (str.charAt(i) <= '9'))){
            //alert(" Bad X ");
            return 0;
        }
    }
    return 1;
}

jQuery('#R_1').on("click", function () { r = 1; });
jQuery('#R_1_5').on("click", function () { r = 1.5; });
jQuery('#R_2').on("click", function () { r = 2; });
jQuery('#R_2_5').on("click", function () { r = 2.5; });
jQuery('#R_3').on("click", function () { r = 3; });
});