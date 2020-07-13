


void CMD_from_SerialPort() 
{
  
  if (Serial.available() > 0) 
  {    
    int inByte = Serial.read() - 48 + 10;    
    IR_Transmit(inByte);      
    Serial.println(inByte);
  }
}





void IR_Transmit(int IR_code)
{
/*
    11  IR_POWER       
    12  IR_Vol_UP       
    13  IR_Vol_DOWN     
    14  IR_MUTE         
    15  IR_Input_Select 
    16  IR_Arrow_UP     
    17  IR_Arrow_DOWN   
    18  IR_OK           
    19  IR_BACK           
*/
  switch(IR_code)
      {
        case 11: 
              for(int i=0; i<IR_Repeat;i++) 
                {
                  irsend.sendNEC(IR_POWER, IR_NEC_bits);
                  delay(40);
                }
               break;
        
        case 12: 
              for(int i=0; i<IR_Repeat;i++) 
                {
                  irsend.sendNEC(IR_Vol_UP, IR_NEC_bits);
                  delay(40);
                }
               break;  
        
        case 13: 
              for(int i=0; i<IR_Repeat;i++) 
                {
                  irsend.sendNEC(IR_Vol_DOWN, IR_NEC_bits);
                  delay(40);
                }
               break;
        
        case 14: 
              for(int i=0; i<IR_Repeat;i++) 
                {
                  irsend.sendNEC(IR_MUTE, IR_NEC_bits);
                  delay(40);
                }
               break;  
        
        case 15: 
              for(int i=0; i<IR_Repeat;i++) 
                {
                  irsend.sendNEC(IR_Input_Select, IR_NEC_bits);
                  delay(40);
                }
               break;
        
        case 16: 
              for(int i=0; i<IR_Repeat;i++) 
                {
                  irsend.sendNEC(IR_Arrow_UP, IR_NEC_bits);
                  delay(40);
                }
               break;  
        
        case 17: 
              for(int i=0; i<IR_Repeat;i++) 
                {
                  irsend.sendNEC(IR_Arrow_DOWN, IR_NEC_bits);
                  delay(40);
                }
               break;
        
        case 18: 
              for(int i=0; i<IR_Repeat;i++) 
                {
                  irsend.sendNEC(IR_OK, IR_NEC_bits);
                  delay(40);
                }
               break;        
        
        case 19: 
              for(int i=0; i<IR_Repeat;i++) 
                {
                  irsend.sendNEC(IR_BACK, IR_NEC_bits);
                  delay(40);
                }
               break;                                                                             
      }
}
