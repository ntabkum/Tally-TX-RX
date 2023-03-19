
//************************************************************
// Written by Nava Tabkum
// 2/18/2019 Version 3.0
// 1. USing ESP8266 to send GPIO by UDP
// 2. Client is setup to output to GPIO 
//
//
//************************************************************

#include <ESP8266WiFi.h>
//#include <WiFi.h>  //esp32
#include <WiFiUdp.h>
#include <SimpleTimer.h>
 
const char *ssid = "CH3";
const char *pass = "2127271234";
int ch = 3; 
const char *ON = "1";
const char *OFF = "0";
int MAX = 4;
bool hidden = false; //
bool FF;
int X1,X2,X3;
unsigned int localPort = 9999; // local port to listen for UDP packets
int A,B,C,D,E,F;
IPAddress ServerIP(10,10,10,10);
IPAddress ClientIP1(10,10,10,20);
IPAddress ClientIP2(10,10,10,21);
IPAddress ClientIP3(10,10,10,22);

IPAddress NMask(255, 255, 255, 0);
 
// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;
SimpleTimer timer, timer1; 
char packetBuffer[1];   //Where we get the UDP data
//=======================================================================
//                Setup
//=======================================================================
void setup()
{
    Serial.begin(115200);
    Serial.println();
    pinMode(5, INPUT_PULLUP);//D1
    pinMode(4, OUTPUT);//D2
    
    pinMode(2, OUTPUT);
    
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, pass, ch, hidden, MAX); //WiFi.softAP(ssid, password, channel, hidden, max_connection)
    delay(100);
    WiFi.softAPConfig(ServerIP,ServerIP,NMask); 
    
    //Start UDP
    Serial.println("Starting UDP");
    udp.begin(localPort);
    
    timer1.setInterval(250, LED);
}
void LED() {
    
    digitalWrite(2, !digitalRead(2));  //LED flip-flop
    
}

//======================================================================
//                MAIN LOOP
//======================================================================
void loop()
{
    X1 = digitalRead(5);
    digitalWrite(4, X1); //turn off LED at gpio 4 when 
    
    delay(5); 
    
    udp.beginPacket(ClientIP3, 9993);
    //udp.write(ON);
    udp.print(X1);
    udp.endPacket();

}
   
     
    
    
