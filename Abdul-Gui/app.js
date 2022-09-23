// Initiating variables 
var particle = new Particle();
var token;
//var devicesPr;

// This function validates the user log in details, stores their token in local storage with an id and redirects to the gui page.
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

// The below functions help control the movement of the rover through the gui. They are called when their buttons are pressed.
// This function is to tell the rover to move forward
function Forward(){
    // Status update is done 
    RoverStatus('forward');
    // Here the token used on log in is stored locally
    token = localStorage.getItem('token');
    // The particle function is called and arguments like the deviceId, name of event, argument for function and token are passed which 
    // get set as part of the data to the device and return an error if failed otherwise giving a success message.
    var fnPr = particle.callFunction({ deviceId: '7ab7a3f4696568b6b853d66d', name: 'guimovement', argument: 'Forward', auth: token });
    fnPr.then(
    function(data) {
        console.log('Function called succesfully:', data);
    }, function(err) {
        console.log('An error occurred:', err);
    });
}

// This function is to tell the rover to move backward
function Backward(){
    // Status update is done 
    RoverStatus('backward');
    // Here the token used on log in is stored locally
    token = localStorage.getItem('token');
    // The particle function is called and arguments like the deviceId, name of event, argument for function and token are passed which 
    // get set as part of the data to the device and return an error if failed otherwise giving a success message.
    var fnPr = particle.callFunction({ deviceId: '7ab7a3f4696568b6b853d66d', name: 'guimovement', argument: 'Backward', auth: token });
    fnPr.then(
    function(data) {
        console.log('Function called succesfully:', data);
    }, function(err) {
        console.log('An error occurred:', err);
    });
}

// This function is to tell the rover to turn left
function Left(){
    // Status update is done 
    RoverStatus('left');
    // Here the token used on log in is stored locally
    token = localStorage.getItem('token');
    // The particle function is called and arguments like the deviceId, name of event, argument for function and token are passed which 
    // get set as part of the data to the device and return an error if failed otherwise giving a success message.
    var fnPr = particle.callFunction({ deviceId: '7ab7a3f4696568b6b853d66d', name: 'guimovement', argument: 'Left', auth: token });
    fnPr.then(
    function(data) {
        console.log('Function called succesfully:', data);
    }, function(err) {
        console.log('An error occurred:', err);
    });
}

// This function is to tell the rover to turn right
function Right(){
    // Status update is done 
    RoverStatus('right');
    // Here the token used on log in is stored locally
    token = localStorage.getItem('token');
    // The particle function is called and arguments like the deviceId, name of event, argument for function and token are passed which 
    // get set as part of the data to the device and return an error if failed otherwise giving a success message.
    var fnPr = particle.callFunction({ deviceId: '7ab7a3f4696568b6b853d66d', name: 'guimovement', argument: 'Right', auth: token });
    fnPr.then(
    function(data) {
        console.log('Function called succesfully:', data);
    }, function(err) {
        console.log('An error occurred:', err);
    });
}

// This function is to tell the rover to stop
function Stop(){
    // Status update is done 
    RoverStatus('stop');
    // Here the token used on log in is stored locally
    token = localStorage.getItem('token');
    // The particle function is called and arguments like the deviceId, name of event, argument for function and token are passed which 
    // get set as part of the data to the device and return an error if failed otherwise giving a success message.
    var fnPr = particle.callFunction({ deviceId: '7ab7a3f4696568b6b853d66d', name: 'guimovement', argument: 'Stop', auth: token });
    fnPr.then(
    function(data) {
        console.log('Function called succesfully:', data);
    }, function(err) {
        console.log('An error occurred:', err);
    });
}

// This function is to tell the rover to start
function Start(){
    // Status update is done 
    RoverStatus('start');
    // Here the token used on log in is stored locally
    token = localStorage.getItem('token');
    // The particle function is called and arguments like the deviceId, name of event, argument for function and token are passed which 
    // get set as part of the data to the device and return an error if failed otherwise giving a success message.
    var fnPr = particle.callFunction({ deviceId: '7ab7a3f4696568b6b853d66d', name: 'guimovement', argument: 'Start', auth: token });
    fnPr.then(
    function(data) {
        console.log('Function called succesfully:', data);
    }, function(err) {
        console.log('An error occurred:', err);
    });
}

// This function sets the status of the rover based on the argument recieved from functions above
function RoverStatus(stat){
    var element = document.getElementById("status");
    if (stat == 'start'){
        element.innerHTML = "Rover Status: Rover Moving";
    } else if (stat == 'stop'){
        element.innerHTML = "Rover Status: Rover Stationary";
    }
    else if(stat == 'forward'){
        element.innerHTML = "Rover Status: Rover Going Forward";
    }
    else if(stat == 'backward'){
        element.innerHTML = "Rover Status: Rover Going Backward";
    }
    else if(stat == 'right'){
        element.innerHTML = "Rover Status: Rover Going Right";
    }
    else if(stat == 'left'){
        element.innerHTML = "Rover Status: Rover Going Left";
    }
}
