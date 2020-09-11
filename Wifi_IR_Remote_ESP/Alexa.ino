

WebSocketsClient webSocket;

uint64_t heartbeatTimestamp = 0;
bool isConnected = false;


void Alexa_Config()
{
  webSocket.begin("iot.sinric.com", 80, "/");
  webSocket.onEvent(webSocketEvent);
  webSocket.setAuthorization("apikey", SECRET_Sinric_API_Key);
  webSocket.setReconnectInterval(5000);
}


void Alexa_Handle() 
{
  webSocket.loop();  
  if(isConnected) 
  {
    if((millis()/1000 - heartbeatTimestamp) > 300) 
      {
        heartbeatTimestamp = millis()/1000;
        webSocket.sendTXT("H");          
      }
  }   
}





void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) 
{
  switch(type) 
  {
    case WStype_DISCONNECTED:
        isConnected = false;            
        Serial.printf("Sinric disconnected\n");
        break;

    case WStype_CONNECTED: 
        isConnected = true;
        Serial.printf("Sinric connected\n");                    
        break;

    case WStype_TEXT:
      {
       Serial.printf("Sinric cmd:%s\n", payload);
       
       DynamicJsonDocument json(1024);
       deserializeJson(json, (char*) payload);              

       String deviceId = json ["deviceId"];
       String action = json ["action"];
       
       if(deviceId == SECRET_Sinric_DeviceID7a)
       {
          // alexa, turn on tv ==> {"deviceId":"xx","action":"setPowerState","value":"ON"}
          if(action == "setPowerState") 
          {            
            String value = json ["value"];
            if(value == "ON") 
              {IR_Transmit(11);} 
            else 
              {IR_Transmit(11);}
          } 
          
          // alexa, mute tv ==> {"deviceId":"xxx","action":"SetMute","value":{"mute":true}}
          else if(action == "SetMute") 
          {             
            bool mute = json ["value"]["mute"];
            IR_Transmit(14);
          }

          // alexa, turn the volume down on tv by 20 ==> {"deviceId":"xxx","action":"AdjustVolume","value":{"volume":-20,"volumeDefault":false}}
          // alexa, lower the volume on tv ==> {"deviceId":"xx","action":"AdjustVolume","value":{"volume":-10,"volumeDefault":true}}          
          else if(action == "AdjustVolume") 
          {             
            String vol = json ["value"]["volume"];
            int volume = vol.toInt();  
            
            if(volume > 0)
            {
              IR_Transmit(103);
            }
            else
            {
              IR_Transmit(104);
            }            
          }          
         
          else if(action == "SelectInput") 
          { 
          // alexa, change the input to hdmi ==> {"deviceId":"xx","action":"","value":{"input":"HDMI"}}
          // "SelectInput","value":{"input":"HDMI 1"}}
          // "action":"SelectInput","value":{"input":"XBOX"}}
            String Input_cmd  = json ["value"]["input"];
            
            if(Input_cmd == "HDMI 1")
            {
              IR_Transmit(102);
            }
            if(Input_cmd == "XBOX")
            {
              IR_Transmit(101);
            }
          }

          else if(action == "ChangeChannel") 
          { 
            String value = json ["value"]["channelMetadata"]["name"];          
            //alexa, change channel to 200 on tv ==> {"deviceId":"xx","action":"ChangeChannel","value":{"channel":{},"channelMetadata":{"name":"CH9-200"}}}
            //alexa, change channel to pbs on tv ==> {"deviceId":"xx","action":"ChangeChannel","value":{"channel":{},"channelMetadata":{"name":"pbs"}}}                    
          }
                        
          else if(action == "SkipChannels") 
          { 
          //Alexa, next channel on tv ==>  {"deviceId":"xx","action":"SkipChannels","value":{"channelCount":1}}
          // Alexa may say Sorry, TV is not responding. but command works               
          }

          else if(action == "Previous" || action == "Play") 
          { 
          // alexa, previous on tv ==> {"deviceId":"xx","action":"Previous","value":{}}
          // alexa, resume tv ==> {"deviceId":"xx","action":"Play","value":{}}
          // Alexa, pause tv ==> says I dont know that one...
          // for others check https://developer.amazon.com/docs/device-apis/alexa-playbackcontroller.html
          }
        }

      if(deviceId == SECRET_Sinric_DeviceID7b)
       {
          // alexa, turn on mood light ==> {"deviceId":"xx","action":"setPowerState","value":"ON"}
          if(action == "setPowerState") 
          {            
            String value = json ["value"];
            if(value == "ON") 
              {
                IR_Transmit(51);
                IR_Transmit(53);
              } 
            else 
              {
                IR_Transmit(52);
              }
          }
       }

       break;
      }
    
    case WStype_BIN:
      {
        Serial.printf("Get binary length: %u\n", length);
        break;
      }    
  }
}

