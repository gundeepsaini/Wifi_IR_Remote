

/******************** LIB **************************************/
#define MQTT_MAX_PACKET_SIZE 1024  // < ----- Change in lib: This is because the defaul maxium length is 128b. So just go to PubSubClient.h and change #define MQTT_MAX_PACKET_SIZE 128 to #define MQTT_MAX_PACKET_SIZE 1024
#include <PubSubClient.h>
#include <ArduinoJson.h>


/********************* Var *************************************/
WiFiClient espClient;
PubSubClient client(espClient);

long lastReconnectAttempt = 0;

/******************** Config **************************************/
const char* mqtt_server     = SECRET_MQTT_Server;
const char* mqtt_user       = SECRET_MQTT_User;
const char* mqtt_password   = SECRET_MQTT_Pass;

// Motion Sensor
//#define MQTT_CONFIG_PIR        "homeassistant/sensor/PIR/Kitchen/config"
#define MQTT_TOPIC_STATE_IR_Remote  "homeassistant/device/Wifi_IR_Remote/state"
#define MQTT_TOPIC_CMD_IR_Remote    "homeassistant/device/Wifi_IR_Remote/cmd"


unsigned long MQTT_heartbeat_timestamp = 0;

/**************** External Functions ************************************/

void MQTT_Config()
{
  client.setServer(mqtt_server, SECRET_MQTT_Port);
  client.setCallback(MQTT_MessageRecd_callback);  
}


void MQTT_loop()
{
  if (!client.connected())
      MQTT_reconnect();              
  
  client.loop();
}


void MQTT_publish()
{   
    MQTT_heartbeat();
}


/**************** Internal Functions ************************************/

void MQTT_reconnect() 
{
  if (millis()/1000 - lastReconnectAttempt > 30 || lastReconnectAttempt == 0) 
  {
      Serial.println("MQTT reconnecting");
      if (client.connect(DeviceHostName, mqtt_user, mqtt_password)) 
      {
        //MQTT_publish_config();  
        Serial.println("MQTT connected");
        client.subscribe(MQTT_TOPIC_CMD_IR_Remote);
      }
      lastReconnectAttempt = millis()/1000;
  }

}


void MQTT_MessageRecd_callback(char* p_topic, byte* p_payload, unsigned int p_length) 
{
  String payload;
  for (uint8_t i = 0; i < p_length; i++) 
    { payload.concat((char)p_payload[i]); }

  if (String(MQTT_TOPIC_CMD_IR_Remote).equals(p_topic)) 
  {
    int IR_code = payload.toInt();
    Serial.print("MQTT CMD :");
    Serial.println(IR_code);
    IR_Transmit(IR_code);         
  } 

}


void MQTT_heartbeat()
{
  if(millis()/1000 - MQTT_heartbeat_timestamp > 300 || MQTT_heartbeat_timestamp==0)
  {
    MQTT_heartbeat_timestamp = millis()/1000;
    client.publish(MQTT_TOPIC_STATE_IR_Remote, "1", true);
  }
}
