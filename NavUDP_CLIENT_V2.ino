
//************************************************************
// Written by Nava Tabkum
// 2/17/2019  Version 2.0
// 1. USing ESP8266 to receive GPIO by UDP
// 2. Output to GPIO
// 3. Fail-safe feature within the code!!! 
//
//************************************************************

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <SPI.h>
#include <BlynkSimpleEsp8266.h>

const char *ssid = "CH8";//CH9 red, CH3 green, CH8 orange
const char *pass = "2127271234";
IPAddress ServerIP(10,10,10,10);
IPAddress ClientIP(10,10,10,21);//10.10.10.20:9991 = red, 10.10.10.22:9993 = green, 10.10.10.21:9992 = org
IPAddress NMask(255, 255, 255, 0); 
BlynkTimer TIMER; 
WiFiUDP udp1;
int chan = 8;  // 3, or 9, or 8



char packetBuffer[1];   //address location of 2 bytes for 1 char and null char
//======================================================================
//                Setup
//======================================================================
void setup()
{
    Serial.begin(115200);
    Serial.println();
    pinMode(D4, OUTPUT); //LED on Board
    pinMode(D5, OUTPUT); //D0 GPIO16, D5 GPIO 14
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass, chan);   //Connect to access point
    delay(100);
    WiFi.config(ClientIP,ServerIP,NMask); //ip, dns, mask
    
    Serial.println("");
    Serial.println(WiFi.macAddress());
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
    
    //Start UDP
    Serial.println("Starting UDP");
    udp1.begin(9992); //   9991, 9992, 9993
    
    Serial.print("Local port1: ");
    Serial.println(udp1.localPort());
    
    
    TIMER.setInterval(1000, LED);
}
void LED() { 
  digitalWrite(D4, !digitalRead(D4));  //LED flip-flop
}
//======================================================================
//                MAIN LOOP
//======================================================================
void loop()
{
    
    int cb1 = udp1.parsePacket();
    
    if (cb1) 
    {
      // We've received a UDP packet, send it to serial
      udp1.read(packetBuffer, 1); // read the packet into the buffer, read only one byte
      //Serial.print(packetBuffer);
      delay(1);
      char p = *packetBuffer; // move char from address location packetBuffer into p 
      if (p == '0') {
      
      digitalWrite(D5, 0);} else {
        
      digitalWrite(D5, 1);}          
      
    }
    TIMER.run();
    while (WiFi.status() != WL_CONNECTED ) 
    { 
      
      digitalWrite(D5, 1); // gpio 14
      delay(200);
      LED();
      }   
    
    
}    
   
