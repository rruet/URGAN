/***************************************/
/*Here is the program to configure your*/
/*****RFDuino into a simple marker******/
/*To configure a new marker just change*/
/*********the id from 51 to 99**********/
/***************************************/


#include <RFduinoGZLL.h>


//DEVICE1..7, whatever, only the id is important
device_t role = DEVICE1;
int id =9; //51 to 99

void setup()
{

  RFduinoGZLL.txPowerLevel = 0;

  // start the GZLL stack
  RFduinoGZLL.begin(role);

  Serial.begin(115200);
}

void loop()
{
  delay(1000);

  // request the state from the Host (send a 0 byte payload)
  RFduinoGZLL.sendToHost(id);
}
