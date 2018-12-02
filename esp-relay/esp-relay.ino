
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "DS18B20.h"

#ifndef STASSID
#define STASSID "evilnet"
#define STAPSK  "AiGuINet"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

DS18B20 DS18B20Sensor(D1);

void handleRoot() 
{
    server.send(200, "text/plain", "hello from esp8266!");
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
    String message = "{";
    
    message += "\"temperature\":\"";
    message += String(DS18B20Sensor.temperature());
    
    message += "}";
    server.send(200, "application/json", message);
}

void setup() {
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

    server.on("/api/getTemp", []() {
        server.send(200, "text/plain", String(DS18B20Sensor.temperature()));
    });

    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("HTTP server started");
}

float t = 0.0;

void loop() {
    server.handleClient();

    DS18B20Sensor.detectTemperature();

    if (t != DS18B20Sensor.temperature())
    {
        t = DS18B20Sensor.temperature();
        Serial.println(t);
    }
    
}
