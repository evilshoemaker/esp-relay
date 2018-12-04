char MAIN_page[] PROGMEM = R"=====(<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8"/>
        <title>Slim 3</title>
        <link href='//fonts.googleapis.com/css?family=Lato:300' rel='stylesheet' type='text/css'>
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

        </style>
    </head>
    <body>
        <div>
            <span>Relay algorithm state: </span>
            <span id="algorithm_satate" class="algorithm-state running">running</span>
        </div>
        <div>
            <span>Current temperature: </span><span id="temperature">0.0</span>°
        </div>

        <div>
            <span>Relay algorithm:</span>&nbsp;
            <input type="button" value="Start" id="start_button">
        </div>

        <div>
            <span>Temp algorithm:</span>&nbsp;

            <input type="number" value="-5" id="temp_min_value" class="time-input">
            <input type="number" value="20" id="temp_max_value" class="time-input">
            <input type="checkbox" id="temperature_algorithm_checkbox">
            <label for="temperature_algorithm_checkbox">enable</label>
        </div>

        <div>
            <span>Relay 4:</span>&nbsp;
            <input type="number" value="900" id="relay4_time_value" class="time-input">
            <span>ms</span>&nbsp;
            <input type="button" value="Start" id="relay4_button">
        </div>

        <div>
            <span>Relay 5:</span>&nbsp;
            <input type="number" value="900" id="relay5_time_value" class="time-input">
            <span>ms</span>&nbsp;
            <input type="button" value="Start" id="relay5_button">
        </div>

        <div>
            <span>Relay 6:</span>&nbsp;
            <input type="number" value="900" id="relay6_time_value" class="time-input">
            <span>ms</span>&nbsp;
            <input type="button" value="Start" id="relay6_button">
        </div>


        <script type="text/javascript">
            document.getElementById("start_button").addEventListener("click" , function() {
                alert('Hi!')
            });

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
