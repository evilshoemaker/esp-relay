
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "avdweb_Switch.h"

#include "DS18B20.h"
#include "RelayAlgorithm.h"
#include "TimerRelay.h"

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

Switch cancelButton = Switch(D8, INPUT, HIGH);

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

    message += "\"isRunning\":\"";
    message += String(relayAlgorithm.isRunning());
    message += "\"";
    
    message += "}";
    server.send(200, "application/json", message);
}

void setup() 
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
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
    server.on("/api/startAlhorithmTime", handleAllInfo);
    server.on("/api/startAlhorithmTemp", handleAllInfo);
    server.on("/api/stopAlhorithm", handleAllInfo);

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

inline void readButton()
{
    cancelButton.poll();
    if (cancelButton.singleClick()) 
    {
        Serial.println("  ==> all_e_B singleClick.");
    }
}

