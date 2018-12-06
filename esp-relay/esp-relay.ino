
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "avdweb_Switch.h"

#include "DS18B20.h"
#include "RelayAlgorithm.h"
#include "TimerRelay.h"
#include "TimeAlgorithm.h"
#include "TempAlgorithm.h"

#include "index.h"

#ifndef STASSID
#define STASSID "em70"
#define STAPSK  "em70Greate"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

DS18B20 DS18B20Sensor(D1);
RelayAlgorithm relayAlgorithm(D2, D3, D4);
TimerRelay relay4(D5);
TimerRelay relay5(D6);
TimerRelay relay6(D7);

TimeAlgorithm timeAlgorithm(&relayAlgorithm);
TempAlgorithm tempAlgorithm(&relayAlgorithm, &DS18B20Sensor);

Switch cancelButton = Switch(D8, INPUT, HIGH);

//uint32_t algorithmTimeStart = 0;
//int tempMin = 0;
//int tempMax = 0;
//uint32_t algorithmTimeEnd = 0; 

enum AlgoritmType {
    TIME_TYPE = 0,
    TEMP_TYPE
} currentType = TIME_TYPE;

void handleRoot() 
{
    server.sendContent_P(MAIN_page);
}

void handleNotFound() 
{
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

void handleAllInfo()
{
    server.sendHeader("Access-Control-Allow-Origin", "*");
    
    String message = "{";
    
    message += "\"temperature\":\"";
    message += String(DS18B20Sensor.temperature());
    message += "\",";

    message += "\"isTempRunning\":\"";
    message += String(tempAlgorithm.isRunning());
    message += "\",";

    message += "\"isTimeRunning\":\"";
    message += String(timeAlgorithm.isRunning());
    message += "\"";
    
    message += "}";
    server.send(200, "application/json", message);
}

void startAlhorithmTime()
{
    server.sendHeader("Access-Control-Allow-Origin", "*");
    
    if (!timeAlgorithm.isRunning())
    {
        String timeStr = server.arg("time_value");

        if (isNumeric(timeStr))
        {
            char longbuf[32];
            timeStr.toCharArray(longbuf, sizeof(longbuf));
            uint32_t time = strtoul(longbuf, 0, 10);
            
            timeAlgorithm.start(time);
            currentType = TIME_TYPE;
            
            server.send(200, "application/json", "{\"result\":\"success\", \"message\":\"\"}");
        }
        else
        {
            server.send(200, "application/json", "{\"result\":\"error\", \"message\":\"Invalid parameters\"}");
        }
    }
}

void startAlhorithmTemp()
{
    server.sendHeader("Access-Control-Allow-Origin", "*");
    
    if (!tempAlgorithm.isRunning())
    {
        String tempMinStr = server.arg("temp_min_value");
        String tempMaxStr = server.arg("temp_max_value");
        
        if (isNumeric(tempMinStr) && isNumeric(tempMaxStr))
        {
            int tempMin = tempMinStr.toInt();
            int tempMax = tempMaxStr.toInt();
            
            tempAlgorithm.start(tempMin, tempMax);
            
            server.send(200, "application/json", "{\"result\":\"success\", \"message\":\"\"}");
        }
        else
        {
            server.send(200, "application/json", "{\"result\":\"error\", \"message\":\"Invalid parameters\"}");
        }
    }
}

void stopTimeAlhorithm()
{
    server.sendHeader("Access-Control-Allow-Origin", "*");
    
    if (timeAlgorithm.isRunning())
    {
        timeAlgorithm.stop();
        server.send(200, "application/json", "{\"result\":\"success\", \"message\":\"\"}");
    }
    else
    {
        server.send(200, "application/json", "{\"result\":\"error\", \"message\":\"Task is not running\"}");
    }
}

void stopTempAlhorithm()
{
    server.sendHeader("Access-Control-Allow-Origin", "*");
    
    if (tempAlgorithm.isRunning())
    {
        tempAlgorithm.stop();
        server.send(200, "application/json", "{\"result\":\"success\", \"message\":\"\"}");
    }
    else
    {
        server.send(200, "application/json", "{\"result\":\"error\", \"message\":\"Task is not running\"}");
    }
}

void turnOnRelay()
{
    
}

void setup() 
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("esp8266")) {
        Serial.println("MDNS responder started");
    }

    server.on("/", handleRoot);
    server.on("/api/getInfo", handleAllInfo);  
    server.on("/api/startAlhorithmTime", startAlhorithmTime);
    server.on("/api/startAlhorithmTemp", startAlhorithmTemp);
    server.on("/api/stopTimeAlhorithm", stopTimeAlhorithm);
    server.on("/api/stopTempAlhorithm", stopTempAlhorithm);
    server.on("/api/turnOnRelay", turnOnRelay);

    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("HTTP server started");

    relayAlgorithm.begin();

    relay4.begin();
    relay5.begin();
    relay6.begin();
}

void loop() 
{
    server.handleClient();

    DS18B20Sensor.detectTemperature();

    relayAlgorithm.tick();

    relay4.tick();
    relay5.tick();
    relay6.tick();

    readButton();
}

inline void checkEndAlhoritm()
{
    
}

inline void readButton()
{
    cancelButton.poll();
    if (cancelButton.singleClick()) 
    {
        Serial.println("  ==> all_e_B singleClick.");
    }
}

bool isNumeric(const String &str) {
    for (char i = 0; i < str.length(); i++) {
        if ( !(isDigit(str.charAt(i)) || str.charAt(i) == '.' || (str.charAt(i) == '-' && i == 0))) {
            return false;
        }
    }
    return true;
}

