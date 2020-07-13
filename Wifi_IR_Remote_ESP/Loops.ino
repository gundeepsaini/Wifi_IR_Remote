

void Always_loop()
{
  OTA_Check();
}


void Fast_Loop()
{ 
  looping();
  server.handleClient(); 
  MQTT_loop();
}


void Slow_Loop()
{  
  

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

