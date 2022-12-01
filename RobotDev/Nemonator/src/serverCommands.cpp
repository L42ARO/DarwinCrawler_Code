#include "Arduino.h"
#include "motorControls.h"
#include "serverCommands.h"
#include <WiFi.h>
#include<WebServer.h>

WebServer server(80);
const char* WIFI_SSID= "SOAR-Phone";
const char* WIFI_PASS = "FRANK2022";

void serverSetup(){
    Serial.begin(57600);
    Serial.println();
    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }
    Serial.print("http://");
    Serial.println(WiFi.localIP());
    Serial.println(" /fishForward");
    Serial.println(" /fishBackward");
    Serial.println(" /fishForwardLeft");
    Serial.println(" /fishForwardRight");
    Serial.println(" /fishBackwardLeft");
    Serial.println(" /fishBackwardRight");
    Serial.println(" /fishStop");

    server.on("/fishForward", handleFishForward);
    server.on("/fishBackward", handleFishBackward);
    server.on("/fishForwardLeft", handleFishForwardLeft);
    server.on("/fishForwardRight", handleFishForwardRight);
    server.on("/fishBackwardLeft", handleFishBackwardLeft);
    server.on("/fishBackwardRight", handleFishBackwardRight);
    server.on("/fishStop", handleFishStop);
    server.begin();
}
void runServer(){
    server.handleClient();
}
void handleFishForward(){
    Serial.println("Fish Forward");
    server.send(200, "text/html", "Fish Forward");
    moveMotor(1, 1.0, 'r');
    moveMotor(1, 1.0, 'l');
    delay(50);
}
void handleFishBackward(){
    Serial.println("Fish Backward");
    server.send(200, "text/html", "Fish Backward");
    moveMotor(-1, 1.0, 'r');
    moveMotor(-1, 1.0, 'l');
    delay(50);
}
void handleFishForwardLeft(){
    Serial.println("Fish Forward Left");
    server.send(200, "text/html", "Fish Forward Left");
    moveMotor(1, 1.0, 'r');
    moveMotor(1, 0.5, 'l');
    delay(50);
}
void handleFishForwardRight(){
    Serial.println("Fish Forward Right");
    server.send(200, "text/html", "Fish Forward Right");
    moveMotor(1, 0.5, 'r');
    moveMotor(1, 1.0, 'l');
    delay(50);
}
void handleFishBackwardLeft(){
    Serial.println("Fish Backward Left");
    server.send(200, "text/html", "Fish Backward Left");
    moveMotor(-1, 1.0, 'r');
    moveMotor(-1, 0.5, 'l');
    delay(50);
}
void handleFishBackwardRight(){
    Serial.println("Fish Backward Right");
    server.send(200, "text/html", "Fish Backward Right");
    moveMotor(-1, 0.5, 'r');
    moveMotor(-1, 1.0, 'l');
    delay(50);
}
void handleFishStop(){
    Serial.println("Fish Stop");
    server.send(200, "text/html", "Fish Stop");
    moveMotor(0, 0.0, 'r');
    moveMotor(0, 0.0, 'l');
    delay(50);
}