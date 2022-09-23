var particle = new Particle();
var token;
var devicesPr;

function login(){
    particle.login({username: document.getElementById("uname").value, password: document.getElementById("psw").value}).then(
    function(data) {
        console.log("Logged in");
        token = data.body.access_token;
        localStorage.setItem('token', token);
        window.location.pathname = "gui.html";
    },
    function (err) {
        console.log('Could not log in.', err);
    }
    );
}

function RoverStatus(stat){
    var element = document.getElementById("status");
    if (stat == 'start'){
        element.innerHTML = "Rover Moving";
    } else if (stat == 'stop'){
        element.innerHTML = "Rover Stationary";
    }
}


function Forward(){
    token = localStorage.getItem('token');
    var fnPr = particle.callFunction({ deviceId: '7ab742cd41cf68e0460ddc50', name: 'guimovement', argument: 'Forward', auth: token });
    fnPr.then(
    function(data) {
        console.log('Function called succesfully:', data);
    }, function(err) {
        console.log('An error occurred:', err);
    });
}

function Backward(){
    token = localStorage.getItem('token');
    var fnPr = particle.callFunction({ deviceId: '7ab742cd41cf68e0460ddc50', name: 'guimovement', argument: 'Backward', auth: token });
    fnPr.then(
    function(data) {
        console.log('Function called succesfully:', data);
    }, function(err) {
        console.log('An error occurred:', err);
    });
}

function Left(){
    token = localStorage.getItem('token');
    var fnPr = particle.callFunction({ deviceId: '7ab742cd41cf68e0460ddc50', name: 'guimovement', argument: 'Left', auth: token });
    fnPr.then(
    function(data) {
        console.log('Function called succesfully:', data);
    }, function(err) {
        console.log('An error occurred:', err);
    });
}

function Right(){
    token = localStorage.getItem('token');
    var fnPr = particle.callFunction({ deviceId: '7ab742cd41cf68e0460ddc50', name: 'guimovement', argument: 'Right', auth: token });
    fnPr.then(
    function(data) {
        console.log('Function called succesfully:', data);
    }, function(err) {
        console.log('An error occurred:', err);
    });
}

function Stop(){
    RoverStatus('stop');
    token = localStorage.getItem('token');
    var fnPr = particle.callFunction({ deviceId: '7ab742cd41cf68e0460ddc50', name: 'guimovement', argument: 'Stop', auth: token });
    fnPr.then(
    function(data) {
        console.log('Function called succesfully:', data);
    }, function(err) {
        console.log('An error occurred:', err);
    });
}

function Start(){
    RoverStatus('start');
    token = localStorage.getItem('token');
    var fnPr = particle.callFunction({ deviceId: '7ab742cd41cf68e0460ddc50', name: 'guimovement', argument: 'Start', auth: token });
    fnPr.then(
    function(data) {
        console.log('Function called succesfully:', data);
    }, function(err) {
        console.log('An error occurred:', err);
    });
}

