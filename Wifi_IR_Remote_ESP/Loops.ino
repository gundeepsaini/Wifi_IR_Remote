

void Always_loop()
{
  OTA_Check();
}


void Fast_Loop()
{ 
  server.handleClient(); 
  MQTT_loop();
  Alexa_Handle();
  IR_Receiver_Handle();
}


void Slow_Loop()
{  
  MQTT_publish();
}



void Mid1_Loop()
{  


}


void Mid2_Loop()
{
  
}



void VerySlow_Loop()
{
  
}

