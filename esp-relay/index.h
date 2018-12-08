char MAIN_page[] PROGMEM = R"=====(<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8"/>
        <title>EspRelay</title>
        <!--<link href='//fonts.googleapis.com/css?family=Lato:300' rel='stylesheet' type='text/css'>-->
        <style>
            body {
                margin: 50px 0 0 0;
                padding: 0;
                width: 100%;
                font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
                text-align: center;
                color: #aaa;
                font-size: 16px;
            }

            h1 {
                color: #719e40;
                letter-spacing: -3px;
                font-family: 'Lato', sans-serif;
                font-size: 100px;
                font-weight: 200;
                margin-bottom: 0;
            }

            .time-input {
             width: 70px;
            }

            .runnind-state {
                color: red;
            }

        </style>
    </head>
    <body>
        <div>
            <span>Relay algorithm state: </span>
            <span id="algorithm_satate" class="algorithm-state running">...</span>
        </div>
        <div>
            <span>Current temperature: </span><span id="temperature">0.0</span>°
        </div>

        <form id="time_alhoritm_form"> 
        <div>
            <span>Time algorithm:</span>&nbsp;
            <input type="number" value="1" name="time_value" min="1" id="time_value" class="time-input">
            <span>min</span>&nbsp;
            <input type="submit" value="Start" id="start_time_button">
        </div>
        </form>

        <form id="temp_alhoritm_form"> 
        <div>
            <span>Temp algorithm:</span>&nbsp;
            
            <input type="number" value="-5" name="temp_min_value" id="temp_min_value" class="time-input">
            <input type="number" value="20" name="temp_max_value" id="temp_max_value" class="time-input">
            <input type="submit" value="Start" id="start_temp_button">
        </div>
        </form>

        <form id="relay4_time_form"> 
        <div>
            <span>Relay 4:</span>&nbsp;
            <input type="number" value="900" name="time_value" class="time-input">
            <input type="hidden" value="4" name="relay_id">
            <span>ms</span>&nbsp;
            <input type="submit" value="Start" id="relay4_button">
        </div>
        </form>

        <form id="relay5_time_form"> 
        <div>
            <span>Relay 5:</span>&nbsp;
            <input type="number" value="900" name="time_value" class="time-input">
            <input type="hidden" value="5" name="relay_id">
            <span>ms</span>&nbsp;
            <input type="submit" value="Start" id="relay5_button">
        </div>
        </form>

        <form id="relay6_time_form">
        <div>
            <span>Relay 6:</span>&nbsp;
            <input type="number" value="900" name="time_value" class="time-input">
            <input type="hidden" value="6" name="relay_id">
            <span>ms</span>&nbsp;
            <input type="submit" value="Start" id="relay6_button">
        </div>
        </form>


        <script type="text/javascript">
            var isTempRunning = false;
            var isTimeRunning = false;

            document.getElementById("temp_alhoritm_form").addEventListener("submit" , function(event) {
                event.preventDefault();

                if (isTempRunning)
                {
                    stopTempAlhorithm();
                }
                else
                {
                    var params = encodeURI("temp_min_value=" + this.temp_min_value.value
                        + "&temp_max_value=" + this.temp_max_value.value
                    );

                    httpGetAsync("/api/startAlhorithmTemp?" + params, function(responseText)
                    {
                        console.log(responseText);
                        var info = JSON.parse(responseText);
                        if (info.result == "success")
                        {
                            alert("Algorithm is running");
                        }
                        else
                        {
                            alert("Error. " + info.message);
                        }
                    });
                }
            });

            document.getElementById("time_alhoritm_form").addEventListener("submit" , function(event) {
                event.preventDefault();

                if (isTimeRunning)
                {
                    stopTimeAlhorithm();
                }
                else
                {
                    var params = encodeURI("time_value=" + this.time_value.value);

                    httpGetAsync("/api/startAlhorithmTime?" + params, function(responseText)
                    {
                        console.log(responseText);
                        var info = JSON.parse(responseText);
                        if (info.result == "success")
                        {
                            alert("Algorithm is running");
                        }
                        else
                        {
                            alert("Error. " + info.message);
                        }
                    });
                }
            });

            document.getElementById("relay4_time_form").addEventListener("submit" , function(event) {
                event.preventDefault();

                var params = encodeURI("time_value=" + this.time_value.value + "&relay_id=" + this.relay_id.value);
                turnOnRelay(params);
            });

            document.getElementById("relay5_time_form").addEventListener("submit" , function(event) {
                event.preventDefault();

                var params = encodeURI("time_value=" + this.time_value.value + "&relay_id=" + this.relay_id.value);
                turnOnRelay(params);
            });

            document.getElementById("relay6_time_form").addEventListener("submit" , function(event) {
                event.preventDefault();

                var params = encodeURI("time_value=" + this.time_value.value + "&relay_id=" + this.relay_id.value);
                turnOnRelay(params);
            });

            function turnOnRelay(params) {
                httpGetAsync("/api/turnOnRelay?" + params, function(responseText)
                {
                    /*console.log(responseText);
                    var info = JSON.parse(responseText);
                    if (info.result == "success")
                    {
                        alert("Algorithm is running");
                    }
                    else
                    {
                        alert("Error. " + info.message);
                    }*/
                });
            }

            function stopTempAlhorithm() {
                httpGetAsync("/api/stopTempAlhorithm", function(responseText) {
                    console.log(responseText);
                    var info = JSON.parse(responseText);
                    if (info.result == "success")
                    {
                        alert("Algorithm is stopped");
                    }
                    else
                    {
                        alert("Error. " + info.message);
                    }
                });
            }

            function stopTimeAlhorithm() {
                httpGetAsync("/api/stopTimeAlhorithm", function(responseText) {
                    console.log(responseText);
                    var info = JSON.parse(responseText);
                    if (info.result == "success")
                    {
                        alert("Algorithm is stopped");
                    }
                    else
                    {
                        alert("Error. " + info.message);
                    }
                });
            }

            setInterval(function() {
                getInfo();
            }, 1000);

            function getInfo() {
                httpGetAsync("/api/getInfo", function(responseText)
                {
                    console.log(responseText);
                    var info = JSON.parse(responseText);
                    document.getElementById("temperature").innerHTML = info.temperature;

                    isTempRunning = info.isTempRunning === "1" || info.isTempRunning === 1 ? true : false;
                    isTimeRunning = info.isTimeRunning === "1" || info.isTimeRunning === 1 ? true : false;


                    document.getElementById("algorithm_satate").textContent = (isTempRunning || isTimeRunning ? "running" : "stopped");
                    if (isTempRunning || isTimeRunning) {
                        document.getElementById("algorithm_satate").classList.add("runnind-state");
                    }
                    else {
                        document.getElementById("algorithm_satate").classList.remove("runnind-state");
                    }
                    

                    document.getElementById("start_time_button").value = (isTimeRunning ? "Stop" : "Start");
                    document.getElementById("start_time_button").disabled = isTempRunning;

                    document.getElementById("start_temp_button").value = (isTempRunning ? "Stop" : "Start");
                    document.getElementById("start_temp_button").disabled = isTimeRunning;
                });  
            }

            function httpGetAsync(theUrl, callback)
            {
                var xmlHttp = new XMLHttpRequest();
                xmlHttp.onreadystatechange = function() { 
                    if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
                        callback(xmlHttp.responseText);
                }
                xmlHttp.open("GET", theUrl, true);
                xmlHttp.send(null);
            }
        </script>
    </body>
</html>
)=====";
