
/*

    Arduino IR Remote

  Configured for HKC 42" TV
  
  Date              : 12.07.2020

  Device            : Atmega328 / ESP8266
  IR Reciever       : Pin 11 (can be any)
  IR Transmitter    : Pin 3 (fixed by lib for Atmega328) / D2 for ESP8266


  TV Code Decoded using :
      Protocol      : NEC
      vol up        : 4FBE01F
      vol down      : 4FBD02F
      POWER         : 4FB40BF
      input select  : 4FBF807
      Arrow up      : 4FB06F9
      Arrow down    : 4FB8679
      OK            : 4FB16E9
      BACK          : 4FB1AE5
      MUTE          : 4FB807F

------------------------------------------- */


/* ------------- LIB ------------------------------ */
#include "Secrets.h"
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
// With ESP8266
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>


/* ------------- CONFIG VAR ------------------------------ */
unsigned long looptime_Fast = 0;    // in secs
unsigned long looptime_Mid1 = 1;    // in secs
unsigned long looptime_Mid2 = 10;   // in secs
unsigned long looptime_Slow       = 1 * (60);      // in mins
unsigned long looptime_VerySlow   = 5 * (60);      // in mins

const uint16_t IR_Tx = 4;  // ESP8266 GPIO pin 4 (D2)

#define IR_Protocol     'NEC'
#define IR_NEC_bits     32
#define IR_Repeat       1
#define IR_POWER        0x4FB40BF
#define IR_Vol_UP       0x4FBE01F
#define IR_Vol_DOWN     0x4FBD02F
#define IR_MUTE         0x4FB807F
#define IR_Input_Select 0x4FBF807
#define IR_Arrow_UP     0x4FB06F9
#define IR_Arrow_DOWN   0x4FB8679
#define IR_OK           0x4FB16E9
#define IR_BACK         0x4FB1AE5  


/* ------------- VAR ------------------------------ */
const char* ssid             = SECRET_WIFI_SSID2;
const char* pass             = SECRET_WIFI_PASS2;
const char* DeviceHostName   = SECRET_Device_Name7;
const char* OTA_Password     = SECRET_Device_OTA_PASS; 
unsigned long lastrun_fast, lastrun_Mid1;
unsigned long lastrun_Mid2, lastrun_slow, lastrun_Veryslow;
unsigned long lastrun_30mins,lastrun_OTA;
bool OTA_Mode=0;
String webpage1="";


ESP8266WebServer server(80);
IRsend irsend(IR_Tx);     


void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.begin(115200);
  Serial.println(DeviceHostName);

  wifi_station_set_hostname(DeviceHostName);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) 
  {
    Serial.println("Wifi Error! Rebooting in 30s...");
    delay(30 *1000);
    digitalWrite(LED_BUILTIN, HIGH);
    Restart_ESP();
  }
  
  Serial.print("Connected to ");
  Serial.print(WiFi.SSID());
  Serial.print(", IP Address: ");
  Serial.println(WiFi.localIP());
  
  irsend.begin();
  OTA_Config();
  WebServer_Config();
  //MQTT_Config();
  
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Ready");
}



void loop() 
{
  // Always
  Always_loop();

  // Fast Loop
 if(!OTA_Mode && ((millis()/1000 - lastrun_fast > looptime_Fast) || lastrun_fast ==0))
  {
    lastrun_fast = millis()/1000;
    Fast_Loop();
  }

/*
  // Mid1 Loop
 if(!OTA_Mode && ((millis()/1000 - lastrun_Mid1 > looptime_Mid1) || lastrun_Mid1 ==0))
  {
    lastrun_Mid1 = millis()/1000;
    Mid1_Loop();
  }


  // Mid2 Loop
 if(!OTA_Mode && ((millis()/1000 - lastrun_Mid2 > looptime_Mid2) || lastrun_Mid2 ==0))
  {
    lastrun_Mid2 = millis()/1000;
    Mid2_Loop();
  }
*/
  // Slow Loop
 if(!OTA_Mode && ((millis()/1000 - lastrun_slow > looptime_Slow) || lastrun_slow ==0))
  {
    lastrun_slow = millis()/1000;
    Slow_Loop();
  }

/*

    // Very Slow Loop
 if(!OTA_Mode && ((millis()/1000 - lastrun_Veryslow > looptime_VerySlow) || lastrun_Veryslow ==0))
  {
    lastrun_Veryslow = millis()/1000;
    VerySlow_Loop();
  }

*/
}



void Restart_ESP()
{
  Serial.println("Restarting ESP");
  ESP.restart();
  delay(1000);
  while(1);
}


