function updateClock() {
    var now = new Date();
    var time = now.getHours() + ':' + now.getMinutes() + ':' + now.getSeconds();

    // a cleaner way than string concatenation
    var date = [now.getDate(),
        now.getMonth()+1,
        now.getFullYear()].join('.');
    document.getElementById('time').innerHTML = [time, date].join(' | ');
    setTimeout(updateClock, 6000);
}


