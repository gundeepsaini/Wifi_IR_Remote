

const uint16_t kRecvPin = 14;                 // D5 
const uint16_t kCaptureBufferSize = 1024;
const uint8_t  kTimeout = 15;
const uint16_t kMinUnknownSize = 24;

IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;


void IR_Rx_Config() 
{
  irrecv.setUnknownThreshold(kMinUnknownSize);  // Ignore messages with less than minimum on or off pulses.
  irrecv.enableIRIn();                          // Start the receiver
}


void IR_Receiver_Handle() 
{
  if(irrecv.decode(&results)) 
  {
    Serial.print(resultToHumanReadableBasic(&results));
    yield();                                    // Feed the WDT as the text output can take a while to print.
    Serial.println();
  }
}