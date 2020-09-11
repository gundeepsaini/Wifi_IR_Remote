


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
    
    // Combination Commands
    101 Switch to Xbox
    102 Switch to HDMI (Fire TV)
    103 Repeat Vol up   x3
    104 Repeat Vol down x3  


    // IR Mood Light Commands
    51 Switch On
    52 Switch Off
    53 Change color to White         
*/

  Serial.print("IR cmd sent:");
  Serial.println(IR_code);

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

        case 51: 
              for(int i=0; i<IR_Repeat;i++) 
                {
                  irsend.sendNEC(IR_Light_ON, IR_NEC_bits);
                  delay(40);
                }
               break;

        case 52: 
              for(int i=0; i<IR_Repeat;i++) 
                {
                  irsend.sendNEC(IR_Light_OFF, IR_NEC_bits);
                  delay(40);
                }
               break;

        case 53: 
              for(int i=0; i<IR_Repeat;i++) 
                {
                  irsend.sendNEC(IR_Light_White, IR_NEC_bits);
                  delay(40);
                }
               break;               
                
        case 101: 
              for(int i=0; i<1;i++) 
                {
                  irsend.sendNEC(IR_Input_Select, IR_NEC_bits);
                  delay(50);
                  irsend.sendNEC(IR_Arrow_DOWN, IR_NEC_bits);
                  delay(50);
                  irsend.sendNEC(IR_OK, IR_NEC_bits);
                  delay(50);
                }
               break;

        case 102: 
              for(int i=0; i<1;i++) 
                {
                  irsend.sendNEC(IR_Input_Select, IR_NEC_bits);
                  delay(50);
                  irsend.sendNEC(IR_Arrow_UP, IR_NEC_bits);
                  delay(50);
                  irsend.sendNEC(IR_OK, IR_NEC_bits);
                  delay(50);
                }
               break;

        case 103: 
              for(int i=0; i<3;i++) 
                {
                  irsend.sendNEC(IR_Vol_UP, IR_NEC_bits);
                  delay(50);
                }
               break;

        case 104: 
              for(int i=0; i<3;i++) 
                {
                  irsend.sendNEC(IR_Vol_DOWN, IR_NEC_bits);
                  delay(50);
                }
               break;                                                                                                                         
      }
}
