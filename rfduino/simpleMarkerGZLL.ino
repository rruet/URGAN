/***************************************/
/*Here is the program to configure your*/
/*****RFDuino into a simple marker******/
/*To configure a new marker just change*/
/*********the id from 51 to 99**********/
/***************************************/


#include <RFduinoGZLL.h>


//DEVICE1..7, whatever, only the id is important
device_t role = DEVICE1;
int id =9; //must be between 0 and MAX_DEVICES defined in the badge code

void setup()
{

  RFduinoGZLL.txPowerLevel = 0;

  // start the GZLL stack as a device (marker)
  RFduinoGZLL.begin(role);

  Serial.begin(115200);
}

void loop()
{
  delay(1000);

  // request the state from the badge all seconds by sending its id
  RFduinoGZLL.sendToHost(id);
}
